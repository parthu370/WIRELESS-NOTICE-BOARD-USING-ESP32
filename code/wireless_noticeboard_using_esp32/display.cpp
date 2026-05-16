#include "display.h"

bool drawJpeg(String filename)
{
  String path = "/" + filename;

  if (!LittleFS.exists(path)) {
    return false;
  }

  if (!JpegDec.decodeFsFile(path)) {
    return false;
  }

  tft.fillScreen(ILI9341_BLACK);

  int imgW = JpegDec.width;
  int imgH = JpegDec.height;

  int screenW = tft.width();
  int screenH = tft.height();

  float scaleX = (float)screenW / imgW;
  float scaleY = (float)screenH / imgH;
  float scale = min(scaleX, scaleY);

  int newW = imgW * scale;
  int newH = imgH * scale;

  int offsetX = (screenW - newW) / 2;
  int offsetY = (screenH - newH) / 2;

  while (JpegDec.read()) {

    int x = JpegDec.MCUx * JpegDec.MCUWidth;
    int y = JpegDec.MCUy * JpegDec.MCUHeight;

    int drawX = offsetX + x * scale;
    int drawY = offsetY + y * scale;

    if (drawX >= screenW || drawY >= screenH) continue;

    tft.drawRGBBitmap(
      drawX,
      drawY,
      JpegDec.pImage,
      JpegDec.MCUWidth,
      JpegDec.MCUHeight
    );
  }

  JpegDec.abort();

  return true;
}
