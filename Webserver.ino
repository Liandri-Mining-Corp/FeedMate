// Include the WIFI and Webserver Library
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi Credentials
const char* WIFI_SSID     = "...";
const char* WIFI_PASSWORD = "...";

// Web Server Configuration
WebServer webServer(80);

// Forward declarations of getters
int getLastLED();           // 0 = Red, 1 = Yellow, 2 = Green
float getTemperature();
float getHumidity();
bool getServiceHatchState();
String getTimeString();

// Convert food level to colored HTML text
String formatFoodLevelHtml(int level) {
  switch (level) {
    case 0: return "<span style='color:red'>Red</span>";
    case 1: return "<span style='color:orange'>Yellow</span>";
    case 2: return "<span style='color:green'>Green</span>";
    default: return "Unknown";
  }
}

// Convert service hatch state to text
String formatServiceHatchText(bool is_open) {
  return is_open ? "Open" : "Closed";
}

// Generate HTML page and Update LCD
String generateStatusPageHtml() {
  int food_level      = getLastLED();
  float temperature  = getTemperature();
  float humidity     = getHumidity();
  bool hatch_open    = getServiceHatchState();
  String time_string = getTimeString();

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>LMC FeederMate</title></head><body>";

  html += "<h1>FeederMate</h1>";
  html += "<p><b>Time:</b> " + time_string + "</p>";
  html += "<p><b>Food Level:</b> " + formatFoodLevelHtml(food_level) + "</p>";
  html += "<p><b>Temperature:</b> " + String(temperature, 1) + " °C</p>";
  html += "<p><b>Moisture:</b> " + String(humidity, 1) + " %</p>";
  html += "<p><b>Service Hatch:</b> " + formatServiceHatchText(hatch_open) + "</p>";
  html += "</body></html>";

  // Update Display
  clearDisplay();
  writeLine1("Moist:" + String(humidity, 1) + "%");
  writeLine2("Temp:" + String(temperature, 1) + " C");

  return html;
}

// Handle root web request
void handleRootRequest() {
  webServer.send(200, "text/html", generateStatusPageHtml());
}

// Initialize web server
void webServerInit() {
  writeLine1("Connecting");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  webServer.on("/", handleRootRequest);
  webServer.begin();

  writeLine1("Connected!");
}

// Web server loop handler
void webServerLoop() {
  webServer.handleClient();
}