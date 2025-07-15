#include "DHT.h"

// DHT11 Sensor an digitalem Pin D2
#define DHTPIN 2
#define DHTTYPE DHT22  // Oder DHT22, je nach Sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT Sensor wird gestartet...");
  dht.begin();
}

void loop() {
  delay(2000);  // DHT11 misst etwa alle 2 Sekunden zuverlässig

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Fehlerbehandlung
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Fehler beim Auslesen des Sensors!");
    Serial.println(humidity);
    Serial.println(temperature);
    return;
  }

  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Temperatur: ");
  Serial.print(temperature);
  Serial.println(" °C");
}
