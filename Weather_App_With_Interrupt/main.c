#define _XTAL_FREQ 4000000

#define RS RD1
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include "lcd.h";
#include "config.h";

void welcome ()
{
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Embedded Systems");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("MiniProject-1");
    __delay_ms(500);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Presented By");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Agrippina W.M");
    __delay_ms(500);
    Lcd_Clear();

  
}


void ADC_Initialize()
{
 ADCON0 = 0b01000001; //ADC ON and Fosc/16 is selected
 ADCON1 = 0b11000000; // Internal reference voltage is selected
}

unsigned int ADC_Read(unsigned char channel)
{
 ADCON0 &= 0x11000101; //Clearing the Channel Selection Bits
 ADCON0 |= channel<<3; //Setting the required Bits
 __delay_ms(2); //Acquisition time to charge hold capacitor
 GO_nDONE = 1; //Initializes A/D Conversion
 while(GO_nDONE); //Wait for A/D Conversion to complete
 return ((ADRESH<<8)+ADRESL); //Returns Result
}

void ISR()
  {
    //TRISA = 0x00;
    //To check if the interrupt is initiated
    if(INTCONbits.INTF == 1)
    {
           __delay_ms(100);
        //clear the interrupt
        INTCONbits.INTF = 0;
        
        TRISD = 0x00;  //Setting portD output
                
            
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Button is Pushed");
            Lcd_Set_Cursor(2,2);
            Lcd_Write_String("Please Wait!");
            __delay_ms(2000);
             
            
            Lcd_Clear();
            Lcd_Set_Cursor(1,3);
            Lcd_Write_String("ISR ON");
            __delay_ms(2000);
           
            
            //blinking the LED on RA0
            for (int y=0; y<5; y++)
            {
                PORTAbits.RA0 = 1;
                __delay_ms(200);
                PORTAbits.RA0 = 0;
                __delay_ms(200);
            }
            

    }
   
    
  } 

  
 

void main()
{
  int i=0;  // shows the digit value to be displayed
  int flag=0;  //creates a delay
  int k1,k2,k3,k4,adc;
  TRISA = 0x00;  //Sets port A to receive input
  PORTA = 0x00;
  TRISD = 0x00;
  TRISC = 0x00;  //sets all port C as output
  PORTD = 0x00;
     

   
    //enabling the global interrupt
    INTCONbits.GIE = 1;
    //enabling the peripheral interrupt
    INTCONbits.PEIE = 1;
    //enabling the interrupt on RD0
    INTCONbits.INTE = 1;
        
    //welcome note
   //welcome();
    
    while(1)
    {
  //potentiometer values from the Pot-HG
    ADC_Initialize();
  //calling the subroutine to read values from the potentiometer
      
    adc=(ADC_Read(4));  //reads values from the potentiometer
    i=adc*0.488281;
    flag =0;  //only if flag is hundred i will get the ADC value
    
     //voltage ranges from 0-5V in the setup

     if(flag>=50) //wait till flag reaches 100
    {
       adc = (ADC_Read(4));
        i = adc*0.488281;
        flag=0; //only if flag is hundred "i" will get the ADC value
       }
       flag++; //increment flag for each flash
       
       //displaying values on the LCD screen
       k1 = (i/1000)%10;
       k2 = (i/100)%10;
       k3 = (i/10)%10;
       k4 = (i/1)%10;

        Lcd_Init();
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("VOLTAGE READING:");
        Lcd_Set_Cursor(2,5);
        Lcd_Write_Char(k1+'0');
        Lcd_Write_Char(k2+'0');
        Lcd_Write_String(".");
        Lcd_Write_Char(k3+'0');
        Lcd_Write_Char(k4+'0');
        Lcd_Write_String("V");
        __delay_ms(200);
        
        
        //introducing an interrupt
       ISR();
       
    }
       

    }
