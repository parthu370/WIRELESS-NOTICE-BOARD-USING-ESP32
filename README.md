**# ESP32 Wireless Notice Board**

**## Overview**



This project is a wireless digital notice board using ESP32 and ILI9341 TFT display. Images can be uploaded wirelessly through a web interface and displayed as a slideshow on the TFT screen.



The project also supports RTC-based image expiry, slideshow delay control, pause/resume functionality, and image management through a browser-based control panel.



An Android mobile application is also under development to provide remote notice management and improved user accessibility.



The system is powered using a solar-powered portable energy supply, making it suitable for standalone and energy-efficient operation



\---



**## Features**



\- Wireless image upload through browser

\- ESP32 WiFi Access Point mode

\- Real-time TFT image slideshow

\- JPEG image rendering on ILI9341 display

\- RTC-based automatic image expiry

\- Adjustable slideshow delay from web panel

\- Pause/Resume slideshow using push button

\- Wireless image deletion support

\- Browser-based control panel

\- LittleFS internal file storage

\- Automatic image scaling to screen size

\- Multi-image slideshow support

\- Dynamic image management

\- Real-time image refresh without reboot

\- Password-protected web login

\- Android mobile app integration (Under Development)

\- Remote notice management through mobile app

\- Solar power supply

\- Baterry backup support



\---



**## Components Used**



\- ESP32 Dev Module

\- ILI9341 TFT Display

\- DS3231 RTC Module

\- Push Button

\- Jumper Wires

\- USB Cable

\- Solar Panel

\- Lithium-Ion Battery

\- Charging Module

\- Boost Converter



\---



**## Technologies Used**



\- Embedded C++

\- ESPAsyncWebServer

\- LittleFS

\- WiFi SoftAP

\- SPI Communication

\- I2C Communication

\- JPEGDecoder Library

\- Android Application Development

\- Solar power management



\---



**## Power Supply System**



The project is powered using a solar energy-based portable power system.



**### Power Components**



\- Solar Panel

\- Lithium-Ion Battery

\- Charging Module

\- Boost Converter



**### Working**



1\. Solar panel charges the lithium-ion battery

2\. Charging module safely manages battery charging

3\. Boost converter regulates output voltage for ESP32 operation

4\. System operates wirelessly without direct external power supply



This improves portability, energy efficiency, and enables standalone operation of the wireless notice board system.



**## Pin Connections**



| Component | ESP32 Pin |

|---|---|

| TFT\_CS | 15 |

| TFT\_DC | 2 |

| TFT\_RST | 4 |

| TFT\_MOSI | 23 |

| TFT\_MISO | 19 |

| TFT\_SCK | 18 |

| Push Button | 13 |



\---



**## Folder Structure**



ESP32\_Wireless\_NoticeBoard/



\- ESP32\_Wireless\_NoticeBoard.ino → Main program

\- config.h → Global configurations

\- display.cpp → TFT image rendering

\- storage.cpp → Image storage handling

\- rtc\_handler.cpp → RTC expiry checking

\- button\_handler.cpp → Button debounce logic

\- server\_routes.cpp → Web server routes

\- images/ → Project screenshots

\- circuit/ → Circuit diagrams

\- report/ → Project report and PPT



\---



**## WiFi Login**



SSID:

ESP32\_NoticeBoard



Password:

12345678



\---



**## Web Login**



Username:

admin



Password:

1234



\---



**## Working**



1\. ESP32 creates a WiFi hotspot

2\. User connects through mobile or laptop

3\. Browser opens the web control panel

4\. Images are uploaded wirelessly

5\. Images are stored in LittleFS

6\. Images display on TFT as slideshow

7\. RTC automatically removes expired images

8\. Delay can be adjusted dynamically

9\. Push button pauses or resumes slideshow

10\. Solar-powered system supplies portable power to the device





\---



**## Mobile Application Development**



An Android mobile application is currently under development for remote notice management and wireless control of the ESP32 notice board system.



**### Current Progress**



\- Approximately 80% completed



**### Planned Features**



\- Wireless image upload

\- Slideshow delay control

\- Image deletion

\- Remote notice management

\- User authentication

\- Real-time image expiry



The mobile application is being developed to improve accessibility and provide a more user-friendly interface for managing notices remotely.



\---



**## Installation**



1\. Install Arduino IDE

2\. Install ESP32 board package

3\. Install required libraries

4\. Open project in Arduino IDE

5\. Select ESP32 Dev Module

6\. Select correct COM port

7\. Compile and upload code

8\. Connect to ESP32 WiFi

9\. Open browser and go to:



192.168.4.1



\---



**## Required Libraries**



\- ESPAsyncWebServer

\- AsyncTCP

\- RTClib

\- Adafruit GFX

\- Adafruit ILI9341

\- JPEGDecoder



\---



**## Advantages**



\- Wireless operation

\- Easy notice management

\- Automatic image expiry handling

\- Real-time image updates

\- Low-cost implementation

\- Portable embedded system

\- User-friendly web interface

\- Manual delay control

\- Image preview in web interface

\- User authentication

\- Solar-powered portable operation

\- Reduced power consumption

\- Eco-friendly embedded solution



\---



**## Applications**



\- Colleges

\- Schools

\- Offices

\- Hospitals

\- Smart campuses

\- Railway stations

\- Public announcement systems

\- Rural digital information boards

\- Portable embedded display systems





\---



**## Project Screenshots**



\### Hardware Setup



Hardware component images are available inside:



images/hardware\_setup/



\### TFT Display Output



TFT display output images are available inside:



images/tft\_display\_output/



\### Web Control Panel



Web interface screenshots are available inside:



images/web\_control\_panel/



**## Future Improvements**



\- OTA firmware updates

\- Full Android app integration

\- Cloud image upload

\- Real-time mobile notifications

\- Cloud synchronization

\- Touchscreen support

\- Firebase integration

\- SD card support

\- Animation effects

\- Video playback support





**## Author**



Partha Sarathi

ECE Student

