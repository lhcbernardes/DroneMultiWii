
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//IMPORTANTE: Manter a mesma numeracao no receptor
const uint64_t pipeOut = 0xE8E8F0F0E1LL; 

RF24 radio(9, 10); // select  CSN  pin

// Os dados em um unico canal
struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
};

MyData data;

void resetData() 
{
  //Valor inicial de cada canal, devido ao joystick utilizado 
  // Throttle esta em 0 para parar os motores
    
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2 = 0;
}

void setup()
{
  //Inicia os valores
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();
}

/**************************************************/

// retorna a posicao correta dos joysticks convertendo o analogico
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}

void loop()
{
  // Calibracao dos joysticks 
  data.throttle = mapJoystickValues( analogRead(A0), 13, 524, 1015, true );
  data.yaw      = mapJoystickValues( analogRead(A1),  1, 505, 1020, true );
  data.pitch    = mapJoystickValues( analogRead(A2), 12, 544, 1021, true );
  data.roll     = mapJoystickValues( analogRead(A3), 34, 522, 1020, true );
  data.AUX1     = digitalRead(4); 
  data.AUX2     = digitalRead(5);

  radio.write(&data, sizeof(MyData));
}
