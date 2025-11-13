Temperature Controlled Fan using Arduino
----------------------------------------

This file contains the complete Arduino code and explanation for the
Temperature-Controlled Fan embedded system project.

The system reads temperature using a DHT11/DHT22 (digital) or LM35 (analog) sensor.
The fan automatically turns ON when the temperature crosses a threshold and the
fan speed increases proportionally using PWM. Hysteresis is added to avoid rapid
ON/OFF switching. Non-blocking code using millis() is used for smooth operation.

Below is the complete Arduino code used in Temperature_Controlled_Fan.ino:


/********************************************************************************
 * Temperature_Controlled_Fan.ino
 *
 * Real-life embedded example: automatic fan control based on temperature.
 * Supports DHT sensors (DHT11/DHT22) or LM35 analog temperature sensor.
 *
 * Author :Aayush Tank
 ********************************************************************************/

/* -------------------- Configuration -------------------- */
#define USE_DHT true

#if USE_DHT
  #include <DHT.h>
  #define DHT_PIN 2
  #define DHT_TYPE DHT22
  DHT dht(DHT_PIN, DHT_TYPE);
#else
  #define LM35_PIN A0
#endif

const uint8_t FAN_PWM_PIN = 9;

float tempThreshold = 30.0;
const float hysteresis = 1.5;
const float controlSpan = 10.0;

const unsigned long SENSOR_READ_INTERVAL = 2000UL;
const unsigned long SERIAL_POLL_INTERVAL = 200UL;

/* -------------------- Internal State -------------------- */
unsigned long lastSensorMillis = 0;
unsigned long lastSerialMillis = 0;
float currentTemp = NAN;
bool fanEnabled = false;
unsigned long startMillis = 0;

/* Function Prototypes */
void initHardware();
void readSensorNonBlocking();
float readTemperature();
void updateFanControl(float temperature);
void applyFanPWM(uint8_t pwmValue);
void handleSerialCommandsNonBlocking();
void printStatus();
void printHelp();

/* -------------------- Setup -------------------- */
void setup() {
  startMillis = millis();
  Serial.begin(9600);

  initHardware();

  Serial.println("=== Temperature Controlled Fan System ===");
  Serial.print("Initial threshold: ");
  Serial.println(tempThreshold);
  printHelp();
}

/* -------------------- Main Loop -------------------- */
void loop() {
  unsigned long now = millis();

  if (now - lastSensorMillis >= SENSOR_READ_INTERVAL) {
    lastSensorMillis = now;
    readSensorNonBlocking();
    if (!isnan(currentTemp)) {
      updateFanControl(currentTemp);
      printStatus();
    }
  }

  if (now - lastSerialMillis >= SERIAL_POLL_INTERVAL) {
    lastSerialMillis = now;
    handleSerialCommandsNonBlocking();
  }
}

/* -------------------- Functions -------------------- */
void initHardware() {
  pinMode(FAN_PWM_PIN, OUTPUT);
  applyFanPWM(0);

#if USE_DHT
  dht.begin();
#endif
}

void readSensorNonBlocking() {
  float t = readTemperature();
  if (!isnan(t)) {
    currentTemp = t;
  }
}

float readTemperature() {
#if USE_DHT
  float t = dht.readTemperature();
  if (isnan(t)) {
    delay(50);
    t = dht.readTemperature();
  }
  return t;
#else
  int raw = analogRead(LM35_PIN);
  float voltage = raw * (5.0 / 1023.0);
  float tempC = voltage * 100.0;
  return tempC;
#endif
}

void updateFanControl(float temperature) {
  static bool lastFanOn = false;

  if (!fanEnabled) {
    if (temperature >= tempThreshold) fanEnabled = true;
  } else {
    if (temperature <= (tempThreshold - hysteresis)) fanEnabled = false;
  }

  if (!fanEnabled) {
    applyFanPWM(0);
  } else {
    float over = temperature - tempThreshold;
    float ratio = over / controlSpan;
    if (ratio < 0) ratio = 0;
    if (ratio > 1.0) ratio = 1.0;

    uint8_t pwm = (uint8_t)(ratio * 255.0);
    if (pwm > 0 && pwm < 60) pwm = 60;
    applyFanPWM(pwm);
  }

  if (fanEnabled != lastFanOn) {
    Serial.print("[STATE] Fan ");
    Serial.println(fanEnabled ? "ON" : "OFF");
    lastFanOn = fanEnabled;
  }
}

void applyFanPWM(uint8_t pwmValue) {
  analogWrite(FAN_PWM_PIN, pwmValue);
}

void handleSerialCommandsNonBlocking() {
  if (Serial.available() == 0) return;
  String line = Serial.readStringUntil('\n');
  line.trim();
  if (line.length() == 0) return;

  char cmd = line.charAt(0);

  switch (cmd) {
    case 'h':
      printHelp();
      break;
    case 'p':
      printStatus();
      break;
    case 't':
      Serial.print("Current threshold: ");
      Serial.println(tempThreshold);
      break;
    case 's': {
      String val = line.substring(1);
      float newVal = val.toFloat();
      if (newVal != 0 || val == "0") {
        tempThreshold = newVal;
        Serial.print("Threshold updated to: ");
        Serial.println(tempThreshold);
      } else {
        Serial.println("Invalid number");
      }
      break;
    }
    default:
      Serial.println("Unknown command");
      break;
  }
}

void printStatus() {
  Serial.print("[STATUS] Temp: ");
  Serial.print(currentTemp);
  Serial.print(" °C | Threshold: ");
  Serial.print(tempThreshold);
  Serial.print(" °C | Fan: ");
  Serial.println(fanEnabled ? "ON" : "OFF");
}

void printHelp() {
  Serial.println("Commands:");
  Serial.println("p -> Print status");
  Serial.println("t -> Print threshold");
  Serial.println("s<value> -> Set threshold");
  Serial.println("h -> Help");
}
