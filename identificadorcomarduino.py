import cv2
import numpy as np
import serial
import time

# Configuração do Arduino
porta_arduino = 'COM5'  # ajustar porta
baud_rate = 9600
arduino = serial.Serial(porta_arduino, baud_rate, timeout=1)
time.sleep(2)  # aqui ele vai esperar o Arduino inicializar

cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("[ERRO] Não foi possível acessar a câmera.")
    exit(1)

print("[INFO] Iniciando detecção de cores e envio para Arduino...")

peca_presente = False
cor_anterior = None
min_area = 5000  # área mínima para a peça passar tranquila

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # DETECÇÃO DE VERMELHO 
    lower_red1 = np.array([0, 120, 70])
    upper_red1 = np.array([10, 255, 255])
    mask_red1 = cv2.inRange(hsv, lower_red1, upper_red1)
    lower_red2 = np.array([170, 120, 70])
    upper_red2 = np.array([180, 255, 255])
    mask_red2 = cv2.inRange(hsv, lower_red2, upper_red2)
    mask_red = mask_red1 + mask_red2
    area_red = cv2.countNonZero(mask_red)

    #  DETECÇÃO DE VERDE
    lower_green = np.array([36, 100, 100])
    upper_green = np.array([86, 255, 255])
    mask_green = cv2.inRange(hsv, lower_green, upper_green)
    area_green = cv2.countNonZero(mask_green)

    cor_detectada = None
    if area_red > min_area:
        cor_detectada = 'Vermelho'
    elif area_green > min_area:
        cor_detectada = 'Verde'

    # Lógica por peça
    if cor_detectada:
        if not peca_presente or cor_detectada != cor_anterior:
            print(f"[PEÇA DETECTADA] {cor_detectada}")
            if cor_detectada == 'Verde':
                # envia sinal para Arduino
                arduino.write(b'G')  # G = verde
                print("[ENVIO] Sinal enviado para Arduino")
            peca_presente = True
            cor_anterior = cor_detectada
    else:
        peca_presente = False
        cor_anterior = None

    cv2.imshow("Camera", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
