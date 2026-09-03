#define Pin_ain1 17
#define Pin_ain2 5
#define Pin_pwma 18
#define Pin_stby 16
const int servoPin = 13;
const int channel = 0;
unsigned long preMillis = 0;
const long interval1 = 20000;
const long interval2 = 15000;
int n = 0;
const int buttonPin = 25;
const int channel_motor = 4;

int mode = 1;
int lastButtonState = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long delayTime = 50;

unsigned long preMillisMotor = 0;
int run = 5000;
int stop = 5000;
bool mtRunning = true;

void setup() {
    ledcSetup(channel, 50, 16);     //channel 0, frequency 50 Hz, resolution 16 bit
    ledcAttachPin(servoPin, channel);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(Pin_ain1, OUTPUT);
    pinMode(Pin_ain2, OUTPUT);
    pinMode(Pin_pwma, OUTPUT);
    pinMode(Pin_stby, OUTPUT);
    digitalWrite(Pin_stby, HIGH);
    ledcSetup(channel_motor, 1000, 8);
    ledcAttachPin(Pin_pwma, channel_motor);  
    motor(150);   
}

void loop() {
    unsigned long Millis = millis();
    int read = digitalRead(buttonPin);
    if(read != lastButtonState){
        lastDebounceTime = Millis;
    }
    if(Millis - lastDebounceTime >= delayTime){
        if(read != buttonState){
            buttonState = read;
            if(buttonState == LOW){
                mode = (mode == 1) ? 2:1;
            }
        }
    }
    lastButtonState = read;
    if(mode == 1)
        servo1();
    else
        servo2();

    unsigned long interval = (mtRunning) ? run:stop;
    if(Millis - preMillisMotor >= interval){
    preMillisMotor = Millis;
    mtRunning = !mtRunning;
    motor(mtRunning ?150:0);
  }
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

void motor(int speed){
    speed = constrain(speed, 0, 255);
    digitalWrite(Pin_ain1, HIGH);
    digitalWrite(Pin_ain2, LOW);
    ledcWrite(channel_motor, speed);
}