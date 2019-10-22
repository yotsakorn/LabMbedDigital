#include "mbed.h"
#define time_wait 0.2

AnalogIn AnalogValue(A5);
BusOut LED_OUT(D2,D3,D4,D5,D6,D7,D8,D9);

int value_bit[] = {0,1,3,7,15,31,63,127,255}; 
int state1[] = {24,36,66,129};
int state2[] = {1,2,4,8,16,32,64,128};


InterruptIn SW_STATE1(D10);
InterruptIn SW_STATE2(D11);

int s1_count;
int s2_count;

void LED_State1()
{
    
    for(int i=0;i<8;i++)
    {
      LED_OUT = state2[i];
      wait(time_wait);
    }
    for(int i=7;i>0;i--)
    {
      LED_OUT = state2[i];
      wait(time_wait);
    }
    LED_OUT = 0;
    
}
void LED_State2()
{
    for(int i=0;i<4;i++)
    {
      LED_OUT = state1[i];
      wait(time_wait);
    }
    for(int i=3;i>=0;i--)
    {
      LED_OUT = state1[i];
      wait(time_wait);
    }
    LED_OUT = 0;
  
}

void Count_State1()
{
  s1_count = 1;
  s2_count = 0;
}
void Count_State2()
{
  s2_count = 1;
  s1_count = 0;
}


int main() 
{
  Serial pc(USBTX,USBRX);
  SW_STATE1.rise(&Count_State1);
  SW_STATE2.rise(&Count_State2);

  while(1)
  {
    if(s1_count == 1)
    {
      LED_State1();
    }
    else if(s2_count == 1)
    {
      LED_State2();
    }
    pc.printf("%d\t",s1_count);
    pc.printf("%d\n",s2_count);
  }
  
  
}