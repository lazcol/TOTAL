#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>

/*char ssid[] = "Infiniem";
char key[] = "ladesiempre";*/
char ssid[] = "Guadalupe";
char key[] = "laconchadetuputamadre24";
int keyIndex = 0;
int status = WL_IDLE_STATUS;

void printMacAddress(byte mac[]);
void printCurrentNet();
void printWiFiData();
void printCurrentNet();
void printWiFiData(); 

WiFiClass client;

void setup()
{
  Serial.begin(BAUDIOS);
  while (!Serial);
  if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println("WiFi 101 Shield not present");
    while (true);
  }

  while ( status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to WEP network, SSID: ");
    Serial.println(ssid);
    //status = WiFi.begin(ssid, keyIndex, key);
    status = WiFi.begin(ssid, key);
    delay(10000);
  }

  Serial.print("You're connected to the network");
  printCurrentNet();
  printWiFiData();
}

void loop() 
{
  delay(10000);
  printCurrentNet();
}

void printWiFiData() 
{
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) 
{
  for (int i = 5; i >= 0; i--) 
  {
    if (mac[i] < 16) 
    {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) 
    {
      Serial.print(":");
    }
  }
  Serial.println();
}
