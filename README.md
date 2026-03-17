## Esteira Seletora de Peças com Visão Computacional

![Protótipo da Esteira](<imagens/Protótipo esteira.jpeg>)

Este projeto consiste em um sistema de automação mecatrônica que utiliza **Visão Computacional** para identificar cores em tempo real e comandar uma esteira física para realizar a triagem automática de peças. 

O projeto integra inteligência em Python com o controle robusto do Arduino, utilizando motores de passo e sensores analógicos.

## Funcionalidades
* **Detecção em Tempo Real:** Identifica cores (Verde e Vermelho) via webcam utilizando OpenCV.
* **Controle de Movimento Suave:** Utiliza a biblioteca `AccelStepper` no Arduino para evitar trancos mecânicos nos motores de passo.
* **Comunicação Serial:** Integração bidirecional PC-Arduino via porta COM.
* **Atuação Dinâmica:** Acionamento de motores de passo e módulos relê baseados no processamento de imagem e feedback de sensores.

## Tecnologias e Ferramentas
* **Linguagens:** Python 3.13, C++ (Arduino)
* **Bibliotecas Python:** `OpenCV`, `NumPy`, `PySerial`
* **Firmware:** `AccelStepper.h` para controle preciso de motores
* **Hardware:** Arduino Uno, Motores de Passo, Driver de Motor, Relê e Sensores Analógicos.

## Estrutura do Projeto
* `identificadorcomarduino.py`: Script principal de visão computacional em Python.
* `programacao_picotadeira/`: Código fonte (`.ino`) para controle do hardware via Arduino.
* `imagens/`: Registros do protótipo e do funcionamento do software.
* `.gitignore`: Configuração para manter o repositório limpo.

## Como Rodar o Projeto

1. **Upload do Arduino:**
   Abra o arquivo na pasta `programacao_picotadeira` na Arduino IDE e faça o upload para sua placa.

2. **Configuração do Python:**
   Instale as dependências necessárias:
   ```bash
   pip install opencv-python numpy pyserial
