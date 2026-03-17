#include <Servo.h>

Servo meuServo;

void setup() {
  Serial.begin(9600);    // mesma taxa do Python
  meuServo.attach(9);    // servo conectado na porta 9
  meuServo.write(90);    // posição inicial (meio)
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();  // lê o caractere enviado pelo Python

    if (comando == 'G') {
      Serial.println("Recebido G - Ativando servo");

      // Movimento do servo
      meuServo.write(0);    // gira para a esquerda (ajuste se precisar)
      delay(200);           // espera meio segundo
      meuServo.write(90);   // volta para o centro
      delay(200);
    }
  }
}
