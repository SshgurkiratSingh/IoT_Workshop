/*
  IoT Club - ISTC Workshop
  Reading DHT22 Sensor Data with ESP32

  This code demonstrates how to read temperature and humidity 
  data from a DHT22 sensor and print the values to the serial monitor.
*/

// Include the DHT sensor library
#include <DHT.h>

// Constants for DHT pin and sensor type
const int dhtPin = 17; // Change this to the actual pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302)

// Initialize DHT sensor object
DHT dht(dhtPin, DHTTYPE);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the temperature and humidity values
  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.println("°C");

  delay(2000); // Delay between readings
}