//besmellaherrahmanerrahim
#include <mega128a.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <dynamixelPro2018.h>
#include <iobits.h>  // EQUBIT

#include <alcd.h>
#asm
   .equ __i2c_port=0x1b ;PORTA
   .equ __sda_bit=7
   .equ __scl_bit=6
#endasm
#include <i2c.h>

#define xs 20
#define ys 10
#define oneMin 3040

#define CR TOSC1      // RIGHT ENCODER
                                           
#define Mot1  PORTB.3    // motor victim
#define Mot2  PORTB.2

#define check_sarbala    (shib1>20&&shib1<40)
#define check_sarpaeen   (shib1>200&&shib1<235)

#define R1  PORTB.4
#define SR1 OCR1A       // Speed of L2 PORTB.7
#define SL1 OCR1B       // Speed of R2 PORTB.4
#define L1  PORTB.7

#define next_page    PINA.0
#define enter        PINA.1
#define previuse_page    PINA.2
#define increase     PINB.1
#define decrease     PINB.2

//#define PBACK PINC.7

#define KFL PINC.7    // SWFL
#define KFR PINC.6    // SWFR
#define KBL TSTBIT(PING,0)
#define KBR TSTBIT(PING,1)

#define ULTRA_F  PINC.3
#define ULTRA_RF PINC.0
#define ULTRA_RB PINA.3
#define ULTRA_LF PINC.1
#define ULTRA_LB PINB.3

#define buz     PORTD.7
#define LED_ON    PORTE.6=1;
#define LED_OFF   PORTE.6=0;

#define ADC_VREF_TYPE 0x00

#define deg        cmps(1)
#define shib1      cmps(2)                                   
#define shib2      cmps(3)

#define UF      ULTRA(1)   
#define ULF     ULTRA(2)  //ULTRA SONIC
#define URF     ULTRA(3)
#define ULB     ULTRA(4)
#define URB     ULTRA(5)
#define UR      adc(4)
#define UL      adc(5)

#define SDR adc(0)
#define SDL adc(1)


#define beep(num)   for(i=0;i<num*2;i++) {buz=~buz;delay_ms(50);}
#define start_pwm  {TCCR1A=0xA1;TCCR1B=0x0B;}
#define CHARKH 6

#define T0 TCNT*256 +TCNT0

#define tempL  MLX(106)
#define tempR  MLX(58)
#define tempF  MLX(250)
typedef unsigned char byte;

typedef enum {false,true} bool;

flash byte char0[8]={0x00, 0x0F, 0x09, 0x0B, 0x1B, 0x18, 0x00, 0x00};
flash byte char1[8]={0x0E, 0x1B, 0x11, 0x11, 0x13, 0x17, 0x1F, 0x1F};
flash byte char2[8]={0x00, 0x0A, 0x00, 0x00, 0x11, 0x0E, 0x00, 0x00};//:-)
flash byte char3[8]={0x00, 0x0A, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00};//Heart
flash byte char4[8]={0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F};//[]
flash byte char5[8]={0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00};//|




eeprom int cheshmak =10,flagt=0;
eeprom unsigned int STR,T90L,T90R,T180,TimeAgo=0;
eeprom unsigned char Xramp,Yramp,temp;
eeprom unsigned char xcp,ycp;
eeprom signed char mem[60][30],lastM[2];
//Olaviat==1 (mamuli) , Olaviat==2 (start az bala), Olaviat==3(start az bala + returning=1) ,Olaviat==4(2ta Ramp darim Ke aln 2 2omie im!(IO 2017))
eeprom signed int Xd=40,Yd=-10,Olaviat=0,number,Tedad;
eeprom int AXmin=440,AXmax=670;
eeprom char returning=0;
eeprom int djN,djE,djS,djW;    // degree of North east saout west
eeprom int DN,DE,DS,DW;
eeprom bool _lastM;

bit sarbala=0,sarpaeen=0,back;
bit vfounded=0,Timer_on=0;

char ulf_value;
char str_cnt,right_cnt,left_cnt; //tedad  dafaate harekat be samte jahatha
char text[40];
char M,memL,memF,memR,memB;
char M;

//bool LeftFar=false,RightFar=false;
static int error1,error2;
int DL,DF,DR,DB;
int x,y;
int dir=1;
int i;
int error;
int TCNT;
unsigned int TimeAgo1=0;
int signed dj=0;

int testTurnL=110,testTurnR=715;

void sarbalaee (void);
void sarpaeeni (void);
void go (int spl,int spr);
void Tanzim(void);

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
    {
    TCNT++;
    TCNT0=0;
    }

    static bit UFupdate=0,ULFupdate=0,URFupdate=0,ULBupdate=0,URBupdate=0;
    static char previous_ultra=0;
    static unsigned int refresh_time=0;
    unsigned int TC2=0;
    
interrupt [TIM2_OVF] void timer2_ovf_isr(void)
    {
    if(Timer_on==1)
     {
     TimeAgo1++;
     if (TimeAgo1>=oneMin/60)
       {
       TimeAgo++;
       TimeAgo1=0;
       }
     if(TimeAgo>=120&& flagt==0)
      {
      flagt=1;
      }
     else if(TimeAgo>=240&& flagt==1)
      {
      flagt=2;
      }
     else if(TimeAgo>=360&& flagt==2)
      {
      flagt=3;
      } 
     } 
    }
int ULTRA(char number)
    {   
    static int value;       
    //tcnt+=TCNT1;  // adad TCNT ro save mikonim ta badan dobare bezarim tooye TCNT
//    if (previous_ultra!=number) // age meghdare ye ultra dige khaste shod
//        while(refresh_time<wait_time);
//    previous_ultra=number;

    if (number==1)          // UF
        {
        DDRC.3=1;    
            
        PORTC.3=1;
        delay_us(20);
        PORTC.3=0; 
            
        DDRC.3=0;   
            
        TCNT2=0;TC2=0;
        while(PINC.3==0 && TC2<100)
            { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
            }
        TCNT2=0;TC2=0;
        while(PINC.3==1 && TC2<100)     
            { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
            }
        value= (TC2 * 250 + TCNT2) /8;
        }
    else if (number==2)     // ULF
        {
        DDRC.1=1;
        PORTC.1=1;
        delay_us(20);
        PORTC.1=0;
        DDRC.1=0;
        TCNT2=0;TC2=0;
        while(PINC.1==0 && TC2<50)
            { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
            }
        TCNT2=0;TC2=0;
        while(PINC.1==1 && TC2<50)
            { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
            }
        value= (TC2 * 255 + TCNT2) /8;
        }
    else if (number==3)     // URF
        {   
        DDRC.0=1;
        PORTC.0=1;
        delay_us(20);
        PORTC.0=0;
        DDRC.0=0;
        TCNT2=0;TC2=0;
        while(PINC.0==0 && TC2<100)
        { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
        }
        TCNT2=0;TC2=0;
        while(PINC.0==1 && TC2<100)
        { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
        }
        value= (TC2 * 250 + TCNT2) /8;
        }

    else if (number==4)     // ULB
        {   
        DDRB.3=1;
        PORTB.3=1;
        delay_us(20);
        PORTB.3=0;
        DDRB.3=0;
        TCNT2=0;TC2=0;
        while(PINB.3==0 && TC2<100)
        { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
        }
        TCNT2=0;TC2=0;
        while(PINB.3==1 && TC2<100)
        { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
        }
        value= (TC2 * 250 + TCNT2) /8;
        }

    else if (number==5)     // URB
        {   
        DDRA.3=1;
        PORTA.3=1;
        delay_us(20);
        PORTA.3=0;
        DDRA.3=0;
        TCNT2=0;TC2=0;
        while(PINA.3==0 && TC2<100)
        { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
        }
        TCNT2=0;TC2=0;
        while(PINA.3==1 && TC2<100)
        { 
            if(TCNT2>=250)
                {
                 TCNT2=0;
                 TC2++;
                }
        }
        value= (TC2 * 250 + TCNT2) /8;
        }
    delay_ms(15);
    return value;
    }

unsigned int adc(unsigned char adc_input)
    {
    ADMUX=adc_input | ADC_VREF_TYPE;
    delay_us(10);
    ADCSRA|=(1<<ADSC);
    while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<<ADIF);  
    
    return ADCW;
    }
