// handle websocket get message
void handleWebSocketMessage(uint8_t *payload, size_t len) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload, len);
  toggleLED(doc["led"] == "on");
}

// websocket events
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *payload, size_t len) {
  switch (type) {
    case WS_EVT_DATA: handleWebSocketMessage(payload, len); break;
    case WS_EVT_CONNECT: getLED(); break;
    case WS_EVT_DISCONNECT: break;
    case WS_EVT_PONG: break;
    case WS_EVT_ERROR: break;
  }
}

void setupWebsocket() {
  server.addHandler(&ws);
  ws.onEvent(onEvent);
}
