# RFID to Google Sheets Attendance Logger

This project uses an **ESP32**, **RFID module (MFRC522)**, and **Google Apps Script** to log RFID card scans to Google Sheets in real time. It also uses an I2C LCD to show scan status.

## Components Used
- ESP32
- MFRC522 RFID Reader
- I2C 16x2 LCD (0x3F)
- Wi-Fi Network
- Google Apps Script Web App
- Arduino IDE

## How It Works
1. ESP32 connects to WiFi.
2. When an RFID card is scanned:
   - UID is matched against the valid list.
   - If valid, user name is shown on LCD and sent to Google Sheets.
   - If not, "Unknown" is logged.
3. Data is sent using a Google Apps Script deployed as a web app.

## Code
Main code is in `rfid_logger.ino`.
Gogle Apps Scripts is in `google_apps_scripts.ino`.

## Configuration
### Configuration in esp32's code(rfid_logger.ino
- Set your WiFi credentials in `ssid` and `password`.(i.e. replace your wifi credentials)
- Replace the `googleScriptURL` with your own Google Apps Script Web App URL.
- Update the `users[]` array with your card UIDs and names.
### Configuration for Google sheets
- Open Google Sheets
- Create a new spreadsheet
- Rename the sheet tab to Sheet1 (or keep the default if using that in the script)
- Rename the spreadsheet if desired
- Click Extensions > Apps Script
- Replace the default code with your Google Apps Script code(`google_apps_scripts.ino`).
- Click Deploy > Manage deployments > New deployment
- Select “Web app”
- Under Execute as: Select Me
- Under Who has access: Select Anyone
- Click Deploy
- Copy the generated web app URL and copy the Sheets ID as well
- Now replace the url in the `rfid_logger.ino` code
- It will look something like this (const char* googleScriptURL = "https://script.google.com/macros/s/AKfycbw12345.../exec";)
- Now replace the Ssheets ID in the `google_apps_scripts.ino` code


## Circuit Diagram
*(You can add photos or circuit diagrams here later)*

## License
Open Source under the MIT License.