float read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA|=0x40;
    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;
    ADCW=((ADCW*5)/1023)*100;
    return ADCW;
}
    


unsigned int cmps(char select)
{
unsigned int pitch,roll,bearing;
i2c_start();
 
i2c_write(0xc0);
i2c_write(2);
 
i2c_start();
i2c_write(0xc1);
bearing=i2c_read(1);
bearing=bearing<<8; 
bearing+=i2c_read(1);
bearing/=10;
pitch=i2c_read(1);

roll=i2c_read(0);
 
i2c_stop(); 
 
delay_ms(5);
if (select==1) 
    return bearing;
else if (select==2) 
    return pitch;
else if (select==3) 
    return roll;
}

void compas_calibrate11 (void)
    {
    lcd_clear();
    lcd_putsf("increase-> calibrate");

    lcd_gotoxy(0,2);
    lcd_putsf("decrease-> fac reset");


    while(increase==1 && decrease==1 && previuse_page==1 && next_page==1);
    if(!increase)          // cmps calibration  
        {  
        #asm("cli");
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf0);
        i2c_stop();
        delay_ms(40);

        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf5);
        i2c_stop();
        delay_ms(40);

        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf7);
        i2c_stop();
        delay_ms(400);
        
        go(30,-30);

        lcd_clear();
        lcd_puts("Now robot will rotate");
        lcd_gotoxy(0,1);
        lcd_puts("press enter when cmp didn't blink");
        while(enter==1);
        while(enter==0);
        go(0,0);
        
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf8);
        i2c_stop();
        delay_ms(500);
        
        
        }
    else if (decrease==0)    // factory reset
        {
        while (decrease==0);
        lcd_clear();
        lcd_putsf("factory rst.");
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0x20);
        i2c_stop();
        delay_ms(20);
        lcd_putsf(".");
        
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0x2A);
        i2c_stop();
        delay_ms(20);
        lcd_putsf(".");

        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0x60);
        i2c_stop();
        delay_ms(20);
        lcd_putsf(".");
        
        delay_ms(300);
        lcd_clear();
        lcd_putsf("factory reset Done");
        lcd_puts("press enter for exit");
        while(enter==1);
        while(enter==0);
        }
    }
void calibration_robot (void)
    {
    lcd_clear();
    lcd_puts("   calibrating...");
    delay_ms(1000);
    lcd_clear();
    lcd_puts("     North");

    djN=deg;
    sprintf(text,"djn   %2d   ",djN);
    lcd_puts(text);
    delay_ms(1000);
    
    lcd_clear();
    lcd_puts("     East");
    TCNT=0;
    TCNT0=0;
    while(T0<T90R)
        
        {
        //if (TCNT<T90L*0.2 || TCNT>T90L*0.8)
            go(150,-150);
        //else
          //  go(220,-220);
        }
    go(0,0);
    delay_ms(500);

    djE=deg;
    lcd_gotoxy(1,1);
    sprintf(text,"dje   %2d   ",djE);
    lcd_puts(text);
    delay_ms(1000);
    lcd_clear();   
    
   
    lcd_puts("     South ");
    TCNT=0;
    TCNT0=0;
    while(T0<T90R)
        {
        //if (T0<T90R*0.2 || T0>T90R*0.8)
            go(150,-150);
        //else
          //  go(220,-220);
        }
    go(0,0);
    delay_ms(500);

    djS=deg;
    lcd_gotoxy(1,1);
    sprintf(text,"djs   %2d   ",djS);
    lcd_puts(text);
    delay_ms(1000);
    lcd_clear();
    lcd_puts("     West ");
    TCNT=0;
    TCNT0=0;
    while(T0<T90R)
        {
        //if (T0<T90R*0.2 || T0>T90R*0.8)
            go(150,-150);
        //else
           // go(220,-220);
        }
    go(0,0);
    delay_ms(500);

    djW=deg;
    lcd_gotoxy(1,1);
    sprintf(text,"djw   %2d   ",djW);
    lcd_puts(text);

    
    if (djE<0)   djE+=360;
    if (djS<0)   djS+=360;
    if (djW<0)   djW+=360;

    TCNT=0;
    TCNT0=0;
    while(T0<T90R)
        {
        //if (T0<T90R*0.2 || T0>T90R*0.8)
            go(150,-150);
        //else
           // go(220,-220);
        }
    go(0,0);
    lcd_clear();
    lcd_putsf("calibration done");
    delay_ms(500);
    }

void define_char(byte flash *pc,byte char_code)
{
/* function used to define user characters */
byte i,a;
a=(char_code<<3) | 0x40;
for (i=0; i<8; i++) lcd_write_byte(a++,*pc++);
}

int MLX(char address)
    {
    int MLX_LowData,MLX_Data;
    int MLX_HighData;
    
    i2c_start();
    i2c_write(address<<1);
    i2c_write(0x07);
    i2c_start();
    i2c_read(1);
    MLX_LowData=i2c_read(1);
    MLX_HighData=i2c_read(0);
    MLX_HighData&=0x007F;
    MLX_HighData=(MLX_HighData)<<8;
    MLX_HighData+=MLX_LowData;
    MLX_HighData=MLX_HighData*0.02;
    MLX_Data=MLX_HighData-273.15;
    i2c_stop();
    if (MLX_Data>100)     MLX_Data=0;
    delay_ms(5);
    return MLX_Data;
    }

int MLX2(char num)
    {
    int MLX_LowData,MLX_Data;
    int MLX_HighData;
    i2c_start();
    i2c_write(num<<1);
    i2c_write(0x07);
    i2c_start();
    i2c_read(1);
    MLX_LowData=i2c_read(1);
    MLX_HighData=i2c_read(0);
    MLX_HighData&=0x007F;
    MLX_HighData=(MLX_HighData)<<8;
    MLX_HighData+=MLX_LowData;
    MLX_HighData=MLX_HighData*0.02;
    MLX_Data=MLX_HighData-273.15;
    i2c_stop();
    if (MLX_Data>100)     MLX_Data=0; 
    return MLX_Data;
    delay_ms(5);

    }

void victim2 (void)
    {
        if (tempL>=temp && vfounded==0 )    //left sensors
        {
            go(0,0);
            for (i=0;i<cheshmak;i++)
                {LED_ON; delay_ms(50); LED_OFF;delay_ms(50);}
            go(-150,150); 
            TCNT=0;             
            TCNT0=0;
            delay_ms(50);
            while(T0<T90L)
            { 
                if (T0<T90L*0.3 || T0>T90L*0.7)
                    go(-100 ,100);    
                else
                    go(-80,80);
            }
            go(0,0);
            
            if (tempF>=temp)
            {
                XL(32,580,200);
                delay_ms(1000);
                XL(32,530,200);
            }
            
            go(150,-150); 
            TCNT=0;             
            TCNT0=0;
            delay_ms(50);
            while(T0<T90R)
            { 
                if (T0<T90R*0.3 || T0>T90R*0.7)
                    go(100 ,-100);    
                else
                    go(80,-80);
            }
            go(0,0);
        } 
        
        else if (tempR>=temp && vfounded==0 ) //right sensors
        {
           go(0,0);
           for (i=0;i<cheshmak;i++)
           {
               LED_ON; 
               delay_ms(50); 
               LED_OFF;
               delay_ms(50);
           }
           
           go(150,-150); 
            TCNT=0;             
            TCNT0=0;
            delay_ms(50);
            while(T0<T90R)
            { 
                if (T0<T90R*0.3 || T0>T90R*0.7)
                    go(100 ,-100);    
                else
                    go(80,-80);
            }
            go(0,0);
            
            if (tempF>=temp)
            {
                XL(32,580,200);
                delay_ms(1000);
                XL(32,530,200);
            }
            
            go(-150,150); 
            TCNT=0;             
            TCNT0=0;
            delay_ms(50);
            while(T0<T90L)
            { 
                if (T0<T90L*0.3 || T0>T90L*0.7)
                    go(-100 ,100);    
                else
                    go(-80,80);
            }
            go(0,0);
            
        }
        
        else if (tempF>=temp)  //front sensor
        {
            go(0,0);
            for (i=0;i<cheshmak;i++)
                {LED_ON; delay_ms(50); LED_OFF;delay_ms(50);}
            
            XL(32,580,200);
            delay_ms(1000);
            XL(32,530,200);
            
        }
    

    }
