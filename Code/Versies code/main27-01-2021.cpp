#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "ASUS1424";//type your ssid
const char* password = "MaJaNe14245.";//type your password
String STATE = "STOP";

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

//char value[16] = "STOP"; 

//int trigPinUltra = 9;
//int echoPinUltra = 10;
long tijdUltra;
int afstandUltra;

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
const int trigPinUltra = D10;
//const int echoPinUltra = A0;
//echoPinUltra = GPIO 10 / 10

void stop();
void forwards();
void backwards();
void rightOnSpot();
void leftOnSpot();
//long ultrasonic();

ICACHE_RAM_ATTR void rightIr(){
    Serial.println("DANGER! RIGHT IR!");
    stop();
    delay(200);
    backwards();
    delay(1000);
    leftOnSpot();
    delay(500);
    stop();
    return;
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
              //pinMode(10, INPUT); // Sets the echoPin as an Input
              //pinMode(11, OUTPUT); // Sets the trigPin as an Output
 
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
              //pinMode(trigPinUltra, OUTPUT); // Sets the trigPin as an Output

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

long ultrasonic() {
    // Clears the trigPin condition
    digitalWrite(trigPinUltra, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinUltra, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinUltra, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    int duration = pulseIn(10, HIGH);
    // Calculating the distance
    long distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
}

void printwebserver(int value, WiFiClient client) {
    client.flush();

if (client) {                             // If a new client connects,
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
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>Rescue Car status: " + STATE + "</p>");
            // If the output5State is off, it displays the ON button       
            //if (STATE=="STOP") {
              client.println("<p><a href=\"FORWARDS\"><button class=\"button\">FORWARDS</button></a></p>");
            //} else {
              client.println("<p><a href=\"STOP\"><button class=\"button button2\">STOP</button></a></p>");
            //} 

            // If the output4State is off, it displays the ON button       
            //if (STATE=="STOP") {
              client.println("<p><a href=\"BACKWARDS\"><button class=\"button\">BACKWARDS</button></a></p>");
            //} else {
            //  client.println("<p><a href=\"STOP\"><button class=\"button button2\">OFF</button></a></p>");
            //}
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

    /*
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
    */
   /*
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS to style the on/off buttons 
    // Feel free to change the background-color and font-size attributes to fit your preferences
    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    client.println(".button2 {background-color: #77878A;}</style></head>");
            
    // Web Page Heading
    client.println("<body><h1>Rescue Car Web Server</h1>");


    // Display current state, and ON/OFF buttons for GPIO 5  
            //client.println("<p>STATE=" + value + "</p>");
            // If the output5State is off, it displays the ON button       
            if (value==1) {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            // Display current state, and ON/OFF buttons for GPIO 4  
            //client.println("<p>GPIO 4 - State " + ouput4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (value==0) {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
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
*/
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
    int tijd = 1000;
    if (request.indexOf("FORWARDS") != -1) {
        value = 1;
        printwebserver(value, client);
        forwards();
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

    /*if (request.indexOf("SELFDRIVE") != -1){
        long selfdriveX = 1;
        //val = analogRead(analogPin);
        while(selfdriveX == 1) {
            forwards();
            delay(500);
            selfdriveX = ultrasonic();
        }
    }*/
    /*
    int x = digitalRead(interruptRight);

    Serial.println(x);
    */
      delay(200);
}