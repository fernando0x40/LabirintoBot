/*Programa do robô que resolve labirintos do grupo:
* Ricardo Vieira
* Flávia Abdalla
* Fernando Bisi
 */
//biblioteca do sensor ultrassônico
#include <Ultrasonic.h>

//pinos dos motores A e B
#define inA1 9
#define inA2 6
#define inB3 11
#define inB4 10
//pinos dos sensores ultrassônico
#define echoE 5
#define triggE 4
#define echoF 2
#define triggF 3
//variáveis de ajuste
#define veloA 190
#define veloB 180
#define tempoS 3000
#define tempoP 1000
#define tempoE 300
#define tempoD 300
#define distMaxF 50
#define distMaxE 50

//Inicialização dos sensores
Ultrasonic ultrasonicE(triggE,echoE);
Ultrasonic ultrasonicF(triggF,echoF);

void setup() {
  // put your setup code here, to run once:
pinMode(inA1,OUTPUT);
pinMode(inA2,OUTPUT);
pinMode(inB3,OUTPUT);
pinMode(inB4,OUTPUT);
pinMode(echoE,INPUT);
pinMode(echoF,INPUT);
pinMode(triggE,OUTPUT);
pinMode(triggF,OUTPUT);
Serial.begin(9600);
Serial.println("Lendo dados do sensor...\n");
delay(tempoS);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  //variável que armazena o tempo do echo (frontal)
  long tempoEchoF = ultrasonicF.timing();
  //variável que armazena a distância em cm (frontal)
  float distF = ultrasonicF.convert(tempoEchoF, Ultrasonic::CM);
  Serial.print("Distancia frontal: ");
  Serial.print(distF);
  Serial.print(" - ");
  //variável que armazena o tempo do echo (esquerda)
  long tempoEchoE = ultrasonicE.timing();
  //variável que armazena a distância em cm (esquerda)
  float distE = ultrasonicE.convert(tempoEchoE, Ultrasonic::CM);
  Serial.print("Distancia esquerda: ");
  Serial.print(distE);
  Serial.print('\n');
  if(distF > distMaxF)
  {
    andarFrente(veloA,veloB);
    //delay(500);
    //ajuste da trajetória
    if(distE < 7)
    {
      //ajuste para a direita
      Serial.print("Ajustando para a direita\n");
      andarFrente(150,130);
    }
    else if(distE > 12 && distE < 45)
    {
      //ajuste para a esquerda
      Serial.print("Ajustando para a esquerda\n");
      andarFrente(130,150);
    } //vira a esquerda se aparecer um entrada à esquerda
    else if(distE > distMaxE)
    {
      Serial.print("Virando a esquerda\n");
      parar(tempoP);
      virarEsquerda(tempoE,veloA,veloB);
      parar(tempoP);
    }
  }else
  {
    Serial.print("Parede a frente, virando a esquerda\n");
    parar(tempoP);
    virarEsquerda(tempoE,veloA,veloB);
    parar(tempoP);
  }
}

void andarFrente(int velA, int velB)
{
  digitalWrite(inA2,LOW);
  digitalWrite(inB4,LOW);
  analogWrite(inA1,velA);
  analogWrite(inB3,velB);
}
void virarEsquerda(int tempo, int velA, int velB)
{
  digitalWrite(inA1,LOW);
  digitalWrite(inB4,LOW);
  analogWrite(inA2,velA);
  analogWrite(inB3,velB);
  delay(tempo);
}
void virarDireita(int tempo, int velA, int velB)
{
  digitalWrite(inA2,LOW);
  digitalWrite(inB3,LOW);
  analogWrite(inA1,velA);
  analogWrite(inB4,velB);
  delay(tempo);
}
void parar(int tempo)
{
  digitalWrite(inA1,LOW);
  digitalWrite(inB3,LOW);
  digitalWrite(inA2,LOW);
  digitalWrite(inB4,LOW);
  delay(tempo);
}

