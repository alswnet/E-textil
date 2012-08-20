/*
 Los estados del sitemas son 
 -  0 Programador
 -  1 Super PWM
 -  2 Super Pendulo
 -  3
 -  4
 -  5
 -  6
 -  7
 -  8
 -  9
 - 10
 - 11
 - 12
 - 13
 - 14
 - 15 Disco Disco
 - 16
 - 17
 - 18
 - 19
 */

#include <EEPROM.h>

int TotalLed = 19;//Cantidad de LED
char Pin[19] = {
  A5,A4,A3,A2,A1,A0,12,13,11,10,9,8,7,6,5,4,3,2,1};//Posiciones de led
char nivel[19];
int Aura = 7;
int Frecuencia = 1;

void setup() {

  pinMode(0,INPUT);
  digitalWrite(0,HIGH);

  for(int Led = 0; Led < TotalLed; Led++)
    pinMode(Pin[Led],OUTPUT);

  Limpiar();

}//Funcion de inicializacion de variables

void loop() {
  switch( EEPROM.read(Aura)){
  case 1:
    E1_SuperPWM();
    break;
  case 2:
    E2_SuperPendulo();
    break;
  case 3:
    E3_DoblePendulo();
    break;
  case 4:
    E4_Ecualizador();
    break;
  case 5:
    E5_EcualizadorRandon();
    break;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:  
    E15_DiscoDisco();
    break;
  case 16:
  case 17:
    E17_Randon();
    break;
  case 18:
    E18_RandonLento();
    break;
  case 19:
    E19_SuperEncendio();
    break;  

  default:
    EEPROM.write(Aura,1);
    return;
    break;
  }
  Leer();
}//Funcion que se repitira en el sistema

void Limpiar(){
  for(int Led = 0; Led < TotalLed; Led++)
    nivel[Led] = 0;
  Frecuencia = 1;
}//Funcion que pone todos los led apagados

void Actualizar(){
  for(int t = 0; t < 10*Frecuencia; t++){
    for(int Led = 0; Led < TotalLed; Led++){
      if(nivel[Led]*Frecuencia <=  t)
        digitalWrite(Pin[Led], LOW);
      else
        digitalWrite(Pin[Led], HIGH);     
    }
    delay(1);
  }
}//Enciende los led dependidendo del nivel que estes

void Leer(){
  Limpiar();
  Actualizar();
  int cont = 0;
  float t0 = millis();
  float t1 = t0;
  int BPasado = 0;
  int BPresente = 0;
  do{
    if( t1 == t0){
      for( int Led = 0; Led < TotalLed; Led++){
        nivel[Led] = ( Led + 1 <= EEPROM.read(Aura)) ? 10 : 0;
      } 
    }

    t1 = millis();
    BPresente = digitalRead(0);

    if(BPresente > BPasado){
      EEPROM.write(Aura, EEPROM.read(Aura) + 1);
      cont = 0;
      if( EEPROM.read(Aura) > TotalLed){
        EEPROM.write(Aura, 1);
      }
      t0 = t1;  
    }

    BPasado = BPresente; 

    Actualizar();
    if( (t1 - t0) >= 1000){
      t0 = t1;
      cont++;
      Limpiar();
      for( int i = 0; i<20;i++){
        Actualizar();
      }
    }

  }
  while( cont <= 3);
}

void E1_SuperPWM(){
  int LedNivel = 0;
  int v = -1;
  float t0 = millis();
  float t1 = t0;
  Limpiar();
  do{
    t1 = millis();

    if( t1 - t0 >= 200){
      t0 = millis();
      for(int Led = 0; Led < TotalLed; Led++){
        nivel[Led] = LedNivel;
      }

      if( LedNivel == -1 || LedNivel == 12)
        v = -v;
      LedNivel = LedNivel + v;  
    }
    Actualizar();
  }
  while(digitalRead(0) == 1);
}//El primer esta un pwm de todos los LED

