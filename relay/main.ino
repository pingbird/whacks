
//#include <JsonListener.h>
//#include <JsonStreamingParser.h>

#include <Adafruit_NeoPixel.h>

extern "C" {
  #include "user_interface.h"
}

/*
   Simple HTTP get webclient test
*/

#include <ESP8266WiFi.h>

const char* ssid     = "WSU-PUBLIC";
const char* password = "";

void initVariant() {
  uint8_t mac[] = {0xC8, 0x3A, 0x35, 0xC4, 0x01, 0x2F};
  wifi_set_macaddr(STATION_IF, &mac[0]);
}

Adafruit_NeoPixel leds = Adafruit_NeoPixel(2, 15, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("MAC: " + WiFi.macAddress());
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
   leds.begin();
   leds.show();
}

int value = 0;

char waitRead() {
    while (Serial.available() == 0);
    return Serial.read();
}

int lastval = 0;
int maxval;
int minval;

void loop() {
  leds.setPixelColor(1, 255, 255, 255);
  leds.setPixelColor(0, 255, 0, 0);
  leds.setBrightness(20);
  leds.show();
  if (waitRead() != 34) return;
  if (waitRead() != 6) return;
  if (waitRead() != 57) return;
  String buf = "";
  while (true) {
    char ch = waitRead();
    if (!isDigit(ch)) break;
    buf += ch;
  }
  int data = buf.toInt();
  if (data == 0) {
    if (lastval != 0) {
      leds.setPixelColor(1, 0, 255, 0);
      leds.setPixelColor(0, 0, 255, 0);
      leds.setBrightness(100);
      leds.show();
      WiFiClient client;
      const int httpPort = 80;
      if (!client.connect("enp.pxtst.com", 80)) {
        Serial.println("connection failed");
      } else {
        Serial.println("connection success");
        client.print("GET /enp.php?x=" + String((maxval + minval) / 2) + " HTTP/1.1\r\nHost: enp.pxtst.com\r\nConnection: close\r\n\r\n");
        delay(100);
      }
    }
    maxval = -99999;
    minval = 99999;
  } else {
    maxval = std::max(maxval, data);
    minval = std::min(minval, data);
  }
  lastval = data;
  /*delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  } else {
    Serial.println("connection success");
  }

  // This will send the request to the server
  client.print(String("GET ") + "/enp.php" + " HTTP/1.1\r\n" +
               "Host: enp.pxtst.com\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);
  //JsonObject& root = jsonBuffer.parseObject(basic);

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    const String data = client.readStringUntil('\r');
    Serial.println(data);
  }

  Serial.println();
  Serial.println("closing connection");*/
}

