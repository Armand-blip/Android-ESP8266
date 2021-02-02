/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
#include <ESP8266WiFi.h>



//Static IP address configuration
IPAddress staticIP(192, 168, 68, 88); //ESP static ip
IPAddress gateway(192, 168, 68, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
String header;
int m_index;
int m_Status;

char m_chr[4];
char ssid[] = "Ramel Dipendenti";     // your network SSID (name)
char password[] = "GigaTeam44RML"; // your network key
// Set web server port number to 80
WiFiServer server(80);

const int ledPin =  LED_BUILTIN;       
unsigned long previousMillis_Up = 0;  
unsigned long previousMillis_Down = 0;
const long interval = 300;
int buttonpushcounter=0;
int lastbuttonstate=0;

void setup() {

  m_Status=0;
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(2, OUTPUT);
  // Set outputs to LOW

  digitalWrite(2, LOW);
  
  delay(1000);
  Serial.println("Avvio sistema");
  delay(1000);
  
  // Set WiFi to station mode and disconnect from an AP if it was Previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  //client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();  //Tell the server to begin listening for incoming connections
}

// the loop function runs over and over again forever
void loop() {

 WiFiClient client = server.available();   // Listen for incoming clients
 if (client) 
 { // If a new client connects,
   
   Serial.println("New Client.");          // print a message out in the serial port
  
   
   
   while (client.connected()) {
       unsigned long currentMillis_Up = millis();
       unsigned long currentMillis_Down = millis();
       if (client.available()) 
       {
        char c = client.read();
        client.print(c);
        Serial.write(c);
        m_chr [m_index]=c;
        m_index++;
          /*if (c=='1') {
          digitalWrite(2, LOW);}
          else if (c=='0') {
          digitalWrite(2, HIGH);*/
        }
        else 
        {
        m_index=0;
        m_chr [0] = 0;
        m_chr [1] = 0;
        m_chr [2] = 0;
        m_chr [3] = 0;
        }

        //Logica Led
        m_Status=0;
        if((m_chr [0]=='U')&&(m_chr [1]=='P')){
          m_Status=1; 
          //Serial.println("UP");
          }
        else if ((m_chr [0]=='D')&&(m_chr [1]=='O')&&(m_chr [2]=='W')&&(m_chr [3]=='N'))
          {
          m_Status=-1;
          //Serial.println("DOWN");
          }
        
       

        //led UP(comando UP)
        // if the LED is off turn it on and vice-versa:
        if (m_Status==1) 
          previousMillis_Up = currentMillis_Up;
        //Serial.println(m_Status);
        if (currentMillis_Up - previousMillis_Up <= interval)
          digitalWrite(ledPin, LOW);
        else 
          digitalWrite(ledPin, HIGH);

        
        

         
           //if (m_Status==-1 )
           
           //previousMillis_Down = currentMillis_Down;
           
           // if (currentMillis_Down - previousMillis_Down <= interval)
           //digitalWrite(ledPin, LOW);
           //else 
           ///digitalWrite(ledPin, HIGH);//
   } // while client.connected 
      
      
    
   digitalWrite(ledPin, HIGH);
   // if the server's disconnected, stop the client:
   if (!client.connected()) {
   Serial.println();
   Serial.println("disconnecting.");
   client.stop();
  }    
    delay(10);
 }
 
    client.stop();
    Serial.println("Client disconnected");
 
 
} //
