#include <Arduino.h>

const int frontRight1 = D0;
const int frontRight2 = D1;
const int frontLeft1 = D2;
const int frontLeft2 = D3;
const int rearRight1 = D4;
const int rearRight2 = D5;
const int interruptLeft = D6;
const int rearLeft1 = D7;
const int rearLeft2 = D8;
const int interruptRight = D9;

//void rightIr();

/**/
ICACHE_RAM_ATTR void rightIr(){
    Serial.println("DANGER! RIGHT!");
}

ICACHE_RAM_ATTR void leftIr(){
    Serial.println("DANGER! RIGHT!");
}



void setup()
{
    Serial.begin(115200);

    pinMode(frontRight1, OUTPUT);
    pinMode(frontRight2, OUTPUT);
    pinMode(frontLeft1, OUTPUT);
    pinMode(frontLeft2, OUTPUT);
    pinMode(rearRight1, OUTPUT);
    pinMode(rearRight2, OUTPUT);
    pinMode(rearLeft1, OUTPUT);
    pinMode(rearLeft2, OUTPUT);
    pinMode(interruptRight, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptRight), rightIr, FALLING);
    pinMode(interruptLeft, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptLeft), leftIr, FALLING);
}



/*
forwards \/
backwards \/
right
left
rightOnSpot \/
leftOnSpot \/
*/

void forwards()
{
    digitalWrite(frontRight1, HIGH);
    digitalWrite(frontLeft1, HIGH);
    digitalWrite(rearRight1, HIGH);
    digitalWrite(rearLeft1, HIGH);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft2, LOW);
    digitalWrite(rearRight2, LOW);
    digitalWrite(rearLeft2, LOW);
    Serial.println("Froward");
}
void backwards(){
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontLeft1, LOW);
    digitalWrite(rearRight1, LOW);
    digitalWrite(rearLeft1, LOW);
    digitalWrite(frontRight2, HIGH);
    digitalWrite(frontLeft2, HIGH);
    digitalWrite(rearRight2, HIGH);
    digitalWrite(rearLeft2, HIGH);
    Serial.println("Backwards");
}
void rightOnSpot(){
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontLeft1, HIGH);
    digitalWrite(rearRight1, LOW);
    digitalWrite(rearLeft1, HIGH);
    digitalWrite(frontRight2, HIGH);
    digitalWrite(frontLeft2, LOW);
    digitalWrite(rearRight2, HIGH);
    digitalWrite(rearLeft2, LOW);
    Serial.println("SPINNING RIGHT");   
}
void leftOnSpot(){
    digitalWrite(frontRight1, HIGH);
    digitalWrite(frontLeft1, LOW);
    digitalWrite(rearRight1, HIGH);
    digitalWrite(rearLeft1, LOW);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft2, HIGH);
    digitalWrite(rearRight2, LOW);
    digitalWrite(rearLeft2, HIGH);
    Serial.println("SPINNING LEFT"); 

}

void loop()
{

   
    forwards();
    delay(2000);
    backwards();
    delay(2000);
    rightOnSpot();
    delay(2000);
    leftOnSpot();
    delay(2000);
    
 /*
   int x = digitalRead(interruptRight);

   Serial.println(x);
   */
   delay(200);
}
