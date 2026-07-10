#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

#define SOIL_PIN 34
#define LED_PIN 23
#define BUZZER_PIN 19

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  dht.begin();
}

void loop() {

  // Read Sensors
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  int soilValue = analogRead(SOIL_PIN);
  int soilPercent = map(soilValue, 0, 4095, 0, 100);

  String status;

  if (soilPercent < 30) {
    status = "DRY";
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else if (soilPercent < 70) {
    status = "MOIST";
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  else {
    status = "WET";
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" C  ");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%  ");

  Serial.print("Soil: ");
  Serial.print(soilPercent);
  Serial.print("%  ");

  Serial.println(status);

  // LCD Display
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(soilPercent);
  lcd.print("% ");

  lcd.print(status);

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temp, 0);
  lcd.print(" H:");
  lcd.print(hum, 0);

  delay(1000);
}
