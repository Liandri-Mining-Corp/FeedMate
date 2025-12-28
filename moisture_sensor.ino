// DHT Moisture Sensor Library Configuration
#include <DHT.h>

// Pin and sensor type
const int DHT_PIN   = 1;
const int DHT_TYPE  = DHT11;

// Create DHT sensor instance
DHT moistureSensor(DHT_PIN, DHT_TYPE);

// Initialize moisture sensor
void moistureSensorInit() {
  moistureSensor.begin();
  Serial.println("Moisture Sensor online");
}

// Read humidity
// Returns: humidity in percent, or NAN on failure
float getHumidity() {
  return moistureSensor.readHumidity();
}

// Read temperature
// Returns: temperature in Celsius, or NAN on failure
float getTemperature() {
  return moistureSensor.readTemperature();
}

//TODO remove Debug funtion if not required

// DEBUG: Validate sensor readings
bool isMoistureReadingValid(float humidity, float temperature) {
  Serial.println(humidity);
  Serial.println(temperature);
  return !isnan(humidity) && !isnan(temperature);
}