void calculate (void)
    {
    if (dir==1)
        {
        memF=mem[x][y+1];
        memB=mem[x][y-1];
        memL=mem[x-1][y];
        memR=mem[x+1][y];
        DF=(Xd-x)     * (Xd-x)       +    (Yd-(y+1))*(Yd-(y+1)) ;
        DB=(Xd-x)     * (Xd-x)       +    (Yd-(y-1))*(Yd-(y-1)) ;
        DR=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)*(Yd-y);
        DL=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)*(Yd-y);
        }
    else if (dir==2)
        {
        memF=mem[x+1][y] ;
        memB=mem[x-1][y] ;
        memL=mem[x][y+1];
        memR=mem[x][y-1];
        DF=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)    *(Yd-y);
        DB=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)    *(Yd-y);
        DR=(Xd-x)     * (Xd-x)       +    (Yd-(y-1))*(Yd-(y-1));
        DL=(Xd-x)     * (Xd-x)       +    (Yd-(y+1))*(Yd-(y+1));
        }
    else if (dir==3)
        {
        memF=mem[x][y-1] ;
        memB=mem[x][y+1] ;
        memL=mem[x+1][y];
        memR=mem[x-1][y];
        DF=(Xd-x)     * (Xd-x)       +    (Yd-(y-1))*(Yd-(y-1));
        DB=(Xd-x)     * (Xd-x)       +    (Yd-(y+1))*(Yd-(y+1));
        DR=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)    *(Yd-y);
        DL=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)    *(Yd-y);
        }
    else if (dir==4)
        {
        memF=mem[x-1][y] ;
        memB=mem[x+1][y] ;
        memL=mem[x][y-1];
        memR=mem[x][y+1];
        DF=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)     *(Yd-y);
        DB=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)     *(Yd-y);
        DR=(Xd-x)     * (Xd-x)       +    (Yd-(y+1)) *(Yd-(y+1));
        DL=(Xd-x)     * (Xd-x)       +    (Yd-(y-1)) *(Yd-(y-1));
        }
    }
void go (signed int spl,signed int spr)
  {
   spr=-spr;
//    char l2,r2,sl1,sr1;
//    if (spl==0 && spr==0)   // fast stop
//        {
//        L2=!L2;R2=!R2;
//        delay_ms(50);
//        }
    if (spr!=0) spr=spr+CHARKH;
    if (spl>255)     spl=255;
    if (spl<-255)    spl=-255;
    if (spr>255)     spr=255;
    if (spr<-255)    spr=-255;
    
    if (spl>0)
        {L1=0;SL1=spl;}
    else if (spl<0)
        {L1=1;SL1=255+spl;}
    else
        {L1=0;SL1=0;}

    if (spr>0)
        {R1=1;SR1=255-spr;}
    else if (spr<0)
        {R1=0;SR1=-spr;}
    else
        {R1=0;SR1=0;}
   
  }  

void check_error(void)  
    {   
    if (UL>120  && abs(ULF-ULB)<100 && ULF<200 && ULB<200 )
        { 
        error1=(ULF-ULB);
        error2=ULF-70;  
        error=error1+error2; 
        lcd_gotoxy(0,2);
        lcd_puts("  left near  ");
        }
    else if (UR>120 && abs(URF-URB)<100 && URF<200 && URB<200 )
        {
        error1=(URB-URF);    // chap & rast bar aks ham hastand
        error2=70-URF;  
        error=error1+error2;
        lcd_gotoxy(0,2);
        lcd_puts("  right near  ");
        }
    else if (abs(ULF-ULB)<100 && ULF<500 && ULF>200 && ULB<500 && ULB>200 )
        {
        error1=(ULF-ULB);
        error2=ULF-370;  
        error=error1+error2;
        if(abs(URF-URB)>285)
            {
            error = 0;
            lcd_gotoxy(0,2);
            lcd_puts("  LF correcting  ");
            }
        
        lcd_gotoxy(0,2);
        lcd_puts("  left far  ");
        }
    else if (abs(URF-URB)<100 && URF<500 && URB<500 && URF>200 && URB>200 )
        {
        error1=(URB-URF);    // chap & rast bar aks ham hastand
        error2=370-URF;  
        error=error1+error2;
        if(abs(ULF-ULB)>285)
            {
            error = 0;
            lcd_gotoxy(0,2);
            lcd_puts("  RF correcting  ");
            }
        lcd_gotoxy(0,2);
        lcd_puts("  right far  ");
        }
           
    else 
        {
        error=0;
       
        lcd_gotoxy(0,2);
        lcd_puts("  else  ");
        }
    
    
    if(error>120)     error=120;
    if(error<-120)   error=-120;
    
//     sprintf(text,"er1=%3d  er2=%3d  ",error1,error2);
//     lcd_gotoxy(0,0);
//     lcd_puts(text);
//
//     sprintf(text,"ULF=%3d  ULB=%3d  ",ULF,ULB);
//     lcd_gotoxy(0,1);
//     lcd_puts(text);
    }

void corection(void)
    {
    while(1)
        {

        if(UF>50 && UF<200)
            {
            beep(3);
            while(!(UF<65))
                {

                go(50,50);
                }
            }

                

        if(UF>30 && UF<60)
            {
            beep(2);
            while(!(UF<65))
                {
                go(-50,-50);
                }  
            }
        else break;    
        }
    //go(0,0);
    //delay_ms(1000);            
    }

void move30(void)
    {
    int save_t0=0;
    bit left_wall=0,right_wall=0,checked=0;
    if (ULF<200)    left_wall=1;
    if (URF<200)    right_wall=1;

    TCNT=0;TCNT0=0;
    go(100,100);
    delay_ms(50);
    while(T0<STR)
        {
        if (UF<90 || KFL+KFR==0)
            {
            go(0,0);

            break;
            }
        check_error();
        if (KFR==0 && KFL==1)
            {
            save_t0=TCNT;
            go(0,-150);
            delay_ms(250);
            go(-150,0);
            delay_ms(250);
            go(150,150);
            delay_ms(250);
            TCNT=save_t0;
            }
        else if (KFL==0 && KFR==1)
            {
            save_t0=TCNT;
            go(-150,0);
            delay_ms(250);
            go(0,-150);
            delay_ms(250);
            go(150,150);
            delay_ms(350);
            TCNT=save_t0;
            }
        else if (TCNT<STR*0.15)//|| TCNT>go30*0.85)
            go(100-error ,100+error);
        else
            go(180-error ,180+error);

        if (SDR>=400 && SDL>=400)//black room
            {
            save_t0 = T0;
            TCNT = 0;
            TCNT0=0;
            go(0,0);
            //go(-120,-120);
            //while(T0<save_t0+10);
            //go(-120,-120);
            
                
               
            while(T0<save_t0+10)
                {
                check_error();
                if (T0<save_t0*0.15 || T0>save_t0*0.85)
                    go((-1)*(70+error),(-1)*(70+error));
                else
                    go((-1)*(130+error),(-1)*(130+error));
                }
                
                
                go(0,0);
                calculate();
            if (dir == 1)
                {
                mem[x][y+1]+=3;
                y--;
                }
            else if (dir == 2)
                {
                mem[x+1][y]+=3;
                x--;
                }
            else if (dir == 3)
                {
                mem[x][y-1]+=3;
                y++;
                }
            else if (dir == 4)
                {
                mem[x-1][y]+=3;
                x++;
                }
            break;
            }

        // edge detection
        if (( (left_wall==1 && ULF>200) || (right_wall==1 && URF>200) )&& checked==0) // END OF WALL
            {
            //lcd_clear();
            //sprintf(text,"T0=%3d S=%3d TL=%3d ",T0,STR,T90L);
            //lcd_gotoxy(0,0);
            //lcd_puts(text);

            //sprintf(text,"S-T=%3d  T0-T90=%3d ",STR-T90L,T0-T90L);
            //lcd_gotoxy(0,3);
            //lcd_puts(text);

//            TCNT=0 ;
//            TCNT0=1;
//            delay_ms(50);
            TCNT=(STR-155)/256 ;
            TCNT0=(STR-155)%256;
            delay_ms(50);
            //sprintf(text,"TC=%3d TC0=%3d=%3d ",TCNT ,TCNT0,T0);
            //lcd_gotoxy(0,1);
            //lcd_puts(text);
            checked=1;
            }

        if (( (left_wall==0 && ULF<200) || (right_wall==0 && URF<200) )&& checked==0 )   // START OF WALL
            {
            //lcd_clear();
            //sprintf(text,"T0=%3d S=%3d TR=%3d ",T0,STR,T90R);
            //lcd_gotoxy(0,0);
            //lcd_puts(text);

            //sprintf(text,"S-T=%3d  T0-T90=%3d ",STR-T90R,T0-T90R);
            //lcd_gotoxy(0,3);
            //lcd_puts(text);

            TCNT=(STR-260)/256 ;
            TCNT0=(STR-260)%256;
//            TCNT=(STR-310)/256 ;
//            TCNT0=(STR-310)%256;

            //sprintf(text,"T0=%3d  ",T0);
            //lcd_gotoxy(0,0);
            //lcd_puts(text);
            checked=1;
            }
        }
    beep(1);
    //go(0,0);
    //while(1);
    calculate();

    //if(sarbala+sarpaeen==0)
        {
        if(dir==1)   {y++;}
        else if(dir==2)   {x++;}
        else if(dir==3)   {y--;}
        else if(dir==4)   {x--;}

        mem[x][y]++;

        calculate();

        if (mem[x][y] == 1)
            number++;

//        if(UF<200&& UF>150)
//            {
//            go(0,0);
//            Tanzim();
//            }
        if (KFL+KFR==0)
            {
            go(0,0);
            go(-80,-80);
            TCNT=0;
            TCNT0=0;
            while(T0<10); //BUG!!!
            //beep(2);
            go(0,0);
            //Tanzim();
            }
        }
    if (++str_cnt > 1 )
        {right_cnt=0; left_cnt=0;}

    if(UF>200)
        {
        if (URF<150 && URB>300)
            {
             beep(2);
             go(-100,-100);
             while(URF<150 && URB>300);
             TCNT=0;TCNT0=0;
             while(T0<STR/10)
                 go(100,100);
            }
        else if (ULF<150 && ULB>300)
            {
             while (ULF<150 && ULB>300)
                 go(100,100);
             TCNT=0;TCNT0=0;
             while(T0<STR/10)
                 go(100,100);
            }
        else if (URB<150 && URF>300)
            {
             beep(2);
             while (URB<150 && URF>300)
                 go(100,100);
             TCNT=0;TCNT0=0;
             while(T0<STR/10)
                 go(100,100);
            }
        else if (ULB<150 && ULF>300)
             {
             while (ULB<150 && ULF>300)
                 go(100,100);
             TCNT=0;TCNT0=0;
             while(T0<STR/10)
                 go(100,100);
             }
        }
    //corection();
    }

