/*
 * Adaptado por Miguel Alonso Abella en Abril 2021 
 * Control para puerta garaje
 *  
 * D5--> Boton - equivalente al botón ya instalado en la puerta
 * D6--> Rele pulso para abir/cerrar  puerta
 * D7 --> Rele para dar alimentación al motor
 * D8-->
 */



//#define DEBUG   //If you comment this line, the DPRINT & DPRINTLN lines are defined as blank.
#ifdef DEBUG    //Macros are usually in all capital letters.
  #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
  #define DPRINT(...)     //now defines a blank line
  #define DPRINTLN(...)   //now defines a blank line
#endif

#define CONFIG_VERSION "v01"
#define CONFIG_START 0

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
//#include <DHT.h>
#include <FS.h>
#include <ArduinoJson.h>  
#include <DNSServer.h>
#include <WiFiManager.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h> //para mqtt
#include <math.h>
//#include <SunPos.h> //Sunpos de la plataforma solar de Almería
#include <spa.h>    //spa del NREL

#include "variables.h" 
#include "PuertaStepper.h"  
#include "ESP8266_Utils_OTA.hpp"
#include <ESP8266mDNS.h>

#include <Espalexa.h>
//callback functions
void puertaChanged(uint8_t brightness);
Espalexa espalexa;

//mqtt
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  setupConfig();
  setup_mqtt();
  server.on("/tabmesures.json", sendTabMesures);
  server.on("/mesures.json", sendMesures);
  server.on("/gpio", updateGpio);
  server.on("/readgpio.json", sendGPIO);
  server.on("/hora.json", sendTime);
  server.on("/sendDataTimers.json", sendDataTimers);
  server.on("/sendDataConf.json", sendDataConf);
  server.on("/save", save);
  server.on("/savemode", savemode);
  server.on("/saveconfig", saveconfig_http);
  server.on("/savePH", savePH);

  server.serveStatic("/js", SPIFFS, "/js");
  server.serveStatic("/css", SPIFFS, "/css");
  server.serveStatic("/img", SPIFFS, "/img");
  server.serveStatic("/html", SPIFFS, "/html");
  server.serveStatic("/", SPIFFS, "/index.html");
  alexasetup();
  //server.begin(); //omit this since it will be done by espalexa.begin(&server)
  Serial.println ( "HTTP server started" );
  InitOTA();
  
}

void loop() {
      //server.handleClient() //you can omit this line from your code since it will be called in espalexa.loop()
      espalexa.loop();
   
      PuertaServoWeb();
      CheckNTPtime();
      server_read();
      horasolar();
      
      //sendThinkspeak();
     
      ArduinoOTA.handle();
      check_wifi();
     
      sendtoemoncms();
      leer_boton();
      for (j=0;j<Num_reles;j++){controlTimers(j);}
      yield();
      
      //mqtt
      if (!client.connected()) {
        reconect();
      }
      client.loop();
      publicar_mqtt();

      if(abriendo_puerta){Abrirpuerta(t_accionamiento);}
      if(cerrando_puerta){Cerrarpuerta(t_accionamiento);}
 
  }
