#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "LaptopieVanSander";//type your ssid
const char* password = "KrijgsheerSander";//type your password
//char value[16] = "STOP"; 

//int trigPinUltra = 9;
//int echoPinUltra = 10;
//long tijdUltra;
//int afstandUltra;

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

ICACHE_RAM_ATTR void rightIr(){
    Serial.println("DANGER! RIGHT!");
    //stop();
}

ICACHE_RAM_ATTR void leftIr(){
    Serial.println("DANGER! RIGHT!");
    //stop();
}

WiFiServer server(80);//Service Port

void setup() {
              Serial.begin(115200);
              delay(10);

              //pinMode(trigPinUltra, OUTPUT); // Sets the trigPin as an Output
              //pinMode(echoPinUltra, INPUT); // Sets the echoPin as an Input

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

              // Connect to WiFi network
              Serial.println();
              Serial.println();
              Serial.print("Connecting to ");
              Serial.println(ssid);

              WiFi.begin(ssid, password);

              while (WiFi.status() != WL_CONNECTED) {
                  delay(500);
                  Serial.print(".");
              }
              Serial.println("");
              Serial.println("WiFi connected");

              // Start the server
              server.begin();
              Serial.println("Server started");

              // Print the IP address
              Serial.print("Use this URL to connect: ");
              Serial.print("http://");
              Serial.print(WiFi.localIP());
              Serial.println("/");
              }

/*
forwards \/
backwards \/
right
left
rightOnSpot \/
leftOnSpot \/
*/

void forwards() {
    digitalWrite(frontRight1, HIGH);
    digitalWrite(frontLeft1, HIGH);
    digitalWrite(rearRight1, HIGH);
    digitalWrite(rearLeft1, HIGH);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft2, LOW);
    digitalWrite(rearRight2, LOW);
    digitalWrite(rearLeft2, LOW);
    Serial.println("Forwards");
}
void backwards() {
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
void rightOnSpot() {
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
void leftOnSpot() {
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
void stop() {
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontLeft1, LOW);
    digitalWrite(rearRight1, LOW);
    digitalWrite(rearLeft1, LOW);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft2, LOW);
    digitalWrite(rearRight2, LOW);
    digitalWrite(rearLeft2, LOW);
    Serial.println("stop");
}

void printwebserver(int value, WiFiClient client) {
    client.flush();

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    client.print("frontRight1 is now: ");

    if(value == 1) {
    client.print("MOVING");
    } else {
    client.print("STOP");
    }

    client.println("<br><br>");
    client.println("Click <a href=\"FORWARDS\">here</a> to go forwards<br>");
    client.println("Click <a href=\"BACKWARDS\">here</a> to go backwards<br>");
    client.println("Click <a href=\"RIGHTONSPOT\">here</a> to turn right<br>");
    client.println("Click <a href=\"LEFTONSPOT\">here</a> to turn left<br>");
    client.println("Click <a href=\"TESTRIDE\">here</a> to do a full test drive<br>");
    client.println("Click <a href=\"STOP\">here</a> to stop<br>");
    client.println("</html>");
}

void loop() {
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()){
        delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Match the request
    int value = 0;
    if (request.indexOf("FORWARDS") != -1) {
        value = 1;
        printwebserver(value, client);
        forwards();
        delay(10000);
        stop();
        value = 0;
    } 
    if (request.indexOf("BACKWARDS") != -1){
        backwards();
        value = 1;
        printwebserver(value, client);
        delay(10000);
        stop();
        value = 0;
    }
    if (request.indexOf("RIGHTONSPOT") != -1) {
        rightOnSpot();
        value = 1;
        printwebserver(value, client);
        delay(10000);
        stop();
        value = 0;
    }
    if (request.indexOf("LEFTONSPOT") != -1){
        leftOnSpot();
        value = 1;
        printwebserver(value, client);
        delay(10000);
        stop();
        value = 0;
    }

    if (request.indexOf("STOP") != -1){
        stop();
        value = 0;
        printwebserver(value, client);
    }

    // Return the response
    printwebserver(value, client);

    if (request.indexOf("TESTRIDE") != -1){
        forwards();
        value = 1;
        printwebserver(value, client);
        delay(2000);
        backwards();
        delay(2000);
        rightOnSpot();
        delay(2000);
        leftOnSpot();
        delay(2000);
        stop();
        value = 0;
        printwebserver(value, client);
    }

    /*
    int x = digitalRead(interruptRight);

    Serial.println(x);
    */
      delay(200);
}