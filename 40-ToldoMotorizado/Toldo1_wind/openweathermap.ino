//  1. Ber variables incluidas en puertaStepper.h
//  2. Borrar o renombrar la funcion sendTabMesures() de la pestaña funciones, está incluida aquí (ver abajo)
//  3. Renombrar sendotemoncms() en su pestaña, está aquí incluida
//https://openweathermap.org/current
// 5 de mayo de 2021


void Request_OpenWheatherMap() {

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
     HTTPClient http;
     http.begin(endpoint + key); //Specify the URL
    int httpCode = http.GET();  //Make the request
     if (httpCode > 0) { //Check for the returning code
         String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        parseJson(payload.c_str());  // parse c string text in parseJson function
      }
     else {
      Serial.println("Error on HTTP request");
    }
     http.end(); //Free the resources
  }
     

}


void parseJson(const char * jsonString) {
  const size_t bufferSize = 2*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(2) + 4*JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 2*JSON_OBJECT_SIZE(7) + 2*JSON_OBJECT_SIZE(8) + 720;
  DynamicJsonDocument doc(bufferSize);

  DeserializationError error = deserializeJson(doc, jsonString);
  
  // Print the result
  Serial.println("parseJson function: Datos recibidos:: ");
  serializeJsonPretty(doc, Serial);
  Serial.println("============");
  temperature=doc ["main"]["temp"];
  Serial.print("Temperatura :");Serial.println(temperature);
  pressure=doc ["main"]["pressure"];
  Serial.print("pressure :");Serial.println(pressure);
  humidity=doc ["main"]["humidity"];
  Serial.print("humidity :");Serial.println(humidity);
  wind=doc ["wind"]["speed"];
  Serial.print("wind :");Serial.println(wind);

  //--- Copy from ArduinoJson Assistant
       coord_lon = doc["coord"]["lon"];
       coord_lat = doc["coord"]["lat"];

      JsonObject weather_0 = doc["weather"][0];
       weather_0_id = weather_0["id"];
       weather_0_main = weather_0["main"].as<String>();
       
       weather_0_description = weather_0["description"].as<String>();
       weather_0_icon = weather_0["icon"].as<String>();

       base = doc["base"].as<String>();

      JsonObject main = doc["main"];
       main_temp = main["temp"];
       main_feels_like = main["feels_like"];
       main_temp_min = main["temp_min"];
       main_temp_max = main["temp_max"];
       main_pressure = main["pressure"];
       main_humidity = main["humidity"];

       visibility = doc["visibility"];

       wind_speed = doc["wind"]["speed"];
       wind_deg = doc["wind"]["deg"];

       clouds_all = doc["clouds"]["all"];

       dt = doc["dt"];

      JsonObject sys = doc["sys"];
       sys_type = sys["type"];
       sys_id = sys["id"];
       sys_country = sys["country"].as<String>();
       sys_sunrise = sys["sunrise"];
       sys_sunset = sys["sunset"];

       timezone = doc["timezone"];
       id = doc["id"];
       name = doc["name"].as<String>();
       cod = doc["cod"];

      //--- End of ArduinoJson Assistant ---
       sprintf(A_sys_sunrise_char, "%02d:%02d:%02d", (int)hour(sys_sunrise), (int)minute(sys_sunrise), (int)second(sys_sunrise));  
       sprintf(dt_char, "%02d:%02d:%02d", (int)hour(dt), (int)minute(dt), (int)second(dt));  
       Serial.print("A_sys_sunrise_char: ");Serial.println(A_sys_sunrise_char);
      
       Serial.print("weather_0_main: ");Serial.println(weather_0_main);
       Serial.print("weather_0_description: ");Serial.println(weather_0_description);
       Serial.print("coord_lat: ");Serial.println(coord_lat);
       Serial.print("coord_lon: ");Serial.println(coord_lon);
 
     sprintf(B_sys_sunset_char, "%02d:%02d:%02d", (int)hour(sys_sunset), (int)minute(sys_sunset), (int)second(sys_sunset));  
     Serial.print("B_sys_sunset_char: ");Serial.println(B_sys_sunset_char);
     Serial.print("dt_char: ");Serial.println(dt_char);

  
  
   t_sunrise=doc ["sys"]["sunrise"];
//   Serial.print("sunrise: ");
//   Serial.print(hour(t_sunrise));
//   Serial.print(":");
//   Serial.print(minute(t_sunrise));
//   Serial.print(":");
//   Serial.println(second(t_sunrise));

  sprintf(salida_sol, "%02d:%02d:%02d", (int)hour(t_sunrise), (int)minute(t_sunrise), (int)second(t_sunrise));  
  //strcpy(sunrise_str,salida_sol); 
  sunrise_str=String(salida_sol); 
 
   t_sunset=doc ["sys"]["sunset"];
//   Serial.print("sunset: ");
//   Serial.print(hour(t_sunset));
//   Serial.print(":");
//   Serial.print(minute(t_sunset));
//   Serial.print(":");
//   Serial.println(second(t_sunset));
 
  
  sprintf(puesta_sol, "%02d:%02d:%02d",(int)hour(t_sunset), (int)minute(t_sunset), (int)second(t_sunset));
  //strcpy(sunset_str,puesta_sol);
 sunset_str=String(puesta_sol);
  
  Serial.print("sunrise_str: ");Serial.println(sunrise_str);
  Serial.print("sunset_str:");Serial.println(sunset_str);
  Serial.println("===============");
  
  // Test if parsing succeeds.
//  if (error) {
//    Serial.print(F("deserializeJson() failed: "));
//    Serial.println(error.f_str());
//    return;
//  }
  
  Serial.println();
}

