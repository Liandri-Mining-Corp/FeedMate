#include <DHT.h> // Einbinden der DHT-Bibliothek
#define DHTPIN 1 // Der digitale Pin, an dem der Sensor angeschlossen ist (z.B. D4)
#define DHTTYPE DHT11 // Oder DHT11, je nach deinem Sensor

DHT dht(DHTPIN, DHTTYPE); // Initialisiere den DHT-Sensor

void setup() {
  Serial.begin(115200); // Starte die serielle Kommunikation  
  dht.begin();          // Starte den DHT-Sensor  
  Serial.println("DHT-Sensor Test!");
}
void loop() {
  delay(2000); // Warte 2 Sekunden zwischen Messungen

  float h = dht.readHumidity();     // Lese Luftfeuchtigkeit
  float t = dht.readTemperature();  // Lese Temperatur (Celsius)
  
  //if (isnan(h) || isnan(t)) { // Prüfe, ob die Messung erfolgreich war
  //  Serial.println("Fehler beim Lesen vom DHT-Sensor!");
  //return;
  //}

  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatur: ");
  Serial.print(t);
  Serial.println(" *C");
}