//APLIKASI SENSOR CAPACITIVE SOIL MOISTURE SKU:SEN0193 DALAM RANCANG BANGUN OTOMASI KELEMBABAN TANAH PADA TANAMAN ANGGREK MENGGUNAKAN NODEMCU ESP32 BERBASIS IOT
//UNIVERSITAS SRIWIJAYA
//ALYA PUTRI YOANDA
#define BLYNK_TEMPLATE_ID "TMPL64_mwFkSz"
#define BLYNK_TEMPLATE_NAME "Smart Garden"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define RELAY_POMPA3 15
//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); //LCD
bool displaylastReading = false;

char ssid[] = "@net-unsri-new";
char pass[] = "";
char auth[] = "lPa47jjERtQy1gBYb8ynJh1iubypsJfw";

void setup() {
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);

  //RELAY
  pinMode(RELAY_POMPA3, OUTPUT);
  sensors.begin();

  digitalWrite(RELAY_POMPA3, LOW);
  //lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 3);
  lcd.print("soil: ");
}

void loop() {
  Blynk.run();
//Alya
   // Baca nilai pada pin analog 35:
    int sensorValue = analogRead(35);

    // Konversi nilai analog ke kelembaban tanah dalam bentuk persen:
    float soilMoisture = (100 - ((sensorValue/ 4096.00) * 100));

    // Print nilai kelembaban tanah dalam bentuk persen:
    Serial.print("Nilai Analog: ");
    Serial.print(sensorValue);
    Blynk.virtualWrite(V8,sensorValue);
    Serial.print(" | Kelembaban Tanah: ");
    Serial.print(soilMoisture);
    Serial.println("%");
      Blynk.virtualWrite(V3,soilMoisture);
    // MENGAKTIFKAN RELAY
if (soilMoisture < 60) {
    digitalWrite(RELAY_POMPA3, LOW); // Turn relay 3 on
  Serial.println("POMPA ON");
    Blynk.logEvent("anggrek_disiram");
    delay(2000);
    digitalWrite(RELAY_POMPA3, HIGH);

  }
  else if (soilMoisture > 80) {
    digitalWrite(RELAY_POMPA3, HIGH);  // Turn relay 3 off
      Serial.println("POMPA OFF");
  }

  if (!displaylastReading) {
    lcd.clear();
     lcd.setCursor(0, 3);
    lcd.print("soil: ");
    lcd.print(soilMoisture);
    lcd.print("%");
    
    delay(5000);
 displaylastReading = true;

  } else 
}