///borrar la funcion sendTabMesures() de la pestaña funciones
//https://openweathermap.org/current


void sendTabMesures() {
  double temp = PH_ant;
  
  String json = "[";
  json += "{\"medida\":\"coord_lon \",\"valor\":\"" + String(coord_lon ) + "\",\"unidad\":\" º\",\"precedente\":\"" + String(coord_lon ) + "\"},";
  json += "{\"medida\":\"coord_lat \",\"valor\":\"" + String(coord_lat ) + "\",\"unidad\":\"º\",\"precedente\":\"" + String(coord_lat ) + "\"},";
  json += "{\"medida\":\"weather_0_main  \",\"valor\":\"" + weather_0_main   + "\",\"unidad\":\"\",\"precedente\":\"" + weather_0_main   + "\"},";
  json += "{\"medida\":\"weather_0_description  \",\"valor\":\"" + String(weather_0_description  ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(weather_0_description  ) + "\"},";
  json += "{\"medida\":\"weather_0_icon  \",\"valor\":\"" + String(weather_0_icon  ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(weather_0_icon  ) + "\"},";
  json += "{\"medida\":\"base  \",\"valor\":\"" + String(base) + "\",\"unidad\":\"\",\"precedente\":\"" + String(base ) + "\"},";
  json += "{\"medida\":\"main_temp  \",\"valor\":\"" + String(main_temp  ) + "\",\"unidad\":\" ºC\",\"precedente\":\"" + String(main_temp  ) + "\"},";
  json += "{\"medida\":\"main_feels_like  \",\"valor\":\"" + String(main_feels_like  ) + "\",\"unidad\":\" ºC\",\"precedente\":\"" + String(main_feels_like  ) + "\"},";
  json += "{\"medida\":\"main_temp_max   \",\"valor\":\"" + String(main_temp_max   ) + "\",\"unidad\":\" ºC\",\"precedente\":\"" + String(main_temp_max   ) + "\"},";
  json += "{\"medida\":\"main_pressure  \",\"valor\":\"" + String(main_pressure  ) + "\",\"unidad\":\" hPa\",\"precedente\":\"" + String(main_pressure  ) + "\"},";
  json += "{\"medida\":\"main_humidity  \",\"valor\":\"" + String(main_humidity  ) + "\",\"unidad\":\" %\",\"precedente\":\"" + String(main_humidity  ) + "\"},";
  json += "{\"medida\":\"visibility   \",\"valor\":\"" + String(visibility   ) + "\",\"unidad\":\" m\",\"precedente\":\"" + String(visibility   ) + "\"},";
  json += "{\"medida\":\"wind_speed   \",\"valor\":\"" + String(wind_speed   ) + "\",\"unidad\":\" m/s\",\"precedente\":\"" + String(wind_speed   ) + "\"},";
  json += "{\"medida\":\"wind_deg   \",\"valor\":\"" + String(wind_deg   ) + "\",\"unidad\":\" º\",\"precedente\":\"" + String(wind_deg   ) + "\"},";
  json += "{\"medida\":\"Nubosidad   \",\"valor\":\"" + String(clouds_all   ) + "\",\"unidad\":\" %\",\"precedente\":\"" + String(clouds_all   ) + "\"},";
  json += "{\"medida\":\"dt   \",\"valor\":\"" + String(dt   ) + "\",\"unidad\":\" s\",\"precedente\":\"" + String(dt   ) + "\"},";
  json += "{\"medida\":\"sys_type   \",\"valor\":\"" + String(sys_type   ) + "\",\"unidad\":\" \",\"precedente\":\"" + String(sys_type   ) + "\"},";
  json += "{\"medida\":\"sys_country    \",\"valor\":\"" + String(sys_country    ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(sys_country    ) + "\"},";
  json += "{\"medida\":\"sys_sunrise    \",\"valor\":\"" + String(sys_sunrise    ) + "\",\"unidad\":\" \",\"precedente\":\"" + String(sys_sunrise    ) + "\"},";
  json += "{\"medida\":\"sys_sunset     \",\"valor\":\"" + String(sys_sunset    ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(sys_sunset    ) + "\"},";
  json += "{\"medida\":\"id    \",\"valor\":\"" + String(id    ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(id    ) + "\"},";
  json += "{\"medida\":\"name    \",\"valor\":\"" + String(name    ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(name    ) + "\"},";
  json += "{\"medida\":\"cod    \",\"valor\":\"" + String(cod    ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(cod    ) + "\"},";
  json += "{\"medida\":\"A_sys_sunrise_char   \",\"valor\":\"" + String(A_sys_sunrise_char   ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(A_sys_sunrise_char   ) + "\"},";
  json += "{\"medida\":\"B_sys_sunset_char   \",\"valor\":\"" + String(B_sys_sunset_char   ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(B_sys_sunset_char   ) + "\"},";
  json += "{\"medida\":\"dt_char   \",\"valor\":\"" + String(dt_char   ) + "\",\"unidad\":\"\",\"precedente\":\"" + String(dt_char   ) + "\"},";
  time_t t = now();
  json += "{\"medida\":\"now   \",\"valor\":\"" + String(t   ) + "\",\"unidad\":\" s\",\"precedente\":\"" + String(t   ) + "\"},";

  temp = temperature;          
  json += "{\"medida\":\"temperature\",\"valor\":\"" + String(temperature) + "\",\"unidad\":\"ºC\",\"precedente\":\"" + String(temp) + "\"},";
  temp = pressure;          
  json += "{\"medida\":\"pressure\",\"valor\":\"" + String(pressure) + "\",\"unidad\":\"hPa\",\"precedente\":\"" + String(temp) + "\"},";
  temp = humidity;          
  json += "{\"medida\":\"humidity\",\"valor\":\"" + String(humidity) + "\",\"unidad\":\"%\",\"precedente\":\"" + String(temp) + "\"},";
  temp = wind;          
  json += "{\"medida\":\"wind\",\"valor\":\"" + String(wind) + "\",\"unidad\":\"m/s\",\"precedente\":\"" + String(temp) + "\"},";
          
  json += "{\"medida\":\"sunrise_str\",\"valor\":\"" + sunrise_str + "\",\"unidad\":\" \",\"precedente\":\"" + "" + "\"},";
 
  json += "{\"medida\":\"t_sunset\",\"valor\":\"" + sunset_str + "\",\"unidad\":\" \",\"precedente\":\"" + "" + "\"},";
 
  temp = PH_ant;          
  json += "{\"medida\":\"PH\",\"valor\":\"" + String(Cenit) + "\",\"unidad\":\"º\",\"precedente\":\"" + String(temp) + "\"},";
  temp = mV_PH_ant;          
  json += "{\"medida\":\"mV_PH\",\"valor\":\"" + String(mV_PH) + "\",\"unidad\":\"ms\",\"precedente\":\"" + String(temp) + "\"},";
  temp = To_ant;     
  json += "{\"medida\":\"To\",\"valor\":\"" + String(To) + "\",\"unidad\":\"ms\",\"precedente\":\"" + String(temp) + "\"}";
  json += "]";
  server.send(200, "application/json", json);
  DPRINTLN("Tabla de medidas enviada");
}




void sendtoemoncms(){
  
      if((millis()-time_emoncms_ant )<conf.time_emoncms){
            return;
      }
     
      time_emoncms_ant =millis();
 
  //Serial.println(WiFi.localIP());
  Serial.print("Estore:connecting emoncms to ");
  Serial.println(conf.ip_emoncms);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(conf.ip_emoncms, httpPort)) {
    Serial.println("connection failed");
    return;
  }
   // We now create a URI for the request
  //http://192.168.8.112/emoncms/input/post?node=emontx&json={power1:100,power2:200,power3:300}
 
  String url = String(conf.url_base)+"/input/post?node="+String(conf.node)+
  "&json={Cenit:"+String(spa.zenith)+
  ",seg:"+String(mV_PH)+
  ",D4_Toldo1:"+String(estados[0])+
  ",IP:"+String(WiFi.localIP()[3])+
  ",arranques:"+String(conf.EEPROM_chk)+
  ",main_temp:"+String(main_temp)+
  ",main_feels_like:"+String(main_feels_like)+
  ",main_temp_min:"+String(main_temp_min)+
  ",main_temp_max:"+String(main_temp_max)+
  ",main_pressure:"+String(main_pressure)+
  ",main_humidity:"+String(main_humidity)+
  ",wind_speed:"+String(wind_speed)+
  ",wind_deg:"+String(wind_deg)+
  ",sys_sunrise:"+String(sys_sunrise)+
  ",sys_sunset:"+String(sys_sunset)+
  
  "}&apikey="+String(conf.apikey); 



  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + String(conf.ip_emoncms) + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    DPRINT(line);
  }
  
  Serial.println();
  Serial.println("closing emoncms connection");
  }
  
