int pin = 3;

void setup() {
  // initialize GPIO 2 as an output.
  pinMode(pin, OUTPUT);
  Serial.begin(115200);
  delay(10);
}
// the loop function runs over and over again forever
void loop() {
  Serial.println();
  Serial.println("Hallo");
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(3000);               // wait for a second
}
