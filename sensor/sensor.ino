#include <TimeLib.h>

#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

#define echoPin 2
#define trigPin 3
#define buzzer 10
#define ledVerde 4
#define ledAmarelo 5
#define ledVermelho 6

long duration;

int distance;
int eixo_X = A0; //PINO REFERENTE A LIGAÇÃO DO EIXO X
int eixo_Y = A1; //PINO REFERENTE A LIGAÇÃO DO EIXO Y
int button = 2; //PINO REFERENTE A LIGAÇÃO NO PINO KEY (EIXO Z)

boolean marcha = false;
boolean first = true;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button, INPUT_PULLUP);

  setSyncProvider(requestSync);
  Serial.println("Waiting for sync message");
}

void loop() {
  if (Serial.available()) {
    processSyncMessage();
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if(marcha) {
    validaDistancia(distance);  
  }
  joystick();
}

void validaDistancia(int distancia) {
  if (distancia > 30) {
    tone(buzzer,5000);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } else if (distancia > 15 && distancia < 30 ) {
    tone(buzzer,1000);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
  } else if (distancia < 15) {
    tone(buzzer,50);
    if (timeStatus()!= timeNotSet) {
      digitalClockDisplay();
    }
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
  }
}

void digitalClockDisplay(){
  if(first) {
    Serial.print("Primeira distância crítica registrada: ");
    first = false;
  } else {
    Serial.print("Carro em distância crítica: ");
  }
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year()); 
  Serial.println(); 
  delay(300);
}

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1652316737; // 1357041600

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) {
       setTime(pctime);
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0;
}

void joystick(){
    if((analogRead(eixo_X)) == 0){
        //Serial.println("Desliga");
        desligar();
    }else{
          if((analogRead(eixo_X)) == 1023){
              //Serial.println("Ligar");
              ligar();
          }else{
                if((analogRead(eixo_Y)) == 0){
                  //Serial.println("Direita");
                }else{
                      if((analogRead(eixo_Y)) == 1023){
                          //Serial.println("Esquerda");
                      }else{
                            if(digitalRead(button) == LOW){
                               //Serial.println("button PRESSIONADO");
                            }  
                      }
                }
          }
    }
}

void desligar() {
  marcha = false;
  noTone(buzzer);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);
}

void ligar() {
  marcha = true;
}
