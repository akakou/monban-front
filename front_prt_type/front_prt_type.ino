#include <WiFi.h>
#include <WiFiUDP.h>

int pir = 35;

const char* ssid     = "";
const char* password = "";
static WiFiUDP wifiUdp; 

void setup()
{
    pinMode(pir, INPUT);
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}


IPAddress ip;
String a,b,c,d;
void loop()
{
  if(digitalRead(pir)){
    Serial.println("ON");
    delay(500);
    // print your subnet mask:
    ip = WiFi.localIP();
    a = ip[0];
    b = ip[1];
    c = ip[2];
    d = a + '.' + b + '.' + c + '.' + "255";
    Serial.println(d);
    int d_length = d.length()+1;
    char IP[d_length];
    d.toCharArray(IP,d_length);
    wifiUdp.beginPacket(IP,5000); 
    wifiUdp.write('1');
    wifiUdp.endPacket();  
  }else{
    Serial.println("Off");
    }
    Serial.println("END");
    delay(5000);
}
