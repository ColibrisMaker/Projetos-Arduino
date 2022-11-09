
// Declarando as portas do carro as portas (12, 9, 10, 13, 8, 11) não podem ser alteradas pois são padrões da ponte L298P

char ComandoRecebido; // Variavél que vai guadar o comando do carro 
int MA1 =  12;     // Motor A
int MA2 =  9;      // Motor A
int PWM_A =10;     // Velocidade PWM Motor A
int MB1 =  13;     // Motor B
int MB2 =  8;      // Motor B
int PWM_B =11;     // Velocidade PWM Motor B
int SPD = 150;     // Velocidade PWM 0 - 255
int buzzer = 4; // Declara a porta do buzzer 

// Declara as portas auxiliares luzes e buzina
int ledVerde = 5; // Leds dos semaforos 
int ledAmarelo = 6; // Leds dos semaforos 
int ledVermelho = 7; // Leds dos semaforos 
int ledAzulSirene = 3; // Sirene de Polcícia
int ledVermelhoSirene = 2; // Sirene de Polcícia


// Declara a variável de tempo de acionamento do led e tempo da sirene buzzer 

int tempo = 100; //variável usada para definir o tempo de acionamento do buzzer
int frequencia = 0; //variável usada para armazenar a frequencia que será usada no acionamento do buzzer
unsigned long millisTarefa1 = millis(); //variável que recebe o tempo atual em milissegundos
int temp = 250; //variável usada para definir o tempo de acionamento do led

void setup() {
  
// Declara como saída as portas do da placa L298P
pinMode(MA1, OUTPUT);   //Motor A1
pinMode(MA2, OUTPUT);   //Motor A2
pinMode(PWM_A, OUTPUT); //Speed PWM Motor A
pinMode(MB1, OUTPUT);   //Motor B1
pinMode(MB2, OUTPUT);   //Motor B2
pinMode(PWM_B, OUTPUT); //Speed PWM Motor B
pinMode(buzzer, OUTPUT); // Declara o buzzer como saída

// Declara as portas de saída 

pinMode(ledVerde, OUTPUT); 
pinMode(ledVermelho, OUTPUT); 
pinMode(ledAmarelo, OUTPUT); 
pinMode(ledAzulSirene, OUTPUT);
pinMode(ledVermelhoSirene, OUTPUT);
pinMode (buzzer, OUTPUT);

Serial.begin(9600);
Serial.println("Recebendo Dados");
}

void loop(){
  
if (Serial.available()){ // Avalia se existe comando enviados a porta serial  
ComandoRecebido = Serial.read();
  
}

switch (ComandoRecebido){

  case 'F': {// Caso for apertado o botão frente carro executa a função Frente
  Frente();
  break;
  }
  case 'B': {// Caso for apertado o botão frente carro executa a função Tras
  Tras();
  break;
  }
  case 'R': {// Caso for apertado o botão frente carro executa a função Frente
  Direita();
  break;
  }
  case 'L': {// Caso for apertado o botão frente carro executa a função Frente
  Esquerda();
  break;
  }
 case 'V': {
 SirenePolicia();
 break;
 }
 case 'v': {
 DesligaSirene();
 break;
}

}
}

// *******************************Funções para controle do carrinho *************************************************************************

// Para o carrro faz ré
void Frente()
{
digitalWrite(MA1, HIGH);
digitalWrite(MA2, LOW);
analogWrite(PWM_A, SPD);
digitalWrite(MB1, HIGH);
digitalWrite(MB2, LOW);


}
// O carrro faz ré
void Tras()
{
digitalWrite(MA1, LOW);
digitalWrite(MA2, HIGH);
analogWrite(PWM_A, SPD);
digitalWrite(MB1, LOW);
digitalWrite(MB2, HIGH);
analogWrite(PWM_B, SPD);

}
// O carrro faz curva para esquerda
void Esquerda()
{
digitalWrite(MA1, HIGH);
digitalWrite(MA2, LOW);
analogWrite(PWM_A, SPD);
digitalWrite(MB1, LOW);
digitalWrite(MB2, HIGH);
analogWrite(PWM_B, SPD);


}
// Para o carrro faz curva para direita
void Direita()
{
digitalWrite(MA1, LOW);
digitalWrite(MA2, HIGH);
analogWrite(PWM_A, SPD);
digitalWrite(MB1, HIGH);
digitalWrite(MB2, LOW);
analogWrite(PWM_B, SPD);


}
// Para o carrro 
void Parar()
{
digitalWrite(MA1, LOW);
digitalWrite(MA2, LOW);
analogWrite(PWM_A, 0);
digitalWrite(MB1, LOW);
digitalWrite(MB2, LOW);
analogWrite(PWM_B, 0);
}

// ***********************************************Acionamento da Buzina***********************************************************************

void SirenePolicia(){
   Parar();
   for (frequencia = 150; frequencia < 1800; frequencia += 1) { //Define frequencia igual a 150; verifica se frequencia é menor que 1800; realiza a soma frequencia = frequencia + 1
    led(); //Chama a função led
    tone(buzzer, frequencia, tempo); //Aciona o led com frequência definida pelo for e tempo igual a 100 milissegundos
    delay(1); //delay de 1 milissegundos
  }
  for (frequencia = 1800; frequencia > 150; frequencia -= 1) { //Define frequencia igual a 1800; verifica se frequencia é maior que 150; realiza a subtração frequencia = frequencia - 1
    led(); //Chama a função led
    tone(buzzer, frequencia, tempo); //Aciona o led com frequência definida pelo for e tempo igual a 100 milissegundos
    delay(1); //delay de 1 milissegundos
    DesligaSirene();
  }

}

void led() {
  if (millis() - millisTarefa1 > temp) {//Se o resultado da subtração de millis() - millisTarefa1 for maior que temp (250 milissegundo)
    digitalWrite(ledAzulSirene, HIGH);//Liga o LED azul
    digitalWrite(ledVermelhoSirene, LOW);//Desliga o LED vermelho
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    
  } else {//Senão
    digitalWrite(ledAzulSirene, LOW);//Desliga o azul
    digitalWrite(ledVermelhoSirene, HIGH);//Liga o LED vermelho
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  }
  if ((millis() - millisTarefa1) > (2 * temp)) {//Se o resultado da subtração de millis() - millisTarefa1 for maior que 2 vezes temp (500 milissegundo)
    millisTarefa1 = millis();//Atribui a millisTarefa1 o valor de millis()
  }
}

void DesligaSirene(){
   noTone(buzzer);
   digitalWrite(ledVerde, LOW);
   digitalWrite(ledAmarelo, LOW);
   digitalWrite(ledVermelho, LOW);
  
}
