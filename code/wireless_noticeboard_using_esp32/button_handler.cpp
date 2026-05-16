#include "button_handler.h"

void handleButton() {

  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastBtnState) {
    lastDebounce = millis();
  }

  if ((millis() - lastDebounce) > debounceDelay) {

    if (lastBtnState == HIGH && reading == LOW) {

      paused = !paused;

      Serial.println(paused ? "Paused" : "Resumed");
    }
  }

  lastBtnState = reading;
}
