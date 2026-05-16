#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <JPEGDecoder.h>

// TFT
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

// Button
#define BUTTON_PIN 13

// WiFi
extern const char* ssid;
extern const char* password;

// Objects
extern Adafruit_ILI9341 tft;
extern RTC_DS3231 rtc;
extern AsyncWebServer server;

// Variables
extern bool paused;
extern bool lastBtnState;
extern unsigned long lastDebounce;
extern const unsigned long debounceDelay;

extern bool loggedIn;

extern String images[50];
extern int imageCount;
extern int currentImage;

extern int slideDelay;
extern unsigned long lastSlide;

extern String lastExpiry;
extern String lastDrawn;

#endif
