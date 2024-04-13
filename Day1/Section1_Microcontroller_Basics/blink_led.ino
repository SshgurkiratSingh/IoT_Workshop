/*
  IoT Club - ISTC Workshop
  Blinking an LED with ESP32

  This code demonstrates the basic functionality of blinking 
  an LED connected to the ESP32 board using the Arduino IDE.
*/

// Constants for LED pin and blink interval
const int ledPin = 22; // Change this to the actual pin connected to the LED
const int blinkInterval = 500; // Blink interval in milliseconds (500ms = 0.5 seconds)

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  delay(blinkInterval);

  // Turn the LED off
  digitalWrite(ledPin, LOW);
  delay(blinkInterval);
}