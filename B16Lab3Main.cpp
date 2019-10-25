#include <mbed.h>

Serial user_side(D8, D2); // change to D8, D2 for BT
Serial server_side(D1,D0); //serial PC

DigitalOut myled(LED1);

BusOut STATE_number(D3,D4,D5,D6);
AnalogIn analog_value(A5);
float value_read;

int main()
{

  uint8_t STATE_Display = 0;

  uint8_t input_user = 0; 
  uint8_t input_server = 0;

  uint64_t nextLedTimeUs = 0;
  uint64_t ledPeriodUs = 500000;

  ///////////////////////////////******* Loop *********//////////////////////////////////////////

  while (1)
  {
    input_user = 0;    
    input_server = 0;

    if (user_side.readable())
    {
      input_user = user_side.getc();
    }
    if (server_side.readable())
    {
      input_server = server_side.getc();   
    }

    ////////////////////////////////////////////////////////////////////////////////////
    switch (STATE_Display)
    {
    case 0:
      STATE_Display = 10;
      break;

    case 10: 
      user_side.printf("************\n");
      user_side.printf("   Menu   \n");
      user_side.printf("************\n");
      user_side.printf("1.7-Segment Show Number 0-9 \n");
      user_side.printf("2.Read Analog Value\n");
      user_side.printf("\n");
      STATE_Display = 11;
      break;

    ////////////////////////////////////////////////////////////////////////////////////
    case 11: //wait state for input
      switch (input_user)
      {

      case 0:
        //no input ; just wait input
        break;

      case '1':
        server_side.printf("Request : 7-Segment Show Number 0-9\n");
        server_side.printf("Enter Y or etc. : ");
        while(user_side.readable() == 0)
        {
        }
        switch(input_server)
        {
          case 'Y':
            server_side.printf("----------------------\n");
            server_side.printf("Access Complete\n");
            server_side.printf("----------------------\n");
            STATE_Display = 20;
            break;
          default:
            server_side.printf("----------------------\n");
            server_side.printf("Access Denied\n");
            server_side.printf("----------------------\n");
            STATE_Display = 19;
            break;
        }
        break;

      case '2':
        server_side.printf("Request : Read Analog Value\n");
        server_side.printf("Enter Y or etc. : ");
        while(user_side.readable() == 0)
        {
        }
        switch(input_server)
        {
          case 'Y':
            server_side.printf("----------------------\n");
            server_side.printf("Access Complete\n");
            server_side.printf("----------------------\n");
            STATE_Display = 30;
            break;
          default:
            server_side.printf("----------------------\n");
            server_side.printf("Access Denied\n");
            server_side.printf("----------------------\n");
            STATE_Display = 19;
            break;
        }
        break;

      default:
        STATE_Display = 19;
        break;
      }
      break;

    ///////////////////////////////////////////////////////////////////////////////////////
    case 19: //error state
      STATE_Display = 10;
      break;

    
    ///////////////////////////////////////////////////////////////////////////////////////
    case 20: //display one time state
      user_side.printf("Enter Number 0-9 : ");
      STATE_Display = 21;
      break;

    case 21:
      switch(input_user)
      {
        case '0':
            server_side.printf("Request : Number 0");
            while(input_server != 'Y')
            {}
            STATE_number = 0;
            break;
        case '1':
            server_side.printf("Request : Number 1");
            while(input_server != 'Y')
            {}
            STATE_number = 1;
            break;
        case '2':
            server_side.printf("Request : Number 2");
            while(input_server != 'Y')
            {}
            STATE_number = 2;
            break;
        case '3':
          STATE_number = 3;
          break;
        case '4':
          STATE_number = 4;
          break;
        case '5':
          STATE_number = 5;
          break;
        case '6':
          STATE_number = 6;
          break;
        case '7':
          STATE_number = 7;
          break;
        case '8':
          STATE_number = 8;
          break;
        case '9':
          STATE_number = 9;
          break;
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 20;
          break;
      }
      break;


    /////////////////////////////////////////////////////////////////////////////////////////
    case 30: //display state
      while(input_user == 0)
      {
        value_read = analog_value.read();
        value_read = value_read*3.3;
        user_side.printf("Analog value read = %4.2f V.\n",value_read);
      }
      STATE_Display = 10;
      break;
  }
}