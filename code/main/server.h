// handle OPTIONS and 404 request
void handleNotFound(AsyncWebServerRequest* request) {
  String url = request->url();

  // end with /
  if (url.endsWith("/")) {
    url += "index.html";
    if (SPIFFS.exists(url)) request-> send(SPIFFS, url, "text/html");
    else request->send(404);
  }
  else if (request->method() == HTTP_OPTIONS) request->send(200);
  else request->send(404, "text/plain", "404");
}

// handle get light status request
void handleGetRequest(AsyncWebServerRequest* request) {
  String message = getLED();
  request->send(200, "application/json", message);
}

// handle turn on light request
void handlePostRequest(AsyncWebServerRequest* request) {
  String message = toggleLED(true);
  request->send(200, "application/json", message);
}

// handle turn off light request
void handleDeleteRequest(AsyncWebServerRequest* request) {
  String message = toggleLED(false);
  request->send(200, "application/json", message);
}

// setup server
void setupServer() {
  DefaultHeaders::Instance().addHeader("Server", "ESP32");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

  server.serveStatic("/", SPIFFS, "/");

  server.on("/api/led", HTTP_GET, handleGetRequest);
  server.on("/api/led", HTTP_POST, handlePostRequest);
  server.on("/api/led", HTTP_DELETE, handleDeleteRequest);

  server.onNotFound(handleNotFound);
  server.begin();
}
