#include <Adafruit_ADS1015.h>
#include <OneWire.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
float Cenit;
float mV_PH;
float To;
float mV_To;
float PH_ant;
float mV_PH_ant;
float To_ant;
boolean puerta_alta, puerta_baja, CO2_activado_timer;
boolean FC_abierta;
boolean FC_cerrada;



//**************************
//para openWheatherMap
//**************************
//#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>
//#include <TimeLib.h>

const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=Collado Villalba,es&&units=metric&APPID=";
//const String endpoint = "http://api.openweathermap.org/data/2.5/find?lat=40.65417&lon=-3.95946&units=metric&APPID=";

const String key = "473eec546b5ba8687fee32a351efae42";

unsigned long lastConnectionTime = 10 * 60 * 1000;     // last time you connected to the server_openweathermap, in milliseconds
const unsigned long postInterval = 10 * 60 * 1000;  // posting interval of 10 minutes  (10L * 1000L; 10 seconds delay for testing)
unsigned long n;

tmElements_t te;  //Time elements structure
time_t unixTime; // a time stamp

float temperature;
float pressure;
float humidity;
float wind;
//char main_w[15];
//char description[15];
String main_w;
String description;
  
time_t t_sunrise;
time_t t_sunset;

String sunrise_str;
String sunset_str;
char salida_sol[8]; 
char puesta_sol[8]; 

char A_sys_sunrise_char[16];
char B_sys_sunset_char[16];
char dt_char[16];

//--- nuevas variables
      float coord_lon ;
      float coord_lat;

      
      int weather_0_id ;
      String weather_0_main ;
      String weather_0_description ;
      String weather_0_icon ;

      String base ;

    
      float main_temp;
      float main_feels_like ;
      float main_temp_min ;
      float main_temp_max;
      int main_pressure ;
      int main_humidity ;

      int visibility ;

      float wind_speed ;
      int wind_deg ;

      int clouds_all ;

      long dt ;

   
      int sys_type ;
      int sys_id;
      String sys_country ;
      long sys_sunrise ;
      long sys_sunset ;

      int timezone ;
      long id ;
      String name ;
      int cod ;

      //--- End of ArduinoJson Assistant ---
      
 
