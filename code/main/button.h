void listenButtonPressed() {
  if (!digitalRead(Button)) {
    delay(10);
    if (!digitalRead(Button)) {
      toggleLED(!digitalRead(LED));
      while (!digitalRead(Button));
    }
  }
}
