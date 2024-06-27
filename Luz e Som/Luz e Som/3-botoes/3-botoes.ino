int btn1 = 1;
int btn2 = 2;
int btn3 = 3;
int snd = 7;
int led = 8;
int startCheck = 0;

String senha = "123";
String senhaAtual = "";
int totalPressionado = 0;
int lastBtn1,lastBtn2,lastBtn3 = LOW;
int state1, state2, state3 = LOW;

void setup()
{
	Serial.begin(9600);
	pinMode(led, OUTPUT);
  pinMode(btn1, INPUT);
	pinMode(btn2, INPUT);
	pinMode(btn3, INPUT);
	pinMode(snd, OUTPUT);
}

void loop()
{	
state1 = digitalRead(btn1);
	if (state1 != lastBtn1) {
    		lastBtn1 = state1;
		if (state1 == HIGH) {
			totalPressionado+=1;
			senhaAtual +="1";
			/*
	     	Serial.println("Button 1 pressed!");
			Serial.println("Senha: " +  senhaAtual);
			Serial.println("T: " + totalPressionado);
			*/
	   }
	}
	
state2 = digitalRead(btn2);
  if (state2 != lastBtn2) {
    lastBtn2 = state2;
  if (state2 == HIGH) {
		totalPressionado+=1;
		senhaAtual +="2";
	}
}

state3 = digitalRead(btn3);
 if (state3 != lastBtn3) {
     lastBtn3 = state3;
 if (state3 == HIGH) {
			totalPressionado+=1;
			senhaAtual +="3";	     	
	 }
}

delay(100);

if (totalPressionado == 3) verifica();
}

void verifica()
{
	if (startCheck != 0)
	{
		totalPressionado = 0;
	if (senhaAtual != senha)
		{
			Serial.println("Senha diferente");
			digitalWrite(led, HIGH); 
			 
			delay(500);
			
			Alarme(snd);
		}
		else
		{
			Serial.println("Senha IGUAL");
			digitalWrite(led, LOW); 
		}
			
		senhaAtual = "";	
		digitalWrite(led, LOW);     
	}
	else
		startCheck += 1;
}

void Alarme(int buzz) { //This function produces the 3rd siren (AMBULANCE sound).tone(buzz,440,200);
	for(int i=0;i<=3;i++)
	{
		noTone(buzz);
		tone(buzz,494,500);
		delay(300);
		
		noTone(buzz);
		tone(buzz,523,300);
		delay(200);
		
		noTone(buzz);
	}
}