void TL (void)
    { 
    go(0,0);
    if (M==11)
        left_cnt++;
    else left_cnt=0; 
    str_cnt=0;
    right_cnt=0;
    while (URF<25)  //BUG!!
        {
        go(0,-200);
        delay_ms(300);
        go(-200,0);
        delay_ms(300);
        go(200,200);
        delay_ms(300);
        }
    go(0,0); 
     
    
     TCNT=0;
     TCNT0=0;
    go(-100 ,100);
    delay_ms(50);    
     while(T0<T90L)
        {
        if (T0<T90L*0.3 || T0>T90L*0.85)
            go(-100 ,100);    
        else
            go(-180,180);
        }
     go(0,0);
     delay_ms(500);
     if (dir==1)
        dir=4;
    else if (dir==2)
        dir=1;
    else if (dir==3)
        dir=2;
    else if (dir==4)
        dir=3;
     //Tanzim();
     if((URF-URB)>=20)
     {
        while((URF-URB)<5)
            go(0,-80);
     }
     
     else if((URB - URF)>=20)
     {
         while((URB - URF)<5)
            go(-80,0);
     }
     
     move30();
    }

void TR (void)
    {
    go(0,0);
    if (M==110)
        right_cnt++;
    else right_cnt=0;
    //beep(10);
    str_cnt=0;
    left_cnt=0;
    
    while (ULF<25)//BUG!!
        {
        go(-200,0);
        delay_ms(300);
        go(0,-200);
        delay_ms(300);
        go(200,200);
        delay_ms(300);
        }
    go(0,0); 
     TCNT=0;
     TCNT0=0;
    go(100 ,-100);
    delay_ms(50);    
     while(T0<T90R)
        {
        if (T0<T90R*0.55 || T0>T90R*0.85)
            go(100 ,-100);    
        else
            go(150,-150);
        }
     go(0,0);
     delay_ms(500);
    if (dir==1)
        dir=2;
    else if (dir==2)
        dir=3;
    else if (dir==3)
        dir=4;
     else if (dir==4)
        dir=1;
     //Tanzim();
     if((ULF - ULB)>=20)
     {
        while((ULF - ULB)<5)
            go(-80,0);
     }
     
     else if((ULB - ULF)>=20)
     {
         while((ULB - ULF)<5)
            go(0,-80);
     }
     move30();

    }

void TB (void)
    { 
    go(0,0);
    left_cnt=0;
    str_cnt=0;
    right_cnt=0;
     
     
     TCNT=0; 
     TCNT0=0;
     delay_ms(500);
     go(-150,150);
     while(T0<T180);
     go(0,0);
     delay_ms(500);
     //Tanzim();
     if (UF<150)  // yani poshtesh divar boode va nabayad door mizade. hala ke door zade nabayad bere jolo va ella mire tu divar
        {
        go(120,120);
        TCNT=0;TCNT=0;
        while((KFL==1 || KFR==1) && TCNT<STR/2);
        go(0,0);
        delay_ms(100);

        go(120,120);
        TCNT=0;TCNT=0;
        while(TCNT<STR/4);
        go(0,0);
        delay_ms(100);
        }
      right_cnt=0;
    left_cnt=0;
    str_cnt=0;


     if (dir==1)
        dir=3;
     else if (dir==2)
        dir=4;
     else if (dir==3)
        dir=1;
     else if (dir==4)
        dir=1;     
     move30();
    }

void Tanzim(void)
    {
    signed int speed,zarib;
    int err,time=0;
    char t=0;


    if (check_sarbala)     // sar bala ee = 227
        {
        go(250,250);
        TCNT=0;
        while(TCNT<5);


        if (check_sarbala)
            sarbalaee();
        go(0,0);

        }
    else if(check_sarpaeen )   // sar paeeni = 15
        {
        go(250,250);
        TCNT=0;
        while(TCNT<5);


        if (check_sarpaeen)
            sarpaeeni();
        go(0,0);
        }
    else  
        {
        while(t<3 && time++<35)     // 40=3000 m sec becouse of ultra
            {
            if (URF<200 && URB<200)
                {
                err=URF-URB;
                zarib=abs(err)*0.5;
                if (zarib>50)    zarib=50;
                speed=40+zarib;
                if (err>5)
                    go(speed,-speed);
                if (err<-5)
                    go(-speed,speed);
                }
            else if (ULF<200 && ULB<200)
                {
                err=ULF-ULB;
                zarib=abs(err)*0.5;
                if (zarib>60)    zarib=60;
                speed=40+zarib;
                if (err>5)
                    go(-speed,speed);
                if (err<-5)
                    go(speed,-speed);
                }
            else if (URF<500 && URB<500 && URF-URB<200 && URF-URB>-200  )
                {
                err=URF-URB;
                zarib=abs(err)*0.5;
                if (zarib>50)    zarib=50;
                speed=40+zarib;
                if (err>5)
                    go(speed,-speed);
                if (err<-5)
                    go(-speed,speed);
                }
            else if (ULF<500 && ULB<500 && (ULF-ULB)<200 && (ULF-ULB)>-200 )
                {
                err=ULF-ULB;
                zarib=abs(err)*0.5;
                if (zarib>60)    zarib=60;
                speed=40+zarib;
                if (err>5)
                    go(-speed,speed);
                if (err<-5)
                    go(speed,-speed);
                }
            else if (back==1)
                 {
                int time=0;
                go(-170,-170);
                TCNT=0;
                while((KBL==1 || KBR==1) && time<2000)
                    {
                    if (KBL==1 && KBR==1)
                        go(-150,-150);
                    else if (KBL==0 && KBR==1)
                        go(50,-150);
                    else if (KBL==1 && KBR==0)
                        go(-150,50);
                    delay_ms(1);
                    }
                go(0,0);
                delay_ms(10);

                go(120,120);
                TCNT=0;
                while(TCNT<STR/4);
                go(0,0);
                delay_ms(10);
                break;
                }
            if (err<5 && err >-5)
                {
                go(0,0);
                t++;
                delay_ms(10);
                }
            else    t=0;
    //        sprintf(text,"UF=%3d  sp=%3d   ",UF,speed);
    //        lcd_gotoxy(0,0);
    //        lcd_puts(text);
    //        sprintf(text,"time=%3d   ",time);
    //        lcd_gotoxy(0,1);
    //        lcd_puts(text);
            }
        t=0; time=0;
        while (t<2 && UF<800 && time++<35)
            {
            if (UF<200)         err=UF-85;
            else if (UF<500)    err=UF-385;
            else if (UF<800)    err=UF-685;
            if (err < -30 )         go(-120,-120);
            else if (err < -10 )    go(-40,-40);
            else if (err < 0 )      go(-30,-30);
            else if (err < 10 )     go(30,30);
            else if (err < 30 )     go(40,40);
            else if (err > 30 )     go(120,120);
            if (err<5 && err>-5)
                {
                go(0,0);
                t++;
                delay_ms(10);
                }
            else    t=0;
    //        sprintf(text,"UF=%3d  sp=%3d   ",UF,speed);
    //        lcd_gotoxy(0,0);
    //        lcd_puts(text);
    //        sprintf(text,"time=%3d   ",time);
    //        lcd_gotoxy(0,1);
    //        lcd_puts(text);
            }
        }
    go(0,0);
    }
    
                    
