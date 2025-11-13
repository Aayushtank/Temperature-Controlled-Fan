# Temperature Controlled Fan using Arduino

## A. Project Overview
This project is a real-life embedded automation system where a DC fan is automatically controlled based on temperature. The system uses either a DHT11/DHT22 sensor or an LM35 analog sensor. When the temperature crosses a set threshold, the fan automatically switches ON and increases speed using PWM. When the temperature reduces, the fan slows down or turns OFF.

The purpose of the project is to demonstrate:
- Sensor reading (digital or analog)
- PWM-based motor/fan control
- Non-blocking code using millis()
- Real-life automation logic
- Basic embedded system QA using GitHub Issues

---

## B. Hardware Components
1. Arduino UNO / Nano / Mega  
2. Temperature Sensor (Choose one):  
   - DHT11 / DHT22 (Digital)  
   - LM35 (Analog)  
3. DC Fan (5V or 12V)  
4. N-channel MOSFET or Motor Driver  
5. External Power Supply for Fan  
6. Jumper Wires  
7. Breadboard  

---

## C. Circuit Description

### If using DHT11/DHT22:
- VCC → 5V  
- GND → GND  
- Signal → Digital Pin 2  

### If using LM35:
- VCC → 5V  
- GND → GND  
- Output → A0  

### Fan Driver Connection:
- Arduino Pin 9 (PWM) → MOSFET Gate  
- MOSFET Drain → Fan Negative  
- Fan Positive → External Power Supply  
- Power Supply GND → Arduino GND  

(Note: Do NOT connect a fan directly to Arduino pins.)

---

## D. Features Implemented
1. Automatic fan control based on temperature  
2. PWM-based fan speed control  
3. Non-blocking timing using millis()  
4. Hysteresis to prevent rapid fan ON/OFF switching  
5. Support for both DHT and LM35 sensors  
6. Serial command menu for debugging and threshold control  

Example Serial Commands:
- `p` → Print status  
- `t` → Show temperature threshold  
- `s30` → Set threshold to 30°C  
- `h` → Help  

---

## E. File Description
1. **Temperature_Controlled_Fan.ino**  
   Contains the full Arduino implementation of the temperature-controlled fan system.

2. **code.txt**  
   Contains code summary and explanation.

3. **README.md**  
   Documentation for the project, including circuit, features, usage, and learning outcomes.

---

## F. How to Run the Project
1. Connect the components as per the wiring section.  
2. Open Arduino IDE → Load `Temperature_Controlled_Fan.ino`.  
3. Select Arduino board and COM port.  
4. Upload the code.  
5. Open Serial Monitor at **9600 baud**.  
6. Observe readings and fan behavior.  

---

## G. QA Issues Logged (for GitHub)
Examples of issues that can be created in the repository:
1. Sensor reading inconsistency at high temperature  
2. Fan not starting at low PWM values  
3. Improve documentation for wiring  
4. Add option to save threshold to EEPROM  
5. Add OLED display for temperature output  

These can be added to GitHub Issues section for QA tracking.

---

## H. Collaboration Summary
- Issues were created for bugs, documentation, and enhancements.  
- Code changes were pushed using commits and branches.  
- Pull requests were reviewed and merged.  
- Team members collaborated through issue comments and code feedback.  

---

## I. Learning Outcomes
- Learned interfacing temperature sensors with Arduino  
- Understood PWM-based motor/fan control  
- Practiced non-blocking embedded programming  
- Improved documentation and version control skills  
- Applied real-life automation logic  
- Used GitHub for QA, issue tracking, and collaboration  

---

## J. Author
Aayush Tank 
Div B (2025-26)
Btech 
