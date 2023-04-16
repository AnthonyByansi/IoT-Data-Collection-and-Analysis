#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define MQTT_SERVER "your_mqtt_broker_ip_address"
#define MQTT_USERNAME "your_mqtt_username"
#define MQTT_PASSWORD "your_mqtt_password"
#define MQTT_PORT 1883
#define TEMPERATURE_TOPIC "temperature"
#define HUMIDITY_TOPIC "humidity"
#define LIGHT_TOPIC "light"

#define DHT_PIN 2
#define DHT_TYPE DHT11

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
DHT dht(DHT_PIN, DHT_TYPE);

float temperature;
float humidity;
int lightLevel;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

  connectToWifi();
  connectToMqtt();

  dht.begin();
}

void loop() {
  readTemperatureAndHumidity();
  readLightLevel();
  publishTemperatureAndHumidity();
  controlLight();

  mqttClient.loop();
  delay(5000);
}

void connectToWifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("connected!");
}

void connectToMqtt() {
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqttClient.connect("ESP8266Client", MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void readTemperatureAndHumidity() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

void readLightLevel() {
  lightLevel = analogRead(A0);
}

void publishTemperatureAndHumidity() {
  mqttClient.publish(TEMPERATURE_TOPIC, String(temperature).c_str());
  mqttClient.publish(HUMIDITY_TOPIC, String(humidity).c_str());
}

void controlLight() {
  if (lightLevel > 500) {
    mqttClient.publish(LIGHT_TOPIC, "off");
  } else {
    mqttClient.publish(LIGHT_TOPIC, "on");
  }
}
