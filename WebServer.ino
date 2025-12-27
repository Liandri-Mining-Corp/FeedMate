#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "....";
const char* password = "....";

WebServer server(80);

const int ledPin = 2; // onboard LED for many ESP32 boards (adjust if needed)
bool ledState = false;

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
      <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>ESP32 Web Server</title>
        <style>
          body{font-family:Arial,Helvetica,sans-serif; padding:20px;}
          button{font-size:16px;padding:10px 16px;}
        </style>
      </head>
      <body>
        <h1>ESP32 Web Server</h1>
  )rawliteral";

  html += "<p>LED state: <strong>" + String(ledState ? "ON" : "OFF") + "</strong></p>";
  html += "<p><a href=\"/toggle\"><button>Toggle LED</button></a></p>";
  html += R"rawliteral(
        <hr>
        <p>API: <code>/status</code> (returns JSON)</p>
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);

  // Redirect back to root so browsers show the updated page
  server.sendHeader("Location", "/");
  server.send(303); // 303 See Other
}

void handleStatus() {
  String payload = "{ \"led\": ";
  payload += (ledState ? "true" : "false");
  payload += " }";
  server.send(200, "application/json", payload);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "OTHER";
  message += "\n";
  server.send(404, "text/plain", message);
}

void webserverinit() {
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);

  // Wait for connection (with a simple timeout)
  int attempts = 0;
  const int maxAttempts = 40; // ~20 seconds
  while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected. IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi connection failed - check credentials.");
    // Server will still start, but without WiFi the page won't be reachable on the network.
  }

  // Register URL handlers
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void webserverloop()
{
  server.handleClient();
}