/*
  IoT Club - ISTC Workshop
  Reading LDR Sensor Data with ESP32

  This code demonstrates how to read data from an LDR sensor
  connected to the ESP32 and print the values to the serial monitor.
*/

// Constant for the analog pin connected to the LDR sensor
const int ldrPin = 36; // Change this to the actual pin connected to the LDR

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
}

void loop() {
  // Read the analog value from the LDR sensor
  int ldrValue = analogRead(ldrPin);

  // Print the LDR value to the serial monitor
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  delay(250); // Delay for stability and readability
}