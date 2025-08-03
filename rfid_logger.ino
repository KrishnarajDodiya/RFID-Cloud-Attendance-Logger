#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5
#define RST_PIN 2
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//replace with your pasword and ssid
const char* ssid = "HDD_2.4G";
const char* password = "Benq@123";

// Replace with your URL
const char* googleScriptURL = "https://script.google.com/macros/s/AKfycbyUfAy_ha9MlHCXyy6VtyLOHmuI4tHHFU42ZYLyLnkavJpgRnzNPA0X4Nd_XYomOb1g/exec";

typedef struct {
  const char* uid;
  const char* name;
} validUID;
validUID users[] = {
  {"CA1FE916", "User 1"},
  {"9A9BB11A", "User 2"}
};
int listSize = sizeof(users) / sizeof(users[0]);

void defaultlcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome!!");
  lcd.setCursor(0, 1);
  lcd.print("Scan Card");
}

void sendToGoogleSheets(String uid, String name) {
  HTTPClient http;
  String url = String(googleScriptURL) + "?uid=" + uid + "&name=" + name;

  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Sent to Sheets: " + payload);
  } else {
    Serial.println("Error sending to Sheets.");
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  defaultlcd();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  lcd.clear();
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);
  defaultlcd();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String rfidUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) rfidUID += "0";
    rfidUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  rfidUID.toUpperCase();

  Serial.print("Scanned UID: ");
  Serial.println(rfidUID);

  const char* name = "";
  for (int i = 0; i < listSize; i++) {
    String uidStr = String(users[i].uid);
    uidStr.toUpperCase();
    if (uidStr == rfidUID) {
      name = users[i].name;
      break;
    }
  }

  lcd.clear();
  if (strlen(name) > 0) {
    Serial.print("UID found. Name: ");
    Serial.println(name);
    lcd.setCursor(0, 0); lcd.print("Hello");
    lcd.setCursor(0, 1); lcd.print(name);
    sendToGoogleSheets(rfidUID, name);
  } else {
    Serial.println("UID not found.");
    lcd.setCursor(0, 0); lcd.print("Unknown Card");
    lcd.setCursor(0, 1); lcd.print("Try Again");
    sendToGoogleSheets(rfidUID, "Unknown");
  }

  delay(2000);
  defaultlcd();
}