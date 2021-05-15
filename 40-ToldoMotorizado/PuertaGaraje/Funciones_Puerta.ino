
void leer_boton(){
  int buttonState = digitalRead(D5);
       if (buttonState == HIGH && (millis()-timeOld3) > 1000) {
          t_funciona=0;
          //PuertaGaraje, relés al revés
          digitalWrite(D6,HIGH); // D6  abre/cierra puerta
          digitalWrite(D7,HIGH);  // D7  alimenta motor puerta
        timeOld3=millis();
        Serial.println("Boton pulsado");

        if( abriendo_puerta || cerrando_puerta){
          abriendo_puerta=0;
          cerrando_puerta=0;
          estados[0]=!estados[0];
          estado_anterior=!estado_anterior;
          return;
         }
          
        if ( estados[0] ){
          Cerrarpuerta(0);
        }else{
          Abrirpuerta(0);
        }
      } 
   }

/////////////////////////////////////////PuertaGaraje

 

void PuertaServoWeb(){
  mV_PH_ant=ciclo_actual;
  mV_PH=millis()/1000;
  PH_ant=Cenit;
  Cenit=spa.zenith;
  To_ant=To;
  mV_To=t_abierta;
  To=estados[0];
}

 
void controlpuerta(boolean estado){
  if(estado){Abrirpuerta(0);} else{Cerrarpuerta(0);}
}
      
void Abrirpuerta_parcial(int brightness){
    if(brightness>0){
      if(estado_anterior){
           t_accionamiento=brightness*conf.a*1000/255;
        } else{
            t_accionamiento=brightness*conf.b*1000/255;
        }
    }else{
        if(estado_anterior){
           t_accionamiento=conf.a*1000; //tiempo maximo de mover el motor
        } else{
            t_accionamiento=conf.b*1000; //tiempo maximo de mover el motor
        }
    }
    
  if(estado_anterior){
    Cerrarpuerta(t_accionamiento); 
  } else{
    Abrirpuerta(t_accionamiento);
  }

}


//en este caso abir y cerrar la puerta es lo mismo
//es dar un pulso.

void Abrirpuerta(int t_accionamiento){
  //int t_accionamiento=conf.a*1000; //tiempo maximo de mover el motor
  if(t_accionamiento==0){
      t_accionamiento=conf.a*1000;
    }
  if(estado_anterior){Serial.println("Error:puerta ya abierta");return;} //ya está abierta
  Serial.print("Abrir puerta (ms): ");Serial.println(t_funciona);

     if(!abriendo_puerta){
      Serial.print("Abriendo puerta : ");
      abriendo_puerta=1;
      digitalWrite(D4,HIGH);
      digitalWrite(D7,LOW);  // D7  alimenta motor
      delay(1000);      
      digitalWrite(D6,LOW); // D6  cierra relé
      delay(500); //espera 500ms para dar un pulso
      digitalWrite(D6,HIGH);  // D6  abre relé
      t_ini_abrir=millis();
     }
     
      t_funciona=millis()-t_ini_abrir;
      
       if(t_funciona>t_accionamiento){
          abriendo_puerta=0;
          Serial.print("Puerta Abierta en (ms) : ");Serial.println(t_funciona);
          estado_anterior=1;
          estados[0]=1;
          t_funciona=0;
          digitalWrite(D6,HIGH); // D6  abre/cierra puerta
          digitalWrite(D7,HIGH);  // D7  apaga motor
          }
    
}

void Cerrarpuerta(int t_accionamiento){
  
  if(t_accionamiento==0){
      t_accionamiento=conf.b*1000;
    }
   if(!estado_anterior){
    Serial.println("Error:puerta ya cerrada");
    return;} //ya está cerrada
    Serial.print("Cerrando puerta (ms): ");Serial.println(t_funciona);

     if(!cerrando_puerta){
      Serial.print("Cerrando puerta : ");
      cerrando_puerta=1;
      digitalWrite(D4,LOW);
      digitalWrite(D7,LOW);  // D7  alimenta motor
      delay(1000);      
      digitalWrite(D6,LOW); // D6  cierra relé
      delay(500); //espera 500ms para dar un pulso
      digitalWrite(D6,HIGH);  // D6  abre relé
      t_ini_cerrar=millis();
     }
     
      t_funciona=millis()-t_ini_cerrar;
      
       if(t_funciona>t_accionamiento){
          cerrando_puerta=0;
          Serial.print("puerta cerrado en (ms) : ");Serial.println(t_funciona);
          estado_anterior=0;
          estados[0]=0;
          t_funciona=0;
          digitalWrite(D6,HIGH); // D6  abre puerta
          digitalWrite(D7,HIGH);  // D7  cierra puerta
          }
}



  
