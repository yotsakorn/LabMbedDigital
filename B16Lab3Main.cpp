#include <mbed.h>

Serial user_side(D8, D2); // change to D8, D2 for BT
Serial server_side(D1,D0); //serial PC

BusOut STATE_number(D3,D4,D5,D6);
AnalogIn analog_value(A5);
float value_read;

int main()
{

  uint8_t STATE_Display = 0;

  uint8_t input_user = 0; 
  uint8_t input_server = 0;


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
        server_side.printf("Enter Y or etc. : \r");
        STATE_Display = 12;
        break;

      case '2':
        server_side.printf("Request : Read Analog Value\n");
        server_side.printf("Enter Y or etc. : \r");
        STATE_Display = 13;
        break;

      default:
        STATE_Display = 10;
        break;
      }
      break;

    case 12:
      switch(input_server)
        {
          case 0:
            break;
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

      case 13:
      switch(input_server)
        {
          case 0:
            break;
          case 'Y':
            server_side.printf("----------------------\n");
            server_side.printf("Access Complete\n");
            server_side.printf("----------------------\n");
            STATE_Display = 40;
            break;
          default:
            server_side.printf("----------------------\n");
            server_side.printf("Access Denied\n");
            server_side.printf("----------------------\n");
            STATE_Display = 19;
            break;
        }
      break;
      

    ///////////////////////////////////////////////////////////////////////////////////////
    case 19: //error state
      user_side.printf("----------------------\n");
      user_side.printf("Access Denied\n");
      user_side.printf("----------------------\n");
      user_side.printf("\n");
      STATE_Display = 10;
      break;

    
    ///////////////////////////////////////////////////////////////////////////////////////
    case 20: //display one time state
      user_side.printf("----------------------\n");
      user_side.printf("Access Complete\n");
      user_side.printf("----------------------\n");
      user_side.printf("\n");
      user_side.printf("Enter Number 0-9 : ");
      STATE_Display = 21;
      break;

    case 21:
      switch(input_user)
      {
        case 0:
          break;

        case '0':
          server_side.printf("Request : Number 0 \n");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 22;
          break;
         
        case '1':
          server_side.printf("Request : Number 1 \n");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 23;
          break;

        case '2':
          server_side.printf("Request : Number 2");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 24;
          break;
        case '3':
          server_side.printf("Request : Number 3");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 25;
          break;
        case '4':
          server_side.printf("Request : Number 4");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 26;
          break;
        case '5':
          server_side.printf("Request : Number 5");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 27;
          break;
        case '6':
          server_side.printf("Request : Number 6");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 28;
          break;
        case '7':
          server_side.printf("Request : Number 7");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 29;
          break;
        case '8':
          server_side.printf("Request : Number 8");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 30;
          break;
        case '9':
          server_side.printf("Request : Number 9");
          server_side.printf("Enter Y or etc. : \n");
          STATE_Display = 31;
          break;
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;
      }
      break;

      /////////////******************************************//////////////////////

    case 22:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 0;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;

    case 23:
        switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 1;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;
    case 24:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 2;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;

    case 25:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 3;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;

    case 26:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 4;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;
    
    case 27:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 5;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;

    case 28:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 6;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;

    case 29:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 7;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;
    
    case 30:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 8;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;
    
    case 31:
      switch(input_server)
      {
        case 0:
          break;

        case 'Y':
          STATE_number = 9;
          STATE_Display = 10;
          break;
      
        default:
          user_side.printf("Please Enter Number 0-9\n");
          STATE_Display = 21;
          break;

      }
      break;

    /////////////////////////////////////////////////////////////////////////////////////////
    case 40: //display state
      value_read = analog_value.read();
      value_read = value_read*3.3;
      user_side.printf("Analog value read = %4.2f V.\n",value_read);
      STATE_Display = 10;
      break;

  }
}
}