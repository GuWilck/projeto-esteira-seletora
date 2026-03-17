#include <AccelStepper.h>

// Definição dos pinos dos sensores
#define pinEsp1 A0
#define pinEsp2 A1

// Relê Azul
#define pinRelay 2

// Pinos do Primeiro Stepper
#define IN1 4  // IN1
#define IN2 5  // IN2
#define IN3 6  // IN3
#define IN4 7  // IN4

// Pinos do Segundo Stepper
#define IN5 8  // IN1
#define IN6 9  // IN2
#define IN7 10 // IN3
#define IN8 11 // IN4

// Criação dos objetos AccelStepper para cada motor
AccelStepper myStepper1(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4);
AccelStepper myStepper2(AccelStepper::FULL4WIRE, IN5, IN7, IN6, IN8);

int esp1, esp2;

void setup() {
  // Configuração dos pinos dos sensores e do relê
  pinMode(pinEsp1, INPUT);
  pinMode(pinEsp2, INPUT);
  pinMode(pinRelay, OUTPUT);

  // Configuração da velocidade dos motores (em passos por segundo)
  myStepper1.setMaxSpeed(5 * 2048 / 60); // Converte 15 RPM para passos por segundo
  myStepper2.setMaxSpeed(15 * 2048 / 60);

  // Configuração da aceleração dos motores
  myStepper1.setAcceleration(500);  // Aceleração suave
  myStepper2.setAcceleration(1000);
}

void loop() {
  // Leitura dos sensores
  esp1 = analogRead(pinEsp1);
  esp2 = analogRead(pinEsp2);

  // Controle dos motores baseado nos sensores
  if (esp1 > 500) {
    myStepper1.move(-128); // Move o motor 1 128 passos para trás
    myStepper2.move(-128); // Move o motor 2 128 passos para trás
  } else {
    desligarMotores(); // Desliga os motores se esp1 for falso
  }

  // Executa o movimento dos motores
  myStepper1.run();
  myStepper2.run();

  // Controle do relê baseado no segundo sensor
  if (esp2 > 500) {
    digitalWrite(pinRelay, HIGH);
  } else {
    digitalWrite(pinRelay, LOW);
  }
}

// Função para desligar os motores
void desligarMotores() {
  // Desativa todos os pinos dos motores
  for (int i = IN1; i <= IN4; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for (int i = IN5; i <= IN8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}