void sarbalaee (void)
    {
    int i;
    right_cnt=0; left_cnt=0;
    lcd_gotoxy(0,1);
    lcd_putsf("   Sar Bala ee  ");

        Xramp=x;
        Yramp=y;
    while(UF>80)
        {
        check_error();
        if (KFL==0)
            {
            go(250,-250);
            delay_ms(50);
            go(250,250);
            delay_ms(100);
            go(-250,250);
            delay_ms(30);
            }
        else if (KFR==0)
            {
            go(-250,250);
            delay_ms(50);
            go(250,250);
            delay_ms(100);
            go(250,-250);
            delay_ms(30);
            }
        else   
            go(220-error,220+error);
        if ((tempL>=temp || tempR>=temp) && vfounded==0 )
            {
             go(0,0);
            for (i=0;i<cheshmak;i++)
                {LED_ON; delay_ms(50); LED_OFF;delay_ms(50);}
            vfounded=1;

            XL(32,580,200);
            delay_ms(1000);
            XL(32,530,200);

            }
        }
    //Tanzim();
    x+=5;      // chon momkene sathe shibdar az akhare zamin nabashe
    Xd=20;Yd=7;
    mem[x+1][y]++;   // bara inke balaye sar balee dor nazane
    sarbala=0;
    TR();

    }
void sarpaeeni (void)
    {
    right_cnt=0; left_cnt=0;
    lcd_gotoxy(0,1);
    lcd_putsf("   Sar Paeeni  ");
     // resid be ramp
    while(UF>80)
        {
        check_error();
        if (KFL==0)
            {
            go(250,-250);
            delay_ms(50);
            go(250,250);
            delay_ms(100);
            go(-250,250);
            delay_ms(30);
            }
        else if (KFR==0)
            {
            go(-250,250);
            delay_ms(50);
            go(250,250);
            delay_ms(100);
            go(250,-250);
            delay_ms(30);
            }
        else   
            go(220-error,220+error);
        if ((tempL>=temp || tempR>=temp) && vfounded==0 )
            {
             go(0,0);
            for (i=0;i<cheshmak;i++)
                {LED_ON; delay_ms(50); LED_OFF;delay_ms(50);}
            vfounded=1;
            XL(32,580,200);
            delay_ms(1000);
            XL(32,530,200);
            }
        }
    //Tanzim();
    Xd=4;
    Yd=4;
    x=Xramp;
    y=Yramp;
    mem[Xramp][Yramp]=10;
    mem[Xramp-1][Yramp]=10;

    sarpaeen=0;
    returning=1;
    TL();
    }
void clear_memory(void)
    { 
    if (STR==-1)
        {
        T180=600;
        T90L=255;
        T90R=774;
        STR=305;
        temp=12;
        cheshmak =10;
        }
        
        //volume=30;
        
        Olaviat=0;
        Tedad = 16; /// add to setup page
        lastM[0]=-1;
        lastM[1]=-1;
    for (y=0;y<30;y++)
        {
        for (x=0;x<60;x++)
            mem[x][y]=0;
        lcd_puts(".");
        }
    xcp=xs;ycp=ys;
    Xramp=0;Yramp=0;
    lcd_clear();
    number = 0;
    returning=0;
    AXmin=440;
    AXmax=680;

    lcd_clear();
    lcd_puts(" memory cleared ");
    delay_ms(500);
    lcd_clear();

    }
void DirCheck(void)
{
 int MinDeg=400;
  
 if ( abs(deg-djN) < MinDeg )    {dir=1; MinDeg=abs(deg-djN);}
 if ( abs(deg-djE) < MinDeg )    {dir=2; MinDeg=abs(deg-djE);}
 if ( abs(deg-djS) < MinDeg )    {dir=3; MinDeg=abs(deg-djS);}
 if ( abs(deg-djW) < MinDeg )    {dir=4;}
 //if(hasGoneDown)dir=2;
 //if(hasGoneUp)dir=4;

}
void lcd(void)
    {
    calculate();
    sprintf(text,"(%2d,%d)=%d cp=(%2d,%d)",x,y,mem[x][y],xcp,ycp);
    lcd_gotoxy(0,0);
    lcd_puts(text);
    sprintf(text,"mem L=%d F=%d B=%d R=%d",memL,memF,memB,memR);
    lcd_gotoxy(0,1);
    lcd_puts(text);
//    sprintf(text,"FL=%3d F=%3d FR=%3d",ULF,UF,URF);
    sprintf(text,"dest(%2d,%2d)   ",Xd,Yd);
    lcd_gotoxy(0,2);
    lcd_puts(text);
    sprintf(text,"BL=%3d Dir=%d BR=%3d",ULB,dir,URB);
    lcd_gotoxy(0,3);
    lcd_puts(text);

    }
