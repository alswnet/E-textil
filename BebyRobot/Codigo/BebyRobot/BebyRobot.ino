#include <EEPROM.h>

int Pin[3] = {
  3, 2, 1};
//{R, B, G}
int nivel[3];
int SuperBoton = 0;
int Aura = 7;
int Frecuencia = 1;
int Estados = 8;

void setup() {                

  for(int i; i < 3; i++)
    pinMode(Pin[i], OUTPUT);  

  pinMode(SuperBoton,INPUT);
  digitalWrite(SuperBoton,HIGH);

}

void loop() {
  switch( EEPROM.read(Aura)){
  case 1:
    E1_RojoPasion();
    break;
  case 2:
    E2_GreenTree();
    break;
  case 3:
    E3_MarAzul();
    break;
  case 4:
    E4_CorazonRojo();
    break; 
  case 5:
    E5_VerdeCresimiento();
    break;
  case 6:
    E6_AzulMarea();
    break;
  case 7:
    E7_Aurora();
    break;
  case 8:
    E8_Randon();
    break;
  default:
    EEPROM.write(Aura,1);
    return;
    break;
  }  
  SiquienteEstado();
}

void E1_RojoPasion(){
  Limpiar();
  nivel[0] = 10;
  do{
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);
}

void E2_GreenTree(){
  Limpiar();
  nivel[1] = 10;
  do{
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);
}

void E3_MarAzul(){
  Limpiar();
  nivel[2] = 10;
  do{
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);
}

void E4_CorazonRojo(){
  Limpiar();
  int V = 1;
  unsigned long Pasado = millis();
  do{
    if( millis() - Pasado >= 100){
      nivel[0] += V;
      if( nivel [0]> 10 || nivel[0] < 0)
        V = -V;
    }
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);

}

void E5_VerdeCresimiento(){
  Limpiar();
  int V = 1;
  unsigned long Pasado = millis();
  do{
    if( millis() - Pasado >= 100){
      nivel[1] += V;
      if( nivel [1]> 10 || nivel[1] < 0)
        V = -V;
    }
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);

}

void E6_AzulMarea(){
  Limpiar();
  int V = 1;
  unsigned long Pasado = millis();
  do{
    if( millis() - Pasado >= 100){
      nivel[2] += V;
      if( nivel [2]> 10 || nivel[2] < 0)
        V = -V;
    }
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);
}

void E7_Aurora(){
  nivel [0] = 5;
  nivel [1] = 1;
  nivel [2] = 5;
  //Frecuencia = 10;
  int X = 1;
  int Y = 1;
  int Z = -1;
  unsigned long Pasado = millis();
  do{
    if( millis() - Pasado >= 200){
      Pasado = millis();
      nivel[0] += X;
      nivel[1] += Y;
      nivel[2] += Z;
      if( nivel [0]> 10 || nivel[0] < 0)
        X = -X;
      if( nivel [1]> 10 || nivel[1] < 0)
        Y = -Y;
      if( nivel [2]> 10 || nivel[2] < 0)
        Z = -Z;
    }
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);
  Frecuencia = 1;
}

void E8_Randon(){
  unsigned long Pasado = millis();
  do{
    if( millis() - Pasado >= 500){
    Pasado = millis();
    nivel[0] = random(0,10);
    nivel[1] = random(0,10);
    nivel[2] = random(0,10);
    }
    Actualizar();
  }
  while(digitalRead(SuperBoton) == 1);

}
void SiquienteEstado(){
  EEPROM.write(Aura, EEPROM.read(Aura) + 1);
  if( EEPROM.read(Aura) > Estados){
    EEPROM.write(Aura, 1);
  }
  delay(100);
  do{
    delay(10);    
  }
  while(digitalRead(SuperBoton) == 0);
}

void Limpiar(){
  for(int i = 0; i < 3; i++){
    nivel[i] = 0;
  }
}

void Actualizar(){
  for(int t = 0; t < 10; t++){
    for(int Led = 0; Led*Frecuencia < 3; Led++){
      if(nivel[Led]*Frecuencia <=  t)
        digitalWrite(Pin[Led], HIGH);
      else
        digitalWrite(Pin[Led], LOW);     
    }
    delay(1);
  }
}








