
#include <mega128a.h>
#include <stdio.h>
#include <delay.h>
#include <string.h>
#include <stdlib.h>
#include <alcd.h>
#include <i2c.h>
///////////////////
#define next PINA.0
#define previos PINA.2
#define ok PINA.1   //
#define KFR PINC.6  //
#define KFL PINC.7   //
#define up PINB.1     //
#define down PINB.2   //
#define ML1 PORTB.7
#define ML2 PORTB.6
#define MR1 PORTB.5
#define MR2 PORTB.4

#define MVL3 PIND.0
#define MVL2 PIND.1
#define MVL1 PORTD.2   //
#define MVR1 PORTD.4   //
#define MVR2 PIND.5    //
#define MVR3 PIND.6   //
#define buzzer PORTD.7

#define KBL PORTG.0   vv
#define KBR PORTG.1   vv
#define Led PORTE.6   vv
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))
///////////////////////////////////////////



void defall(void);
unsigned int read_adc(unsigned char adc_input);

void main(void)
{
defall();
while (1)
      {

      }
}
void defall(void)
{
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (1<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);

DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (0<<PORTB0);

DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
PORTC=(1<<PORTC7) | (1<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (1<<DDD4) | (0<<DDD3) | (1<<DDD2) | (0<<DDD1) | (0<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

DDRE=(0<<DDE7) | (1<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (0<<DDE1) | (0<<DDE0);
PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (0<<PORTE1) | (0<<PORTE0);

DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);

DDRG=(0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
PORTG=(0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (1<<PORTG1) | (1<<PORTG0);
lcd_init(20);
i2c_init();

// ADC initialization
// ADC Clock frequency: 691.200 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ACME);
}


