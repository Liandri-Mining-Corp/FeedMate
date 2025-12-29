bool getServiceHatchState();
float getHumidity();
float getTemperature();

const int FEEDING_TIME_HOUR = 14;
const int FEEDING_TIME_MINUTE = 1;
//const int FEEDING_TIME_SEC = 0; // Can be used to control to the Secound food shall be dispensed

void setup(){
  //Enable Serial and set Baudrate
  Serial.begin(115200);
  displayInit();
  rfidInit();
  serviceHatchInit();
  ledControllerInit();
  ultrasonicInit();
  moistureSensorInit();
  feederInit();
  timerInit();
  webServerInit();
  displayBootDone(); 
}

void loop(){
  if (isTime(FEEDING_TIME_HOUR, FEEDING_TIME_MINUTE, 0) == true)
  {
    turnfeeder();
  }
  
  if (isAuthorizedCardDetected() == true && getServiceHatchState() == false)
  {
    Serial.println("opening");
    openServiceHatch();
    delay(1600);
  } else if (isAuthorizedCardDetected() == true && getServiceHatchState() == true)
  {
    Serial.println("closing");
    closeServiceHatch();
    delay(1600);
  }
  webServerLoop();
  updateLedByDistance(getDistance());
}

void turnfeeder() {
  for (int i = 0; i < 4; i++) 
  {
    if (getFeederPOS() == 0)
    {
      setfeederPosition1();
      delay(4000);
    } else
    {
     setfeederPosition0();
     delay(4000);
    }
  }
  updateLedByDistance(getDistance());
}