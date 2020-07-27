// Pins:
#define GREEN   2
#define RED     3
#define YELLOW1 4
#define YELLOW2 5
#define YELLOW3 6
#define YELLOW4 7
#define WHITE   8
#define BLUE    9
#define BUTTON1 12
#define BUTTON2 13

// Periods:
#define CAROUSEL_TIMEFOREACH 50
#define INIT_TIMEOUT_MIN     3500
#define INIT_TIMEOUT_MAX     10000

// Globals
int button1State = 0;
int button2State = 0;

// Protos:
void carousel(int times);
void __init();

// Setup:
void setup()
{
    randomSeed(analogRead(0));

    pinMode(GREEN, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(YELLOW1, OUTPUT);
    pinMode(YELLOW2, OUTPUT);
    pinMode(YELLOW3, OUTPUT);
    pinMode(YELLOW4, OUTPUT);
    pinMode(WHITE, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);

    carousel(2);
    __init();

    on(GREEN);
}

// Helpers:
void on(uint8_t pin){
    digitalWrite(pin, HIGH);
}

void off(uint8_t pin){
    digitalWrite(pin, LOW);
}

void onOff(uint8_t pin, int period){
    on(pin);
    delay(period);
    off(pin);
}

void onOffDouble(uint8_t pin1, uint8_t pin2, int period){
    on(pin1);
    on(pin2);
    delay(period);
    off(pin1);
    off(pin2);
}

// Routines:
void carousel(int times){
    for (int iter=0; iter<times; ++iter){
        onOff(GREEN, CAROUSEL_TIMEFOREACH);
        onOff(RED, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW1, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW2, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW3, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW4, CAROUSEL_TIMEFOREACH);
        onOff(WHITE, CAROUSEL_TIMEFOREACH);
        onOff(BLUE, CAROUSEL_TIMEFOREACH);
        //----------------------------------
        onOff(BLUE, CAROUSEL_TIMEFOREACH);
        onOff(WHITE, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW4, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW3, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW2, CAROUSEL_TIMEFOREACH);
        onOff(YELLOW1, CAROUSEL_TIMEFOREACH);
        onOff(RED, CAROUSEL_TIMEFOREACH);
        onOff(GREEN, CAROUSEL_TIMEFOREACH);
    }
}

void __init(){
    on(YELLOW1);
    on(YELLOW2);
    on(YELLOW3);
    on(YELLOW4);
    delay(random(INIT_TIMEOUT_MIN, INIT_TIMEOUT_MAX+1));
    off(YELLOW1);
    off(YELLOW2);
    off(YELLOW3);
    off(YELLOW4);
}

// Fake link blinks
void linkBlink() {
    int firstLed = int(random(YELLOW1, YELLOW4+1));
    int secondLed = int(random(YELLOW1, YELLOW4+1));
    while (secondLed == firstLed) {
        secondLed = int(random(YELLOW1, YELLOW4+1));
    }

    off(GREEN);
    off(RED);
    
    for(int blink=0; blink<int(random(200, 300)); ++blink) {
        on(firstLed);
        delay(random(1, 5));
        off(secondLed);
        delay(random(1, 50));
        on(secondLed);
        delay(random(1, 5));
        off(firstLed);
        delay(random(1, 50));
    }

    off(firstLed);
    off(secondLed);
    on(int(random(GREEN, RED+1)));
}

// Outward carousel
void outvardCarousel(int times) {
    for (int iter=0; iter<times; ++iter){
        onOffDouble(YELLOW2, YELLOW3, CAROUSEL_TIMEFOREACH);
        onOffDouble(YELLOW1, YELLOW4, CAROUSEL_TIMEFOREACH);
        onOffDouble(RED, WHITE, CAROUSEL_TIMEFOREACH);
        onOffDouble(GREEN, BLUE, CAROUSEL_TIMEFOREACH);
        //--------------------------------------------------
        onOffDouble(GREEN, BLUE, CAROUSEL_TIMEFOREACH);
        onOffDouble(RED, WHITE, CAROUSEL_TIMEFOREACH);
        onOffDouble(YELLOW1, YELLOW4, CAROUSEL_TIMEFOREACH);
        onOffDouble(YELLOW2, YELLOW3, CAROUSEL_TIMEFOREACH);
    }
}

void handleButton1Press(){
    linkBlink();
}

void handleButton2Press(){
    const uint8_t nrOfRoutines = 2; // <-- Change if more routines are added

    int whatRoutine = int(random(1, nrOfRoutines+1));
    off(GREEN);
    off(RED);

    switch(whatRoutine){
        case(1):
            // Show carousel 1-4 times
            carousel(int(random(1, 5)));
            break;
        case(2):
            outvardCarousel(int(random(5, 10)));
            break;
        default:
            break;
    }

    on(int(random(GREEN, RED+1)));
}


// Main loop
void loop()
{
    // Read button state:
    button1State = digitalRead(BUTTON1);
    button2State = digitalRead(BUTTON2);

    // Handle presses:
    if(button1State == 0) handleButton1Press();
    if(button2State == 0) handleButton2Press();
}
