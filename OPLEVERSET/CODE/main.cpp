#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "LaptopieVanSander";//ssid / name Wifi
const char* password = "KrijgsheerSander";//Wifi password
String STATE = "STOP";

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

//Ultrasonic variables
long duration;
int distance;
int CountUltrasonic;

//Pins
const int frontRight1 = D0;
const int frontRight2 = D1;
const int frontLeft1 = D2;
const int frontLeft2 = D3;
const int interruptLeft = D6;
const int interruptRight = D5;
const int trigPinUltra = D7;
const int echoPinUltra = D4;
const int reedSensor = D8;

//IR
bool automaticDrive = false;
bool interruptRightCheck = false;
bool interruptLeftCheck = false;

void stop();
void forwards();
void backwards();
void rightOnSpot();
void leftOnSpot();

WiFiServer server(80);//Service Port

void setup() {
              Serial.begin(115200);
              delay(10);

              pinMode(trigPinUltra, OUTPUT); // Sets the trigPin as an Output
              pinMode(frontRight1, OUTPUT);
              pinMode(frontRight2, OUTPUT);
              pinMode(frontLeft1, OUTPUT);
              pinMode(frontLeft2, OUTPUT);
              pinMode(interruptRight, INPUT);
              pinMode(interruptLeft, INPUT);
              pinMode(trigPinUltra, OUTPUT); // Sets the trigPin as an Output
              pinMode(reedSensor, INPUT);

              // Connect to WiFi network
              Serial.println();
              Serial.println();
              Serial.print("Connecting to2 ");
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

void forwards() {
    digitalWrite(frontRight1, HIGH);
    digitalWrite(frontLeft1, HIGH);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft2, LOW);
    Serial.println("Forwards");
}
void backwards() {
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontLeft1, LOW);
    digitalWrite(frontRight2, HIGH);
    digitalWrite(frontLeft2, HIGH);
    Serial.println("Backwards");
}
void rightOnSpot() {
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontLeft1, HIGH);
    digitalWrite(frontRight2, HIGH);
    digitalWrite(frontLeft2, LOW);
    Serial.println("SPINNING RIGHT");   
}
void leftOnSpot() {
    digitalWrite(frontRight1, HIGH);
    digitalWrite(frontLeft1, LOW);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft2, HIGH);
    Serial.println("SPINNING LEFT"); 
}
void stop() {
    digitalWrite(frontRight1, LOW);
    digitalWrite(frontLeft1, LOW);
    digitalWrite(frontRight2, LOW);
    digitalWrite(frontLeft2, LOW);
    Serial.println("stop");
}

void endturn(){
    stop();
    delay(200);
    rightOnSpot();
    delay(600);
    return;
}

void rightLine(){   // to move off the line on the right                    
    Serial.println("DANGER! RIGHT IR!");
    stop();
    delay(100);
    leftOnSpot();
    delay(300);
    stop();
    interruptRightCheck = false;
}

void leftLine(){    // to move off the line on the left                  
    Serial.println("DANGER! LEFT IR!");
    stop();
    delay(100);
    rightOnSpot();
    delay(300);
    stop();
    interruptLeftCheck = false;
}


long ultrasonic() {
    int OUTCOME = 1;
    
    // Clears the trigPin condition
    digitalWrite(trigPinUltra, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinUltra, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinUltra, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPinUltra, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    //Serial.print("Distance: ");
    //Serial.print(distance);
    //Serial.println(" cm");
    if (distance > 5) {
      OUTCOME = 1;
    }
    if (distance <= 5) {
      OUTCOME = 0;
    }
    return OUTCOME;
}

void printwebserver(int value, WiFiClient client) {
    client.flush();

if (client) {                               // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            client.println("<p><a href=\"FORWARDS\"><button class=\"button\">FORWARDS</button></a></p>");
            client.println("<p><a href=\"BACKWARDS\"><button class=\"button\">BACKWARDS</button></a></p>");
            client.println("<p><a href=\"RIGHTONSPOT\"><button class=\"button\">RIGHT TURN</button></a></p>");
            client.println("<p><a href=\"LEFTONSPOT\"><button class=\"button\">LEFT TURN</button></a></p>");
            client.println("<p><a href=\"TESTRIDE\"><button class=\"button\">TEST DRIVE</button></a></p>");
            client.println("<p><a href=\"STOP\"><button class=\"button button2\">STOP</button></a></p>");
            client.println("<p><a href=\"SELFDRIVE\"><button class=\"button button2\">ACTIVATE SELFDRIVE</button></a></p>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            delay(500);
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void loop() {

  if (automaticDrive == true) {
      forwards();
      if (ultrasonic() == 0) {
        if(CountUltrasonic == 0) {
          stop();
          delay(100);
          backwards();
          delay(700);
          stop();
          delay(100);
          leftOnSpot();
          delay(1500);
          forwards();
        }
        if(CountUltrasonic == 1) {
          stop();
          delay(100);
          backwards();
          delay(700);
          stop();
          delay(100);
          rightOnSpot();
          delay(1500);
          forwards();
          CountUltrasonic = 0;
        }
        if(CountUltrasonic == 0) {
          CountUltrasonic = 1;
        }
      }
      if(digitalRead(interruptLeft) == 1 && digitalRead(interruptRight) == 1){
        Serial.print("both activated");
        endturn();
      }
      if(digitalRead (interruptLeft) == 1) {
        Serial.println("LeftIR");
        leftLine();
        forwards();
      }
      if(digitalRead (interruptRight) == 1) {
        Serial.println("RightIR");
        rightLine();
        forwards();
      }

      if(digitalRead (reedSensor) == 1) {
        Serial.println("Person detected!");
        stop();
        delay(5000);
        forwards();
      }
  }

    WiFiClient client = server.available();
    if (!client) {
      return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    if(automaticDrive != true){
      while(!client.available()){
          delay(1);
      }
    }
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    

    // Match the request
    int value = 0;
    int tijd = 1000;
    if (request.indexOf("FORWARDS") != -1) {
        forwards();
        value = 1;
        printwebserver(value, client);
        delay(tijd);
        stop();
        value = 0;
    } 
    if (request.indexOf("BACKWARDS") != -1){
        backwards();
        value = 1;
        printwebserver(value, client);
        delay(tijd);
        stop();
        value = 0;
    }
    if (request.indexOf("RIGHTONSPOT") != -1) {
        rightOnSpot();
        value = 1;
        printwebserver(value, client);
        delay(tijd);
        stop();
        value = 0;
    }
    if (request.indexOf("LEFTONSPOT") != -1){
        leftOnSpot();
        value = 1;
        printwebserver(value, client);
        delay(tijd);
        stop();
        value = 0;
    }

    if (request.indexOf("STOP") != -1){
        stop();
        automaticDrive = false;
        value = 0;
        printwebserver(value, client);
    }

    // Return the response
    printwebserver(value, client);

    if (request.indexOf("TESTRIDE") != -1){
        Serial.println("Testdrive activated");
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

    if (request.indexOf("SELFDRIVE") != -1){
        Serial.println("Selfdrive activated");
        automaticDrive = true;
    } 
}