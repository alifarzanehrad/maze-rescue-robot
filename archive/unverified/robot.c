//besmellaherrahmanerrahim 
#include <God.h>        =20             
#include <mega128.h>
=include <delay.h>
#include <stdio.h>
#include <stdlib.h>=0A#include <string.h>
#include <alcd.h>
#include <i2c.h>=0A#include "LiB/NextionLCD.h" 
#include "LiB/deff.h"

=ool IsInRampUp = false;
bool IsStartPage = false;
=ool IsInRampDown = false;
bool MLX_R_Detects = false;=0Abool IsInTurn = false;
bool JumpStack = false;
=ool hasGoneUp = false ,hasGoneDown = false;
bool IsD=bugMode = false; // For Disabling The Nextion LCD Put =1' For "DebugMode" At Nextion Lib.
bit sarbala=0,sarpaee==0;
bit vfounded=0,Timer_on=0,first=0;
eeprom signed =har memvic[60][30],mem[60][30],lastM[2]; 
eeprom char returnin==0;
eeprom unsigned char Xramp,Yramp,Xramp1,Yramp1,temp,xcp,yc=;
//Olaviat==1 (mamuli) , Olaviat==2 (start az bal=), Olaviat==3(start az bala + returning=1) ,Olaviat===(2ta Ramp darim Ke aln 2 2omie im!(IO 2017))
eeprom =igned int number,Tedad,Olaviat=0,Xd=40,Yd=-10;
eeprom int =heshmak=10,volume=30,AXmin=780,AXmax=516,djN,djE,djS,djW,flagt=0;=0D
eeprom unsigned int go30,turn,TimeAgo=0;

eeprom b=ol _lastM;

char gbpParameter[128],gbpTxBuffer[128];
int=20default_buffer[10] = {0x7E , 0xFF , 0x06 , 0x00 , 0=00 , 0x00 , 0x00 , 0xEF}; // Default Buffer
int bu=fer_data[10] = {0x7E , 0xFF , 0x06 , 0x00 , 0x00 , =x00 , 0x00 , 0xEF}; // Sending Buffer

unsigned i=t TimeAgo1=0;
 
int signed x,y,UFL,UBL,UF,UB,UFR,UBR,DL=DF,DR,DB,dj=0,dir=1;

float VSDF,VSDB,VLDR,vbat;    =20                         =20      
int i,Track,SL,SR,deg_bat,memL,memF,memR,memB,e=ror,TCNT;
char str_cnt,right_cnt,left_cnt; //tedad  dafaate =arekat be samte jahatha
char text[40],M,shib1,roll;//,PWMSpeed=ontrol=0;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)=
interrupt [TIM2_OVF] void timer2_ovf_isr(void);
void def=ll(void);
void LED_BLINK (void);
void sarbalaee (void);=0Avoid sarpaeeni (void);
void go (int, int);
void Tan=im(void);
void victim(void);
void DropVic(void);
void =mps(void);
void play_track(int);
void send(int X,int Y,in= Mem,int Dir,int MemF,int MemB,int MemR,int MemL,int Xd,int =d);
char TxPacket(char bID, char bInstruction, char bParam=terLength);
void AX12 (char bID,int position, int speed);=0Avoid adc(void);
float read_adc(unsigned char adc_input);
=oid send_buffer(void);
void set_volume( int volume ); 
=oid sleep(void);
void wakeup(void);
void play_track(int t=ack_number);
void define_char(byte flash *pc,byte char_code);=0Avoid Mp3_player(void);
void battery_deg(void);
void DirCh=ck(void);
void victimCorection(void);
void cmps(void);
/=bool CheckedRooms(void);
void calibration_cmp11 (void);
voi= calibration_robot (void);
int MLXReadData(char MLX_ID);
=/void calibration_cmp10 (void);
//void MLX_find_address(void);=0A//void MlxChangeAddress(char new_id);
void victim (void);=0Avoid setup(void);
void calculate (void);
void go (int=20spl,int spr);
void check_error(void);
void move30 (void=;
void TL (void);
void TR (void);
void TB (void)=
void Tanzim(void);
void sarbalaee (void);
void sarp=eeni (void);
void clear_memory(void);
void memory(void);=0Avoid search (void);
void lcd(void);
void forceHardReset=);
void Finished(void);

void main(void)
{
 =20  defall(); 
    
    go(0,0);    =20    
    
    LED_BLINK();
   =20
    if (POK==0)
        {
 =20      while (POK==0);
        memo=y();
        }

    if (PBACK===)
        {
        while (PBAC===0);
        setup();
        =
                
    x==cp;y=ycp;

    if (KFR==0)
      =20 {
        set_volume(volume);
     =20  while (KFR==0);
        
    =20   Mp3_player();
        }
    el=e if (KFL==0)
        {
      =20 vfounded=1;
        while (KFL==0);
=20       lcd_puts("  Ready ...");
      =20 while (POK==1);
        while (POK==0=;
        play_track(threetoone);
     =20  delay_ms(2000); 
        go(50,50); 
=20       delay_us(700);
        go(100,1=0); 
        delay_us(700);
       =20go(150,150); 
        delay_us(700);
   =20    go(200,200); 
        delay_us(500);=0A        go (255,255);
        lcd_=lear();
        while(1)
        =20   { 
            delay_ms(200);
=20           sprintf(text," TCNT=%3d ",TCNT);=0A            lcd_gotoxy(0,0);
     =20      lcd_puts(text);
            = 
            go(0,0);
      =20     lcd_clear();
            lcd_=uts("Finished!!!"); 
            while(1);=0A        }
    if(dj==0&&shib1==255&&=oll==255)
    {
     LED_OFF;
   =20 lcd_clear();
     lcd_gotoxy(3,1);
     =cd_puts("Compass Error ");
     delay_ms(100);
  =20  change_baud();
     printf("page Compass Error")=
     _buffer();
     while(1);
   =20} 
    vfounded=0;     
    set_v=lume(25);
    delay_ms(100);    
    batt=ry_deg(); if(deg_bat<=50) play_track(Track); 
    chan=e_baud();
    printf("page Please Wait");
    =buffer();
    lcd_clear();
    lcd_gotoxy(0,1);=0A    lcd_puts("    Please wait "); 
    =et_volume(25);
    play_track(threetoone);
    de=ay_ms(2000);
   
    DirCheck();

   =20lcd_clear();
    sprintf(text,"dir=%d ",dir);
  =20 lcd_gotoxy(9,2);
    lcd_puts(text);
    del=y_ms(300);
    
    if (mem[xs][ys] == =)
      mem[xs][ys] = 1; 
       =20      
    lcd();
    move30();
=20   sleep();
    calculate();
    lcd();=0A    Timer_on=1; 
    while(1)
     =20  {
        calculate();
      =20 M=0;
        if((UFR<200 && UBR<200) || =emR>7)     M+=1;
        if (UF<200 ||=20memF>7)                  M+=10;
=20       if (UFL<200 || memL>7)        =20        M+=100; 
        //save = last M
        if(lastM[0]==-1)
   =20    {
            lastM[0]=M;
=20           _lastM=true;
       =20}
        else if(lastM[1]==-1)
   =20    {
            lastM[1]=M;
=20           _lastM=false;
       =20}                   
   =20    else if(_lastM==true)
        {=0A            lastM[1]=M;
      =20     _lastM=false;    
        }=0D
        else
        {
  =20         lastM[0]=M;
         =20  _lastM=true;
        }
      =20 /////////////////
        if(left_cnt>=3)
=20           {
           =20lcd_clear();
            lcd_puts("Left Lo=p");
            delay_ms(400);
   =20        left_cnt=0;
          =20 if      (dir==1)
           =20    {
                mem[x]=y]+=5;
                mem[x-1][y]+==;
                mem[x][y-1]+=5;=0A                }
      =20     else if (dir==2)
          =20     {
                mem=x][y]+=5;
                mem[x-1][y=+=5;
                mem[x][y+1]+==;
                }

   =20        else if (dir==3)
       =20        {
              =20 mem[x][y]+=5;
                m=m[x+1][y]+=5;
                mem[x]=y+1]+=5;
                }
  =20         else if (dir==4)
      =20         {
             =20  mem[x][y]+=5;
                =em[x+1][y]+=5;
                mem[x=[y-1]+=5;
                }
 =20          calculate();
         =20  }
        if(right_cnt>=3)
    =20       {
            lcd_clear=);
            lcd_puts("Right Loop");
=20           delay_ms(400);
       =20    right_cnt=0;
            if =20    (dir==1)
               =20{
                mem[x][y]+=5;=0A                mem[x+1][y]+=5;
 =20              mem[x][y-1]+=5;
   =20            }
          =20 else if (dir==2)
              =20 {
                mem[x][y]+=5;=0D
                mem[x-1][y]+=5;
=20               mem[x][y-1]+=5;
  =20             }

       =20    else if (dir==3)
           =20    {
                mem[x]=y]+=5;
                mem[x-1][y]+==;
                mem[x][y+1]+=5;=0A                }
      =20     else if (dir==4)
          =20     {
                mem=x][y]+=5;
                mem[x+1][y=+=5;
                mem[x][y+1]+==;
                }
     =20      calculate();
            }=0D

        search();

       =20if (sarbala==1)
                =arbalaee();
        if (sarpaeen==1 )
 =20              sarpaeeni();
     =20          
        calculate();=0A        adc();
        if (VSDF<0.= && VSDB<0.8)   // check point
         =20  {
            go(0,0);
    =20       LED_OFF;
            LE=_G_OFF;
            LED_B_OFF;
    =20       LED_R_OFF;             =0A                         =20    
            LED_R_ON;
  =20         LED_B_ON;
           =20xcp=x;ycp=y;  
            send(x,y,=em[x][y],dir,memF,memB,memR,memL,Xd,Yd);
          =20 lcd_clear();        
          =20 lcd_puts(" Check point ");
           =20change_baud();
            printf("page Ch=ckpoint");
            _buffer();
   =20        IsStartPage = false;
      =20     sprintf(text,"Tedad = %d ",number);
   =20        Nextion_cmd22("t0.txt=",text);
    =20       sprintf(text," x=%2d   y=%2d   ",x=p,ycp );
            lcd_puts(text);
 =20          delay_ms(100);
        =20   lcd_clear();
            sprintf(te=t,"Tedad=%d",number);
            lcd_puts(t=xt);
            delay_ms(400);
   =20        if (((x==xs+2 || x==xs || x===s-2|| x==xs-1 || x==xs+1 )&&( y==ys+2 || y==y= ||y==ys-2 ||y==ys+1 ||y==ys-1 ) && returning===)|| flagt>=3)  // finish
            =20   {
                 if(fla=t>=3 || ((x==xs+2 || x==xs-2 )&&( y==ys+2 || ===ys-2 )) || Olaviat==3)//Olaviat==3 Chon Zamin 2 =a Ramp Dre!
                 {=0A                  change_baud();
=20                 printf("page Error")= 
                  _buffer();=0A                  delay_ms(1000);
=20                 go(-100,100);
 =20                delay_ms(5000);
  =20               Tanzim();
     =20            Finished();
       =20         }
             =20      
                s=nd(x,y,mem[x][y],dir,memF,memB,memR,memL,Xd,Yd);
       =20        lcd_clear();
           =20    lcd_puts("  Start room    ");
    =20           delay_ms(100);
       =20        calculate();
           =20    M=0;
                i=(UFR<200 && UBR<200)   M+=1;
          =20     if(UF<200 )   M+=10;
        =20       if(UFL<200 )   M+=100;
     =20          if ((M==0 || M==1 || M==3D100 || M==101) && memF==0)
         =20          move30();
          =20     else if ((M==0 || M==1 || M==10 =| M==11) && memL==0)
            =20       TL();
              =20 else if ((M==0 || M==10 || M==100 || M===10) && memR==0)
                =20   TR();
                  =20 
                   
 =20              else
       =20            { 
         =20          lcd_clear();
         =20          //lcd_putchar(0xFF);
      =20             //delay_ms(4000); 
   =20                if (number >= Ted=d)
                       =20{
                      =20   Finished();
                =20       }        
       =20            }
          =20     }
                els= if((Olaviat==3 && returning==1 )|| flagt>=3)
  =20             {
         =20       lcd_clear();
            =20    //lcd_putchar(0xFF);
            =20    //delay_ms(4000); 
            =20    if (number >= Tedad)
         =20              { 
       =20                Finished();
   =20                    }
  =20             }
         =20      LED_OFF;
            }
=20       lcd();
        }
   =20}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{=0ATCNT++;
TCNT0=0;
if(vfounded==0 && flagt<3 && !Is=nRampUp && !IsInRampDown)
 {
  //if(memvic[x][y]==0=
  // {
    #asm("cli")
    victim();=0A    #asm("sei")
  //}
 }
}
interrupt =TIM2_OVF] void timer2_ovf_isr(void)      // ULTRA TIMME=
{
    static char refresh;
    static =har u=1;
    char TCN=0;
    refresh++; =20    

    if (refresh++>1)
     =20  {
        if (u>5 || u<1)    u==;
        refresh=0;
        TC=R2=0x02;
        TCNT2=0;

     =20  if (u==1)          // UBR
   =20        {
            u++;=0A            DDRD.4=1;
       =20    PORTD.4=1;
            delay_u=(20);
            PORTD.4=0;
    =20       DDRD.4=0;
            =CN=0;
            TCNT2=0;
    =20       while ( PIND.4==0 && TCN<40 )
 =20              {
        =20       if (TCNT2>250)
          =20         {
             =20      TCN++;
               =20    TCNT2=0;
               =20    }
                }
=20           TCN=0;
         =20  TCNT2=0;
            while ( PIN=.4==1 && TCN<40 )
              =20 {
                if (TCNT2>250=
                    {
 =20                  TCN++;
   =20                TCNT2=0;
   =20                }
      =20         }
            UBR=3D (TCN*250 + TCNT2)/Ultra;       //  crystal 11.=592 MHz
            if (UBR>2000)   =20 UBR=0;
            }
     =20  else if (u==2)      // UBL
     =20      {
            u++;
 =20          DDRC.5=1;
         =20  PORTC.5=1;
            delay_us(20);=0D
            PORTC.5=0;
      =20     DDRC.5=0;
            TCN==;
            TCNT2=0;
      =20     while ( PINC.5==0 && TCN<40 )
   =20            {
          =20     if (TCNT2>250)
            =20       {
               =20    TCN++;
                 =20  TCNT2=0;
                 =20  }
                }
  =20         TCN=0;
           =20TCNT2=0;
            while ( PINC.5==3D1 && TCN<40 )
                =
                if (TCNT2>250)
=20                   {
   =20                TCN++;
     =20              TCNT2=0;
     =20              }
        =20       }
            UBL= =TCN*250 + TCNT2)/Ultra;       //  crystal 11.0592 =Hz
            }
        =lse if (u==3)     // UFR
         =20  {
            u++;
     =20      DDRD.5=1;
            PO=TD.5=1;
            delay_us(20);
  =20         PORTD.5=0;
          =20 DDRD.5=0;
            TCN=0;
 =20          TCNT2=0;
         =20  while ( PIND.5==0 && TCN<40 )
      =20         {
             =20  if (TCNT2>250)
               =20    {
                  =20 TCN++;
                    =CNT2=0;
                    =
                }
     =20      TCN=0;
            TCNT2=3D0;
            while ( PIND.5==1 &= TCN<40 )
                {
 =20              if (TCNT2>250)
   =20                {
      =20             TCN++;
        =20           TCNT2=0;
        =20           }
           =20    }
            UFR=(TCN*250 +=20TCNT2)/Ultra;       //  crystal 11.0592 MHz
=0A            if (UFR>2000)     UFR=0=
            }
        el=e if (u==4)     // UF
          =20 {
            u++;
      =20     DDRA.7=1;
            PORTA=7=1;
            delay_us(20);
   =20        PORTA.7=0;
           =20DDRA.7=0;
            TCN=0;
  =20         TCNT2=0;
          =20 while ( PINA.7==0 && TCN<40 )
       =20        {
              =20 if (TCNT2>250)
                =20   {
                   =20TCN++;
                    T=NT2=0;
                    }=0D
                }
     =20      TCN=0;
            TCNT2=3D0;
            while ( PINA.7==1 &= TCN<40 )
                {
 =20              if (TCNT2>250)
   =20                {
      =20             TCN++;
        =20           TCNT2=0;
        =20           }
           =20    }
            UF= (TCN*250 = TCNT2)/Ultra;       //  crystal 11.0592 MHz
 =20          if (UF>2000)     UF=0;
 =20          }
        else if =u==5)    // UFL
            {=0A            u=1;
         =20  DDRC.4=1;
            PORTC.4=1;=0A            delay_us(20);
      =20     PORTC.4=0;
            DDRC=4=0;
            TCN=0;
     =20      TCNT2=0;
            whi=e ( PINC.4==0 && TCN<40 )
          =20     {
                if =TCNT2>250)
                    =
                    TCN++;=0A                    TCNT2=0;=0A                    }
  =20             }
         =20  TCN=0;
            TCNT2=0;
 =20          while ( PINC.4==1 && TCN<40 )=0D
                {
     =20          if (TCNT2>250)
       =20            {
          =20         TCN++;
            =20       TCNT2=0;
            =20       }
               =20}
            UFL=(TCN*250 + TCNT2)/Ul=ra;       //  crystal 11.0592 MHz
     =20      if (UFL>2000)     UFL=0;
    =20       }
        }
    TC=R2=0x05;
    TCNT2=0;
    cmps();
  =20 
    switch(UDR0)
       {
  =20    case '^^':
       forceHardReset();
=20      break;
       default:
   =20   break;
       }
    if(Timer_on==3D1)
     {
     TimeAgo1++;
    =20if (TimeAgo1>=oneMin/60)
       {
    =20  TimeAgo++;
       TimeAgo1=0;
    =20  }
     if(TimeAgo>=120&& flagt==0)
  =20   {
      play_track(twoMin);
     =20flagt=1;
      }
     else if(TimeAgo==240&& flagt==1)
      {
      pl=y_track(fourMin);
      flagt=2;
      =
     else if(TimeAgo>=360&& flagt==2)
  =20   {
      play_track(sixMin);
     =20flagt=3;
      } 
     }
   =20}
