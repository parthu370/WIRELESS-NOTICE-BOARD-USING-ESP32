#include "storage.h"

void loadImages() {

  imageCount = 0;

  File root = LittleFS.open("/");

  File file = root.openNextFile();

  while (file) {

    String name = file.name();

    name.replace("/", "");

    if (name.endsWith(".jpg")) {

      if (imageCount < 50) {
        images[imageCount++] = name;
      }
    }

    file = root.openNextFile();
  }

  Serial.println("Images: " + String(imageCount));
}

void deleteImage(String name) {

  Serial.println("Deleting: " + name);

  JpegDec.abort();

  LittleFS.remove("/" + name);

  LittleFS.remove("/" + name + ".txt");

  tft.fillScreen(ILI9341_BLACK);

  lastDrawn = "";
}
