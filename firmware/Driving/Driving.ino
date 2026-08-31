const int servoPin = 18;
const int channel = 0;
unsigned long preMillis = 0;
const long interval = 2000;
int n = 0;

void setup() {
    ledcSetup(channel, 50, 16);     //channel 0, frequency 50 Hz, resolution 16 bit
    ledcAttachPin(servoPin, channel);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - preMillis >= interval){
        preMillis = currentMillis;
        if (n == 0){
            ledcWrite(channel, 3277);
            n = 1;
        }
        else{
            ledcWrite(channel, 6554);
            n = 0;
        }
    }
}