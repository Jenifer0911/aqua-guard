#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

#define SOIL_PIN 34
#define RELAY_PIN 27

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(SOIL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);  // Motor OFF

  delay(2000);
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int soilValue = analogRead(SOIL_PIN);

  int moisture = map(soilValue, 4000, 1400, 0, 100);
  moisture = constrain(moisture, 0, 100);

  Serial.println("--------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Soil Value: ");
  Serial.println(soilValue);

  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  if (moisture < 40) {

    digitalWrite(RELAY_PIN, LOW);

    Serial.println("SOIL DRY -> RELAY ON -> MOTOR ON");

  } else {

    digitalWrite(RELAY_PIN, HIGH);

    Serial.println("SOIL WET -> RELAY OFF -> MOTOR OFF");
  }

  Serial.println("--------------------");

  delay(2000);
}