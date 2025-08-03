# RFID to Google Sheets Attendance Logger

This project uses an **ESP32**, **RFID module (MFRC522)**, and **Google Apps Script** to log RFID card scans to Google Sheets in real time. It also uses an I2C LCD to show scan status.

## 📦 Components Used
- ESP32
- MFRC522 RFID Reader
- I2C 16x2 LCD (0x3F)
- Wi-Fi Network
- Google Apps Script Web App
- Arduino IDE

## 🔧 How It Works
1. ESP32 connects to WiFi.
2. When an RFID card is scanned:
   - UID is matched against the valid list.
   - If valid, user name is shown on LCD and sent to Google Sheets.
   - If not, "Unknown" is logged.
3. Data is sent using a Google Apps Script deployed as a web app.

## 🧾 Code
Main code is in `rfid_logger.ino`.

## 🔐 Configuration
- Set your WiFi credentials in `ssid` and `password`.
- Replace the `googleScriptURL` with your own Google Apps Script Web App URL.
- Update the `users[]` array with your card UIDs and names.

## 📝 To Do
- Add date and time logging
- Use EEPROM or SD card for local backup
- Add a better web dashboard

## 📸 Screenshots
*(You can add photos or circuit diagrams here later)*

## 📄 License
Open Source under the MIT License.
