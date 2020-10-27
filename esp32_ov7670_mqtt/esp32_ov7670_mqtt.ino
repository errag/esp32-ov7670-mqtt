#include "OV7670.h"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "BMP.h"

const int SIOD = 21; //SDA
const int SIOC = 22; //SCL

const int VSYNC = 34;
const int HREF = 35;

const int XCLK = 32;
const int PCLK = 33;

const int D0 = 27;
const int D1 = 17;
const int D2 = 16;
const int D3 = 15;
const int D4 = 14;
const int D5 = 13;
const int D6 = 12;
const int D7 = 4;

const char* ssid        = "<YOUR SSID>";
const char* password    = "<YOUR PASSWORD>";
const char* MQTT_BROKER = "<MQTT BROKER IP>";
const char* TOPIC       = "<YOUR TOPIC>";

WiFiClient espClient;

OV7670 *camera;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

unsigned char bmpHeader[BMP::headerSize];

void serve()
{
  bool stateImage = false;
  
  reconnect();
  
  mqttClient.beginPublish(TOPIC, (BMP::headerSize) + (camera->xres * camera->yres * 2), false);

  mqttClient.write(bmpHeader, BMP::headerSize);
  mqttClient.write(camera->frame, camera->xres * camera->yres * 2);
  
  stateImage = mqttClient.endPublish();

  Serial.print("Send frame = ");
  Serial.print(stateImage);
  Serial.println();
}

void setup() 
{
  Serial.begin(115200);

  Serial.println("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  mqttClient.setServer(MQTT_BROKER, 1883);
  
  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
}

void loop()
{
  camera->oneFrame();
  serve();
  delay(250);
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Reconnecting...");

    if (!mqttClient.connect("EspCam")) {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      delay(500);
    } else {
      Serial.println(" still connected");
    }
  }
}
