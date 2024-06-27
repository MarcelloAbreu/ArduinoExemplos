int ledAMARELO = 7;
int myButton = 11;
boolean ledStatus = false;

void setup() {
 pinMode(ledAMARELO, OUTPUT);
 pinMode(myButton,INPUT_PULLUP);
 Serial.begin(9600);

}

void loop() {
  if(digitalRead(myButton) == LOW){
    delay(500);
    if(ledStatus == false){
      digitalWrite(ledAMARELO,HIGH);
      ledStatus = true;
    }
    else{
      digitalWrite(ledAMARELO,LOW);
      ledStatus = false;      
    }
    escreveLog(ledStatus);
  }
}

void escreveLog(boolean myStatus){
  if(myStatus){
    Serial.println("Circuito OK pronto para uso");
  }
  else{
    Serial.println("Circuito está Desligado");
  }
}
