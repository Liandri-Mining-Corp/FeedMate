#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "...";
const char* password = "...";

// Webserver on port 80
WebServer server(80);

// Forward declarations of getters from the controller file
int getLastLED();           // 0 = Red, 1 = Yellow, 2 = Green
float getTemperature();
float getHumidity();
bool getServiceHatchState();

// Convert food level to colored text
String foodLevelText(int level) {
  switch(level) {
    case 0: return "<span style='color:red'>Red</span>";
    case 1: return "<span style='color:orange'>Yellow</span>";
    case 2: return "<span style='color:green'>Green</span>";
    default: return "Unknown";
  }
}

// Convert hatch boolean to text
String serviceHatchText(bool open) {
  return open ? "Open" : "Closed";
}

// Generate HTML page
String generateHTML() {
	int food = getLastLED();
  float temp = getTemperature();
  float moist = getHumidity();
  bool hatch = getServiceHatchState();

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta http-equiv='refresh' content='5'><title>LMC FeederMate</title></head><body>";
  html += "<h1>FeederMate</h1>";
  html += "<p><b>Food Level:</b> " + foodLevelText(food) + "</p>";
  html += "<p><b>Temperature:</b> " + String(temp, 1) + " °C</p>";
  html += "<p><b>Moisture:</b> " + String(moist, 1) + " %</p>";
  html += "<p><b>Service Hatch:</b> " + serviceHatchText(hatch) + "</p>";
  html += "</body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", generateHTML());
}

void webServerInit() {
  //Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void webServerLoop() {
	server.handleClient();
}