int ledAMARELO = 7; //led colocado no pino 7
int myButton = 11; //botão colocado no pino 11


boolean ledStatus = false; //estado do led inicializado como falso

void setup() {
  // inicializações necessárias
  pinMode(ledAMARELO, OUTPUT);
  pinMode(myButton, INPUT_PULLUP);
}

void loop() {
  //bloco principal que será executado até que o equipamento seja desligado
  //para testar o status do botão neste caso é necessário ligar o aterramento nele também
  if (digitalRead(myButton) == LOW) //testa se o botão foi pressionado 
  {    
    if (!ledStatus) //pode ser também ledStatus == false
    {
      digitalWrite(ledAMARELO, HIGH); //se o estado for falso ele liga o led e seta o estado para verdadeiro
      ledStatus = true;
    }
    else
    {
      digitalWrite(ledAMARELO, LOW); //se o estado for verdadeiro ele desliga ga o led e seta o estado para falso
      ledStatus = false;
    }
  }

}
