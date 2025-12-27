// DHT (Temperature & Humidity) Sensor
#include <DHT.h>   // Include the DHT sensor library

// DHT sensor configuration
#define DHTPIN 1        // Digital pin where the DHT sensor is connected
#define DHTTYPE DHT11  // Sensor type: DHT11 (change if using DHT22, etc.)

// Create a DHT sensor object with defined pin and type
DHT dht(DHTPIN, DHTTYPE);


// Initialize the moisture (humidity) sensor
void moistureSensorinit() {
  dht.begin();   // Start communication with the DHT sensor
  Serial.println("Moisture Sensor Online");
}


// Read and display moisture and temperature values
void CheckMoisture() {
  // Read humidity value (percentage)
  float h = dht.readHumidity();

  // Read temperature value in Celsius
  float t = dht.readTemperature();
  
  // Check if the readings failed
  // isnan() returns true if the value is not a number
  if (isnan(h) || isnan(t)) {
    Serial.println("Error reading from DHT sensor!");
    return;
  }

  // Output sensor values to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
}
