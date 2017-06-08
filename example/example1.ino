#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN  5
#define RELAYPIN  4
DHT dht(DHTPIN, DHTTYPE);
float humidity, temp;  // Values read from sensor
unsigned long previousMillis = 0;
const long interval = 5000;          // interval at which to read sensor / Update values

char* clientName = "mqtt";
char* mqttServer = "server";

char* ssid = "ssid";
char* password = "password";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  client.setServer(mqttServer, 1883);

  if (client.connect(clientName)) {
    Serial.println("Connected to MQTT broker");
  }
  else {
    Serial.println("MQTT connect failed");
    abort();
  }

  pinMode(RELAYPIN, OUTPUT);
  client.setCallback(callback);
  if (client.subscribe("relay_switch")) {
    Serial.println("Subscribe switch ok");
  }
  else {
    Serial.println("Subscribe switch failed");
  }

  dht.begin();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientName)) {
      Serial.println("connected");
    } else {
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishSensorData() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    humidity = dht.readHumidity();
    temp = dht.readTemperature(false);

    if (client.connected()) {
      String payload = "{\"Humidity\":";
      payload += humidity;
      payload += ",\"Temperature\":";
      payload += temp;
      payload += "}";

      if (client.publish("temperature_humidity_sensor", (char*) payload.c_str())) {
        Serial.println("Publish ok");
      }
      else {
        Serial.println("Publish failed");
      }
    }

    if (isnan(humidity) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("set Switch state");
  if ((char)payload[0] == 't') {
    digitalWrite(RELAYPIN, HIGH);
  } else {
    digitalWrite(RELAYPIN, LOW);
  }
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  publishSensorData();
  client.loop();
}