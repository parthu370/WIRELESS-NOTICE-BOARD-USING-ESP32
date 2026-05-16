#include "rtc_handler.h"
#include "storage.h"

void checkExpiry() {

  static unsigned long lastCheck = 0;

  if (millis() - lastCheck < 5000) {
    return;
  }

  lastCheck = millis();

  DateTime now = rtc.now();

  uint32_t currentTime = now.unixtime();

  for (int i = 0; i < imageCount; i++) {

    String meta = "/" + images[i] + ".txt";

    if (!LittleFS.exists(meta)) {
      continue;
    }

    File f = LittleFS.open(meta, "r");

    String data = f.readString();

    f.close();

    data.trim();

    if (data == "" || data == "0") {
      continue;
    }

    uint32_t expTime = data.toInt();

    if (currentTime >= expTime) {

      deleteImage(images[i]);

      loadImages();

      currentImage = 0;

      return;
    }
  }
}
