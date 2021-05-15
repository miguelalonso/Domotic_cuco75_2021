int hora_delay(int hora, int delay_time, int signo){
  //preparo fechas

long segundos_h=int(hora/100)*3600+int(hora%100)*60;
long segundos_delay= int(delay_time/100)*3600+int(delay_time%100)*60;
long diferencia= segundos_h + signo*segundos_delay;
int hh = int(diferencia/3600);
int mm = int(diferencia%3600)/60;

int nueva  =(int)hh*100+(int)mm;

//Serial.print ("delay: ");
//Serial.println(delay_time);
//Serial.print ("diferencia: ");
//Serial.println(diferencia);
//Serial.print ("nueva hora: ");
//Serial.println(nueva);
//
//Serial.print ("=====================================: ");

return nueva;

  }

void randomTimers(){
    //crea las variables aleatorias una vez al dia
    int ds=weekday() - 2; //(1=domingo) (1~7)
    char str[6];
            
            int mm = 60.0 * (spa.sunrise - (int)(spa.sunrise));
            sprintf(str, "%02d:%02d",  (int)(spa.sunrise),(int)mm);
            conf.sunrise=(int)spa.sunrise*100+(int)mm;
            conf.sunrise+=conf.TimeZone;
            mm = 60.0 * (spa.sunset - (int)(spa.sunset));
            sprintf(str, "%02d:%02d",  (int)(spa.sunset),(int)mm);
            conf.sunset=(int)spa.sunset*100+(int)mm;
            conf.sunset+=conf.TimeZone;
   
     if (ds==ds_anterior){
      return;
     }
     
    ds_anterior=ds;
 
 //chequeo
//timers[0].Tiempo_procesado[1]=hora_delay(conf.sunset, timers[0].delay_time[1], timers[0].sign_delay[1]);
//Serial.print ("timers[0].Tiempo_procesado[1]: ");
//Serial.println(timers[0].Tiempo_procesado[1]);
 

   
    for (i=0;i<Num_reles;i++){
      for (j=0;j<7;j++){
                    timers[i].Tiempo_procesado[j]=timers[i].ON_Time[j];
                   if(timers[i].sun_set[j]==1 ){ //en este caso es un delay
                       // timers[i].Tiempo_procesado[j]=conf.sunrise+timers[i].sign_delay[j]*timers[i].delay_time[j];
                        timers[i].Tiempo_procesado[j]=hora_delay(conf.sunrise, timers[i].delay_time[j], timers[i].sign_delay[j]);
                     }
                    if( timers[i].sun_set[j]==2){
                       //timers[i].Tiempo_procesado[j]=conf.sunset+timers[i].sign_delay[j]*timers[i].delay_time[j];
                       timers[i].Tiempo_procesado[j]=hora_delay(conf.sunset, timers[i].delay_time[j], timers[i].sign_delay[j]);
                    }
                   if(timers[i].aleatorio_Time[j]!=0){
                          int aleat=random(-timers[i].aleatorio_Time[j],timers[i].aleatorio_Time[j]);
                          timers[i].Tiempo_procesado[j]+=aleat;
                   }
      }
    }
     Serial.println("Random timers :");
     Serial.println(timers[0].Tiempo_procesado[0]);
      Serial.println(timers[0].Tiempo_procesado[1]);
     Serial.print("Delay_time: ");
     Serial.println(timers[0].delay_time[1]);
     
}


void controlTimers(int j){ 
  timeNow = (100 * hour()) + minute();
  boolean salida=false;
  boolean salida2=false;
  boolean actuar=false;
  
  //j es numero de rele 0 a 3
  //i de 0 a 6 --> 7 programas

   if (timers[j].Mode == 0) {
    salida = false;
    control_rele(j,0);
    return;
  }
  
  if (timers[j].Mode == 1) {
    salida = true;
    control_rele(j,1);
    return;
  }
  
  // Is mode invalid
  if (timers[j].Mode != 2) {
    return;
  }

  if (time_old[j] != timeNow) { //una vez cada minuto
      time_old[j] = timeNow;
      randomTimers();
         int ds=weekday() - 2; //(1=domingo) (1~7)
         if (ds<0){ds=6;} //si ds=-1  es domingo dia 6
         
          for ( int p = 0; p < 7; p++) {
              if(timers[j].ON_Days[p][ds] == true){
                   if (timeNow == timers[j].Tiempo_procesado[p]) {
                        salida2=timers[j].onoff[p];
                        actuar=true;
                    }
                  }
           }
     
//       Serial.println("============NEW======================");
//       Serial.print(" Salida2: "); Serial.println(salida2);
//       Serial.print(" actuar: ");Serial.println(actuar);
//       Serial.println("==========================================");
//       
      if (actuar){ //obligar a actuar
         Serial.print(" Iniciando control : ");Serial.println(salida2);
//          abriendo_Estore=0;
//          cerrando_Estore=0;
          estados[0]=!salida2;
          estado_anterior=!salida2;
          timers_estado_anterior=!salida2;
          control_rele(j,salida2);
          Serial.print(" Finalizado control : ");Serial.println(salida2);
      }
         
      }//timeold
 
}
  
void control_rele(int j, int Output){
    timers[j].Estado_rele=Output;
    if(timers_estado_anterior==Output ){return;}
    timers_estado_anterior=Output;
    Serial.print("Acctuando Outpu a:"); Serial.println(Output);
    switch( j){
    case 0:
      controlestore(Output);
      break;
    }
}