void defall(void)
{
    Timer_on=0;
 =20  DDRB  =  0b11110010;
     
    =DRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (1<<DDE4) | (0<<D=E3) | (1<<DDE2) | (0<<DDE1) | (0<<DDE0);
    DDRG==0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (1<<DDG1) | (1<<DDG0);=0A    DDRD=(0<<DDD7) | (1<<DDD6) | (0<<DDD5) | (0<<DD=4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
 =20  PORTD.6=1;//Nextion TX En PIN
    PORTC = =200b11110011; 
    PORTE =  0b10000000; 
  =20 PORTB =  0b00000001;
    
    ADMUX==DC_VREF_TYPE & 0xff;
    ADCSRA=(1<<ADEN) | (0<<ADSC= | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<=ADPS1) | (0<<ADPS0);
    ADCSRA=0x84;
     =20 
    ASSR=8;  TCCR0=1;   // ENCR
 =20  TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<=OM1B0) | (0<<COM1C1) | (0<<COM1C0) | (0<<WGM11) | (1<<WGM10=;
    TCCR1B= 0b0001011;
    //(0<<ICNC1) |=20(0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS=1) | (1<<CS10);
    TCCR2=5;          =20// ultra
    TCCR3A=0;TCCR3B=6;

    =CSR1A=(0<<RXC1) | (0<<TXC1) | (0<<UDRE1) | (0<<FE1) | (0<=DOR1) | (0<<UPE1) | (0<<U2X1) | (0<<MPCM1);
    UC=R1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (0<<RXEN1) | =1<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
   =20UCSR1C=(0<<UMSEL1) | (0<<UPM11) | (0<<UPM10) | (0<<USBS1) = (1<<UCSZ11) | (1<<UCSZ10) | (0<<UCPOL1);
    UBRR1H=3D0x00;
    UBRR1L=0x47;

    UCSR0A=(0<=RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | =0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
    UCSR0B=(0<<RX=IE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) = (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
    UCSR0C==0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCS=01) | (1<<UCSZ00) | (0<<UCPOL0);
    UBRR0H=0x00;=0A    UBRR0L=0x47; //9600
    
    TI=SK=0x41;   // TCNT0 over flow intrrupt
    #as=("sei")
    
    lcd_init(20);
    =0A    if (go30==-1) clear_memory();
}
void LED_=LINK (void)
{
    LED_ON; 
    LED_R_ON;=0D
    LED_G_ON;
    LED_B_ON;
    dela=_ms(50);
    LED_OFF;
}
void send(int X,int Y,=nt Mem,int Dir,int MemF,int MemB,int MemR,int MemL,int Xd,int=20Yd)
{
 if(IsDebugMode)
 {
 int buffer[17];=0A int i=0,x1,x2;
 int Mem1,Mem2;
 int MemF1,MemF2;=0D
 int MemB1,MemB2;
 int MemR1,MemR2;
 int MemL1,M=mL2; 
 int Xd1,Xd2;
 int Yd1;

 UCSR0C=(0=<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ0=) | (1<<UCSZ00) | (0<<UCPOL0);
 UBRR0L=0x05;//115200
=0D
  x1=X;
  x2=x1%10;
  x1/=10;
  x==0x+(x1+48);//+48 because of ascii table(numbers starts from =8)
  x2=0x+(x2+48);
  
  Y=0x+(Y+48);
 =20
  Mem1=Mem;
  Mem2=Mem1%10;
  Mem1/=10;=0D
  Mem1=0x+(Mem1+48);//+48 because of ascii table(numbers=20starts from 48)
  Mem2=0x+(Mem2+48);
  
  =emF1=MemF;
  MemF2=MemF1%10;
  MemF1/=10;
  =emF1=0x+(MemF1+48);//+48 because of ascii table(numbers starts =rom 48)
  MemF2=0x+(MemF2+48);

  MemB1=MemB;=0A  MemB2=MemB1%10;  
  MemB1/=10;
  MemB1==x+(MemB1+48);//+48 because of ascii table(numbers starts from =8)
  MemB2=0x+(MemB2+48);

  MemR1=MemR;
 =20MemR2=MemR1%10;   
  MemR1/=10;
  MemR1=0x+=MemR1+48);//+48 because of ascii table(numbers starts from 48=
  MemR2=0x+(MemR2+48);
 
  MemL1=MemL;
 =20MemL2=MemL1%10; 
  MemL1/=10;
  MemL1=0x+(MemL1=48);//+48 because of ascii table(numbers starts from 48)
=20 MemL2=0x+(MemL2+48);
  
  Dir=0x+(Dir+48);
=20 
  Xd1=Xd;
  Xd2=Xd1%10;
  Xd1/=10;=0A  Xd1=0x+(Xd1+48);//+48 because of ascii table(numbers st=rts from 48)
  Xd2=0x+(Xd2+48);
  
  Yd1==x+(Yd+48);

  buffer[0]=x1;
  buffer[1]=x2;
=20 buffer[2]=Y;
  buffer[3]=Mem1;
  buffer[4]=Mem=;
  buffer[5]=Dir;
  buffer[6]=MemF1;
  buff=r[7]=MemF2;
  buffer[8]=MemB1;
  buffer[9]=MemB2;=0A  buffer[10]=MemR1;
  buffer[11]=MemR2;
  buffe=[12]=MemL1;
  buffer[13]=MemL2;
  buffer[14]=Xd1;=0A  buffer[15]=Xd2;
  buffer[16]=Yd1;

  for= i=0; i<17; i++)
  putchar(buffer[i]);
  for( i=3D0; i<17; i++)
  buffer[i]=0;
  putchar('\n');
=20 putchar('\r');
 UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<=UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL=);
 UBRR0L=0x47;//9600
 }
}
char TxPacket(char =ID, char bInstruction, char bParameterLength)
{
   =20char bCount,bCheckSum,bPacketLength;
    gbpTxBuffer[0] =3D 0xff;
    gbpTxBuffer[1] = 0xff;
    g=pTxBuffer[2] = bID;
    gbpTxBuffer[3] = bParamete=Length+2; //Length(Paramter,Instruction,Checksum)
    gbpTxB=ffer[4] = bInstruction;
    for(bCount = 0; bCou=t < bParameterLength; bCount++)
        {
 =20      gbpTxBuffer[bCount+5] = gbpParameter[bCount];
=20       }
    bCheckSum = 0;
   =20bPacketLength = bParameterLength+4+2;
    for(bCount =3D 2; bCount < bPacketLength-1; bCount++) //except 0xff,check=um
        {
        bCheckSum == gbpTxBuffer[bCount];
        }
    =bpTxBuffer[bCount] = ~bCheckSum; //Writing Checksum with Bit =nversion
    for(bCount = 0; bCount < bPacketLengt=; bCount++)
        {
        w=ile(!TXD_READY);
        UDR1 = gbpTxBuffer[bCou=t];
        }
    while(!CHECK_TXD_FINISH=; //Wait until TXD Shift register empty
    return=bPacketLength);
    }
void AX12 (char bID,int pos=tion, int speed)
{
    gbpParameter[0] = P_GOAL=POSITION_L; //Address of Firmware Version
    gbpParam=ter[1] = position & 255;    //Writing Data P_GOAL_POS=TION_L
    gbpParameter[2] = position >> 8;   =20//Writing Data P_GOAL_POSITION_H
    gbpParameter[3] ==20speed & 255;       //Writing Data P_GOAL_SPEED_L=0A    gbpParameter[4] = speed >>8;         =/Writing Data P_GOAL_SPEED_H
    TxPacket(bID,INST_WRITE,5=;
    delay_ms(10);
    }
void adc(void)=0A{ 

    //LDR:
    ADMUX=0 | (ADC_=REF_TYPE & 0xff);
    delay_us(10);
    ADCSR=|=0x40;
    while ((ADCSRA & 0x10)==0);
  =20 ADCSRA|=0x10;
    VLDR=ADCW;
    VLDR==LDR*5/1023;
    //SDF:
    ADMUX=1 | (ADC_V=EF_TYPE & 0xff);
    delay_us(10);
    ADCSRA==0x40;
    while ((ADCSRA & 0x10)==0);
  =20 ADCSRA|=0x10;
    VSDF=ADCW;
    VSDF==SDF*5/1023;
    //SDB:
    ADMUX=2 | (ADC_V=EF_TYPE & 0xff);
    delay_us(10);
    ADCSRA==0x40;
    while ((ADCSRA & 0x10)==0);
  =20 ADCSRA|=0x10;
    VSDB=ADCW;
    VSDB==SDB*5/1023;

    }
float read_adc(unsigned char =dc_input)
{
    ADMUX=adc_input | ADC_VREF_TYPE;=0A    // Delay needed for the stabilization of the =DC input voltage
    delay_us(10);
    // S=art the AD conversion
    ADCSRA|=(1<<ADSC);
  =20 // Wait for the AD conversion to complete
   =20while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<=ADIF);
    return ADCW;
}
void send_buffer(void)=0D
{
         int i; 
       =20    for( i=0; i< 10; i++){
        =20       putchar(buffer_data[i]);
        =20       buffer_data[i] = default_buffer[i];
  =20         }
        }
void s=t_volume( int volume )    // Set Volume min=0 max==0
{
            buffer_data[3] = 0x=6;
            buffer_data[6] = volume;=0A            send_buffer();
      =
void sleep(void)
{
    buffer_data[3] = 0x0=;
    send_buffer();
}
void wakeup(void)
{=0A    buffer_data[3] = 0x09;
    buffer_data[6] =3D 2;
    send_buffer();
}
void play_track(int =rack_number)
{
    go(0,0);
    wakeup();=0A    delay_ms(200);
    buffer_data[3] = 0x03;=0A    buffer_data[6] = track_number;
    send_bu=fer(); 
    go(SL,SR);
}
void define_char(byte =lash *pc,byte char_code)
{
/* function used to define=20user characters */
byte i,a;
a=(char_code<<3) | 0x4=;
for (i=0; i<8; i++) lcd_write_byte(a++,*pc++);
}
=oid Mp3_player(void)
{
 int p=1;
 #asm("cli")
=20wakeup();
while(1)
{
     int b = read_a=c(6);
     int   c = read_adc(5);
   =20 
     char left,right,up,down;
     lc=_gotoxy(5,1);
      lcd_puts("Mp3 Player");
   =20  define_char(char0,0);
      lcd_gotoxy(9,2);
=20     lcd_putchar(0);
        if (b<100) =20        left=1;
        else if =b>=100)    left=0;
        if (b>900) =20        right=1;
        else if=20(b<=900)    right=0;

        if =c<100)          down=1;
        =lse if (c>=100)    down=0;
        if =c>900)          up=1;
        el=e if (c<=900)    up=0;
       if(first==3D0)
             {change_baud();
  =20          printf("page Mp3");
      =20      _buffer(); 
            =20}
             first=1;
    =20  if(POK==0)
        {

    =20    if(p==1){

        buffer_data[=] = 0x0E;
       send_buffer();

   =20   delay_ms(500);
       p=0;
    =20  }
       else if (p==0){

  =20     buffer_data[3] = 0x0D;
       sen=_buffer();

       delay_ms(500);
    =20  p=1;
       }
       }
