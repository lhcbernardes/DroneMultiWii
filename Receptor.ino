#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*
*	Configuracao principal do receptor, o numero de canais, frequencia dos pulsos e a forca
*/
#define channel_number 6  //numero de canais
#define sigPin 2  //set PPM signal output pin on the arduino
#define PPM_FrLen 27000  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 400  //Forca do pulso

int ppm[channel_number];

//Manter o mesmo do emissor
const uint64_t pipeIn =  0xE8E8F0F0E1LL;

RF24 radio(9, 10);

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
  // valores de seguranca quando receber os dados
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2= 0;
  
  setPPMValuesFromData();
}

void setPPMValuesFromData()
{
  ppm[0] = map(data.throttle, 0, 255, 1000, 2000);
  ppm[1] = map(data.yaw,      0, 255, 1000, 2000);
  ppm[2] = map(data.pitch,    0, 255, 1000, 2000);
  ppm[3] = map(data.roll,     0, 255, 1000, 2000);
  ppm[4] = map(data.AUX1,     0, 1, 1000, 2000);
  ppm[5] = map(data.AUX2,     0, 1, 1000, 2000);  
  }

/**************************************************/

void setupPPM() {
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, 0);  //torna o sinal do PPM para 0

  cli();
  TCCR1A = 0; // set entire TCCR1 to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register (not very important, sets the timeout for the first interrupt)
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
}

void setup()
{  
  resetData();
  setupPPM();
  
  radio.begin();
  radio.setDataRate(RF24_250KBPS); 
  radio.setAutoAck(false);

  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

/**************************************************/

unsigned long lastRecvTime = 0;

void recvData()
{  
  while ( radio.available() ) {        
    radio.read(&data, sizeof(MyData));
    lastRecvTime = millis();
  }
}

/**************************************************/

void loop()
{
  recvData();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    // sem sinal????
    resetData();
  }
  
  setPPMValuesFromData();
}

/**************************************************/

#error Delete this line befor you cahnge the value (clockMultiplier) below
#define clockMultiplier 2 // deixa em 2 caso 16MHz arduino, caso 1 para 8MHz arduino

ISR(TIMER1_COMPA_vect){
  static boolean state = true;

  TCNT1 = 0;

  if ( state ) {
    //fim do pulso
    PORTD = PORTD & ~B00000100; // turn pin 2 off. Could also use: digitalWrite(sigPin,0)
    OCR1A = PPM_PulseLen * clockMultiplier;
    state = false;
  }
  else {
    //inicio do pulso
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    PORTD = PORTD | B00000100; // liga porta 2. pode usar: digitalWrite(sigPin,1)
    state = true;

    if(cur_chan_numb >= channel_number) {
      cur_chan_numb = 0;
      calc_rest += PPM_PulseLen;
      OCR1A = (PPM_FrLen - calc_rest) * clockMultiplier;
      calc_rest = 0;
    }
    else {
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * clockMultiplier;
      calc_rest += ppm[cur_chan_numb];
      cur_chan_numb++;
    }     
  }
}
