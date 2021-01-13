#include <ESP8266WiFi.h>

const char* ssid = "VielvoyeResidence24Ghz";//type your ssid
const char* password = "J3S1GH5F";//type your password

//int trigPinUltra = 9;
//int echoPinUltra = 10;
//long tijdUltra;
//int afstandUltra;

const int frontRight1 = 16; //D0
const int frontRight2 = 05;//D1
const int frontLeft1 = 04;//D2
const int frontLeft2 = 00;//D3
const int rearRight1 = 02;//D4
const int rearRight2 = 14;//D5
const int interruptLeft = 12;//D6
const int rearLeft1 = 13;//D7
const int rearLeft2 = 15;//D8
const int interruptRight = 03;//D9

//void rightIr();

/**/
ICACHE_RAM_ATTR void rightIr(){
    Serial.println("DANGER! RIGHT!");
}

ICACHE_RAM_ATTR void leftIr(){
    Serial.println("DANGER! RIGHT!");
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

int value = LOW;
if (request.indexOf("/MOTOR1=ON") != -1) {
digitalWrite(frontRight1, HIGH);
value = HIGH;
} 
if (request.indexOf("/MOTOR1=OFF") != -1){
digitalWrite(frontRight1, LOW);
value = LOW;
}

//Set ledPin according to the request
digitalWrite(frontRight1, value);

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("frontRight1 is now: ");

if(value == HIGH) {
client.print("On");  
} else {
client.print("Off");
}
client.println("<br><br>");
client.println("Click <a href=\"/frontRight1=ON\">here</a> to turn motor1 on pin 2 ON<br>");
client.println("Click <a href=\"/frontRight1=OFF\">here</a> to turn motor1 on pin 2 OFF<br>");
client.println("</html>");

delay(1);
Serial.println("Client disconnected");
Serial.println("");

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
