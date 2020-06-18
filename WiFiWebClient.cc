/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using a WiFi shield.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the WiFi.begin() call accordingly.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 왕초보IoT메이커 풀잎스쿨
 by 서종원 3dkdkids4u@gmail.com
 */

#include <ArduinoJson.h>
#include <SPI.h>
#include <WiFi101.h>
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "api.openweathermap.org";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

//수정하기
int getInt(String input);
int val, temp;
float tempVal;
String rcvbuf;
boolean readingVal;
boolean getIsConnected = false;
unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 1000L; // delay between updates, in milliseconds

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /data/2.5/weather?q=seoul,korea&appid=47ecc0d7d94cb4cf0097b7a0d13234d7");
    client.println("Host: openweathermap.org");
    client.println("Connection: close");
    client.println();
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  // if there's incoming data from the net connection send it out the serial port
  // this is for debugging purposes only
  String valString;
  while (client.available()) {

    if ( rcvbuf.endsWith("\"temp\":")) {
      readingVal = true;
      valString = "";
    }

    char c = client.read();

    if ( c != NULL ) {
      if (rcvbuf.length() > 30)
        rcvbuf = "";
      rcvbuf += c;
      //Serial.write(c);
    }

    if (readingVal) {
      if (c != ',' ) {
        valString += c;
        //Serial.write(c);
      }
      else {
        readingVal = false;
        //Serial.println(valString);
        tempVal = valString.toFloat() - 273.0;
        Serial.println(tempVal);
      }
    }
  }
  if (millis() - lastConnectionTime > postingInterval) {
    
    if (getIsConnected) {
      Serial.println(valString);
      Serial.println(F("==================="));
      Serial.print(F("Temperature : "));
      Serial.println(tempVal);
      Serial.println(F("==================="));
    }
    //httpRequest();
  }
  rcvbuf = "";

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