void search (void)
{
    // 1Way
    if (M==101)
     {
      if(memB<memF) TB();
      else  
       move30();
     }
    else if (M==110)
          {
            if(memB<memR) TB();
            else      
             TR();
          }
    else if (M==11)
           {
           if(memB<memL) TB();
            else       
            TL();
           }
    else if(M==111)
            {   
            mem[x][y]+=5;
            TB();
            }
    
    // 2Ways
    else if (M==1)
            {
            if (memL<memF)
              TL();
            else if (memL>memF)
                move30();
            else
                {
                    if(memF+memL==0)
                    {
                      if(DL>DF)
                          TL();
                     else if(DL<DF)
                          move30();
                      else 
                          TL(); 
                    }
                    
                    else 
                    {
                        if(DL>DF)
                          move30(); 
                     else if(DL<DF)
                           TL();
                     else 
                        move30(); 
                     }
                        
                }
            }
    else if (M==10)
            {
            if (memL<memR)
                   TL();
            else if (memL>memR)
                   TR();
            else
                {
                    if(memR+memL==0)
                    {
                      if(DL>DR)
                          TL();
                     else if(DL<DR)
                          TR();
                      else 
                          TR(); 
                    }
                    
                    else 
                    {
                        if(DL>DR)
                          TR(); 
                     else if(DL<DR)
                           TL();
                     else 
                        TR(); 
                     }
                }
            }
    else if (M==100)
            {
            if (memF<memR)
                   move30();
            else if (memF>memR)
                   TR();
            else
                {  
                 if(memF+memR==0)
                    {
                      if(DR>DF)
                          TR();
                     else if(DR<DF)
                          move30();
                      else 
                          TR(); 
                    }
                    
                    else 
                    {
                        if(DR>DF)
                          move30(); 
                     else if(DR<DF)
                           TR();
                     else 
                       move30(); 
                     }
                }
            }
    // 2<Ways
    else if (M==0)
            {
            if (memF<memR && memF<memL)
            {
              switch(dir)
                      {
                       case 4 :
                       TB();   //we have to check
                       break;
                       default:
                       move30();
                      }
            }
            else if (memR<memF && memR<memL)
              TR();
            else if (memL<memR && memL<memF)// why we have if in Left and Front
            {
                switch(dir)
                      {
                       case 1 :
                       TR();//we have to check this line
                       break;
                       case 2 :
                       move30();// we have to check this line
                       break;
                       default:
                       TL();
                      }
            }
            ///////////////////////////////////       
            else if (memL==memF && memF!=memR)
                    {
                    if(memF+memL==0)     //what a beatifull code!!!
                     move30();
                    else if (DL>DF)
                          TL();
                    else
                     TL(); //move30(); 
                    }
            else if (memR==memF && memF!=memL)
                    {
                    if(memF+memR==0)
                     move30();
                    else if (DR>DF)
                          TR();           
                    else
                     TR(); //move30();        
                    }
            else if (memR==memL && memL!=memF)
                    {
                    if(memR+memL==0)
                     TL();
                    else if (DR>DL)
                          TR();        
                    else
                      TL();           
                    }
            else
                {
                if(memL+memF+memR==0)
                    {
//                    if (DF<DR && DF<DL)
//                        move30();
//                    else if (DR<DF && DR<DL)
//                        TR();
//                    else if (DL<DR && DL<DF)
//                        TL();
                    switch(dir)
                      {
                       case 1 :
                       move30();
                       break;
                       case 2 :
                       TL();
                       break;
                       case 3 :
                       TL();
                       break;
                       case 4 :
                       move30();
                       break;
                       default:
                       move30();
                      }
                    }
                else
                     {
                    if (DF<DR && DF<DL)
                    move30();
                    else if (DR<DF && DR<DL)
                    TR();
                    else if (DL<DR && DL<DF)
                    TL();
                    //////////////////////////////////
                    else if((DF == DR) && ( DF > DL))
                          TL();
                    else if((DF == DL) && ( DF > DR))
                          TR();
                    else if((DL == DR) && ( DL > DF))
                          move30();
                    //////////////////////////////////                 
                    else
                     move30();
                    }
                }

            }

}

void  menu_setup (void)
    {
    static char page=1,last_page=6; 
    lcd_clear();

    while(1)
        {
        if (next_page==0)
            {
            while (next_page==0);
            page++;
            if (page>last_page) page=1;
            lcd_clear();
            }
        if (previuse_page==0)
            {
            while (previuse_page==0);
            page--;
            if (page<1) page=last_page;
            lcd_clear();
            }
        if (page<5)
            {
            sprintf(text,"T90R         %4d",T90R);
            lcd_gotoxy(3,0);
            lcd_puts(text); 
            
             sprintf(text,"T90L         %4d",T90L);
            lcd_gotoxy(3,1);
            lcd_puts(text);
            
            
            
            sprintf(text,"STR          %4d",STR);
            lcd_gotoxy(3,2);
            lcd_puts(text);
            
//            sprintf(text,"block_dis    %4d",block_dis);
//            lcd_gotoxy(3,2);
//            lcd_puts(text);
//                
            sprintf(text,"T180         %4d",T180);
            lcd_gotoxy(3,3);
            lcd_puts(text);

            lcd_gotoxy(0,page-1);
            lcd_puts("->");
            }
        else if (page<9)
            { 
            
//            sprintf(text,"spd         %4d",spd);
            lcd_gotoxy(3,0);
            lcd_puts("clear memory");
            
//            sprintf(text,"silver        %1.1f",silver);
            lcd_gotoxy(3,1);
            lcd_puts("motor calibrating");
//
//            sprintf(text,"left_value   %d  ",left_value);
//            lcd_gotoxy(3,2);
//            lcd_puts(text);
//
//            sprintf(text,"right_value   %d  ",right_value);
//            lcd_gotoxy(3,3);
//            lcd_puts(text);
//
            lcd_gotoxy(0,page-5);
            lcd_puts("->");

            }

        else if (page<14)
            {


            }



        if(page==1)  // T90R
            {
            if(increase==0)
                {
                delay_ms(80);
                T90R+=1;
                }
            else if(decrease==0)
                {
                delay_ms(80);
                T90R-=1; 
                }
            else if(enter==0)
                {
                go(150,-150); 
                TCNT=0;
                TCNT0=0;
                delay_ms(50);
                while(T0<T90R)
                    {
                    if (T0<T90R*0.3 || T0>T90R*0.7)
                        go(100 ,-100);    
                    else
                        go(150,-150);
                    }
                go(0,0);
                }
            }
        else if(page==2) // T90L
            {
            if(increase==0)
                {
                delay_ms(80);
                T90L+=1;
                }
       
            else if(decrease==0)
                {
                delay_ms(80);
                T90L-=1; 
                }
            else if(enter==0)
                {
                go(-150,150); 
                TCNT=0;             
                TCNT0=0;
                delay_ms(50);
                while(T0<T90L)
                    { 
                    if (T0<T90L*0.3 || T0>T90L*0.7)
                        go(-100 ,100);    
                    else
                        go(-150,150);
                    }
                go(0,0);
                }                                                                
            }  
        else if(page==3) //STR 
            {
              if (increase==0)
                {
                delay_ms(200);
                STR+=10;
                }
            else if (decrease==0)
                {
                delay_ms(200);
                STR -=10; 
                }     
            else if(enter==0)
                {
                while(enter==0); 
                delay_ms(500);
                move30();
                go(0,0);
                }
                
            if (STR>2000) STR=2000;                                                                          
            if (STR<=1) STR=1;    
            }  
        else if(page==4)  // T180
            {
             if(increase==0)
                {
                delay_ms(80);
                T180+=1;
                }
            else if(decrease==0)
                {
                delay_ms(80);
                T180-=1; 
                }
            else if(enter==0)
                {            
                TCNT=0;
                TCNT0=0;
                delay_ms(500);
                go(-150,150);
                while(T0<T180);
                go(0,0);
                }   
           
           
           
            }
        else if(page==5)  // eprom reset
            {
            if(enter==0)
                { 
                clear_memory();
                } 
            }                     
        else if (page==6)// go str
            {
            if (enter==0)
             {
             while(UF<90||KFR+KFL!=0)
             {move30();}
             go(0,0);
             }    
            }
        }  
    } 
void  menu_sensor(void)
    {
    static char page=1,last_page=5; 

    lcd_clear();

    while(1)
        {
        if (next_page==0)
            {
            while (next_page==0);
            page++;
            if (page>last_page) page=1;
            lcd_clear();
            }
        if (previuse_page==0)
            {
            while (previuse_page==0);
            page--;
            if (page<1) page=last_page;
            lcd_clear();
            }  
        if (increase==0)
            go(60,60);
        else if (decrease==0)
            go(-60,-60);
        else
            go(0,0);
            
    ///////////////

        if(page==2)    // ultra
            {
            sprintf(text,"      UF=%3d   ",UF);
            lcd_gotoxy(0,0);
            lcd_puts(text);  

            sprintf(text,"ULF=%3d      URF=%3d ",ULF,URF);
            lcd_gotoxy(0,1);
            lcd_puts(text);  

            sprintf(text,"ULB=%3d      URB=%3d ",ULB,URB);
            lcd_gotoxy(0,2);
            lcd_puts(text);
            delay_ms(100);  
            }
        else if(page==1)   // switches
            {
            sprintf(text,"KFL=%d          KFR=%d",KFL,KFR);
            lcd_gotoxy(0,0);
            lcd_puts(text);  
            sprintf(text,"KBL=%d          KBR=%d",KBL,KBR);
            lcd_gotoxy(0,1);
            lcd_puts(text);  

            sprintf(text,"SDL=%4d  SDR=%4d   ",SDL,SDR);
            lcd_gotoxy(0,2);
            lcd_puts(text);  

            sprintf(text,"Enc=%-3d vic=%d  Rs=%d",T0,0,0);
            lcd_gotoxy(0,3);
            lcd_puts(text);  
            }
        else if(page==3)   // cmps
            {  
            DirCheck() ;
            sprintf(text," deg=%3d  dir=%d  ",deg,dir);      //corner
            lcd_gotoxy(0,0);
            lcd_puts(text);  

            sprintf(text," shib1          %3d",shib1);       //safo soof krdn
            lcd_gotoxy(0,1);
            lcd_puts(text);

            sprintf(text," shib2         %3d",shib2);      //shib
            lcd_gotoxy(0,2);
            lcd_puts(text); 
            
            lcd_gotoxy(0,3);
            lcd_puts("press enter to calib"); 
            if (enter==0)
            compas_calibrate11();            
            }
        else if(page==4)  // MLX
            {
            check_error();
            sprintf(text,"er1=%d er2=%d er=%d   ",error1,error2,error);
            lcd_gotoxy(0,0);
            lcd_puts(text);
            }
        else if(page==5)
            {
            sprintf(text,"ur=%2d  ul=%2d    ",UR,UL);
            lcd_gotoxy(0,0);
            lcd_puts(text);
            delay_ms(50);
            
            }
        }
    }
