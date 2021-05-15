
void leer_boton(){
  int buttonState = digitalRead(D5);
       if (buttonState == HIGH && (millis()-timeOld3) > 1000) {
          t_funciona=0;
          digitalWrite(D6,HIGH); // D6  abre Estore
          digitalWrite(D7,HIGH);  // D7  cierra Estore
        timeOld3=millis();
        Serial.println("Boton pulsado");
        Serial.print("estados[0]: ");Serial.println(estados[0]);
        Serial.print("estado_anterior: ");Serial.println(estado_anterior);

        

        if( abriendo_Estore || cerrando_Estore){
          abriendo_Estore=0;
          cerrando_Estore=0;
          estados[0]= !estados[0];
          estado_anterior=estados[0];
          Serial.println("cambiando estado");
          return;
         }
         
        
        if ( estados[0] ){
         estado_anterior=estados[0];
         CerrarEstore(0);
        }else{
          estado_anterior=estados[0];
          AbrirEstore(0);
        }
      } 
   }

/////////////////////////////////////////Estore1

 

void PuertaServoWeb(){
  mV_PH_ant=ciclo_actual;
  mV_PH=millis()/1000;
  PH_ant=Cenit;
  Cenit=spa.zenith;
  To_ant=To;
  mV_To=t_abierta;
  To=estados[0];
}

 
void controlEstore(boolean estado){
  if(estado){AbrirEstore(0);} else{CerrarEstore(0);}
}
      
void AbrirEstore_parcial(int brightness){
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
    CerrarEstore(t_accionamiento); 
  } else{
    AbrirEstore(t_accionamiento);
  }

}
     
void AbrirEstore(int t_accionamiento){
  //int t_accionamiento=conf.a*1000; //tiempo maximo de mover el motor
  if(t_accionamiento==0){
      t_accionamiento=conf.a*1000;
    }
  if(estado_anterior){return;} //ya está abierta
  Serial.print("Abrir Estore: ");Serial.println(t_funciona);

     if(!abriendo_Estore){
      Serial.print("Abriendo Estore : ");
      abriendo_Estore=1;
      digitalWrite(D4,HIGH);
      digitalWrite(D7,LOW); // D6  abre Estore
      digitalWrite(D6,HIGH);  // D7  cierra Estore
      t_ini_abrir=millis();
     }
     
      t_funciona=millis()-t_ini_abrir;
      
       if(t_funciona>t_accionamiento){
          abriendo_Estore=0;
          Serial.print("Estore Abierto en (ms) : ");Serial.println(t_funciona);
          estado_anterior=1;
          estados[0]=1;
          t_funciona=0;
          digitalWrite(D6,HIGH); // D6  abre Estore
          digitalWrite(D7,HIGH);  // D7  cierra Estore
          publicar_mqtt();
          }
    
}

void CerrarEstore(int t_accionamiento){
  
  if(t_accionamiento==0){
      t_accionamiento=conf.b*1000;
    }
   if(!estado_anterior){return;} //ya está cerrada
    Serial.print("Cerrar Estore: ");Serial.println(t_funciona);

     if(!cerrando_Estore){
      Serial.print("Cerrando Estore : ");
      cerrando_Estore=1;
      digitalWrite(D4,LOW);
      digitalWrite(D7,HIGH); // D6  abre Estore
      digitalWrite(D6,LOW);  // D7  cierra Estore
      t_ini_cerrar=millis();
     }
     
      t_funciona=millis()-t_ini_cerrar;
      
       if(t_funciona>t_accionamiento){
          cerrando_Estore=0;
          Serial.print("Estore cerrado en (ms) : ");Serial.println(t_funciona);
          estado_anterior=0;
          estados[0]=0;
          t_funciona=0;
          digitalWrite(D6,HIGH); // D6  abre Estore
          digitalWrite(D7,HIGH);  // D7  cierra Estore
          publicar_mqtt();
          }
    
}



  
