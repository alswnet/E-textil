int led = 2;
int SuperBoton = 0;

void setup() {                

  pinMode(led, OUTPUT);  
   
  pinMode(SuperBoton,INPUT);
  digitalWrite(SuperBoton,HIGH);
  
}

void loop() {
  if(digitalRead(0) == 1){
  digitalWrite(led, HIGH);
  delay(1000);
  }
  else{
  digitalWrite(led, LOW);
  }
}
