/*
  IoT Club - ISTC Workshop
  Controlling LED Brightness with ESP32 and LDR

  This code demonstrates how to control the brightness of an LED
  based on the readings from an LDR sensor using PWM.
*/

const int ledPin = 2;   // Change this to the actual pin connected to the LED
const int ldrPin = 36;  // Change this to the actual pin connected to the LDR

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the analog value from the LDR sensor
  int ldrValue = analogRead(ldrPin);

  // Map the LDR value to a PWM range (0-255)
  int brightness = map(ldrValue, 0, 4095, 0, 255); 

  // Set the LED brightness using PWM
  analogWrite(ledPin, brightness);
}