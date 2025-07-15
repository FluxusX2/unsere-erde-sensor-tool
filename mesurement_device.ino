#include "Grove_Temperature_And_Humidity_Sensor.h"

#include <Wire.h>
#include "rgb_lcd.h"

#define DHTPIN 2        // D3
#define DHTTYPE DHT11   // Oder DHT22, je nach Sensor

const int soilPin = A0; // soilPin
const int airPin = A1;

int soilValue = 0; // Initalwert
int airValue = 0;

rgb_lcd lcd; 
DHT dht(DHTPIN, DHTTYPE);

//TODO: TempAndHumid Fixen

void setup() {
  Serial.begin(9600);
  screenSetup();
  tempAndHumidSetup();
}

void loop() {
  //airQualityLoop();
  //soilLoop();
  tempAndHumidLoop();
  //screenLoop();
  delay(5000);
}

void screenSetup() {
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);
}

void tempAndHumidSetup() {
  Wire.begin();
  dht.begin();
}

void screenLoop() {
  lcd.setCursor(0, 0);    // Erste Zeile
  lcd.print("Luftqual:");
  lcd.print(airValue);
  lcd.print("   ");       // Leerzeichen, um alte Zeichen zu löschen

  lcd.setCursor(0, 1);    // Zweite Zeile
  lcd.print("Bodenf:");
  lcd.print(soilValue);
  lcd.print("    ");      // Leerzeichen
}

void soilLoop() {
  soilValue = analogRead(soilPin);
  Serial.print("Bodenfeuchtigkeit: ");
  Serial.println(soilValue);  // Je trockener, desto höher der Wert (z. B. 800–1023 trocken, 300–500 feucht)
}

void tempAndHumidLoop() {

  float temp_hum_val[2] = {0};
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  if (!dht.readTempAndHumidity(temp_hum_val)) {
    Serial.print("Humidity: ");
    Serial.print(temp_hum_val[0]);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp_hum_val[1]);
    Serial.println(" *C");
  } else {
    Serial.println("Failed to get temprature and humidity value.");
  }
}


void airQualityLoop() {
  airValue = analogRead(airPin);
  Serial.print("Luftqualitätswert (analog): ");
  Serial.println(airValue);  // Je höher, desto schlechter meist
}
