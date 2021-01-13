#include <ESP8266WiFi.h>

const char* ssid = "VielvoyeResidence24Ghz";//type your ssid
const char* password = "J3S1GH5F";//type your password

//int trigPinUltra = 9;
//int echoPinUltra = 10;
int motor1 = 8;
int motor2 = 3;
int motor3 = 4;
int motor4 = 5;
//long tijdUltra;
//int afstandUltra;

WiFiServer server(80);//Service Port

void setup() {
Serial.begin(115200);
delay(10);

//pinMode(trigPinUltra, OUTPUT); // Sets the trigPin as an Output
//pinMode(echoPinUltra, INPUT); // Sets the echoPin as an Input

pinMode(motor1, OUTPUT);
pinMode(motor2, OUTPUT);
pinMode(motor3, OUTPUT);
pinMode(motor4, OUTPUT);
digitalWrite(motor1, LOW);
digitalWrite(motor2, LOW);
digitalWrite(motor3, LOW);
digitalWrite(motor4, LOW);

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
digitalWrite(motor1, HIGH);
value = HIGH;
} 
if (request.indexOf("/MOTOR1=OFF") != -1){
digitalWrite(motor1, LOW);
value = LOW;
}

//Set ledPin according to the request
digitalWrite(motor1, value);

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("motor1 is now: ");

if(value == HIGH) {
client.print("On");  
} else {
client.print("Off");
}
client.println("<br><br>");
client.println("Click <a href=\"/MOTOR1=ON\">here</a> to turn motor1 on pin 2 ON<br>");
client.println("Click <a href=\"/MOTOR1=OFF\">here</a> to turn motor1 on pin 2 OFF<br>");
client.println("</html>");

delay(1);
Serial.println("Client disconnected");
Serial.println("");
}