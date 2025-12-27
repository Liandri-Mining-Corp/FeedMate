void setup(){
  //Enable Serial and set Baudrate
  Serial.begin(115200);
  initRFIDHatch();
  ultraAmpelInit();
  moistureSensorinit();
  webserverinit();
}

void loop(){
  webserverloop();
  checkCard();
  pulse();
  changeLight();
  CheckMoisture();
  delay(1600);
}

