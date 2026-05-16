#include "config.h"
#include "display.h"
#include "storage.h"
#include "rtc_handler.h"
#include "button_handler.h"
#include "server_routes.h"

// =====================================================
//                    OBJECTS
// =====================================================

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

RTC_DS3231 rtc;

AsyncWebServer server(80);

// =====================================================
//                    BUTTON
// =====================================================

bool paused = false;

bool lastBtnState = HIGH;

unsigned long lastDebounce = 0;

const unsigned long debounceDelay = 250;

// =====================================================
//                    LOGIN
// =====================================================

bool loggedIn = false;

// =====================================================
//                    STORAGE
// =====================================================

String images[50];

int imageCount = 0;

int currentImage = 0;

// =====================================================
//                    SLIDESHOW
// =====================================================

int slideDelay = 4;

unsigned long lastSlide = 0;

// =====================================================
//                    STATUS
// =====================================================

String lastExpiry = "";

String lastDrawn = "";

// =====================================================
//                    WIFI
// =====================================================

const char* ssid = "ESP32_NoticeBoard";

const char* password = "12345678";

// =====================================================
//                    SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // File System
  LittleFS.begin(true);

  // I2C
  Wire.begin();

  // RTC
  if (!rtc.begin()) {

    Serial.println("RTC not found");
  }

  if (rtc.lostPower()) {

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // SPI
  SPI.begin(18, 19, 23);

  // TFT
  tft.begin();

  tft.setRotation(3);

  tft.fillScreen(ILI9341_BLACK);

  // WiFi Access Point
  WiFi.softAP(ssid, password);

  Serial.println("WiFi AP Started");

  Serial.println(WiFi.softAPIP());

  // Load images
  loadImages();

  // Start server
  setupServer();

  Serial.println("Server Started");
}

// =====================================================
//                      LOOP
// =====================================================

void loop() {

  // Check image expiry
  checkExpiry();

  // Handle pause button
  handleButton();

  // Pause mode
  if (paused) {
    return;
  }

  // No images
  if (imageCount == 0) {
    return;
  }

  // Single image display fix
  if (imageCount == 1) {

    static String lastSingle = "";

    if (lastSingle != images[0]) {

      drawJpeg(images[0]);

      lastSingle = images[0];
    }

    return;
  }

  // Slideshow
  if (millis() - lastSlide >= (unsigned long)slideDelay * 1000) {

    drawJpeg(images[currentImage]);

    currentImage++;

    if (currentImage >= imageCount) {

      currentImage = 0;
    }

    lastSlide = millis();
  }
}
