/*
  IoT Club - ISTC Workshop
  Controlling LED with MQTT

  This code demonstrates how to control the state of an LED connected ,button,dht22
  to the ESP32 based on messages received from a specific MQTT topic.
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>
DHTesp dht;

// Update these with your Wi-Fi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT Broker settings
const char* mqtt_server = "ec2-3-83-31-167.compute-1.amazonaws.com";
const int mqtt_port = 1883;


// Topic for controlling the LED
const char* ledTopic = "myLed";

const int ledPin = 23; // Change this to the actual pin connected to the LED
const int pushButton=22;
const int dhtPin=21;
bool ledStatus=0;
WiFiClient espClient;
PubSubClient client(espClient);
void connectToMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe(ledTopic);
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

  // Control the LED based on the message
  if (message == "1") {
    ledStatus=1;
  } else if (message == "0") {
    ledStatus=0;
  } 
}
float hum,temp;
void updateTempHum()
{
    float t = dht.getTemperature();
    float h = dht.getHumidity();

    if (isnan(t) || isnan(h) || t == 0 || h == 0)
    {
        return;
    }
    else
    {

        if ((temp != t) || (hum != h))
        {
            temp = t;
            hum = h;
            Serial.println("updatte detected");
          
            client.publish("myTemp", String(temp).c_str(), true);
            client.publish("myHum", String(hum).c_str(), true);
        }
    }
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
  dht.setup(dhtPin, DHTesp::DHT22);
  connectToMQTT();
}

/**
 * Function to continuously check the connection status, 
 * and reconnect to MQTT if not connected. tu
 */
void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();
  if (digitalRead(pushButton)==LOW){
    client.publish(ledTopic,String(!ledStatus).c_str());
    delay(200);
  }
  digitalWrite(ledPin,ledStatus);
  updateTempHum();
}