=20      if(right==1)
        {
 =20      lcd_gotoxy(18,2);
        lcd_puts="->");
        buffer_data[3] = 0x01;
  =20     send_buffer();
        delay_ms(500);=0D
        lcd_clear();
       }
=20      if(left==1)
        {
 =20      lcd_gotoxy(0,2);
        lcd_puts(=<-");
        buffer_data[3] = 0x02;
  =20     send_buffer();
        delay_ms(500);=0D
        lcd_clear();
       }
=20        lcd_gotoxy(0,3);
         =printf(text,"     Volume:%d   ",volume);
     =20   lcd_puts(text);
         Nextion_cmd2("n0=val=",volume);
         if (down==1)
 =20         {
           volume==1;
           delay_ms(100);
    =20      if (volume<1)
           v=lume=30;
           set_volume(volume);
 =20         }

          if =up==1)
            {
      =20     volume+=1;
            dela=_ms(100);
            if (volume>30)
 =20           volume=1;
        =20   set_volume(volume);
            } =20
            switch(UDR0)//UDR0 = Usar=0 Data Reseive --> Beter Than "gets" or "scanf" Becaue =t Doesnt Wait For Data!!!     
       =20     {
              case 'P=:
              if(p==1)
   =20          {
            =20  buffer_data[3] = 0x0E;
           =20   send_buffer();
               =elay_ms(500);
               p=0;
=20             }
         =20    else if (p==0)
           =20  {
               buffer_data[3] =3D 0x0D;
               send_buffer();=0D
               delay_ms(500);
  =20            p=1;
         =20     }   
              =reak; 
              case 'N':
 =20            buffer_data[3] = 0x01;
 =20            send_buffer();
      =20       delay_ms(500);   
        =20     break; 
              c=se 'Q':
              buffer_data[3] ==200x02;
              send_buffer();
=20             delay_ms(500);    
 =20            break;
         =20    case 'U':
              vo=ume+=1;
              delay_ms(100);
=20             if (volume>30)
    =20         volume=1;
          =20   set_volume(volume);    
         =20    break;
              case =D': 
              volume-=1;
 =20            delay_ms(100);
      =20       if (volume<1)
           =20  volume=30;
              set_vol=me(volume);   
              break;=0A              default:
      =20       break;
             }=20
     }
}
void battery_deg(void)
{
 =20 vbat = read_adc(3);
   vbat /= 50.71;
// =20 deg_bat=vbat*7.936;
   if     (vbat>=12.6)deg=bat=100;
   else if(vbat>=11.6 && vbat<12.5) deg_bat=3D100-((12.6-vbat)*90);
   else if(vbat>=1.16 && vbat<11=6) deg_bat=10-(((11.6-vbat)*90)/104.4);
   
   if=deg_bat>=80&&deg_bat<=100)Track=full;   
   else i=(deg_bat>=60&&deg_bat<=79)Track=sevenfive;
   else if(de=_bat>=40&&deg_bat<=59)Track=fifty;
   else if(deg_bat>==0&&deg_bat<=39)Track=twentyfive;
   else if(deg_bat>=0&&=eg_bat<=19) Track=low; 
}
void cmps(void)
 {
=20   //delay_ms(30);
    i2c_start();
    i=c_write(0xC0);
    i2c_write(0x02);
    i2c_stop(=;
    i2c_start();
    i2c_write(0xC1);
  =20 delay_us(50);
    dj=i2c_read(1);
    dj==j<<8;
    dj+=i2c_read(1);
    dj=dj/10;
=20   shib1=i2c_read(1);
    roll=i2c_read(0);
 =20  i2c_stop();
 }
    /*
void calibration_c=p10 (void)
{
    lcd_clear();
    lcd_puts=(" cmp calibration ");
    while(POK==0);
  =20 i2c_start();
    i2c_write(0xC0);
    i2c_wr=te(22);
    i2c_write(0xf0);
    i2c_stop();
=20   delay_ms(20);
    while(POK==1)
    =20   {
        //cmps();
      =20 lcd_gotoxy(0,0);
        sprintf(text,"Turn To = degree      degree=%3d  ",dj);
      =20 lcd_puts(text);
        }
    while =POK==1);
    while (POK==0);

    =2c_start();
    i2c_write(0xC0);
    i2c_write(22=;
    i2c_write(0xf5);
    i2c_stop();
  =20 delay_ms(100);

    lcd_clear();
    lc=_puts("     East");
    TCNT=0;
    w=ile(TCNT<turn)
        {
        =f (TCNT<turn*0.2 || TCNT>turn*0.8)
          =20 go(150,-150);
        else
      =20     go(220,-220);
        }
   =20go(0,0);
    delay_ms(500);
    i2c_start();=0A    i2c_write(0xC0);
    i2c_write(22);
   =20i2c_write(0xf5);
    i2c_stop();
//    delay_ms=100);

    lcd_clear();
    lcd_puts("  =20  Sout");
    TCNT=0;
    while(TCNT<turn=
        {
        if (TCNT<tur=*0.2 || TCNT>turn*0.8)
            go(150,=150);
        else
          =20 go(220,-220);
        }
    go(0,0);=0D
    delay_ms(500);
    i2c_start();
   =20i2c_write(0xC0);
    i2c_write(22);
    i2c_wri=e(0xf5);
    i2c_stop();
//    delay_ms(100);
=0D
    lcd_clear();
    lcd_puts("     Wes=");
    TCNT=0;
    while(TCNT<turn)
  =20     {
        if (TCNT<turn*0.2 || =CNT>turn*0.8)
            go(150,-150);
 =20      else
            go(220,-2=0);
        }
    go(0,0);
   =20delay_ms(500);
    i2c_start();
    i2c_write(0=C0);
    i2c_write(22);
    i2c_write(0xf5);
=20   i2c_stop();
//    delay_ms(100);

   =20lcd_clear();
    lcd_puts("     North");
  =20 TCNT=0;
    while(TCNT<turn)
       =20{
        if (TCNT<turn*0.2 || TCNT>turn*0.8)=0A            go(150,-150);
      =20 else
            go(220,-220);
  =20     }
    go(0,0);
    delay_ms(500)=
    lcd_clear();
    lcd_putsf("calibration do=e");
    delay_ms(1000);
    } 
*/
vo=d calibration_cmp11 (void)
{ 
    while(POK==0)=
    lcd_clear();
    lcd_puts("Press OK to =alib   back to factory reset"); 
    delay_ms(10=0);
    while(POK && PBACK); 
    if (POK=3D=0)
        {
        delay_m=(1000);
        i2c_start();
       =20i2c_write(0xC0);
        i2c_write(0);
   =20    i2c_write(0xf0);
        i2c_stop();
=20       delay_ms(25);
        
 =20      i2c_start();
        i2c_write(0xC=);
        i2c_write(0);
        =2c_write(0xf5);
        i2c_stop();
     =20  delay_ms(25);
        
      =20 i2c_start();
        i2c_write(0xC0);
  =20     i2c_write(0);
        i2c_write(0xf6)=
        i2c_stop();
        dela=_ms(25);
          
         =0D
        lcd_clear();
        lcd_=uts("Rotate the compass  in 3 directions");
     =20  lcd_gotoxy(0,3);
        lcd_puts("Press OK =or Rotating"); 
        delay_ms(100);
  =20     while(POK);
        delay_ms(200);=0A        TCNT=0;
        go(70,-70)=
        while(TCNT<=turn*5);TCNT=0;
   =20    go(0,0);
        while(POK);
  =20     delay_ms(200);
        TCNT=0;
=20       go(70,-70);
        while(TCNT<=3Dturn*5);
        go(0,0);
       =20while(POK);
        delay_ms(200);
    =20   TCNT=0;
        go(70,-70);
   =20    while(TCNT<=turn*5); 
        go(0,0=;
        while(POK);
        del=y_ms(100);
        i2c_start();
      =20 i2c_write(0xC0);
        i2c_write(0);
  =20     i2c_write(0xf8);
        i2c_stop();=0A        delay_ms(20);

        =hile(1)
            {
       =20    lcd_gotoxy(0,2);
            spr=ntf(text,"shib1=%3d   dj=%3d ",shib1,dj);
      =20     lcd_puts(text);
            l=d_gotoxy(0,3);
            }
    =20   }
        
    else if (PB=CK==0)
        {
        i2c_=tart();
        i2c_write(0xC0);
      =20 i2c_write(0);
        i2c_write(0x20);
  =20     i2c_stop();
        delay_ms(30);
=20       
        i2c_start();
  =20     i2c_write(0xC0);
        i2c_write(0)=
        i2c_write(0x2A);
        =2c_stop();
        delay_ms(30);
      =20 
        i2c_start();
        =2c_write(0xC0);
        i2c_write(0);
    =20   i2c_write(0x60);
        i2c_stop();
 =20      delay_ms(30);
        lcd_clear();=0D
        lcd_puts("reset factory done.");
  =20     while(1)
            {
 =20          lcd_gotoxy(0,2);
       =20    sprintf(text,"shib1=%3d   dj=%3d ",shib1,dj);
=20           lcd_puts(text);
       =20    lcd_gotoxy(0,3);
            }=0A        
        }
    =20   
    }
void calibration_robot (void)
=
  if(dj==0&&shib1==255&&roll==255)
    {=0D
     lcd_clear();
     lcd_gotoxy(3,1);
=20    lcd_puts("Compass Error ");
     delay_ms(=00);
     change_baud();
     printf("page =ompass Error");
     _buffer();
     while(=);
    } 
    lcd_clear();
    lcd=puts("   calibrating...");
    delay_ms(1000);
  =20 lcd_clear();
    lcd_puts("     North");
/=    cmps();
    djN=dj;

    lcd_c=ear();
    lcd_puts("     East");
    T=NT=0;
    while(TCNT<turn)
        {=0A        if (TCNT<turn*0.2 || TCNT>turn*0.8)
 =20          go(150,-150);
        =lse
            go(220,-220);
    =20   }
    go(0,0);
    delay_ms(500);
=/    cmps();
    djE=dj;
    lcd_clear(=;

    lcd_puts("     South ");
   =20TCNT=0;
    while(TCNT<turn)
        =
        if (TCNT<turn*0.2 || TCNT>turn*0.8)
=20           go(150,-150);
       =20else
            go(220,-220);
   =20    }
    go(0,0);
    delay_ms(500);=0A//    cmps();
    djS=dj;

    l=d_clear();
    lcd_puts("     West ");
  =20 TCNT=0;
    while(TCNT<turn)
       =20{
        if (TCNT<turn*0.2 || TCNT>turn*0.8)=0A            go(150,-150);
      =20 else
            go(220,-220);
  =20     }
    go(0,0);
    delay_ms(500)=
//    cmps();
    djW=dj;

   =20if (djE<0)   djE+=360;
    if (djS<0)   dj=+=360;
    if (djW<0)   djW+=360;

  =20 TCNT=0;
    while(TCNT<turn)
       =20{
        if (TCNT<turn*0.2 || TCNT>turn*0.8)=0A            go(150,-150);
      =20 else
            go(220,-220);
  =20     }
    go(0,0);
    lcd_clear();=0A    lcd_putsf("calibration done");
    delay_ms(50=);
    }
int MLXReadData(char MLX_ID)
{
 =20  unsigned int MLX_LowData,MLX_HighData,MLX_Data;
    =asm("cli")
    i2c_start();
    i2c_write(MLX_ID<=1);
    i2c_write(0x07);
    i2c_start();
 =20  i2c_read(1);
    MLX_LowData=i2c_read(1);
  =20 MLX_HighData=i2c_read(0);
    MLX_HighData&=0x007F;=0A    MLX_HighData=(MLX_HighData)<<8;
    MLX_HighDa=a+=MLX_LowData;
    MLX_HighData=MLX_HighData*0.02;
 =20  MLX_Data=MLX_HighData-273.15;
    i2c_stop();
=0A    if (MLX_Data>100)  MLX_Data=0;
    retur= MLX_Data;
    delay_ms(10);
    #asm("sei")=0A    delay_ms(10);
    }
    /*
voi= MLX_find_address(void)
{
    int MLX_OUT,id;
 =20  #asm("cli")
    for (id=0;id<255;id+=2)
 =20      {
        delay_ms(30);
  =20     MLX_OUT=MLXReadData(id);
        sp=intf(text,"ID=0x%X   t=%3d  ",id,MLX_OUT);
     =20  lcd_gotoxy(0,0);
        lcd_puts(text);
=20       if (MLX_OUT>0 && MLX_OUT<100)
    =20       {
            while(POK=3D=1)
                {
   =20            delay_ms(50);
      =20         MLX_OUT=MLXReadData(id);
     =20          sprintf(text,"ID=0x%X   t=%3d  =,id,MLX_OUT);
                lcd_goto=y(0,0);
                lcd_puts(text)=

                }
   =20        }
        }
    =
void MlxChangeAddress(char new_id)
{

//agar CRC=20Found neshon dad k che behtar ama agaram neshon nadad =ohem nis , faghat 3 ta noktaro havaseton bashe
//aval =nke ro port i2c faghat 1 mlxi k mikhaein addressesho av=z konin bashe
//dovom inke bad az inke Finish dad ha=man robot ro khamush konin , mlx ro ghat konin , in =ode ro gheire comment konin bad dobare program konin vase=20inke bazi oghat agar havaseton nabashe dobare in code e=ra beshe o mlx ha vasl bashan ehtemale sokhtaneshon hast=0A//sevom inke dar code bala address 0x2A hast k moghe =hundanesh bayad be sorate 0x2A<<1 bashe albate in to code=20khundane(read) khodam rayat shode va faghat kafie in 0x2A=20ro janeshine masalan 0x5A konin .


    =har a,found=0;
    lcd_clear();
    lcd_putsf="Erasing...");
    delay_ms(100);
    //Erase A=dress >>>>>>
    i2c_start();
    i2c_write(0x0=<<1); // All Mlx on i2c port will accept this
  =20 i2c_write(0x2E);  // Address Register
    i2c_wri=e(0x00); //Erase LowByte of address
    i2c_write(0x00=; //Erase HighByte of address
    i2c_write(0x6F); /=Send PEC
    i2c_stop();
    //Erase Address =<<<<<<
    lcd_putsf("Writing...");
    delay_ms(=00);
    for(a=0;a<255;a++)  // while for finding =he CRC of address * but sometimes it works
    =20    {
         i2c_start();
   =20     i2c_write(0x00<<1); // All mlx devices
  =20      i2c_write(0x2E);    // address register
=20        i2c_write(new_id);    // <<<<<<<<< wr=te NewAddress
         i2c_write(0x00);    =/ all mlx devices for find CRC
         =f(i2c_write(a)==1)
               {=0A               lcd_clear();
    =20          sprintf(text,"CRC Found =%d   "=a);
               lcd_puts(text);
=20              found=1;
     =20         delay_ms(1000);
         =20     break;
               }=0D
         }
    i2c_stop();
   =20lcd_clear();
    sprintf(text,"ID changed to    =20 0x%X   ",new_id);
    lcd_puts(text);
   =20delay_ms(2000);
    while(1);
    }
*/
=oid victimCorection(void)
{
   #asm ("sei")
  =20play_track(prgact);
   while (UFL>50)
    {
=20    go(0,-200);
     delay_ms(300);
   =20 go(-200,0);
     delay_ms(300);
     go(=00,200);
     delay_ms(300);
     }
  =20  go(0,0);
     #asm ("cli")        =0D
}
void victim (void)
{   
    int s=atic SaveTCNT;
    SaveTCNT = TCNT;
    #=sm("cli")
    
    if (tempL2>=temp || te=pR2>=temp || tempL1>=temp || tempR1>=temp)
     =20  {
                    =0D
        if(IsInTurn) JumpStack=true;  
 =20      go(0,0);
         
   =20    play_track(lifeform);
         
 =20      for (i=0;i<cheshmak;i++)
       =20    {LED_ON;LED_R_ON;delay_ms(50);LED_OFF;delay_ms(50);}
 =20        
         vfounded=1;=0A          
         if(tempL2>=3Dtemp || tempL1>=temp)
         {
  =20        if(!JumpStack) victimCorection();
   =20     }
         
      =20  else if(tempR2>=temp || tempR1>=temp)
     =20   {
            #asm ("sei")
/=            TCNT=0; 
//       =20    go(230,-230);
//            whil=(TCNT<(turn*2)+2);
//            go(0,0);
=/            victimCorection();
     =20      MLX_R_Detects = true;
        =20   if(!JumpStack)
            {
 =20           play_track(prgact);
     =20       while (UFR>50)
          =20  {
             go(-200,0);
  =20          delay_ms(300);
        =20    go(0,-200);
             delay=ms(300);
             go(200,200);
  =20          delay_ms(300);
        =20    }
             go(0,0);
 =20          }
            =asm ("cli")
         }
        =20            
        if (m=mvic[x][y]==0 && !JumpStack)
           =20{
            AX12(1,AXmin,500);
  =20         delay_ms(1000);
         =20  AX12(1,AXmax,500);
            memvic[=][y]++;
            delay_ms(500);
  =20         }
//            i=(MLX_R_Detects)     
//            {=0D
//            #asm ("sei")
//    =20       while (UFL<25)
//          =20  {
//              go(-200,0);
=/              delay_ms(300);
//    =20         go(0,-200);
//         =20    delay_ms(300);
//             =20go(200,200);
//              delay_ms(30=);
//             }
//      =20      TCNT=0;
//             =20go(-230,230);
//            while(TCNT<(turn=2)+2);
//            go(0,0);      =20     
//            Tanzim();
=/            }
         go(S=,SR);
         TCNT = SaveTCNT;
   =20    }
    #asm("sei")
    }
