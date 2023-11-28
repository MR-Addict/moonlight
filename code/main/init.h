void init(uint32_t baud_rate, const char* ssid, const char* password) {
  // init led
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
  Serial.begin(baud_rate);

  // init SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  // init wifi
  WiFi.hostname(hostname);
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.printf("\nLocal IP: %s\n", WiFi.localIP().toString().c_str());
}
