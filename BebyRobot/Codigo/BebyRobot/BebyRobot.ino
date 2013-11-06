#include <EEPROM.h>

int Pin[3] = {
  3, 2, 1};
//{R, B, G}
int nivel[3];
int SuperBoton = 0;
int Aura = 7;
int Frecuencia = 1;
int Estados = 3;

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

void SiquienteEstado(){
  EEPROM.write(Aura, EEPROM.read(Aura) + 1);
  if( EEPROM.read(Aura) > Estados){
    EEPROM.write(Aura, 1);
  }
  delay(100);
  do{
    delay(10);    
  }while(digitalRead(SuperBoton) == 0);
}

void Limpiar(){
  for(int i = 0; i < 3; i++){
    nivel[i] = 0;
  }
}

void Actualizar(){
  for(int t = 0; t < 10; t++){
    for(int Led = 0; Led < 3; Led++){
      if(nivel[Led] <=  t)
        digitalWrite(Pin[Led], HIGH);
      else
        digitalWrite(Pin[Led], LOW);     
    }
    delay(1);
  }
}

