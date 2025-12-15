int trigger_pin = 27;
int echo_pin = 14;

long dauer = 0;
long entfernung = 0;

void setup() {
  Serial.begin(115200);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  Serial.println("Pulse");
  digitalWrite(trigger_pin, HIGH);
  delay(10);
  digitalWrite(trigger_pin, LOW);
  Serial.println("Done");
  Serial.println("");

  dauer = pulseIn(echo_pin, HIGH);
  Serial.println(dauer);
  Serial.println("");

  entfernung = (dauer/2) * 0.03432;
  Serial.print(entfernung);
  Serial.println(" cm");
}