void =etup(void)
   {
    int page=1;
    =it first=0;
    int b,c;
    char left,ri=ht,up,down; 
    // USART Baud Rate: 38400
  =20 UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0= | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
    UB=R0L=0x11;
    delay_ms(1);
    lcd_clear();
=20   IsStartPage = false;
    while (1)
 =20  {
        b = read_adc(6);
   =20    c = read_adc(5);
           =20
        // USART Baud Rate: 38400
  =20         UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0=<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPO=0);
            UBRR0L=0x11;
    =20       delay_ms(1);
            =0D
        if (b<100)          left=3D1;
        else if (b>=100)    left==;
        if (b>900)          ri=ht=1;
        else if (b<=900)    righ==0;

        if (c<100)        =20 down=1;
        else if (c>=100)   =20down=0;
        if (c>900)        =20 up=1;
        else if (c<=900)    =p=0;

        if (right==1)
   =20        {
            delay_=s(200);
            page++;
     =20      first=0;
            if =page>7) page=1;
            lcd_clear();=0A            }
        if (=eft==1)
            {
     =20      delay_ms(200);
            =age--;  
            first=0;
  =20         if (page<1) page=7;
     =20      lcd_clear();
            }=0D

           
        i= (page==1)   // fasele
           =20{
            lcd_gotoxy(0,0);
   =20        sprintf(text,"L=%3d %3d  R=%3d",UFL,UF,=FR);
            lcd_puts(text);

 =20          lcd_gotoxy(0,1);
       =20    sprintf(text,"LB=%3d    RB=%3d",UBL,UBR);
 =20          lcd_puts(text);
        =20    if(first==0)
             =change_baud();
             printf("page S=tup_1");
             _buffer(); 
 =20           }
           =20 first=1;
             Nextion_cmd2("n=.val=",UFL);
             Nextion_cmd2("n1=val=",UBL);
             Nextion_cmd2("n2.=al=",UFR);
             Nextion_cmd2("n3.v=l=",UBR);
             Nextion_cmd2("n4.va==",UF);
            if(up==1)
  =20         {
            go(=0,60);   
            }
    =20       else if(down==1)
        =20   {
            go(-60,-60);
 =20          }

          =lse    go(0,0);}
        else if (page===)   // compass
            {
  =20         go(0,0);
           =20//cmps();
            //shib();
   =20        lcd_gotoxy(0,0);
         =20  sprintf(text,"Shib=%3d   Dj=%3d        Ro=l=%3d",shib1,dj,roll);
            lcd_puts(=ext);
            lcd_gotoxy(0,3);
  =20         if(first==0)
        =20   { 
            change_baud();
=20           printf("page Setup_2");
   =20        _buffer();
           =20}
            first=1;
     =20       cmps();
             =irCheck();
             Nextion_cmd2("n3.val=3D",dir);
             Nextion_cmd2("n0.val==,shib1);
             Nextion_cmd2("n1.val==,dj);
             Nextion_cmd2("n2.val=",=oll);  
             
     =20       lcd_puts("Pres OK to calibrate");
   =20        if ( POK==0)
        =20       {
               =20lcd_clear();
                while(P=K==0);
                lcd_puts(" =re you sure?  ");
               =20lcd_gotoxy(0,1);
                lcd=puts("Press OK or back");
             =20  while(POK==1 && PBACK==1)
        =20           {
           =20        if (POK==0)
         =20              {calibration_cmp11();break;}=0A                    if (PBACK==3D0)
                      =20 break;
                    =
                }
     =20      }
        else if (page==3=   // TCNT & K
            {
=20           #asm("sei")
        =20   lcd_gotoxy(0,0);
            sprint=(text,"TCNT=%5d   ",TCNT);
            =cd_puts(text);

            lcd_gotoxy(0,=);
            sprintf(text,"K:%d %d %d =d  ",KFL,KFR,KBL,KBR);
            lcd_put=(text);
            
       =20    if(first==0)
            {=0A            change_baud();
      =20     printf("page Setup_3");
         =20  _buffer(); 
             }
 =20           first=1;
        =20    
             Nextion_cmd2("n0=val=",TCNT);
             if(KFL==0)=0A             Nextion_cmd("va0.val=1");
 =20           if(KFR==0)
       =20     Nextion_cmd("va0.val=2");
         =20   if(KFL==1&&KFR==1)
           =20 Nextion_cmd("va0.val=0");
//            =20if(KBR==0)
//             Nextion_cmd(=va0.val=3");
//             if(KBL==0)=0D
//             Nextion_cmd("va0.val=4");=0A//             if(KFL==1&&KFR==1&&KBL==3D1&&KBR==1)
//             Nextion_cmd(=va0.val=0");
            
     =20      if (POK==0)
           =20    {
                TCNT==;
                }
     =20      }
        else if (page==4=  // MLX
            {
    =20       lcd_gotoxy(9,0);
          =20 sprintf(text,"%2d",tempF);
            lc=_puts(text);
            lcd_gotoxy(0,0);
=20           sprintf(text,"%2d",tempL1);
   =20        lcd_puts(text);
          =20 lcd_gotoxy(0,1);
            sprintf(text="%2d",tempL2);
            lcd_puts(text);
=20           lcd_gotoxy(0,2);
      =20     sprintf(text,"%2d",tempL3);
         =20  lcd_puts(text);
            lcd_gotoxy=18,0);
            sprintf(text,"%2d",tempR1);=0D
            lcd_puts(text);
     =20      lcd_gotoxy(18,1);
           =20sprintf(text,"%2d",tempR2);
            lcd_=uts(text);
            lcd_gotoxy(18,2);
=20           sprintf(text,"%2d",tempR3);
   =20        lcd_puts(text); 
         =20  
            if(first==0)
 =20          {
            =hange_baud();
            printf("page Setup=4");
            _buffer(); 
    =20        }
             fir=t=1;
             Nextion_cmd2("n0.val="=tempL1);
             Nextion_cmd2("n1.val==,tempL2);
             Nextion_cmd2("n2.val==,tempL3);
             Nextion_cmd2("n3.val==,tempR1);
             Nextion_cmd2("n4.val==,tempR2);
             Nextion_cmd2("n5.val==,tempR3);
            }
      =20 else if (page==5)  //  SDF
        =20   { 
            if(first==0)=0A            {
          =20 change_baud();
            printf("page =etup_5");
            _buffer(); 
  =20          } 
           =20first=1;
            go(0,0);
   =20        #asm("sei")
           =20adc();
            lcd_gotoxy(5,0);
 =20          sprintf(text,"F=%1.1f=%d  ",VSDF,SD=);
            lcd_puts(text);
    =20                         =0D
            Nextion_cmd23("t7.txt=",VSDF);=0A            Nextion_cmd2("n1.val=",SDF);
 =20                         =0D
            lcd_gotoxy(5,1);
    =20       sprintf(text,"LDR=%1.1f=%d  ",VLDR,LDR);
=20           lcd_puts(text);
       =20     
            Nextion_cmd23("t=.txt=",VLDR);
            Nextion_cmd2("n5.v=l=",LDR);             
       =20                  
     =20      lcd_gotoxy(5,2);
           =20sprintf(text,"B=%1.1f=%d ",VSDB,SDB);
        =20   lcd_puts(text);
               =0D
            Nextion_cmd23("t8.txt=",VSDB);=0A            Nextion_cmd2("n3.val=",SDB);
 =20             
          =20  if(VSDB<=0.8&&VSDF<=0.8)
           =20 {
             lcd_gotoxy(5,3);
 =20          lcd_puts(" Silver"); 
    =20       Nextion_cmd("va0.val=1");
       =20    }
           else if(VSDF>=3.5=&VSDB>=3.5)
            {
     =20       lcd_gotoxy(5,3);
          =20 lcd_puts(" Black ");
            Next=on_cmd("va0.val=2");
            }
  =20        else
            {=0A            lcd_gotoxy(5,3);
     =20      lcd_puts(" White ");
         =20  Nextion_cmd("va0.val=0");  
          =20 }

            if (POK==0)
=20               {
       =20        while(POK==0);
         =20      lcd_clear();
             =20  break;
                }
=20           }
           =20else if (page==6)   //  RGB 
       =20    {
             if(first==0=
             {
        =20    change_baud();
             pr=ntf("page Setup_6");
             _buffer(=;  
             LED_OFF;
   =20         }
             =0D
             first=1; 
    =20        go(0,0);
            =20switch(UDR0)//UDR0 = Usart0 Data Reseive --> Beter Than =gets" or "scanf" Becaue it Doesnt Wait For Data!!!   =20 
             {
      =20       case 'R':
            =20 LED_R_ON;   
              brea=; 
              case 'r':
  =20           LED_R_OFF;   
     =20        break;    
         =20    case 'G':
              LE=_G_ON;    
              break; =0D
              case 'g': 
   =20          LED_G_OFF;    
     =20        break;
             =20case 'B':
              LED_B_ON;  =20 
              break;
    =20         case 'b': 
         =20    LED_B_OFF;    
           =20  break;
              default:
=20             LED_OFF;
       =20      break;
             } =0D
             UDR0='';  
   =20         } 
            =20else if (page==7)        // battery
  =20         {
            if(=irst==0)
             {
    =20        change_baud();
          =20  printf("page Setup_7");
            =20_buffer();  
             LED_OFF;
=20            }
          =20  
               first=1; =0A               go(0,0);
     =20         LED_OFF;
           =20   set_volume(volume);
             =20 define_char(char1,1);
               =cd_gotoxy(18,1);
               lcd_putc=ar(1);
               lcd_gotoxy(0,0);=0A               battery_deg();
   =20           sprintf(text,"V_Battery:%1.2f v",vbat)=
               lcd_puts(text);
 =20             lcd_gotoxy(0,3);
    =20          sprintf(text,"Volume:%2d   ",volume);=0D
               lcd_puts(text);
  =20            lcd_gotoxy(0,1);
     =20         sprintf(text,"   Status:%2d %  ",d=g_bat);
               lcd_puts(text);=0A               Nextion_cmd2("n0.val=",deg=bat);
               Nextion_cmd2("n1.va==",volume);
            if (down==1)=0A                {
      =20           volume-=1;
        =20          delay_ms(100);
        =20          if (volume<1)
        =20           volume=30;
        =20         set_volume(volume);

     =20          }

          =20     if (up==1)
            =20   {
                  vol=me+=1;
                  delay_m=(100);
                   if (=olume>30)
                    =olume=1;
                  set_v=lume(volume);

                }=0A            if (POK==0)
     =20          {
            =20   while (POK==0);
             =20  change_baud();
                =rintf("vis p0,1");           
      =20          _buffer();
         =20      lcd_clear();
             =20  lcd_putsf(" Testing ");
            =20   delay_ms(200);
               =20lcd_putsf(".");
                dela=_ms(200);
                lcd_putsf(".=);
                delay_ms(200);
=20               lcd_putsf(".");
   =20            delay_ms(200);
      =20         battery_deg();
         =20      play_track(Track);
           =20    delay_ms(500);
              =20 lcd_clear();
                chan=e_baud();
                printf("vis =0,0");           
          =20      _buffer();
             =20  }
            } 
     =20     }
        }
void calculate (=oid)
{
    if (dir==1)
        =
        memF=mem[x][y+1];
       =20memB=mem[x][y-1];
        memL=mem[x-1][y];
=20       memR=mem[x+1][y];
        DF==Xd-x)     * (Xd-x)       +    (Yd-(y+1))*=Yd-(y+1)) ;
        DB=(Xd-x)     * (X=-x)       +    (Yd-(y-1))*(Yd-(y-1)) ;
   =20    DR=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)*=Yd-y);
        DL=(Xd-(x-1)) * (Xd-(x-1))   =    (Yd-y)*(Yd-y);
        }
    =lse if (dir==2)
        {
     =20  memF=mem[x+1][y];
        memB=mem[x-1][y]=
        memL=mem[x][y+1];
       =20memR=mem[x][y-1];
        DF=(Xd-(x+1)) * (X=-(x+1))   +    (Yd-y)    *(Yd-y);
     =20  DB=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)   =20*(Yd-y);
        DR=(Xd-x)     * (Xd-x=       +    (Yd-(y-1))*(Yd-(y-1));
     =20  DL=(Xd-x)     * (Xd-x)       +   =20(Yd-(y+1))*(Yd-(y+1));
        }
    el=e if (dir==3)
        {
      =20 memF=mem[x][y-1] ;
        memB=mem[x][y+1]=20;
        memL=mem[x+1][y];
      =20 memR=mem[x-1][y];
        DF=(Xd-x)    =20* (Xd-x)       +    (Yd-(y-1))*(Yd-(y-1));
 =20      DB=(Xd-x)     * (Xd-x)       =    (Yd-(y+1))*(Yd-(y+1));
        DR=(Xd-(x=1)) * (Xd-(x-1))   +    (Yd-y)    *(Yd-y);
 =20      DL=(Xd-(x+1)) * (Xd-(x+1))   +    (=d-y)    *(Yd-y);
        }
    el=e if (dir==4)
        {
      =20 memF=mem[x-1][y] ;
        memB=mem[x+1][y]=20;
        memL=mem[x][y-1];
      =20 memR=mem[x][y+1];
        DF=(Xd-(x-1)) * =Xd-(x-1))   +    (Yd-y)     *(Yd-y);
   =20    DB=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y) =20   *(Yd-y);
        DR=(Xd-x)     = (Xd-x)       +    (Yd-(y+1)) *(Yd-(y+1));
 =20      DL=(Xd-x)     * (Xd-x)       =    (Yd-(y-1)) *(Yd-(y-1));
        }
 =20      send(x,y,mem[x][y],dir,memF,memB,memR,memL,Xd,Yd);
=20   }
void go (signed int spl,signed int spr)
=
    SL=spl;SR=spr; // braye save sorat motor =a baraye start e 2bare  
    //if(spl!=0) spl==pl+CHARKH;
 
    if(spr!=0) spr=spr+CHARKH;  =0D
    if (spl>255)     spl=255;
    i= (spl<-255)    spl=-255;
    if (spr>255)   =20 spr=255;
    if (spr<-255)    spr=-255;
=0D
    if (spl>0)
        {L1=0;SL1=sp=;}
    else if (spl<0)
        {L1==;SL1=255+spl;}
    else
        {L1=0=SL1=0;}

    if (spr>0)
        =R1=1;SR1=255-spr;}
    else if (spr<0)
    =20   {R1=0;SR1=(-1)*spr;}
    else
    =20   {R1=0;SR1=0;}
    }  
void check_err=r(void)
{

    static int error1,error2;
 =20  #asm ("sei")
    
    if (UFL-UBL<150=20 && UFL-UBL>-150  && UFL<200 && UBL<200 )
    =20   {
        error1=(UFL-UBL);
   =20    error2=UFL-70;
        error=error1+=rror2;
        }
    else if (UFR-UBR=150  && UFR-UBR>-150  && UFR<200 && UBR<200 )
  =20     {
        error1=(UBR-UFR);   =20// chap & rast bar aks ham hastand
       =20error2=70-UFR;
        error=error1+error2;
=20       }
    else if (UFL-UBL<150  && =FL-UBL>-150  && UFL<500 && UBL<500 )
       =20{
        error1=(UFL-UBL);
      =20 error2=UFL-370;
        error=error1+error2;=0A        }
    else if (UFR-UBR<150  =& UFR-UBR>-150  && UFR<500 && UBR<500 )
      =20 {
        error1=(UBR-UFR);    // cha= & rast bar aks ham hastand
        error2=3D370-UFR;
        error=error1+error2;
   =20    }
    else error=0;        =0A    if(error>90)    error=90;
    if(error=-90)   error=-90;

    if(abs(error) < 10) =rror += 10 - abs(error); // error < -10 = -10  =20error < 10 = 10 ; 
    
    }
=oid move30 (void)
{
    int tcnt1=0;
   =20TCNT=0;
    vfounded=0;
    LED_OFF;
 =20  go(180,180);
    
    while(TCNT<go30) =20 
        {
        if (UF<=0 || KFL+KFR==0)
            { 
=20           go(0,0);
         =20  break;
            }   
 =20      check_error(); 
        if (KFR=3D=0 && KFL==1)
               =20{
                go(0,0);
  =20             tcnt1=TCNT;
     =20          #asm("cli")
         =20      go(0,-150);
             =20  delay_ms(400);
                =o(0,0);

                go(-150,=);
                delay_ms(550);
=20               go(0,0);

   =20            go(150,150);
       =20        delay_ms(350);

        =20       TCNT=tcnt1;
           =20    #asm("sei")
               =20}
        else if (KFR==1 && KFL==0)=0D
                {
     =20          go(0,0);
          =20     tcnt1=TCNT;
             =20  #asm("cli")
                go=-150,0);
                delay_ms(400)=
                go(0,0);

 =20              go(0,-150);
     =20          delay_ms(585);
        =20       go(0,0);

           =20    go(150,150);
               =20delay_ms(350);

                =CNT=tcnt1;
                #asm("sei=)
                }
     =20  else if (TCNT<go30*0.15)//|| TCNT>go30*0.85)
    =20       go(210-error ,210+error);
       =20else
            go(250-error ,250+error);=0D
            adc();
        =20   
        if (VSDF>=4 && VSDB>=4) =20  // black room
            {
 =20          int SaveTCNT = TCNT;
   =20        LED_OFF;
            =ED_R_ON;
            go(0,0);
    =20       adc();
              =20         
            TCNT=3D0;
            while(TCNT< SaveTCNT )=0A              {
        =20     check_error(); 
            =20 if (TCNT < SaveTCNT*0.15 || TCNT > SaveTCNT*0.85)
 =20             go((-1)*(180+error) ,(-1)*(180-e=ror));
               else
   =20            go((-1)*(200+error) ,(-1)*(200-erro=));
              }
      =20      
            go(0,0);
=0D
            calculate();
      =20     if      (dir==1)
       =20        {
              =20 mem[x][y+1]+=3;
                =--;      // inja yeki kam mishe va dar akhare t=beye move30cm yeki ezafe mishe dar natije bar migarde sar= jaye avalesh
                }=0A            else if (dir==2)
   =20            {
          =20     mem[x+1][y]+=3 ;
           =20    x--;
                }=0A            else if (dir==3)
   =20            {
          =20     mem[x][y-1]+=3 ;
           =20    y++;
                }=0A            else if (dir==4)
   =20            {
          =20     mem[x-1][y]+=3;
            =20   x++;
                }
=20           LED_OFF;
         =20  break;
            }      =20    
            
     =20  sprintf(text,"shib=%3d",shib1);
        lcd_=otoxy(12,3);
        lcd_puts(text);
    =20   }

    calculate();
    //shib();=0D
    if (check_sarbala)// && UFR<200 && UFL<200 && =F>300 )//&& right_cnt>=1)     // sar bala ee = =27    && x>=10 && y<=4
        {
=20       lcd_clear();
        sprintf(te=t,"    shib=%3d    ",shib1);
        =cd_gotoxy(0,3);
        lcd_puts(text);
   =20    TCNT=0; 
         
    =20   go(80-error ,80+error);
        while(TCN=<3);
        go(100-error ,100+error);
   =20    while(TCNT<10);
        go(0,0);
 =20      delay_ms(100);
            =20    
        if (check_sarbala)//&&!hasGon=Up)
            sarbala=1; 
//   =20    else if(check_sarbala2&& hasGoneUp)
//     =20         {
//             =20  TCNT=0;
//                go=-180,-180);
//                while(TC=T<go30);
//                go(0,0);=0A//                lcd_clear();
// =20              lcd_puts("You Have Returene= To The Game!!!         YAAAAYYYYY!!!   :-)")=
//                mem[x-1][y]+=8;=0A//                return;
//   =20           } 
        else =0D
        {
         TCNT=0;=0A         go(-180,-180);
         =hile(TCNT<10);
         go(0,0);
     =20  }    
        go(0,0);
    =20   }
    else if(check_sarpaeen) //&&  UFR<200=20 && UFL<200 && UF>300 ) //&& left_cnt>=1) // sar pa=eni = 15
        {
        =cd_clear();
        sprintf(text,"   shib1=%3d=20   ",shib1);
        lcd_gotoxy(0,3);
 =20      lcd_puts(text);
         
 =20      TCNT=0;
        go(60-error ,6=+error);
        while(TCNT<3);
      =20 go(70-error ,70+error);
        while(TCNT<5);=0A        go(80-error ,80+error);
      =20 while(TCNT<10);
        go(0,0);
    =20   delay_ms(100);
         
    =20   if (check_sarpaeen)
            s=rpaeen=1;
         else 
      =20  {
         TCNT=0;
      =20  go(-20,-20);
         while(TCNT<3);
 =20       go(-60,-60);
         while(T=NT<10);
         go(0,0);
       =20 }    
        go(0,0);
     =20  }
        
    if (sarbala=== && sarpaeen==0)
        {
     =20  if      (dir==1)   y++;
      =20 else if (dir==2)   x++;
        els= if (dir==3)   y--;
        else if =dir==4)   x--;
               =20 
        if(mem[x][y]==0)       =20 LED_B_ON; 
//        else if(mem[x][y]==1=    LED_G_ON;
//        else if(mem[x][y]==3D2)    {LED_R_ON;LED_G_ON;}
//        else =f(mem[x][y]==3)    {LED_G_ON;LED_B_ON;}
//      =20 else if(mem[x][y]>=4)    {LED_B_ON;LED_G_ON;LED_R_ON;}
=20        
        mem[x][y]++;
 =20      calculate();
             =20      
        if (mem[x][y] == =)
            number++; 
     =20             
        if(O=aviat==2&&(x==Xramp-16&&y==Yramp+4)||(x==Xramp-15&&y==Y=amp+4)||(x==Xramp-15&&y==Yramp+3)||(x==Xramp-16&&y==Yramp+3=)
         {
           X==Xramp-7;
           Yd=Yramp+4;
  =20      }
        else if(Olaviat==2=&(x==Xramp-7&&y==Yramp+4)||(x==Xramp-7&&y==Yramp+3)||(x===ramp-8&&y==Yramp+4)||(x==Xramp-8&&y==Yramp+3))
    =20    {
           Xd=Xramp-10;
 =20         Yd=Yramp;     
     =20   }                   
=20       /*      //  Don`t Need This Un=il We Have Complete Search!
         
 =20      if(Olaviat==1&&(x==Xd&&y==Yd)||(x==Xd&&===Yd-1)||(x==Xd-1&&y==Yd)&& returning==1)
    =20    {
         go(0,0);  
   =20     LED_OFF;
         LED_B_ON;
 =20       lcd(); 
         Xd=xs;=0A         Yd=ys; 
         }*=         
        if(UF<200&& UF>1=0) // yani age ziadi aghab tar az divar vaysadeh bood=0A         {
             =o(0,0); 
             Tanzim();
  =20      } 
         
    =20    if(KFL+KFR==0)
         {
 =20        go(0,0);
          go(-1=0,-150);
          TCNT=0;
      =20   while(TCNT<10);
          go(0,0);
=20         Tanzim();
         }=0A            
        }
=/    if (UFR<200 && UBR<200 && UFL<200 && UBL<200 &= UF>300 && memF<4); // yani age faghat az jolo rah da=ht go(0,0) nakone. dar gheire in soorat go(0,0) va eslah =one
//    else
//        {
//   =20    go(0,0);
//        Tanzim();
//  =20     }

    if (++str_cnt > 1 )
=20       {right_cnt=0; left_cnt=0;}
     =20 
    send(x,y,mem[x][y],dir,memF,memB,memR,memL,Xd,Yd); =0D
       
    }
void TL (void)
=
    #asm ("sei")
    if (M==11)
 =20      left_cnt++;
    else left_cnt=0;
=20   str_cnt=0;
    right_cnt=0;
    wh=le (UFR<25)
        {
        g=(0,-200);
        delay_ms(300);
      =20 go(-200,0);
        delay_ms(300);
   =20    go(200,200);
        delay_ms(300);
=20       }
    go(0,0);
    IsInTur==true;
    TCNT=0;
    while(TCNT<turn)
=20       {
        if (TCNT<turn*0.2 =| TCNT>turn*0.8)
            go(-150,150);=0A        else
            go(=220,220);
        }
    go(0,0);
 =20  
    //Tanzim();

    if (dir===)
        dir=4;
    else if (dir==3D2)
        dir=1;
    else if (di===3)
        dir=2;
    else if =dir==4)
        dir=3;
       =20IsInTurn=false;
        if(JumpStack)
   =20    {
         DropVic();
    =20    JumpStack=false;
        }
  =20   send(x,y,mem[x][y],dir,memF,memB,memR,memL,Xd,Yd);
   =20  move30();
    }
void TR (void)
{
 =20  #asm ("sei")
    if (M==110)
    =20   right_cnt++;
    else right_cnt=0;
   =20str_cnt=0;
    left_cnt=0;
    while (UFL=25)
        {
        go(-200,0);=0D
        delay_ms(300);
        go=0,-200);
        delay_ms(300);
      =20 go(200,200);
        delay_ms(300);
   =20    }
    go(0,0);
    IsInTurn=true;=0D
    TCNT=0;
    while(TCNT<turn)
   =20    {
        if (TCNT<turn*0.2 || TCN=>turn*0.8)
            go(150,-150);
  =20     else
            go(220,-220)=
        }
    go(0,0);
    =0D
    //Tanzim();

    if (dir==1)
=20       dir=2;
     else if (dir==2=
        dir=3;
     else if (dir=3D=3)
        dir=4;
     else if=20(dir==4)
        dir=1; 
     =sInTurn=false;
     if(JumpStack)
       =20{
         DropVic();
        =20JumpStack=false;
        }
    send(x=y,mem[x][y],dir,memF,memB,memR,memL,Xd,Yd);
    move30();
=20   }
void TB (void)
{
    #asm ("sei")=0D
    left_cnt=0;
    str_cnt=0;
   =20right_cnt=0;

    /*
    while (UFL<25=
        {
        go(-200,0);=0A        delay_ms(300);
        go(0,=200);
        delay_ms(300);
       =20go(200,200);
        delay_ms(300);
    =20   }
    while (UFR<25)
        =
        go(0,-200);
        dela=_ms(300);
        go(-200,0);
       =20delay_ms(300);
        go(200,200);
    =20   delay_ms(300);
        }  
   =20 */   
    IsInTurn=true;
    TCNT==;
    while(TCNT<(turn*2)+2)
        {=0A//        if((UFL+UBL)<(UFR+UBR))
//      =20     {
            if (TCNT>turn=1.6 || TCNT<turn*0.2)
            go(150,-=50);
            else
       =20    go(200,-200);
//            }=0A//        else 
//           =20{
//            if (TCNT>turn*1.6 || T=NT<turn*0.2)
//            go(-150,150);
=/            else
//         =20  go(-200,200);
//            }
 =20      }
    go(0,0);
    Tanzim();=0A
//    if (back==1)
        {
=/        TCNT=0;
//        while((KB===1 || KBR==1) && TCNT<go30*0.8)
//       =20    {
//            if (KBL==1=20&& KBR==1)
//                g=(-170,-170);
//            else if (KBL==3D0 && KBR==1)
//               =20go(-50,-170);
//            else if (KBL=3D=1 && KBR==0)
//              =20 go(-170,-50);
//            }
//  =20     go(0,0);
//        delay_ms(100);
=/
//        go(120,120);
//        =CNT=0;TCNT=0;
//        while(TCNT<go30/4);
/=        go(0,0);
//        delay_ms(10=);
        }
    if (dir==1)
 =20      dir=3;
    else if (dir==2)
=20       dir=4;
    else if (dir==3)=0A        dir=1;
    else if (dir==4=
        dir=2; 
        
=20   IsInTurn=false; 
     if(JumpStack)
  =20     {
         DropVic();
   =20     JumpStack=false;
        }  =0A    if (UF<150)  // yani poshtesh divar boode va =abayad door mizade. hala ke door zade nabayad bere jolo =a ella mire tu divar
        {
    =20   go(120,120);
        TCNT=0;TCNT=0;
=20       while((KFL==1 || KFR==1) && TCNT<go3=/2);
        go(0,0);
        del=y_ms(100);

        go(120,120);
    =20   TCNT=0;TCNT=0;
        while(TCNT<go30/=);
        go(0,0);
        delay=ms(100);
        }
    else
   =20{send(x,y,mem[x][y],dir,memF,memB,memR,memL,Xd,Yd); move30();}
=0A    right_cnt=0;
    left_cnt=0;
    =tr_cnt=0;
    }
void Tanzim(void)
{
   =20signed int speed,zarib;
    int err,time=0;
 =20  char t=0;
    #asm ("sei")
//    cm=s();
//    shib(); 
    /*
    if =20   (check_sarbala && UFR<200 && UFL<200 && UF>600)// =20&& right_cnt>=1)     // sar bala ee = 227  =20 && x>=10 && y<=4
        {
   =20    go(150 ,150);
        TCNT=0;
 =20      while(TCNT<3);
        go(0,0);=0A        delay_ms(100);
//        shi=();
        lcd_clear();
        =printf(text,"    shib=%3d    ",shib1);
     =20  lcd_gotoxy(0,3);
        lcd_puts(text);
=20       if (check_sarbala)
         =20  sarbala=1;
        go(0,0);
    =20   }
    else if(check_sarpaeen &&  UFR<200 =20&& UFL<200 && UF>600 )//&& left_cnt>=1)   // sar pa=eni = 15
        {
        =o(150 ,150);
        TCNT=0;
      =20 while(TCNT<3);
        go(0,0);
    =20   delay_ms(100);
//        shib();
  =20     lcd_clear();
        sprintf(text," =20 shib1=%3d    ",shib1);
        lcd_goto=y(0,3);
        lcd_puts(text);

    =20   if (check_sarpaeen)
            s=rpaeen=1;
        go(0,0);
       =20}
    */
    lcd_gotoxy(0,3);
    =cd_puts("Tanzim");
    
    if (sarbala==0 =& sarpaeen==0)
        {
      =20 while(t<3 && time++<350)     // 40=3000 m sec =ecause of ulltra
            {
  =20         if (UFR<200 && UBR<200)
    =20           {
           =20    err=UFR-UBR;
              =20 zarib=abs(err)*0.5;
               =20if (zarib>50)    zarib=50;
          =20     speed=40+zarib;
            =20   if (err>5)
                =20   go(speed,-speed);
              =20 if (err<-5)
                 =20  go(-speed,speed);
               =20}
            else if (UFL<200 && UB=<200)
                {
   =20            err=UFL-UBL;
      =20         zarib=abs(err)*0.5;
       =20        if (zarib>60)    zarib=60;
  =20             speed=40+zarib;
    =20           if (err>5)
        =20           go(-speed,speed);
      =20         if (err<-5)
         =20          go(speed,-speed);
       =20        }
            else =f (UFR<500 && UBR<500 && UFR-UBR<200 && UFR-UBR>-200  )=0A                {
      =20         err=UFR-UBR;
         =20      zarib=abs(err)*0.5;
          =20     if (zarib>50)    zarib=50;
     =20          speed=40+zarib;
       =20        if (err>5)
           =20        go(speed,-speed);
         =20      if (err<-5)
            =20       go(-speed,speed);
          =20     }
            else if (UFL=500 && UBL<500 && (UFL-UBL)<200 && (UFL-UBL)>-200 )
  =20             {
         =20      err=UFL-UBL;
            =20   zarib=abs(err)*0.5;
             =20  if (zarib>60)    zarib=60;
        =20       speed=40+zarib;
          =20     if (err>5)
              =20     go(-speed,speed);
            =20   if (err<-5)
               =20    go(speed,-speed);
             =20  }
            if (err<5 && err =-5)
                {
    =20           go(0,0);
         =20      t++;
               =20delay_ms(10);
                }
=20           else    t=0;
    =20       delay_ms(1);
            =
        t=0; time=0;
       =20while (t<2 && UF<800 && time++<1000)    // time=35=0A            {
          =20 if (UF<200)         err=UF-85;
    =20       else if (UF<500)    err=UF-385;
 =20          else if (UF<800)    err=UF-68=;
            if (err < -30 )   =20     go(-120,-120);
            el=e if (err < -10 )    go(-40,-40);
      =20     else if (err < 0 )      go(-30,-30);=0D
            else if (err < 10 )  =20  go(30,30);
            else if (er= < 30 )     go(40,40);
           =20else if (err > 30 )     go(120,120);
    =20       if (err<5 && err>-5)
       =20        {
              =20 go(0,0);
                t++;
=20               delay_ms(10);
   =20            }
          =20 else    t=0;
            delay_=s(1);
            }
       =20} 
    lcd_gotoxy(0,3);
    lcd_puts("Finish"=;
    if (sarbala==0)  lcd_puts("0");
   =20if (sarbala==1)  lcd_puts("1");
    if (sarpaeen=3D=0)  lcd_puts("0");
    if (sarpaeen==1)  lc=_puts("1");
    }
void sarbalaee (void)
{
 =20  
    vfounded=0;
    IsInRampUp = =rue;
    memvic[x][y]=0;
    
    =f(Olaviat==0) Olaviat = 1;
    else if(Olaviat!==) Olaviat = 3;
    right_cnt=0; left_cnt=0;
=20   lcd_clear();
    lcd_gotoxy(0,1);
    =printf(text,"   Sar Bala ee           Olavi=t = %d ",Olaviat);
    lcd_puts(text);
   c=ange_baud();
    printf("page RampUp");
    _bu=fer();
    IsStartPage = false;
    sprintf=text,"Olaviat = %d ",Olaviat);
    Nextion_cmd22("t0.t=t=",text);
    if(lastM[1]==101)
    {
=20   x++;
    if(lastM[0]==101)
    x++=
    }
    if(Olaviat!=3 && Olaviat!=4)=0A        {
        Xramp=x;
 =20      Yramp=y;
        }
   =20#asm ("sei")
    while(UF>80 && UBR<300)//&&check_sarb=la)
        {
        #asm ("se=")
        check_error();
        =f (KFL==0)
            {
    =20       go(250,-250);
           =20delay_ms(50);
            go(250,250);
=20           delay_ms(100);
       =20    go(-250,250);
            delay_=s(30);
            }
       =20else if (KFR==0)
            {
=20           go(-250,250);
       =20    delay_ms(50);
            go(250=250);
            delay_ms(100);
   =20        go(250,-250);
          =20 delay_ms(30);
            }
   =20    else
            go(250-error,25=+error);   
        if ((tempL2>=temp || =empR2>=temp) && vfounded==0)
           =20{
             go(90,90); 
   =20         play_track(lifeform);
       =20    for (i=0;i<cheshmak;i++)
         =20      {LED_ON; delay_ms(50); LED_OFF;delay_ms(50);}
=20               
        =20   vfounded=1;

            AX1=(1,AXmin,500);
            delay_ms(1000);
=20           AX12(1,AXmax,500);
      =20     }
        sprintf(text,"shib=%3d",s=ib1);
        lcd_gotoxy(12,3);
      =20 lcd_puts(text);
        }
    Tanzim=);

    if(Olaviat==1)
        {=0D
        x+=15;     // chon momkene s=the shibdar az akhare zamin nabashe
        =d=x;Yd=y;
        }
    if(Olaviat==3D3)
        {
        returning==;
        x=Xramp;
        y==ramp;
        Xd = xs;
       =20Yd = ys;
        }
    if(Olaviat=3D=4)
    {
        play_track(greeting=);
        x=Xramp1;
        y==ramp1;
        Xd=x;Yd=y;
       =20mem[x][y]+=10;
        Olaviat=1;
   =20    returning=1;
    }    
    =arbala=0;
    hasGoneUp = true;
    #asm ="sei")
    //mem[x][y]+=10;
    DirCheck();
=20   if(M==110)
    {
    memR=-1;=0A    TR(); 
    }
    else if(M===1)
    {
    memL=-1;
    TL();=0A    }
    else
    {
    m=mF=-1;
    move30();
    }
    IsI=RampUp = false;       
    }
void s=rpaeeni (void)
{
    vfounded=0;
    IsI=RampDown = true;
    memvic[x][y]=0;
    =f(Olaviat==0) Olaviat=2;
    
    if(Olav=at==1 && returning!=1)
        { 
 =20      if((x!=Xd || x!=Xd-1 || x!=Xd+1)&&(y!=Y= || y!=Yd-1 || y!=Yd+1))
         {
=20         Olaviat=4;
          =ramp1=x;
          Yramp1=y;
    =20    }
        } 
    if(lastM=1]==101)
    {
    x--;
    if(l=stM[0]==101)
    x--;
    }
    =f(Olaviat==2)
        {
       =20Xramp=x;
        Yramp=y;
      =20 }
    right_cnt=0; left_cnt=0;
    lcd=clear();
    lcd_gotoxy(0,1);
    sprintf(text," =20 Sar paeeni           Olaviat = %d ",Ol=viat);
    lcd_puts(text);
    change_baud();
=20   printf("page RampDown");
    _buffer();
  =20 IsStartPage = false;
    sprintf(text,"Olaviat ==20%d ",Olaviat);
    Nextion_cmd22("t0.txt=",text);
 =20   // resid be ramp
    #asm ("sei")
  =20 while(UF>80 && UBL<300)//&&check_sarpaeen)
      =20 {
        #asm ("sei")
       =20check_error();
        if (KFL==0)
  =20         {
            go(=50,-250);
            delay_ms(50);
  =20         go(250,250);
          =20 delay_ms(100);
            go(-250,250);=0A            delay_ms(30);
      =20     }
        else if (KFR==0)=0A            {
          =20 go(-250,250);
            delay_ms(50);=0A            go(250,250);
       =20    delay_ms(100);
            go(25=,-250);
            delay_ms(30);
   =20        }
        else
   =20        go(210-error,210+error);    
   =20    if ((tempL2>=temp || tempR2>=temp) && vfounded==3D0)
            {
        =20    go(-90,-90); 
             p=ay_track(lifeform);
            for (i=0;i=cheshmak;i++)
                {LED_ON;=20delay_ms(50); LED_OFF;delay_ms(50);}
          =20     
            vfounded=1;=0A
            AX12(1,AXmin,500);
   =20        delay_ms(1000);
          =20 AX12(1,AXmax,500);
            }
 =20      sprintf(text,"shib=%3d",shib1);
      =20 lcd_gotoxy(12,3);
        lcd_puts(text);
 =20      }
    Tanzim();
    
 =20  if(Olaviat==2)
        {
    =20   x=x-15;
        Xd=x-6;
    =20   Yd=y+5;
        }
      =20    
    if(Olaviat==1)
       =20{                        =20                         =20           
         play_tr=ck(low);
         x=Xramp;
      =20  y=Yramp;
         //Xd=Xramp+5;
 =20       //Yd=Yramp+6;
         Xd==;
         Yd=y; 
         =em[Xramp][Yramp]+=5;
         mem[Xramp-1][Yramp]+=;
         returning=1; 
      =20  }
        
          =0D
    if(Olaviat==4) 
    {
    =20play_track(prgact);
     x+=5;
     Xd==ramp1+5;
     Yd=Yramp1;
    }
   =20sarpaeen=0;
    hasGoneDown = true;
    =asm ("sei")
    /*
    if (Olaviat == =)
        {
        int k ==200;
        int i,j;
         =20                     
  =20     if( xs <= Xramp )  // yani start az =val zamin 
            { 
   =20        go(0,0);
            =or (i = Xramp+3 ; i >= Xramp-6 ; i--)
    =20           {
           =20    for (j = Yramp+1 ; j <= Yramp+4 ; j++)=0A                    {
  =20                 if (mem[i][j] ===200)
                    k++;=0A                    }
  =20             if (k >= 3)
   =20                {
      =20             Xd = i;   
  =20                 Yd = Yramp + =;
                    break; =0D
                    }
 =20              k = 0;  
   =20            }
          =20               
        =20   }
        else if( xs > Xramp ) =20// yani start az akhar zamin 
         =20  {
            go(0,0);
    =20       for (i = Xramp-6 ; i <= Xramp+3 = i++)
                {
   =20            for (j = Yramp+1 ; j <==20Yramp+4 ; j++)
                 =20  {
                    =f (mem[i][j] == 0)
              =20     k++;
                =20   }
                if (k == 3)
                    {=0D
                    Xd = =;   
                    =d = Yramp + 4;
               =20    break; 
                =20   }
                k = =;  
                }
   =20                      
 =20          } 
        }
 =20    */
    DirCheck(); 
    if(M===1)
    {
    memL=-1; 
    TL();=0D
    }   
    else if(M==110)
 =20  {
    memR=-1; 
    TR();
  =20 }
    else 
    {
    memF==1; 
    move30();
    }
    IsInRa=pDown = false;
    }
