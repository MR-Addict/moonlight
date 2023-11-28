#include <WiFi.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

const uint8_t LED = 2;
const uint8_t Button = 13;
const char* ssid = "STAS-507";
const char* password = "manke666";
const String hostname = "moonlight";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

#include "init.h"
#include "led.h"
#include "button.h"
#include "websocket.h"
#include "server.h"

void setup() {
  init(115200, ssid, password);
  setupWebsocket();
  setupServer();
}

void loop() {
  ws.cleanupClients();
  listenButtonPressed();
}
