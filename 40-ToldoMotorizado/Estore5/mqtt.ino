//Use MQTT Dash to control a lamp over the internet
//by Fábio Souza https://www.hackster.io/fabiosouza/use-mqtt-dash-to-control-a-lamp-over-the-internet-97fa63

 

//MQTT broker information - Verify the information generated by CloudMQTT
//const char* mqttServer = "broker.hivemq.com";   //server
//const char* mqttServer = "broker.mqttdashboard.com";   //server
const char* mqttServer = "broker.emqx.io";   //server
const char* mqttUser = "emqx";              //user
const char* mqttPassword = "public";      //password
const int mqttPort = 1883;                     //port
const char* mqttTopicSub ="cuco75/Estore5";            //topic
unsigned long lastMsg = 0; 
int value = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
  
void setup_mqtt() {
 mqttClient.setServer(mqttServer, mqttPort);
 mqttClient.setCallback(callback);
  unsigned long t_inicial=millis();
  
 while (!mqttClient.connected()) {
  
    if(millis()-t_inicial>5000){break;}
  
    Serial.println("Connecting to MQTT Broker...");
    String clientId = "Toldo1-";
    clientId += String(random(0xffff), HEX);
    
   if (mqttClient.connect(clientId.c_str(), mqttUser, mqttPassword )) {     Serial.println("Connected");  
      Serial.println("Connected");  
   } else {
      Serial.print("state failure  ");
     Serial.print(mqttClient.state());
     delay(2000);
   }
 }
 //Topic
 mqttClient.subscribe(mqttTopicSub);
}
  
void callback(char* topic, byte* payload, unsigned int length) {
 //stores the received message in a string
 payload[length] = '\0';
 String strMSG = String((char*)payload);
 int porcentaje=strMSG.toInt(); // porcentaje de 0 a 255
 
 Serial.print("The message arrived from the topic: ");
 Serial.println(topic);
 Serial.print("message:");
 Serial.print(strMSG);
 Serial.println();
 Serial.println("-----------------------");
 
     
  if (strcmp(topic , "cuco75/Estore5")==0){ 
    Serial.print("The message arrived from the topic: ");
    Serial.println(topic);
    Serial.println("topic OK");
    
    }else{
    Serial.print("The message arrived from the topic: ");
    Serial.println(topic);
    Serial.println("topic not available, RETURN");
    return;
    }
    
  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(p,payload,length);
  mqttClient.publish("cuco75/Estore5/confirma", p, length);
    
  // Free the memory
  free(p);
  
 if (strMSG == "1"){        //if msg equal "1"
        estado_anterior=0; //por si acaso el programa se ha reseteado, cambio el estado
        estados[0]=0; //en control por voz se supone que se ve lo que hay
        AbrirEstore(0);
 
    //digitalWrite(L1, LOW);  //output LOW to turn on the Lamp 
 }else if (strMSG == "0"){   //if msg equal "0"
        estado_anterior=1; //por si acaso el programa se ha reseteado, cambio el estado
        estados[0]=1; //en control por voz se supone que se ve lo que hay
        CerrarEstore(0);
 
    //digitalWrite(L1, HIGH);   //output LOW to turn off the Lamp 
 } else if(porcentaje > 0){   // porcentaje
        estado_anterior=1; //por si acaso el programa se ha reseteado, cambio el estado
        estados[0]=1; //en control por voz se supone que se ve lo que hay
        AbrirEstore_parcial(porcentaje);

  }
}
  
//Function to reconnect MQTT broker
void reconect() {
 //while disconnected
 if (!mqttClient.connected()) {

   //añadido, si no hay wifi
  if(WiFi.status() != WL_CONNECTED)
  {
     DPRINTLN("reconectando WIFI");
     StartWiFi();
  }
  
   String clientId = "Toldo1-";
   clientId += String(random(0xffff), HEX);
  
   bool connected = strlen(mqttUser) > 0 ?
                    mqttClient.connect(clientId.c_str(), mqttUser, mqttPassword) :
                    mqttClient.connect(clientId.c_str());
   if(connected) {
     
    // Serial.println("Connected!");
     
     //subscribe to the topic
     mqttClient.subscribe(mqttTopicSub, 1); 
   } else {
    
     Serial.println("Failed during connection. Code: ");
     Serial.println( String(mqttClient.state()).c_str());
     Serial.println("Retrying in 10 sec");
     
     //Waiting 10 seconds
     Serial.println("mqtt esperando 0s: ");
     //delay(10000);
   }
 }
}


  void publicar_mqtt(){
    
    unsigned long now = millis();
    
    if (now - lastMsg > 120000) {
      
            if (!mqttClient.connected()) {
              reconect();
             }

      lastMsg = now;
      ++value;
      //snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
      snprintf (msg, MSG_BUFFER_SIZE, "millis Estore5 #%ld", now);
      Serial.print("Publish message: ");
      Serial.println(msg);
      mqttClient.publish("cuco75/Estore5/millis", msg);
      //String ip3=String(WiFi.localIP()[3]);
      snprintf (msg, MSG_BUFFER_SIZE, "ip Estore5 #%ld", WiFi.localIP()[3]);
      mqttClient.publish("cuco75/Estore5/ip", msg);
      
      snprintf (msg, MSG_BUFFER_SIZE, "Estado Estore5 #%ld", estados[0]);
      mqttClient.publish("cuco75/Estore5/estado", msg);
    }
  }
  