void clear_memory(void)
=                      
 =20  #asm("cli")
    
    change_baud();
=20   printf("page Clear Memory");
    _buffer();
=20   
    first=1;
    IsStartPage = =alse;
    TimeAgo=0;
    cheshmak =10;
=20   flagt=0;
    number = 0;
    O=aviat=0;  //dar vooroodi sarbalaee va start az paeen ol=viat 3 mishavad va ba in khat dorost mishavad
   =20for (y=0;y<30;y++)
        {
     =20  for (x=0;x<60;x++)
            {=0A            mem[x][y]=0;
      =20     memvic[x][y]=0;
            =
        lcd_clear(); 
        =cd_puts("  clearing  \n");
        lcd_puts(" =20Please wait  \n");
        Nextion_cmd("t0.txt=3D\"Please Wait!\"");
        sprintf(text,"   =20     %d ",20-y);
        lcd_puts(text);=20                  
     =20  Nextion_cmd2("va0.val=",y*5);
        Nextio=_cmd("t1.txt=\"Clearing...\"");
        }    =0D
    xcp=xs;ycp=ys;
    Xramp=0;Yramp=0;=0A    lcd_clear();
    returning=0;
    =Xmin=780;
    AXmax=516;
    Xd=40;Yd=-10=
    lcd_clear();
    lcd_puts(" memory clear=d ");
    Nextion_cmd("t0.val=\"Memory Cleared!\"");
=20   delay_ms(500);
    lcd_clear();
    if=20(go30==-1)
        {
        =laviat=0;
        Tedad = 30;
    =20   temp=35;
        turn=37;
   =20    volume=25;
        go30=58;
 =20      lastM[0]=-1;
        lastM[1]==1;
        set_volume(volume);
      =20 }
    #asm("sei")
    }
