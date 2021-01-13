//L293D
//Motor A
const int frontRight1  = D2; 
const int frontRight2  = D3;  
const int frontLeft1  = D4; 
const int frontLeft2  = D5;  
const int rearRight1  = 6; 
const int rearRight2  = 7; 
const int rearLeft1  = 8;  
const int rearLeft2  = 9;  

const int interruptPin01 = 11; 
const int interruptPin02 = 10; 

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


    //Set interrupts for the IR sensors
    //pinMode(interruptPin01, INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(interruptPint01), rightIR, FALLING);
    //pinMode(interruptPin02, INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(interruptPint02), leftIR, FALLING);

}
/*
void rightIR(){
    //left wheel forward power, right wheel reverse.
    //all wheels reverse
    //right wheel front power, left wheel reverse.
    //continue straight.

    digitalWrite(frontLeft1, HIGH);
    digitalWrite(fronleft2, LOW);
    digitalWrite(rearLeft1, HIGH);
    digitalWrite(rearLeft2, LOW);
    
}

void leftIR(){
    //right wheel no power, left wheel reverse.
    //all wheels reverse
    //left wheel no power, right wheel no power
    //continue straight
}
*/
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
