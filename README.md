# DroneMultiWii
Drone utilizando MultiWii como base de prototipação

Configuração da disposição dos motores no frame

![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)

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

*Caso for utilizar o receptor proposto

Motor Frente/Esquerdo: D3
Motor Frente/Direito: D10
Motor Traseiro/Esquerdo: D11
Motor Traseiro/Direito: D9

D3 - Reservado para o receptor

MPU-6050
SCL - A5
SDA - A4
VCC - 5V

*Lembrando que os GND devem estar conectados entre o receptor, controlador e motores
*Testado com bateria LI-Po de 11.1V

RECEPTOR

Com outro Arduino reserve a porta D2 para conectar no Arduino controlador de voo do drone
Segue a imagem da configuração do NRF24
![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)

CONTROLE



