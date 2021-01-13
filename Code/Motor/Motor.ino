//L293D
//Motor A
const int frontRight1  = 2;  // Pin 14 of L293
const int frontRight2  = 3;  // Pin 10 of L293
const int frontLeft1  = 4;  // Pin 14 of L293
const int frontLeft2  = 5;  // Pin 10 of L293
const int rearRight1  = 6;  // Pin 14 of L293
const int rearRight2  = 7;  // Pin 10 of L293
const int rearLeft1  = 8;  // Pin 14 of L293
const int rearLeft2  = 9;  // Pin 10 of L293

//This will run only one time.
void setup(){
 
    //Set pins as outputs for the motors
    pinMode(frontRight1, OUTPUT);
    pinMode(frontRight2, OUTPUT);
    pinMode(frontLeft1, OUTPUT);
    pinMode(frontLeft2, OUTPUT);
    pinMode(rearRight1, OUTPUT);
    pinMode(rearRight2, OUTPUT);
    pinMode(rearLeft1, OUTPUT);
    pinMode(rearLeft2, OUTPUT);

}


void loop(){
  //This code  will turn Motor A clockwise for 2 sec.
    digitalWrite(frontRight1, HIGH);
    digitalWrite(frontRight2, LOW);
    delay(2000); 
    //This code will turn Motor A counter-clockwise for 2 sec.
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontRight2, HIGH);
    delay(2000);

}