void E2_SuperPendulo(){
  int x = 0;
  int v = 1;
  float t = 0;
  Limpiar();
  float t0 = millis();
  float t1 = t0;
  do{

    if( t1 - t0 >= 75){
      t0 = t1;
      x = x + v;
      if( x >= 19 || x <= 0)
        v = -v;

      for( int Led = 0; Led < TotalLed; Led++){
        if(nivel[Led] > 0)
          nivel[Led] /= 2;
      }

      nivel[x] = 10;

    }

    t1 = millis();
    Actualizar();


  }
  while(digitalRead(0) == 1);
}

void E3_DoblePendulo(){
  int x = 0;
  int v = 1;
  Limpiar();
  float t0 = millis();
  float t1 = t0;
  do{

    if( t1 - t0 >= 40){
      t0 = t1;
      x = x + v;
      if( x >= 19 || x <= 0)
        v = -v;

      for( int Led = 0; Led < TotalLed; Led++){
        if(nivel[Led] > 0)
          nivel[Led] /= 2;
      }

      nivel[x] = 10;
      nivel[TotalLed - x] = 10;
    }

    t1 = millis();
    Actualizar();
  }
  while(digitalRead(0) == 1);
}

void E4_Ecualizador(){
  int x = -1;
  int Centro = 9;
  int v = 1; 
  float t0 = millis();
  float t1 = t0;
  do{
    t1 = millis();

    if( t1 - t0 >= ((v > 0) ? 200 : 75)){
      t0 = t1;
      x += v;
      if(x ==  10 || x == -3)
        v = -v;
      for( int Led = 0; Led < TotalLed; Led++){
        if(nivel[Led] > 0)
          nivel[Led] /= 2;
      }
      for(int i = 0; i < 10; i++){
        if( i <= x){
          nivel[Centro + i] = 10;
          nivel[Centro - i] = 10;
        }
      } 
    }
    Actualizar();
  }
  while(digitalRead(0) == 1);
}

void E5_EcualizadorRandon(){
  int x = -1;
  int c = 9;
  int v = 1; 
  float t0 = millis();
  float t1 = t0;
  do{
    t1 = millis();

    if( t1 - t0 >= 500 ){
      t0 = t1;
      x = random(-5, 12);

      for( int i = 0; i < TotalLed; i++){
        if(nivel[i] > 0)
          nivel[i] /= 5;
      }
      for(int i = 0; i < 10; i++){
        if( i <= x){
          nivel[c + i] = 10;
          nivel[c - i] = 10;
        }
      } 
    }
    Actualizar();
  }
  while(digitalRead(0) == 1);


}

void E15_DiscoDisco(){
  Limpiar();
  Frecuencia = 10;
  for(int Led = 0; Led < TotalLed; Led++){
    nivel[Led] = 6;
  }
  do{
    Actualizar();
  }
  while(digitalRead(0) == 1);
}//El primer esta un pwm de todos los LED


void E17_Randon(){
  Limpiar();

  do{

    for( int i = 0; i < TotalLed; i++){
      if(nivel[i] > 0)
        nivel[i] /= 2;
    }

    for( int i = 0; i < 3; i++){
      nivel[random(0, TotalLed)] = 10;
    }

    Actualizar();
  }
  while(digitalRead(0) == 1);

}

void E18_RandonLento(){
  Limpiar();
  float t0 = millis();
  float t1 = t0;
  do{
    t1 = millis();
    if ( t1 - t0 >= 100){
      t0 = t1;
      for( int i = 0; i < TotalLed; i++){
        if(nivel[i] > 0)
          nivel[i] /= 2;
      }

      for( int i = 0; i < 3; i++){
        nivel[random(0, TotalLed)] = 10;
        nivel[random(0, TotalLed)] = 5;
        nivel[random(0, TotalLed)] = 0;
      }
    }

    Actualizar();
  }
  while(digitalRead(0) == 1);

}

void E19_SuperEncendio(){
  Limpiar();
  for(int Led = 0;  Led < TotalLed; Led++)
    nivel[Led] = 10;
  do{
    Actualizar();
  }
  while(digitalRead(0) == 1);
}


