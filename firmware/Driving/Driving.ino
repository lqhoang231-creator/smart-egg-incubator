const int servoPin = 18;
const int channel = 0;
unsigned long preMillis = 0;
const long interval1 = 2000;
const long interval2 = 5000;
int n = 0;
const int buttonPin = 4;

void setup() {
    ledcSetup(channel, 50, 16);     //channel 0, frequency 50 Hz, resolution 16 bit
    ledcAttachPin(servoPin, channel);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
    //unsigned long currentMillis = millis();
    if (digitalRead(buttonPin) == HIGH){
        delay(50);
        if (digitalRead(buttonPin) == HIGH)
            servo1();
    }
    else
        servo2();
}

void servo1 (){
    unsigned long currentMillis = millis();
    if (currentMillis - preMillis >= interval1){
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

void servo2(){
    unsigned long currentMillis = millis();
    if (currentMillis - preMillis >= interval2){
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