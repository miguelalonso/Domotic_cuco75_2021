void setupConfig(){
  
    pinMode(D4, OUTPUT); //LED interno para el estado del Motor 1
    pinMode(D7, OUTPUT); //RELE 1
    pinMode(D6, OUTPUT); // rELE2
    pinMode(D5, INPUT); // Botón manual subir/bajar

          
          digitalWrite(D6,HIGH); // D6  pulso abre/cierra puerta
          digitalWrite(D7,HIGH);  // D7  alimenta motor
  
    Serial.begin ( 9600 );
    Serial.println("puerta motorizado Cuco 75!");

    strcpy(conf.pwd,"121212");
    init_display();
    conf.IP_1            = 129;
    conf.IP_2            = 6;
    conf.IP_3            = 15;
    conf.IP_4            = 28;
    conf. EEPROM_chk     =123;
    conf.Latitud         =40.41;
    conf.Longitud        =-3.731;
    strcpy(conf.DevName,"PuertaGaraje");
    strcpy(conf.thingspeak_api_key,thingspeak_api_key);
    conf.time_thinkspeak           = 30000;
    strcpy(conf.ip_emoncms,ip_emoncms);
    strcpy(conf.url_base,url_base);
    strcpy(conf.apikey,apikey);
    strcpy(conf.node,node);
    conf.time_emoncms           = 30000;
    // saveConfig();
    loadConfig();

    if (strlen(conf.thingspeak_api_key) < 10) {
      strcpy(conf.thingspeak_api_key,thingspeak_api_key);
    }
    if (conf.time_thinkspeak <= 0) {
      conf.time_thinkspeak  = 30000;
    }

    if (strlen(conf.apikey) < 5) {
      strcpy(conf.apikey,apikey);
    }
    if (strlen(conf.ip_emoncms) < 5) {
      strcpy(conf.ip_emoncms,ip_emoncms);
    }
    if (strlen(conf.url_base) < 3) {
      strcpy(conf.url_base,url_base);
    }
    if (strlen(conf.node) < 3) {
      strcpy(conf.node,node);
    }
    if (conf.time_emoncms <= 0) {
      conf.time_emoncms  = 90000;
    }
     if (conf.a == 0) {  //en conf.a tiempo subir 90s
      conf.a  = 90;
    }
     if (conf.b == 0) { //en conf.b viene timepo bajar 90s
      conf.b  = 90;
    }

     if (conf.c == 0) { //en conf.c viene reserva
      conf.c  = 0;
    }
    if (conf.ciclos == 0) { //en conf.ciclos viene reserva
      conf.ciclos  = 0;
    }

    if (conf.PH_max  == 0) {  //en conf.PH_max viene el tiempo abierto en el ciclo
      conf.PH_max   = 10;
    }
    if (conf.PH_min  == 0) {  //en conf.PH_min viene el tiempo cerrado del ciclo
      conf.PH_min   = 10;
    }
    
   
    StartWiFi();
    DPRINTLN("Comenzando programa");
 
   
  Serial.println ( "" );
  Serial.print ( "IP address: " ); Serial.println ( WiFi.localIP() );
  Serial.print ( "IP address1: " ); Serial.println ( WiFi.localIP()[3] );
 
  
  if (!SPIFFS.begin())
  {
    DPRINTLN("SPIFFS Mount failed");
  } else {
    DPRINTLN("SPIFFS Mount succesfull");
  }



//fin de setup

  }

void loadConfig() {
       if(!SPIFFS.begin()){
        DPRINTLN("Card Mount Failed");
        return;
        }
        File myFile = SPIFFS.open("/conf.txt", "r");
        myFile.read((byte *)&timers, sizeof(timers));
        myFile.read((byte *)&conf, sizeof(conf));
        myFile.close();
        DPRINTLN("leyendo configuracion");
        DPRINTLN(conf.DevName);
         conf. EEPROM_chk= conf. EEPROM_chk+1;
         saveConfig();
        //Serial.printf( "read: %s, %.5f\n", myStruct.someString, myStruct.someFloat );
        Serial.print( "nº arranque: ");Serial.println(  conf. EEPROM_chk );
}

void saveConfig() {
  DPRINTLN("saving config");
   if(!SPIFFS.begin()){
        DPRINTLN("Card Mount Failed");
        return;
    }
    File myFile = SPIFFS.open("/conf.txt", "w");
    myFile.write((byte *)&timers, sizeof(timers));
    myFile.write((byte *)&conf, sizeof(conf));
    myFile.close(); 
    DPRINTLN("guardando configuracion");
    DPRINTLN(conf.DevName); 
}
