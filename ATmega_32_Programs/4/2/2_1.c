void delay()        //Prescalar=1/256
{
     TCNT1H = 0X00;
     TCNT1L = 0X00;

     TCCR1A = 0X00;
     TCCR1B = 0X0C;
     OCR1AH = 0X3D;
     OCR1AL = 0X09;

     while((TIFR&(0X10))==0);

     TCNT1L = 0X00;
     TIFR = 0x1<<OCF1A;
}
void main()
{
     DDRB= 0xFF;
     while(1)
     {
             PORTB.B0 ^=0x1;
             delay();
     }
}