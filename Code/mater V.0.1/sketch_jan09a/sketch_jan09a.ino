//#define LED D1

const int frontRight1 = D2;
const int frontRight2 = D3;
const int frontLeft1 = D4;
const int frontLeft2 = D5;


void setup() {
    pinMode(frontRight1, OUTPUT);
    pinMode(frontRight2, OUTPUT);
    pinMode(frontLeft1, OUTPUT);
    pinMode(frontLeft2, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:

    digitalWrite(frontRight1, HIGH);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft1, HIGH);
    digitalWrite(frontLeft2, LOW);
    delay(2000);
    digitalWrite(frontRight2, HIGH);
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontLeft2, HIGH);
    digitalWrite(frontLeft1, LOW);
    delay(2000);
    

}
