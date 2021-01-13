const int interruptPin01 = 11; 
const int interruptPin02 = 10; 


void setup() {
    // put your setup code here, to run once:
    pinMode(interruptPin01, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin01), rightIR, FALLING);
    pinMode(interruptPin02, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin02), leftIR, FALLING);
}

void rightIR(){
    //left wheel no power, right wheel reverse.
    //all wheels reverse
    //right wheel no power, left wheel reverse.
    //continue straight.
    
}

void leftIR(){
    //right wheel no power, left wheel reverse.
    //all wheels reverse
    //left wheel no power, right wheel no power
    //continue straight

    
}


void loop() {
    // put your main code here, to run repeatedly:

}
