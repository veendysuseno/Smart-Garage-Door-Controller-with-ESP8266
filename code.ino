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

void setup() {
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
  webPage += "<h1><center>Web Controlled Garage Door</center></h1>";
  webPage += "<a href='/opened'><button>Opened</button></a>";
  webPage += "<a href='/closed'><button>Closed</button></a></center>";

  delay(200);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266", WiFi.localIP()))  {
    Serial.println("MDNS responder started");
  }
  server.on("/", []() {
    server.send(200, "text/html", webPage);
  });
  server.on("/opened", []() {
    server.send(200, "text/html", webPage);
    opened();
  });
  server.on("/closed", []() {
    server.send(200, "text/html", webPage);
    closed();
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void refreshpage() {
  webPage = "";
  webPage += "<html><head><style>";
  webPage += "body { font-family: Arial, sans-serif; background-color: #f0f0f5; margin: 0; padding: 0; text-align: center; }";
  webPage += "h1 { color: #333; margin-top: 20px; font-size: 2.5em; }";
  webPage += "button { background-color: #4CAF50; color: white; padding: 15px 32px; font-size: 1.2em; margin: 10px; border: none; border-radius: 5px; cursor: pointer; box-shadow: 0 4px #999; transition: background-color 0.3s ease; }";
  webPage += "button:hover { background-color: #45a049; }";
  webPage += "button:active { background-color: #3e8e41; box-shadow: 0 2px #666; transform: translateY(4px); }";
  webPage += ".door-status { font-size: 1.5em; margin: 20px; color: #555; }";
  webPage += ".container { margin: 0 auto; padding: 20px; width: 80%; max-width: 500px; background-color: #fff; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }";
  webPage += "</style>";
  
  // Tambahan JavaScript
  webPage += "<script>";
  webPage += "function updateDoorState() {";
  webPage += "  fetch('/door_state').then(response => response.text()).then(state => {";
  webPage += "    document.getElementById('doorStatus').innerText = 'Current door state: ' + state;";
  webPage += "  });";
  webPage += "}";
  webPage += "setInterval(updateDoorState, 3000);"; // Memperbarui status pintu setiap 3 detik
  webPage += "</script>";
  
  webPage += "</head><body>";
  webPage += "<div class='container'>";
  webPage += "<h1>Smart Garage Door Control</h1>";
  webPage += "<button onclick=\"location.href='/opened'\">Open</button>";
  webPage += "<button onclick=\"location.href='/closed'\">Close</button>";
  webPage += "<div id='doorStatus' class='door-status'>Current door state: " + door_state + "</div>";
  webPage += "</div></body></html>";
}

void opened() {
    digitalWrite(MB1, HIGH);
    digitalWrite(MB2, LOW);
    delay(1000);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, LOW);
    door_state = "open";  // Update status pintu
    refreshpage();
}

void closed() {
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
    delay(1000);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, LOW);
    door_state = "close";  // Update status pintu
    refreshpage();
}