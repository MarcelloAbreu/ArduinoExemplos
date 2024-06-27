const int led = 9;
const int botao1 = 2;
const int botao2 = 3;
const int botao3 = 4;
const int buzzer = 11;
int press1, press2, press3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  if (digitalRead(botao1) == LOW) {   
        botaoPressionado(botao1);
  } else if (digitalRead(botao2) == LOW) {
      botaoPressionado(botao2);
    } else if (digitalRead(botao3) == LOW){
      botaoPressionado(botao3);    
    }
}

void botaoPressionado(int botao) {
  if(press1 == 0){
      press1 = botao;
  } else if(press2 == 0){
      press2 = botao;
  }else if(press3 == 0){
      press3 = botao;
      verifica();
  }
}

void verifica() {
  if (press1 != botao1 && press2 != botao2 && press3 != botao3) {
    digitalWrite(led, HIGH);
    tone(buzzer,1000);  
  } else {
    digitalWrite(led, LOW);
    noTone(buzzer);
    
  }
  delay(100);
  press1, press2, press3 = 0;
}
