/*
Control led with arduino uno use shield ethernet.
By Ngoc Khanh IT 
EmaiL: ngockhanh111021994@gmail.com
Tel: 0166 3748 012
*/


//-------------------------------------------------------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = { 0x2C, 0x44, 0xFD, 0xFD, 0xAB, 0x0C };

// The IP address will be dependent on your local network:
// assign an IP address for the controller:

IPAddress ip(192,168,137,229);
IPAddress gateway(192,168,137,100);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(8090);

String readString;
int led = 8;

void setup()
{
pinMode(led, OUTPUT); //pin selected to control
  Serial.begin(9600);

  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("LED Controller Test 1.0");
}
//-------------------------------------------------------------------------------------------------------

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)

  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())

      {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100)

        {

          //store characters to string
          readString += c;
          //Serial.print(c);


          Serial.write(c);
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          //if HTTP request has ended
          if (c == '\n') {
            Serial.println(readString); //print to serial monitor for debuging
//--------------------------------------------------------------------------------------------------------
// Needed to Display Site:
client.println("HTTP/1.1 200 OK"); //send new page
            client.println("Content-Type: text/html");
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");

//--------------------------------------------------------------------------------------------------------
//-------------------------------------------------

// what is being Displayed :     
        
            client.println("<TITLE>Smart Home</TITLE>");
            client.println("<center>");
            client.println("</HEAD>");
            client.println("<BODY>");
            client.println("<H1>Home Automation By NgocKhanh IT</H1>");
            client.println("<hr />");
            client.println("<center>");

            client.println("<a href=\"/?on\"\">Turn On Light</a>");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?off\"\">Turn Off Light</a><br />");     
            client.println("<img src='http://smarthome.lgc.vn/wp-content/uploads/2014/10/energy-3d-house1.png'>");
            client.println("</BODY>");
            client.println("</HTML>");

            delay(1);
            //stopping client
            client.stop();

            //-------------------------------------------------
            // Code which needs to be Implemented:
            if(readString.indexOf("?on") >0)//checks for on
            {
              digitalWrite(8, HIGH);    // set pin 8 high
              Serial.println("Led On");
            }
            else{
              if(readString.indexOf("?off") >0)//checks for off
              {
                digitalWrite(8, LOW);    // set pin 8 low
                Serial.println("Led Off");
              }
            }
            //clearing string for next read
            readString="";

            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
            Serial.println("client disonnected");

          }
        }
      }
    }
  }
}
