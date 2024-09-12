# Smart Garage Door Controller with ESP8266

## Description

The **Smart Garage Door Controller** allows you to control your garage door remotely through a web interface using the ESP8266 microcontroller. You can open or close the door from anywhere with an internet connection. The system updates the door's status in real-time.

## Features

- **Remote Control:** Open and close the garage door using a web interface.
- **Real-Time Status:** Displays the current door state and updates automatically.
- **User-Friendly Interface:** Clean and responsive design with easy-to-use buttons.

## Components Required

- ESP8266 microcontroller
- Relay module or transistors for controlling the garage door motor
- Wi-Fi network

## Wiring

- Connect the ESP8266 GPIO pins to the relay module or transistors controlling the garage door motor.

## Code

The provided code initializes the ESP8266, connects to the Wi-Fi network, and sets up a web server to control the garage door. It includes:

- **HTML/CSS/JavaScript:** A responsive web page to control the door and display its status.
- **Endpoints:** `/opened` and `/closed` to handle door control commands.
- **Real-Time Updates:** JavaScript fetches the door state every 3 seconds.

## Setup

1. **Upload the Code:** Upload the Arduino sketch to the ESP8266 using the Arduino IDE.
2. **Connect to Wi-Fi:** Ensure the ESP8266 is connected to your Wi-Fi network. Modify the `ssid` and `password` variables in the code as needed.
3. **Access the Web Interface:** Open a web browser and navigate to the IP address displayed in the Serial Monitor to access the control interface.

## Code Snippet

```cpp
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Sliding Gate";
const char* password = "Admin12345";
ESP8266WebServer server(80);

String webPage = "";
String door_state = "close";
int MB1 = D1;
int MB2 = D3;

// Setup, loop, and control functions here...
```

