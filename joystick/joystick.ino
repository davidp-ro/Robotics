#define Pin_RX 3
#define Pin_RY 2
#define Pin_LY 1
#define Pin_LX 0

void setup() {
    Serial.begin(9600);
}

/***************************************************************************/

void getData(int time_delay) {
    Serial.print("X-axis:    L: ");Serial.print(analogRead(Pin_LX));Serial.print("    R: ");Serial.print(analogRead(Pin_RX));
    Serial.print("\n");
    Serial.print("Y-axis:    L: ");Serial.print(analogRead(Pin_LY));Serial.print("    R: ");Serial.print(analogRead(Pin_RY));
    Serial.print("\n\n");
    delay(time_delay); 
}

void format_matplotlib(int time_delay) {
    Serial.print(analogRead(Pin_LX));Serial.print(",");Serial.print(analogRead(Pin_LY));
    Serial.print(".");
    Serial.print(analogRead(Pin_RX));Serial.print(",");Serial.print(analogRead(Pin_RY));
    Serial.print("\n");
    delay(time_delay); 
}

/***************************************************************************/

void loop() {
    //getData(500);
    format_matplotlib(100);
}