void memory(v=id)
{
    int page=1;
    int b,c;
=20   char left,right,up,down;
    lcd_clear();
 =20  IsStartPage = false;
    while (1)
  =20     {
        b = read_adc(6);
=20       c = read_adc(5);

      =20 if (b<100)          left=1;
     =20  else if (b>=100)    left=0;
      =20 if (b>900)          right=1;
    =20   else if (b<=900)    right=0;

   =20    if (c<50)          down=1;
  =20     else if (c>=50)    down=0;
    =20   if (c>980)          up=1;
   =20    else if (c<=980)    up=0;


 =20      if (right==1)
          =20 {
            delay_ms(200);
   =20        page++; 
           =20first=0;
            if (page>9) page==;
            lcd_clear();
     =20      }
        if (left==1)
=20           {
           =20delay_ms(200);
            page--; 
 =20          first=0;
         =20  if (page<1) page=9;
            =cd_clear();
            }
     =20  else if (page==5)       // turn
  =20         {
             =20#asm("sei")
            if(first==0)
=20           {
           =20change_baud();
            printf("page Me=ory_2");
            _buffer(); 
  =20          }
            =irst=1;
            sprintf(text,"   T=rn=%4d  ",turn);
            lcd_gotoxy(=,0);
            lcd_puts(text);
   =20        sprintf(text,"l=%d R=%d U=%d B=%d =20",left,right,up,down);
            lcd_gotox=(0,1);
            lcd_puts(text);
  =20         sprintf(text,"B=%3d   C=% d  "=b,c);
            lcd_gotoxy(0,2);
  =20         lcd_puts(text);
         =20  Nextion_cmd("t0.txt=\"Turn = \"");
       =20    Nextion_cmd2("n0.val=",turn);
        =20     
            if (down===)
                {
     =20          turn-=1;
         =20      if (turn<30)
            =20       turn=30;
            =20   delay_ms(100);
               =20}
            else if (up==1)
 =20              {
        =20       turn+=1;
            =20   if (turn>200)
               =20    turn=200;
               =20delay_ms(100);
                }
=20           else if (POK==0)
    =20           {
           =20    while(POK==0);
             =20  Nextion_cmd("vis p0,1");
            =20   Nextion_cmd22("t1.txt=","Testing...");
      =20         lcd_putsf(" Testing ");
     =20          delay_ms(200);
        =20       lcd_putsf(".");
           =20    delay_ms(200);
              =20 lcd_putsf(".");
                d=lay_ms(200);
                lcd_putsf=".");
                delay_ms(200);=0A                TCNT=0;TCNT=0;
 =20              go(-255,+255);
    =20           while(TCNT<turn)
      =20             {
         =20          if (TCNT>turn*0.8)
      =20                 {
     =20                  go(-200,200);
=20                       }=0A                    }
  =20             go(255,-255);
     =20          delay_ms(5);
         =20      go(0,0);
              =20 lcd_clear();
                Next=on_cmd("vis p0,0");
                =extion_cmd22("t1.txt=","");
              =20 }
            }
       =20else if (page==4)      // move 30
    =20       {
              #as=("sei")
            if(first==0)
  =20         {
            cha=ge_baud();
            printf("page Memory_2=);
            _buffer(); 
    =20        }
            first==;
            sprintf(text,"   move30 =0cm        %4d ",go30);
          =20 lcd_gotoxy(0,0);
            lcd_puts(tex=);
            Nextion_cmd22("t0.txt=","Move=2030cm = ");
            Nextion_cmd2("n=.val=",go30);
            if (up==1)=0A                {
      =20         go30+=1;
          =20     delay_ms(75);
             =20  if (go30>500)
                =20   go30=500;
                =
            else if (down==1)
 =20              {
        =20       go30-=1;
            =20   delay_ms(75);
               =20if (go30<30)
                  =20 go30=30;
                }
=20           else if (POK==0)
    =20           {
           =20    while (POK==0);
            =20   Nextion_cmd("vis p0,1");
           =20    Nextion_cmd22("t1.txt=","Testing...");
     =20          lcd_clear();
         =20      lcd_putsf(" Testing ");
        =20       delay_ms(200);
           =20    lcd_putsf(".");
              =20 delay_ms(200);
                lc=_putsf(".");
                delay_ms(=00);
                lcd_putsf(".");=0A                delay_ms(200);
  =20             move30();
       =20        go(0,0);
            =20   lcd_clear(); 
               =20Nextion_cmd("vis p0,0");
              =20 Nextion_cmd22("t1.txt=","");
            =20   }

            }
   =20    else if (page==3)       // mlx
 =20          {
            =f(first==0)
            {
    =20       change_baud();
           =20printf("page Memory_4");
            _buff=r(); 
             }
      =20      first=1;
            lcd=gotoxy(9,0);
            sprintf(text,"%2d",te=pF);
            lcd_puts(text);
   =20        lcd_gotoxy(0,0);
         =20  sprintf(text,"%2d",tempL1);
            =cd_puts(text);
            lcd_gotoxy(0,1);=0A            sprintf(text,"%2d",tempL2);
  =20         lcd_puts(text);
         =20  lcd_gotoxy(0,2);
            sprintf(t=xt,"%2d",tempL3);
            lcd_puts(text);=0A            lcd_gotoxy(18,0);
     =20      sprintf(text,"%2d",tempR1);
        =20   lcd_puts(text);
            lcd_got=xy(18,1);
            sprintf(text,"%2d",tempR=);
            lcd_puts(text);
    =20       lcd_gotoxy(18,2);
          =20 sprintf(text,"%2d",tempR3);
            l=d_puts(text);
            sprintf(text,"Temp==3d   ",temp);
            lcd_gotoxy(7,3=;
            lcd_puts(text);
    =20       Nextion_cmd2("n0.val=",tempL1);
     =20      Nextion_cmd2("n1.val=",tempL2);
      =20     Nextion_cmd2("n2.val=",tempL3);
       =20    Nextion_cmd2("n3.val=",tempR1);
        =20   Nextion_cmd2("n4.val=",tempR2);
         =20  Nextion_cmd2("n5.val=",tempR3);
          =20 Nextion_cmd2("n6.val=",temp);
           =20if (tempL1>=temp || tempR1>=temp || tempL2>=temp || t=mpR2>=temp || tempL3>=temp || tempR3>=temp )
   =20            LED_ON;
        =20   else
                LED_OFF=
            if (up==1)
    =20           {
           =20    temp+=1;
               =20delay_ms(100);
                if =temp>70)
                    g=30=70;
                }
  =20         else if (down==1)
     =20          {
            =20   temp-=1;
                =elay_ms(100);
                if (go=0<10)
                    go30=3D10;
                }
   =20        }
        else if (page==3D2)      // calibration_robot
         =20  {
            #asm("sei")
   =20        if(first==0)
         =20  {
            change_baud();
  =20         printf("page Memory_3");
     =20      _buffer(); 
            =20}
            first=1;
     =20      lcd_gotoxy(0,0);
           =20lcd_puts(" calibration robot ");
          =20 sprintf(text,"N=%3d ",djN);
           =20lcd_gotoxy(7,1);
            lcd_puts(text);=0D
            sprintf(text,"W=%3d  S=%3d=20 E=%3d",djW,djS,djE);
            lcd_go=oxy(0,2);
            lcd_puts(text);
 =20          if (POK==0)
       =20        calibration_robot();
        =20       
            switch(UDR=)
             {
        =20    case 'C':
             calib=ation_robot();
             break;
  =20          default:
          =20  break;
             }
   =20         UDR0='';
          =20 }
        else if (page==1)     =/ clear memory
            { 
  =20         if(first==0)
        =20   {
            change_baud();
 =20          printf("page Memory_1");
    =20       _buffer(); 
           =20 }
            first=1;
    =20       lcd_gotoxy(0,0);
          =20 lcd_puts(" clear memory ");
           =20if (POK==0)
                {=0A                clear_memory();
  =20             first=0;
      =20         }
             =witch(UDR0)
             {
    =20        case 'D':
           =20 clear_memory();
             first=0;=0D
             break; 
      =20      default:
             br=ak;
             }
       =20     UDR0='';
            }
=20       else if (page==6)     // Cheshma= Time
            {
       =20    if(first==0)
            {=0A            change_baud();
      =20     printf("page Memory_2");
         =20  _buffer(); 
             }
 =20          first=1;
         =20  sprintf(text," Cheshmak Time         %d  =,cheshmak);
            lcd_gotoxy(0,0);
=20           lcd_puts(text);
       =20    Nextion_cmd22("t0.txt=","Blink Loop = ");
  =20         Nextion_cmd2("n0.val=",cheshmak);
  =20          if (up==1)
       =20        {
              =20 if(cheshmak ==150)
              =20    cheshmak =10;
             =20  else cheshmak ++;
              =20 }
            if (down==1)
 =20              {
        =20       if(cheshmak == 10)
       =20            cheshmak =10;
     =20          else
           =20        cheshmak--;
           =20    }
            if (POK==0)=0A                {
      =20         while (POK==0);
       =20        Nextion_cmd("vis p0,1");
      =20         Nextion_cmd22("t1.txt=","Testing...");
=20               lcd_clear();
    =20           lcd_putsf(" Testing ");
   =20            delay_ms(200);
      =20         lcd_putsf(".");
         =20      delay_ms(200);
            =20   lcd_putsf(".");
               =20delay_ms(200);
                lcd_p=tsf(".");
                delay_ms(200=;
                for (i=0;i<chesh=ak;i++)
                {LED_ON; del=y_ms(50); LED_OFF;delay_ms(50);}
            =20   lcd_clear();
                =extion_cmd("vis p0,0");
               =20Nextion_cmd22("t1.txt=","");
             =20  }


            }

=20       
        else if (page===)  //  AX
            {
   =20        sleep();
            =f(first==0)
            {
    =20       change_baud();
           =20printf("page Memory_2");
            _buff=r(); 
             }
      =20     first=1;
            lcd_go=oxy(0,1);
            sprintf(text,"AX12 min=20pos=%4d  ",AXmin);
            lcd_put=(text);
            Nextion_cmd22("t0.txt=",=AX12 Min Degree = ");
            Ne=tion_cmd2("n0.val=",AXmin);
            AX12=1,AXmin,200);
             if (POK==0)=0D
                { 
    =20           while (POK==0);
     =20          Nextion_cmd("vis p0,1");
    =20           Nextion_cmd22("t1.txt=","Testing...");=0D
                lcd_clear();
  =20             lcd_putsf(" Testing ");
 =20              delay_ms(200);
    =20           lcd_putsf(".");
       =20        delay_ms(200);
          =20     lcd_putsf(".");
             =20  delay_ms(200);
                =cd_putsf(".");
                delay_m=(200);
                AX12(1,AXmin,50=);
                delay_ms(1000);
=20               AX12(1,AXmax,500);
  =20             delay_ms(1000);
     =20          lcd_clear();
         =20      Nextion_cmd("vis p0,0");
        =20       Nextion_cmd22("t1.txt=","");
      =20         }
            if =up==1)
                {
  =20             AXmin++;
       =20        delay_ms(50);
          =20     }
            if (down===)
                {
     =20          AXmin--;
          =20     delay_ms(50);
             =20  }
            }
      =20 else if (page==7)  //  AX
        =20   {
            LED_OFF;
   =20        sleep();
            =f(first==0)
            {
    =20       change_baud();
           =20printf("page Memory_2");
            _buff=r(); 
             }
      =20     first=1;
            lcd_go=oxy(0,1);
            sprintf(text,"AX12 Max=20pos=%4d  ",AXmax);
            lcd_put=(text);
            Nextion_cmd22("t0.txt=",=AX12 Max Degree = ");
            Ne=tion_cmd2("n0.val=",AXmax);
            AX12=1,AXmax,200);
             if (POK==0)=0D
                {
     =20          while (POK==0);
      =20         Nextion_cmd("vis p0,1");
     =20          Nextion_cmd22("t1.txt=","Testing...");=0A                lcd_clear();
   =20            lcd_putsf(" Testing ");
  =20             delay_ms(200);
     =20          lcd_putsf(".");
        =20       delay_ms(200);
           =20    lcd_putsf(".");
              =20 delay_ms(200);
                lc=_putsf(".");
                delay_ms(=00);
                AX12(1,AXmin,500)=
                delay_ms(1000);
=20               AX12(1,AXmax,500);
  =20             delay_ms(1000);
     =20          lcd_clear();
         =20      Nextion_cmd("vis p0,0");
        =20       Nextion_cmd22("t1.txt=","");
      =20         }
            if =up==1)
                {
  =20             AXmax++;
       =20        delay_ms(50);
          =20     }
            if (down===)
                {
     =20          AXmax--;
          =20     delay_ms(50);
             =20  }
            }
//     =20      else if (page==10)  //  LED B
//=20           {
//
//        =20   sleep();
//            if (POK==3D0)
//             LED_OFF;
//   =20        lcd_gotoxy(0,1);
//         =20  sprintf(text,"    RGB LEDs  ");
//     =20      lcd_puts(text);
//
//        =20       LED_B_ON;
//            =
//            else if (page==11)  =/  LED   R
//            {
// =20           if (POK==0)
//     =20       LED_OFF;
//            =cd_gotoxy(0,1);
//            sprintf(text," =20  RGB LEDs   ");
//            l=d_puts(text);
//
//                =ED_R_ON;
//            }
//     =20      else if (page==12)  //  LED G
//=20           {
//           =20if (POK==0)
//             LED_OFF;=0A//            lcd_gotoxy(0,1);
//    =20       sprintf(text,"    RGB LEDs  ");
/=            lcd_puts(text);
//
//   =20            LED_G_ON;
//       =20    }
             else if (pa=e==9)  //  Tedad
            {
=20           //#asm("sei")
       =20    if(first==0)
            {=0A            change_baud();
      =20     printf("page Memory_2");
         =20  _buffer(); 
             }
 =20           first=1;
        =20   LED_OFF;
            sprintf(text,"=20 MinTedad  %2d                  =20             tedad = %2d ",Tedad,number=;
            lcd_gotoxy(0,0);
    =20       lcd_puts(text);
           =20Nextion_cmd("t0.txt=\"Min Search Count = \"");
   =20        Nextion_cmd2("n0.val=",Tedad);
    =20       if (up==1)
          =20     {
                Ted=d+=1;
                delay_ms(75);=0A                if (Tedad>50)
  =20                 Tedad=0;
  =20             }
         =20  else if (down==1)
            =20   {
                Tedad-==;
                delay_ms(75);
 =20              if (Tedad<0)
    =20               Tedad=50;
    =20           }
           =20    }

            }
  =20     }
void search (void)
{
    // =Way
    if (M==101)
     {
   =20  if(memB<memF) TB();
      else  
  =20    move30();
     }
    else if =M==110)
          {
       =20    if(memB<memR) TB();
            =lse      
             TR();
=20         }
    else if (M==11)
=20          {
           if(=emB<memL) TB();
            else    =20  
            TL();
     =20     }
    else if(M==111)
    =20       {   
            =em[x][y]+=5;
            TB();
   =20        }
    // 2Ways
    el=e if (M==1)
            {
   =20        if (memL<memF)
         =20    TL();
            else if (m=mL>memF)
                move30();
=20           else
          =20     {
                 =20  if(memF+memL==0)
              =20     {
                 =20    if(DL>DF)
                =20         TL();
            =20        else if(DL<DF)
         =20                move30();
    =20                 else 
   =20                      TL(); =0D
                    }
 =20                  
     =20              else 
      =20             {
         =20              if(DL>DF)
      =20                   move30(); 
=20                    else if(DL<=F)
                       =20   TL();
                  =20  else 
                  =20     move30(); 
              =20      }
                =20       
                =
            }
    else if (M=3D=10)
            {
      =20     if (memL<memR)
            =20      TL();
            else i= (memL>memR)
                   =R();
            else
       =20        {
              =20     if(memR+memL==0)
           =20        {
              =20       if(DL>DR)
             =20            TL();
         =20           else if(DL<DR)
      =20                   TR();
  =20                   else 
 =20                        T=(); 
                    }=0A                    
   =20                else 
    =20               {
       =20                if(DL>DR)
    =20                     TR(); =0A                     else if(=L<DR)
                      =20    TL();
                 =20   else 
                 =20      TR(); 
              =20      }
                =
            }
    else if (M=3D=100)
            {
      =20     if (memF<memR)
            =20      move30();
            else=20if (memF>memR)
                 =20 TR();
            else
     =20          {  
          =20      if(memF+memR==0)
          =20         {
             =20        if(DR>DF)
            =20             TR();
        =20            else if(DR<DF)
     =20                    move30();
=20                     else =0A                         =20TR(); 
                    =
                    
 =20                  else 
  =20                 {
     =20                  if(DR>DF)
  =20                       move=0(); 
                     =lse if(DR<DF)
                  =20        TR();
             =20       else 
             =20         move30(); 
          =20          }
            =20   }
            }
    //=202<Ways
    else if (M==0)
       =20    {
            if (memF<memR =& memF<memL)
            {
    =20         switch(dir)
          =20           {
           =20           case 4 :
        =20              TB();   //we have to =heck
                      =20break;
                     =20 default:
                   =20   move30();
                 =20    }
            }
    =20       else if (memR<memF && memR<memL)
  =20           TR();
          =20 else if (memL<memR && memL<memF)// why we have if in=20Left and Front
            {
  =20             switch(dir)
      =20               {
       =20               case 1 :
    =20                  TR();//we have =o check this line
                =20      break;
               =20       case 2 :
            =20          move30();// we have to check this=20line
                     =20 break;
                    =20  default:
                  =20    TL();
                 =20    }
            }
    =20       ///////////////////////////////////      =20
            else if (memL==memF &= memF!=memR)
                  =20 {
                    if(=emF+memL==0)     //what a beatifull code!!!
  =20                  move30();
  =20                 else if (DL>DF)=0A                         =20TL();
                    el=e
                     TL();=20//move30(); 
                  =20 }
            else if (memR==memF =& memF!=memL)
                  =20 {
                    if(=emF+memR==0)
                  =20  move30();
                  =20 else if (DR>DF)
               =20          TR();           
=20                   else
  =20                  TR(); //move30();=20       
                =20   }
            else if (memR===emL && memL!=memF)
               =20    {
                  =20 if(memR+memL==0)
               =20     TL();
                =20   else if (DR>DL)
             =20            TR();        
 =20                  else
   =20                  TL();     =20     
                  =20 }
            else
      =20         {
             =20  if(memL+memF+memR==0)
            =20       {
//               =20    if (DF<DR && DF<DL)
//          =20             move30();
//      =20             else if (DR<DF && DR<DL)=0A//                        =R();
//                    els= if (DL<DR && DL<DF)
//             =20          TL();
           =20        switch(dir)
           =20          {
            =20          case 1 :
         =20             move30();
       =20               break;
      =20                case 2 :
   =20                   TL();
  =20                    break;
 =20                     case 3 =
                       =L();
                      =20break;
                     =20 case 4 :
                  =20    move30();
                =20      break;
               =20       default:
             =20         move30();
           =20          }
            =20       }
               =20else
                    {=0A                    if (DF<DR =& DF<DL)
                    =ove30();
                    e=se if (DR<DF && DR<DL)
             =20      TR();
               =20    else if (DL<DR && DL<DF)
        =20           TL();
          =20         //////////////////////////////////
  =20                 else if((DF ===20DR) && ( DF > DL))
             =20            TL();
         =20          else if((DF == DL) && ( DF = DR))
                     =20    TR();
                 =20  else if((DL == DR) && ( DL > DF))
   =20                      move30(=;
                    ////////=/////////////////////////                 =0D
                    else
=20                    move30();
=20                   }
   =20            }

        =20   }
    }
void lcd(void)
{     =20
    calculate();
    if(!IsStartPage)
 =20  {
    Nextion_page("Start");
    IsStartP=ge=true;
    } 
    Nextion_cmd2("n0.val=",=);
    Nextion_cmd2("n1.val=",y);
    Nextion_c=d2("n2.val=",xcp);
    Nextion_cmd2("n3.val=",ycp);   =0D
    Nextion_cmd2("n4.val=",Xd);
    Nextion_cmd=("n5.val=",Yd);
    Nextion_cmd2("n6.val=",mem[x][y]);
=20   Nextion_cmd2("n7.val=",dir); 
    Nextion_cmd2(=dir.val=",dir); 
    
    sprintf(text,"(%2d,=d)=%d cp=(%2d,%d)",x,y,mem[x][y],xcp,ycp);
    lcd_gotox=(0,0);
    lcd_puts(text);
    sprintf(text,"mem ==%d F=%d B=%d R=%d",memL,memF,memB,memR);
    lc=_gotoxy(0,1);
    lcd_puts(text);
    sprintf(tex=,"FL=%3d F=%3d FR=%3d",UFL,UF,UFR);
    sprintf(text="dest(%2d,%2d) dir=%d  ",Xd,Yd,dir);
    lcd_gotoxy(0,=);
    lcd_puts(text);
    //sprintf(text,"BL=%=d Dir=%d BR=%3d",UBL,dir,UBR);
    sprintf(text,"Time==3d    shib=%3d",TimeAgo,shib1);
    lcd_gotoxy(0,3);=0D
    lcd_puts(text);
    }
void forceHardRe=et()
{
  #asm("cli") // disable interrupts
  W=TCR=0x18;
  WDTCR=0x08;
  #asm("wdr")
  whil=(1); // wait for watchdog to reset processor
}
/*bo=l CheckedRooms(void)
{
  int i,j,Count=0,RoomsCount=0=
  float Result=0;
  
  RoomsCount = a=s(x-xs) * abs(y-ys);
  
  for(j=ys;j<=y;j++) =0A   for(i=xs;i<=x;i++)
     Count+=mem[i][j];=0A   
   Result = Count/RoomsCount;
   if=Result<0.8) return false; 
   else return true; 
=*/
void DropVic(void)
{
  
  if(MLX_R_Detects=
  {
   #asm ("sei")
   play_track(prgact)=
             while (UFR>50)
   =20         {
             =o(-200,0);
             delay_ms(300);
=20            go(0,-200);
       =20     delay_ms(300);
             =o(200,200);
             delay_ms(300);
=20            }
     go(0,0);
 =20   #asm ("cli")
  }
  else  victimCorection=); 
  
  AX12(1,AXmin,500);
  delay_ms(1000);=0A  AX12(1,AXmax,500);
  memvic[x][y]++;
  delay_ms(1=00);
}
void DirCheck(void)
{
 int MinDeg=400;=0A  
 if ( abs(dj-djN) < MinDeg )    {dir=1;=20MinDeg=abs(dj-djN);}
 if ( abs(dj-djE) < MinDeg )  =20 {dir=2; MinDeg=abs(dj-djE);}
 if ( abs(dj-djS) < =inDeg )    {dir=3; MinDeg=abs(dj-djS);}
 if ( ab=(dj-djW) < MinDeg )    {dir=4;}
 //if(hasGoneDown)di==2;
 //if(hasGoneUp)dir=4;

}
void Finished(voi=)
{
    //Khodaya Shokr!!!   :-)

  =20 play_track(complete);
    define_char(char2,2);
  =20 define_char(char3,3);
    define_char(char4,4);
  =20 define_char(char5,5);
    lcd_clear();
    l=d_puts("     Finished    ");
     lcd_goto=y(9,2);
    lcd_putchar(2);
    lcd_gotoxy(10,2);=0D
    lcd_putchar(3);
    Nextion_page("Finish");=0A    while(1)
        {
      =20  lcd_gotoxy(3,0);
         lcd_putchar(5);=0A         lcd_gotoxy(14,0);
        =20lcd_putchar(5);
         LED_R_ON; 
   =20     delay_ms(120);
         LED_OFF;=0A         lcd_gotoxy(3,0);
        =20lcd_putchar(4);
         lcd_gotoxy(14,0);
 =20       lcd_putchar(4);
         LED_=_ON;
         LED_B_ON; 
       =20 delay_ms(120);
         LED_OFF;
   =20     lcd_gotoxy(3,0);
         lcd_putch=r(5);
         lcd_gotoxy(14,0);
     =20   lcd_putchar(5);
         LED_B_ON; 
=20        delay_ms(120);
         LE=_OFF;
         lcd_gotoxy(3,0);
     =20   lcd_putchar(4);
         lcd_gotoxy(14,0)=
         lcd_putchar(4);
       =20 LED_B_ON;
         LED_G_ON;
     =20   delay_ms(120);
         LED_OFF;
 =20       lcd_gotoxy(3,0);
         lcd=putchar(5);
         lcd_gotoxy(14,0);
   =20     lcd_putchar(5);
         LED_G_ON;=0A         delay_ms(120);
         =ED_OFF;
         lcd_gotoxy(3,0);
     =20   lcd_putchar(4);
         lcd_gotoxy(14,0)=
         lcd_putchar(4);
       =20 LED_R_ON;
         LED_G_ON;
     =20   delay_ms(120);
         LED_OFF;
 =20      }
 }
=
