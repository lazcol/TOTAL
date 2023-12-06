#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>
#include <ThingSpeak.h>

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

WiFiClient client;

/* ThingSpeak: datos para conexión, escritura y lectura */
String thingSpeakAPI = "api.thingspeak.com";    /* dir de la Api */
unsigned long myChannelNumber = 2361691;        /* número de canal */
const char *myWriteAPIKey = "4OWTBZB8H76R44B6"; /* habilita la escritura */

/* Timer variables */
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

/* 4 variables para hacer un dashboard con 4 charts */
int tem; /* variable del 1er chart */
int pre; /* variable del 2do chart */
int hum; /* variable del 3er chart */
int lux; /* variable del 4to chart */

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
    Serial.print("resultado conex ThingSpeak: ");
    Serial.println(ThingSpeak.begin(client));   /* Se establece conexión a la página de ThingSpeak */
}

void loop() 
{
    if((millis() - lastTime) > timerDelay)
    {
        /* Si se desconecta: que se conecte de nuevo */
        if(WiFi.status() != WL_CONNECTED)
        {
            Serial.print("Intentanco conectar a: ");
            Serial.print(ssid);
            while(status != WL_CONNECTED)
            {
                WiFi.begin(ssid, key);
                delay(3500);
            }
            Serial.println("\nConectado");
            printCurrentNet();
            Serial.print("resultado conex ThingSpeak: ");
            Serial.println(ThingSpeak.begin(client));   /* Se establece conexión a la página de ThingSpeak */
        }
        delay(10000);
        tem = 57.5;
        /* Se prepara el vector que será escrito en */
        ThingSpeak.setField(1, tem); /* 1er gráfico */
        /* ThingSpeak.setField(2, hum);*/ /* 2do gráfico */
        /* ThingSpeak.setField(3, pre);*/ /* 3er gráfico */
        /* ThingSpeak.setField(4, lux);*/ /* 4to gráfico */
        /* Escribe en la página con el código de autorización myWriteAPIKey */
        int x = ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
        Serial.print("Resultado de la función: ");
        Serial.println(x);
        if(x == 200) { Serial.println("Canal Actualizado Correctamente."); }
        else
        {
            Serial.println("Problemas con la actualización. Código de error HTTP " + String(x));
            Serial.print("Intentando conectar a ThingSpeak: ");
            Serial.println(ThingSpeak.begin(client));
        }
        lastTime = millis();
    }
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
