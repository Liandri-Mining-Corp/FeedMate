// LED Pin Configuration
const int RED_LED_PIN    = 15;
const int YELLOW_LED_PIN = 16;
const int GREEN_LED_PIN  = 17;

// Distance thresholds (cm)
const int FAR_DISTANCE_CM    = 11;
const int MEDIUM_DISTANCE_CM = 5;

// Last LED State
int LAST_LED = 0; // 0 = Red, 1 = Yellow, 2 = Green

// Initialize LEDs
void ledControllerInit() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    allLightsOff(); //set all LEDs off
    Serial.println("LED Online");
}


// Update LEDs based on distance
void updateLedByDistance(long distance_cm) {
    allLightsOff();

    if (distance_cm > FAR_DISTANCE_CM) {
        digitalWrite(RED_LED_PIN, HIGH);
        LAST_LED = 0;
    }
    else if (distance_cm > MEDIUM_DISTANCE_CM) {
        digitalWrite(YELLOW_LED_PIN, HIGH);
        LAST_LED = 1;
    }
    else {
        digitalWrite(GREEN_LED_PIN, HIGH);
        LAST_LED = 2;
    }
}

// get last LED State
int getLastLED()
{
    return LAST_LED;
}

// turn off all LEDs
void allLightsOff() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
}