void  menu_motor (void)
    {
    static char page=1,last_page=2; 
    signed int spd=0; 
    int deg_1=550;
    lcd_clear();  

    while(1)
        {
        if (next_page==0)
            {
            while (next_page==0);
            delay_ms(50);
            page++;
            if (page>last_page)  page=1;
            lcd_clear();
            }
            
        if (previuse_page==0)
            {
            while (previuse_page==0);
            delay_ms(50);
            page--;
            if (page<1) page=last_page;
            lcd_clear();
            }
                     
        if(page<=4)
            {
            sprintf(text,"go(%4d,%4d)    ",spd,spd);
            lcd_gotoxy(3,0);
            lcd_puts(text);

            sprintf(text,"MOT XL 32    %4d",deg_1); 
            lcd_gotoxy(3,1);
            lcd_puts(text);

            lcd_gotoxy(0,page-1);
            lcd_puts("-> ");
            }

            
        if(page==1)     // go
            {

            if (increase==0)
                {
                spd+=50;
                delay_ms(400);
                }
            else if (decrease==0)
                {
                spd-=50;
                delay_ms(400);
                }
            else
               spd=0;
            
            if (spd>255)     spd=255;
            if (spd<-255)    spd=-255;
            
            go(spd,spd);               
            }   
        else if(page==2) // xl
            {
            if (increase==0)
                {
                delay_ms(50);
                if(deg_1<700)
                    deg_1+=1;

                XL(32,deg_1,150);  
                }
            else if (decrease==0)
                {
                delay_ms(50);

                if(deg_1>170)
                    deg_1 -=1; 

                XL(32,deg_1,150);  
                }
            else if (enter==0)
                {
                deg_1 = 510; 
                XL(32,deg_1,150);  
                }
            }
        }
    }

void  menu_pist_calib (void)
    
    
    {   
    lcd_clear();
    lcd_puts(" put robot to North ");
    lcd_puts("  and press enter   ");

    sprintf(text,"       DN=%3d    ",DN);
    lcd_gotoxy(0,2);
    lcd_puts(text);

    sprintf(text,"DW=%3d DS=%3d DE=%3d",DW,DS,DE);
    lcd_gotoxy(0,3);
    lcd_puts(text);

    while(enter==1);

    DN=deg; 
    go(500,-500);  while(TCNT<T90L);
    delay_ms(500);       
        
    DE=deg; 
    go(500,-500);  while(TCNT<T90L);
    delay_ms(500);       
        
    DS=deg; 
    go(500,-500);  while(TCNT<T90L);
    delay_ms(500);       
        
    DW=deg; 
    go(500,-500);  while(TCNT<T90L);
    delay_ms(500);       
        
    lcd_clear();
    lcd_puts("  and press exit   ");

    sprintf(text,"     DN=%3d    ",DN);
    lcd_gotoxy(0,2);
    lcd_puts(text);

    sprintf(text,"DW=%3d DS=%3d DE=%3d",DW,DS,DE);
    lcd_gotoxy(0,3);
    lcd_puts(text);

    }
void  menu(void)
    {
    static unsigned char page=1,last_page=8;
    float battery;
    lcd_init(20);
    lcd_clear();
    lcd_puts("Error: check switch");

    sprintf(text,"KFL=%d   KFR=%d",KFL,KFR);
    lcd_gotoxy(0,1);
    lcd_puts(text);  
    sprintf(text,"KBL=%d   KBR=%d",KBL,KBR);
    lcd_gotoxy(0,2);
    lcd_puts(text);  
    sprintf(text,"p_p=%d next_p=%d Ent=%d",previuse_page,next_page,enter);
    lcd_gotoxy(0,3);
    lcd_puts(text);  
    if (enter==0 || next_page==0 || previuse_page==0 ) 
        {      
        beep(10);
        }
    lcd_clear();
    while (1)
        {
        if (next_page==0)
            {
            while (next_page==0);
            page++;
            if (page>last_page) page=1;
            lcd_clear();
            }
        if (previuse_page==0) 
            {
            while (previuse_page==0);
            page--;
            if (page<1) page=last_page;
            lcd_clear();
            }  
        if (page<=4)  
            {
            lcd_gotoxy(3,0);
            lcd_puts("Start ");
            lcd_gotoxy(3,1);
            lcd_puts("Test Sensor      ");
            lcd_gotoxy(3,2);
            lcd_puts("Setup            ");
            lcd_gotoxy(3,3);
            lcd_puts("Test Motor       ");
            lcd_gotoxy(0,page-1);
            lcd_puts("-> ");
            }
        else if (page>4)
            {
            lcd_gotoxy(3,0);
            lcd_puts("Test Motor       ");
            lcd_gotoxy(3,1);
            lcd_puts("pist calibration ");
             lcd_gotoxy(3,2);
            lcd_puts("tanzim  ");
            lcd_gotoxy(0,page-5);
            lcd_puts("-> ");
            }

        if (page==1)    // start 
            {
            if (enter==0)
                {
                while (enter==0);
                break;
                }
            battery=read_adc(3);
            battery=(battery*5/1023)*3.1;
            sprintf(text,"batt=%1.2fv ",battery);
            lcd_gotoxy(9,0);
            lcd_puts(text);
            if (battery<10.5)
                {
                LED_ON;
                delay_ms(50);
                LED_OFF;
                delay_ms(50);
                }
            }
        else if (page==2)    // Test Sensor  
            {
            if (enter==0)
                {
                while (enter==0);
                menu_sensor();
                }
            }
        else if (page==3)     // Setup
            {
            if (enter==0)
                {
                while (enter==0);
                menu_setup();
                }
            }
        else if (page==4)    // Test Motor  
            {
            if (enter==0)
                {
                lcd_clear();
                while (enter==0);
                menu_motor();
                }
            }  
        else if (page==5)    // Test   
            {
            if (enter==0)
                {
                while (enter==0);
                //menu_motor();
                }
            }
        else if (page==6)    // pist calibration 
            {
            if (enter==0)
                {
                lcd_clear();
                while (enter==0);
                while(1)
                {
                delay_ms(200);
                sprintf(text,"djn=%d dje=%d \n djw=%d djs=%d  ",djN,djE,djW,djS);
                lcd_gotoxy(0,0);
                lcd_puts(text);
                
                if (enter==0)
                    {
                     calibration_robot();
                    }
                }
                }
            }  
        
        else if (page==7)    // pist calibration 
            {
            if (enter==0)
                {
                Tanzim();
                }
            }  
        
        } 
    } 

