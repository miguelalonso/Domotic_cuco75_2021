
void leer_boton(){
  int buttonState = digitalRead(D5);
       if (buttonState == LOW && (millis()-timeOld3) > 1000) {
          t_funciona=0;
          //ReleEntrada, 
        timeOld3=millis();
        Serial.println("Boton pulsado");
        
        if ( estados[0] ){
          Apagar();
        }else{
          Encender();
        }
      } 
   }


void ReleServoWeb(){
  mV_PH_ant=ciclo_actual;
  mV_PH=millis()/1000;
  PH_ant=Cenit;
  Cenit=spa.zenith;
  To_ant=To;
  mV_To=t_abierta;
  To=estados[0];
}

 
void controlrele(boolean estado){
  if(estado){Encender();} else{Apagar();}
}
      

void Encender(){
      estados[0]=1;
      Serial.print("Abriendo Rele : ");
      digitalWrite(D4,HIGH);
      digitalWrite(D6,HIGH);  // 
      digitalWrite(D7,HIGH); // D6  cierra relé
}

void Apagar(){
  estados[0]=0;
  Serial.print("Cerrando Rele : ");
  digitalWrite(D4,LOW);
  digitalWrite(D7,LOW);  
  digitalWrite(D6,LOW); 
     
}



  
