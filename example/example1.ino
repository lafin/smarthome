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

char* mqttServer = "server";
char* ssid = "ssid";
char* password = "password";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

String getClientName() {
  String clientName = "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  return clientName;
}

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  client.setServer(mqttServer, 1883);

  String clientName = getClientName();
  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");

    pinMode(RELAYPIN, OUTPUT);
    client.setCallback(callback);
    if (client.subscribe("relay_switch")) {
      Serial.println("Subscribe switch ok");
    }
    else {
      Serial.println("Subscribe switch failed");
    }

    if (client.publish("HELO", (char*) clientName.c_str())) {
      Serial.println("Publish HELO ok");
    }
    else {
      Serial.println("Publish HELO failed");
    }

    dht.begin();
  }
  else {
    Serial.println("MQTT connect failed");
    abort();
  }
}

void reconnect() {
  String clientName = getClientName();
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect((char*) clientName.c_str())) {
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

    if (isnan(humidity) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

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
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  bool state = (char)payload[0] == 't';
  Serial.println("set Switch state");
  if (state) {
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