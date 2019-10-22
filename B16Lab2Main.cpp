#include "mbed.h"
AnalogIn analog_value(A5);
BusOut LED_OUT(D2,D3,D4,D5,D6,D7,D8,D9);
BusOut unit(D10,D11);
BusOut point(A1,A2,A3,A4);

int value_BusOut[] = {412,824,1236,1648,2060,2472,2884,3296};
int value_bit[] = {0,1,3,7,15,31,63,127,255}; 

float value_read;
int num_point,num_unit;

int main() {
  Serial pc(USBTX,USBRX);
  while(1) {
  value_read = analog_value.read();
  value_read = value_read*3300;

  num_unit = value_read/1000;
  num_point = (value_read - (num_unit*1000)) / 100;

  unit = num_unit;
  point = num_point;

  if(value_read < value_BusOut[0])
  {
    LED_OUT = value_bit[0];
  }
  else if(value_read < value_BusOut[1])
  {
    LED_OUT = value_bit[1];
  }
  else if(value_read < value_BusOut[2])
  {
    LED_OUT = value_bit[2];
  }
  else if(value_read < value_BusOut[3])
  {
    LED_OUT = value_bit[3];
  }
  else if(value_read < value_BusOut[4])
  {
    LED_OUT = value_bit[4];
  }
  else if(value_read < value_BusOut[5])
  {
    LED_OUT = value_bit[5];
  }
  else if(value_read < value_BusOut[6])
  {
    LED_OUT = value_bit[6];
  }
  else if(value_read < value_BusOut[7])
  {
    LED_OUT = value_bit[7];
  }
  else
  {
    LED_OUT = value_bit[8];
  }
  
  pc.printf("%.1f \t",value_read);
  pc.printf("%d.",num_unit);
  pc.printf("%d\n",num_point);


  }
}