void Finished(void)
{
    //Khodaya Shokr!!!   :-)

    go(0,0);
    define_char(char2,2);
    define_char(char3,3);
    define_char(char4,4);
    define_char(char5,5);
    lcd_clear();
    lcd_puts("     Finished    ");
     lcd_gotoxy(9,2);
    lcd_putchar(2);
    lcd_gotoxy(10,2);
    lcd_putchar(3);
    
    while(1)
        {
         
         buz=~buz;
         delay_ms(10);
         buz=~buz;
         
         lcd_gotoxy(3,0);
         lcd_putchar(5);
         lcd_gotoxy(14,0);
         lcd_putchar(5);
          
         delay_ms(120);
         
         lcd_gotoxy(3,0);
         lcd_putchar(4);
         lcd_gotoxy(14,0);
         lcd_putchar(4);
         delay_ms(120);
         
         lcd_gotoxy(3,0);
         lcd_putchar(5);
         lcd_gotoxy(14,0);
         lcd_putchar(5);
         
         delay_ms(120);
        
         lcd_gotoxy(3,0);
         lcd_putchar(4);
         lcd_gotoxy(14,0);
         lcd_putchar(4);
         lcd_gotoxy(3,0);
         lcd_putchar(5);
         lcd_gotoxy(14,0);
         lcd_putchar(5);
        
         delay_ms(120);
        
         lcd_gotoxy(3,0);
         lcd_putchar(4);
         lcd_gotoxy(14,0);
         lcd_putchar(4);
        
         delay_ms(120);
         
        }
 }

void main(void)
{
    char add=0;    
    {
    DDRA=0b11000000;PORTA=0b00000111;
    DDRB=0b11110000;PORTB=0b00000110;
    DDRC=0b01111110;PORTC=0b11000011;
    DDRD=0b10001000;PORTD=0b00000000;
    DDRE=0b01100111;PORTE=0b00000000;
    DDRF=0b00000000;PORTF=0b00000000;
    DDRG=0b00000;   PORTG=0b00011;

    ASSR=0x08;
    TCCR0=0x01;    // encoder R
    TCCR1A=0xA1;   // PWM
    TCCR1B=0x09;
    TCCR2=0x02;    // timer baraye ultra
    TCCR3A=0x01;   // ENC L
    TCCR3B=0x0E;

    TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    ETIMSK=0x04;

    ADMUX=0x00 & 0xff;
    ADCSRA=0x83;

    lcd_init(20);
    i2c_init(); 
    dxl_init(); 
        
    #asm("sei")
    LED_ON;
    delay_ms(50);
    LED_OFF;

    if (STR==-1)
    clear_memory();

    x=xcp;y=ycp;

    lcd_clear();
    lcd_gotoxy(5,1);
    lcd_puts("Please wait ");
    //delay_ms(1500);

    
    DirCheck();
    lcd_clear();
    sprintf(text,"dir=%d ",dir);
    lcd_gotoxy(9,2);
    lcd_puts(text);
    delay_ms(300);
    }
    menu(); 
    lcd_clear();
    //beep(1);
    x=xcp;y=ycp;                  
    go(0,0);          
     
    vfounded=0;
    delay_ms(1800);
    DirCheck();

    lcd_clear();
    sprintf(text,"dir=%d ",dir);
    lcd_gotoxy(9,2);
    lcd_puts(text);
    delay_ms(300);
    
    if (mem[xs][ys] == 0)
      mem[xs][ys] = 1; 
              
    lcd();
    move30();
    calculate();
    lcd();
       
    while(1)
    {
                                                       
    
      calculate();
      M=0;
        if((URF<200 && URB<200) || memR>9)     M+=1;
        if (UF<200 || memF>9)                  M+=10;
        if((ULF<200 && ULB<200) || memL>9)                 M+=100;
    /**************victim***********/
         victim2();
    
    /******************************/    
        if (number == 3)
        {
           go(0,0);
           beep(3);
           for (i=0;i<cheshmak;i++)
            {
                LED_ON;
                delay_ms(50); 
                LED_OFF;
                delay_ms(50);
            }
           
           XL(32,580,250);
           delay_ms(5000);
           XL(32,530,250); 
        }
        
        if (number == 7)
        {
           go(0,0);
           beep(3);
           for (i=0;i<cheshmak;i++)
            {
                LED_ON;
                delay_ms(50); 
                LED_OFF;
                delay_ms(50);
            }
           
           XL(32,580,250);
           delay_ms(5000);
           XL(32,530,250); 
        }
        
    //save 2 last M           
        
        if(lastM[0]==-1)
        {
            lastM[0]=M;
            _lastM=true;
        }
        else if(lastM[1]==-1)
        {
            lastM[1]=M;
            _lastM=false;
        }                   
        else if(_lastM==true)
        {
            lastM[1]=M;
            _lastM=false;    
        }
        else
        {
            lastM[0]=M;
            _lastM=true;
        }
        /////////////////
        
     if(left_cnt>=3)
            {
            lcd_clear();
            lcd_puts("Left Loop");
            delay_ms(400);
            left_cnt=0;
            if      (dir==1)
                {
                mem[x][y]+=5;
                mem[x-1][y]+=5;
                mem[x][y-1]+=5;
                }
            else if (dir==2)
                {
                mem[x][y]+=5;
                mem[x-1][y]+=5;
                mem[x][y+1]+=5;
                }

            else if (dir==3)
                {
                mem[x][y]+=5;
                mem[x+1][y]+=5;
                mem[x][y+1]+=5;
                }
            else if (dir==4)
                {
                mem[x][y]+=5;
                mem[x+1][y]+=5;
                mem[x][y-1]+=5;
                }
            calculate();
            }
        if(right_cnt>=3)
            {
            lcd_clear();
            lcd_puts("Right Loop");
            delay_ms(400);
            right_cnt=0;
            if      (dir==1)
                {
                mem[x][y]+=5;
                mem[x+1][y]+=5;
                mem[x][y-1]+=5;
                }
            else if (dir==2)
                {
                mem[x][y]+=5;
                mem[x-1][y]+=5;
                mem[x][y-1]+=5;
                }

            else if (dir==3)
                {
                mem[x][y]+=5;
                mem[x-1][y]+=5;
                mem[x][y+1]+=5;
                }
            else if (dir==4)
                {
                mem[x][y]+=5;
                mem[x+1][y]+=5;
                mem[x][y+1]+=5;
                }
            calculate();
            }
       
       search();
       /****
       we have to add sarbala&sarpaeen
       ****/
       calculate();
       lcd();
       if(SDL<100 && SDR<100) // check piont
        {
        //finish:
        {
            beep(4);
            go(0,0);
           
            xcp=x;ycp=y;  
            
            lcd_clear();        
            lcd_puts(" Check point ");
            delay_ms(100);
            lcd_clear();
            sprintf(text,"Tedad = %d ",Tedad);
            lcd_puts(text);
            delay_ms(100);
            lcd_clear();
            sprintf(text," x=%2d   y=%2d   ",xcp,ycp );
            lcd_puts(text);
            delay_ms(100);
            lcd_clear();
            sprintf(text,"Number = %d",number);
            lcd_puts(text);
            delay_ms(400);
        if (((x==xs+2 || x==xs || x==xs-2|| x==xs-1 || x==xs+1 )&&( y==ys+2 || y==ys ||y==ys-2 ||y==ys+1 ||y==ys-1 )))//|| flagt>=3)  // finish
                {
                 if(((x==xs||x==xs+2 || x==xs-2 ||x==xs-1 || x==xs+1)&&(y==ys|| y==ys+2 || y==ys-2 ||y==ys-1 || y==ys+1)))//Olaviat==3 Chon Zamin 2 ta Ramp Dre!
                 {
                  if(number>=Tedad)
                  {
                  lcd_clear();
                  lcd_putchar(0xFF);
                  delay_ms(4000); 
                  //Tanzim();
                  Finished();
                  }
                 }
                    
                lcd_clear();
                lcd_puts("   Start room    ");
                delay_ms(100);
                calculate();
                M=0;
                if(URF<200 && URB<200)   M+=1;
                if(UF<200 )   M+=10;
                if(ULF<200 )   M+=100;
                if ((M==0 || M==1 || M==100 || M==101) && memF==0)
                    move30();
                else if ((M==0 || M==1 || M==10 || M==11) && memL==0)
                    TL();
                else if ((M==0 || M==10 || M==100 || M==110) && memR==0)
                    TR();
                    
                   
                else
                    { 
                    lcd_clear();
                    //lcd_putchar(0xFF);
                    beep(3);
                    delay_ms(4000); 
                    if (number >= Tedad)
                        { 
                          
                          Finished();
                        }        
                    }
                }
           
          
         else if(flagt>=2)//&& returning=1
                {
                 lcd_clear();
                 lcd_putchar(0xFF);
                 beep(3);
                 delay_ms(4000); 
                 if (number >= Tedad)
                    { 
                    Finished();
                    }
                }
                
        }
            
        }
    }
}