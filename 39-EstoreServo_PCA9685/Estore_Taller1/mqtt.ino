//Use MQTT Dash to control a lamp over the internet
//by Fábio Souza https://www.hackster.io/fabiosouza/use-mqtt-dash-to-control-a-lamp-over-the-internet-97fa63

 

//MQTT broker information - Verify the information generated by CloudMQTT
//const char* mqttServer = "broker.hivemq.com";   //server
//const char* mqttServer = "broker.mqttdashboard.com";   //server
const char* mqttServer = "broker.emqx.io";   //server

const char* mqttUser = "emqx";              //user
const char* mqttPassword = "public";      //password
const int mqttPort = 1883;                    //port
const char* mqttTopicSub ="cuco75/Estore_Taller1";            //topic
unsigned long lastMsg = 0; 
int value = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
  
void setup_mqtt() {

 int i;
 
 client_mqtt.setServer(mqttServer, mqttPort);
 client_mqtt.setCallback(callback);
 while (!client_mqtt.connected()) {
   Serial.println("Connecting to MQTT Broker...");
    String clientId = "Estore_Taller1-";
    clientId += String(random(0xffff), HEX);
    
   if (client_mqtt.connect(clientId.c_str(), mqttUser, mqttPassword )) {     Serial.println("Connected");  
   } else {
      Serial.print("state failure  ");
     Serial.print(client_mqtt.state());
     delay(2000);
   }
   i++;
   if(i>100){break;}
 }
 //Topic
 client_mqtt.subscribe(mqttTopicSub);
}
  
void callback(char* topic, byte* payload, unsigned int length) {
 //stores the received message in a string
 payload[length] = '\0';
 String strMSG = String((char*)payload);
 
 Serial.print("The message arrived from the topic: ");
 Serial.println(topic);
 Serial.print("message:");
 Serial.print(strMSG);
 Serial.println();
 Serial.println("-----------------------");
 Serial.print("2:The message arrived from the topic: ");
  Serial.println(topic);
 
     
  if (strcmp(topic , "cuco75/Estore_Taller1")==0){ 
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
  client_mqtt.publish("cuco75/confirma", p, length);
 

    
  // Free the memory
  free(p);
  
 if (strMSG == "1"){        //if msg equal "1"
        estado_anterior=0; //por si acaso el programa se ha reseteado, cambio el estado
        estados[0]=0; //en control por voz se supone que se ve lo que hay
        AbrirPuerta();
 
    //digitalWrite(L1, LOW);  //output LOW to turn on the Lamp 
 }else if (strMSG == "0"){   //if msg equal "0"
        estado_anterior=1; //por si acaso el programa se ha reseteado, cambio el estado
        estados[0]=1; //en control por voz se supone que se ve lo que hay
        CerrarPuerta();
 
    //digitalWrite(L1, HIGH);   //output LOW to turn off the Lamp 
 }
}
  
//Function to reconnect MQTT broker
void reconect() {

int counter;
  
 //while disconnected
 while (!client_mqtt.connected()) {

  //añadido, si no hay wifi
  if(WiFi.status() != WL_CONNECTED)
  {
     DPRINTLN("reconectando WIFI");
     StartWiFi();
  }
  
   #ifdef DEBUG
   Serial.println("Trying connect to MQTT broker");
   #endif
   String clientId = "Estore_Taller1-";
   clientId += String(random(0xffff), HEX);
  
   bool connected = strlen(mqttUser) > 0 ?
                    client_mqtt.connect(clientId.c_str(), mqttUser, mqttPassword) :
                    client_mqtt.connect(clientId.c_str());
   if(connected) {
     #ifdef DEBUG
     Serial.println("Connected!");
     #endif
     //subscribe to the topic
     client_mqtt.subscribe(mqttTopicSub, 1); 
   } else {
     #ifdef DEBUG
     Serial.println("Failed during connection. Code: ");
     Serial.println( String(client_mqtt.state()).c_str());
     Serial.println("Retrying in 10 sec");
     #endif
     //Waiting 10 seconds
     Serial.println("Retrying in 10 sec");
     delay(10000);
     counter++;
   }
   yield();
   if(counter>10){break;}
 }
 counter=0;
}


  void publicar_mqtt(){
    
    unsigned long now = millis();
    
    if (now - lastMsg > 65000) {
      lastMsg = now;
      ++value;
      snprintf (msg, MSG_BUFFER_SIZE, "Estore_Taller1 millis #%ld", now);
      //Serial.print("Publish message: ");
      //Serial.println(msg);
      client_mqtt.publish("cuco75/millis", msg);
      snprintf (msg, MSG_BUFFER_SIZE, "Estore_Taller1 ip #%ld", WiFi.localIP()[3]);
      client_mqtt.publish("cuco75/millis", msg);
    }
  }
  
