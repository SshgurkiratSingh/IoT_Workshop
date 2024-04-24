/*
  IoT Club - ISTC Workshop
  Controlling LED with MQTT

  This code demonstrates how to control the state of an LED connected 
  to the ESP32 based on messages received from a specific MQTT topic.
*/

#include <WiFi.h>
#include <PubSubClient.h>

// Update these with your Wi-Fi credentials
const char* ssid = "Node";
const char* password = "12345678";

// MQTT Broker settings
const char* mqtt_server = "192.168.1.100";
const int mqtt_port = 1883;

#define NumberOfTopics 4
String topic[NumberOfTopics]={"esp32/led","esp32/led2","esp32/led/brightness","esp32/led2/brightness"};
int values[NumberOfTopics]={0,0,0,0};
#define FIRST_VALUE values[0]
#define SECOND_VALUE values[1]
#define THIRD_VALUE values[2]
#define FOURTH_VALUE values[3]

// MQTT Topics

WiFiClient espClient;
PubSubClient client(espClient);
/**
 * Function to establish connection to MQTT server.
 *
 * @return void
 *
 * @throws None
 */
void connectToMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT Broker!");
      for (int i = 0; i < NumberOfTopics; i++) {
        client.subscribe(topic[i].c_str());
      }

    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

// Callback function for received MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  for (int i = 0; i < NumberOfTopics; i++) {
    if (String(topic) == topic[i]) {
      values[i] = message.toInt();
    }
  } 
}

void DoSomethingWithThoseValues() {
  // Do something with the values
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  connectToMQTT();
  
}

/**
 * Function to continuously check the connection status, 
 * and reconnect to MQTT if not connected. 
 */
void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }  
  
  client.loop();
DoSomethingWithThoseValues();
  delay(200);
}


