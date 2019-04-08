# DroneMultiWii
http://www.multiwii.com/wiki/index.php?title=Main_Page
Drone utilizando MultiWii como base de prototipação

Código para o drone se encontra em MultiWii_2_3.zip/MultiWii/config.h
(Abra na IDE Arduino e compile no Arduino Nano)

Configuração da disposição dos motores no frame

![alt text](https://github.com/lhcbernardes/DroneMultiWii/blob/master/Esquema%20drone.jpg)

*Caso for utilzar o receptor semelhante ao Receptor Flysky utilizar a seguinte configuração:

Motor Frente/Esquerdo: D3
Motor Frente/Direito: D10
Motor Traseiro/Esquerdo: D11
Motor Traseiro/Direito: D9

AUX2 - D8
AUX1 - D7
YAW - D6
PITCH - D5
ROLL - D4
THROTTLE - D2

MPU-6050
SCL - A5
SDA - A4
VCC - 5V

Caso for utilizar o receptor proposto

Motor Frente/Esquerdo: D3
Motor Frente/Direito: D10
Motor Traseiro/Esquerdo: D11
Motor Traseiro/Direito: D9

D3 - Reservado para o receptor

MPU-6050
SCL - A5
SDA - A4
VCC - 5V

Lembrando que os GND devem estar conectados entre o receptor, controlador e motores
Testado com bateria LI-Po de 11.1V

RECEPTOR

Com outro Arduino reserve a porta D2 para conectar no Arduino controlador de voo do drone
Segue a imagem da configuração do NRF24
![alt text](https://github.com/lhcbernardes/DroneMultiWii/blob/master/NRF.jpg)

CONTROLE

Tendo o conhecimento que um joystick semelhante ao encontrado em video-games seja o conjunto de potenciomentros (X e Y)
o controle sera composto por dois joysticks, dois switches, um Arduino e NRF24.

O joystick esquerdo utilizara as portas A0 e A1
O joystick direito utilizara as portas A2 e A3

Os switches D4 e D5

A configuração do NRF24 segue a da imagem
![alt text](https://github.com/lhcbernardes/DroneMultiWii/blob/master/NRF.jpg)

PARA REALIZAR CALIBRAÇÕES OU SALVAR CONFIGURAÇÕES PERSONALIZADAS UTILIZAR O SOFTWARE DA MULTIWII



