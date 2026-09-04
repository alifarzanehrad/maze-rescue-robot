//   *******       USF maze 2020     *******     // 
#define XS 20
#define YS 20

#include <mega128.h>
//#asm
//    .equ __i2c_port=0x03 ;PORTE
//   .equ __sda_bit=6
//   .equ __scl_bit=5
//#endasm
#include <i2c.h>
#include <alcd.h>
#include <delay.h>                                 
#include <stdio.h>
#include <stdlib.h>


#define SFL  PINC.7

#define LED  PORTE.6

#define SBL   PING.0
#define SBR   PING.1
#define MR1   PORTB.4
#define MR2   PORTB.5
#define ML1   PORTB.6
#define ML2   PORTB.7

#define DN       PINB.2  
#define OK       PINA.1  
#define SFR      PINC.6  
#define UP       PINB.1  

#define SDFL      PINF.0  
#define SDFR      PINF.1  
#define SDB       PINF.2  
#define BATTERY   PINF.3  

#define ENCR      PING/32

//#define TCNTL  TL*256+TCNT3L
#define TCNTR  TR*3+TCNT0
#define Treset {TR=0;TCNT0=0;TL=0;TCNT3L=0;TCNT3H=0;}

#define VSDFL vsens(0)
#define VSDFR vsens(1)
#define PTC   vsens(2)
#define VSDB  vsens(3)

#define MLXFR MLX(1)
#define MLXFL MLX(2)
#define MLXF  MLX(3)
#define MLXBR MLX(4)
#define MLXBL MLX(5)



bit masdoom_enable=1;
bit ramp;
char jahat=1;
char x,y;
char ultra_number=1;
eeprom int khune_min,masdoom_min;
eeprom char xsil,ysil;
eeprom int m30,m90,mL90,m180,Xd,Yd,Xshib,Yshib;
eeprom char finish_enable;
eeprom float black,silver;
eeprom int ekhtelaf1,ekhtelaf2,ekhtelaf3,ekhtelaf4,m45;
eeprom int dama_high,dama_low;
eeprom char detect_error;
eeprom int first_check;
eeprom char vic[40][40],H[40][40];
char lcd[40];
int i;
char mode_harekat;
char P;
int FL,FF,FR,BR,BL;
int DF,DL,DR,HF,HL,HR;
int global_speedL,global_speedR;
unsigned char tedad_khune=0;
unsigned char tedad_masdoom=0;
int z,shib,shib2; // zaviveye robot
char k,j;
int TL,TR;
int interupt_enable=0;


void eslah (char accuracy);
void eslahaghab (void);
void mostaghim(void);
void eslahjolo (void);
void mohasebat (void);
void motor (signed int speedL,signed int speedR,int count);
float vsens (char num);
void masdoom (void);

interrupt [TIM0_COMP] void timer0_comp_isr(void)   // ENC R
    {
    TR++;
    TCNT0=0;
    }

interrupt [TIM2_OVF] void ultra(void)      // ULTRA TIMMER
    {    
    static int refresh;
    int TIME;
    refresh++;
    if(refresh>1000)
        refresh=1000;
    if (refresh>240 && interupt_enable==0)
        {    
        refresh=0;

        if (ultra_number==1)   //FL
            {
            DDRC.2=1;
            PORTC.2=1;
            delay_us(20);
            PORTC.2=0;
            DDRC.2=0;
            TCNT2=0;TIME=0;
            while (PINC.2==0 && TIME<100)
                {      
                if (TCNT2>200)
                    {
                    TIME++;
                    TCNT2=0;
                    }
                }
            TCNT2=0;TIME=0;
            while (PINC.2==1 && TIME<100)
                {      
                if (TCNT2>200)
                    {
                    TIME++;
                    TCNT2=0;
                    }
                }
            FL= (TIME*200 + TCNT2) /5.8 ; 
            //if (FL>2000)     FL=0;
            }                          
            
        else if (ultra_number==2) //FF
            {
            DDRD.1=1;
            PORTD.1=1;
            delay_us(20);
            PORTD.1=0;
            DDRD.1=0;
            TCNT2=0;TIME=0;
            while (PIND.1==0 && TIME<100)
                {      
                if (TCNT2>200)
                    {
                    TIME++;
                    TCNT2=0;
                    }
                }
            TCNT2=0;TIME=0;
            while (PIND.1==1 && TIME<100)
                {      
                if (TCNT2>200)
                    {
                    TIME++;
                    TCNT2=0;
                    }
                }
            FF= (TIME*200 + TCNT2) /5.8 ; 
            }

        else if (ultra_number==3) //FR
            {
            DDRD.4=1;
            PORTD.4=1;
            delay_us(20);
            PORTD.4=0;
            DDRD.4=0;
            TCNT2=0;TIME=0;
            while (PIND.4==0 && TIME<100)
                {      
                if (TCNT2>200)
                    {
                    TIME++;
                    TCNT2=0;
                    }
                }
            TCNT2=0;TIME=0;
            while (PIND.4==1 && TIME<100)
                {      
                if (TCNT2>200)
                    {
                    TIME++;
                    TCNT2=0;
                    }
                }
            FR= (TIME*200 + TCNT2) /5.8 ;
            
            //if (FR>2000)     FR=0;
            }             
            

        if (++ultra_number>3)    // mlx
            {
            ultra_number=1;
            }
        }
    
//    sprintf(lcd,"ref=%4d ie=%d %d ",refresh,interupt_enable,ultra_number);
//    lcd_gotoxy(0,0);
//    lcd_puts(lcd);
//
//    sprintf(lcd,"fl=%4d ff=%d %d ",FL,FF,FR);
//    lcd_gotoxy(0,1);
//    lcd_puts(lcd);

    }

interrupt [TIM3_OVF] void timer3_ovf_isr(void)    // ENC L
    {
    TL++; 
    TCNT3H=0;TCNT3L=0;
    }

unsigned int read_adc(unsigned char adc_input)
    {
    ADMUX=adc_input | (0x00 & 0xff);
    delay_us(10);
    ADCSRA|=0x40;
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;
    return ADCW;
    }



    
 
void go (signed int speedL,signed int speedR,int count)
    {
    if (speedL>255)     speedL=255;
    if (speedL<-255)    speedL=-255;
    if (speedR>255)     speedR=255;
    if (speedR<-255)    speedR=-255;
    speedL=-speedL;
    speedR=-speedR;
    global_speedL=speedL;
    global_speedR=speedR;
//    sprintf(lcd,"move(%4d,%4d)  ",speedL,speedR);
//    lcd_gotoxy(0,3);
//    lcd_puts(lcd);

    if (speedR>0) 
        {PORTB.4=1;OCR1A=255-speedR;}      
    else if (speedR<0)
        {PORTB.4=0;OCR1A=-speedR;}
        
    else
        {PORTB.4=0;OCR1A=0;}
    
    if (speedL>0) 
        {PORTB.7=1;OCR1B=255-speedL;}
    else if (speedL<0)
        {PORTB.7=0;OCR1B=-speedL;}
    else
        {PORTB.7=0;OCR1B=0;}
    
    if (count>0)
        {
        Treset;
        while(TCNTR<count) ;          

        PORTB.7=0;OCR1A=0;PORTB.4=0;OCR1B=0;
        }
    } 
     
void sensor_checkup (void)
    {
    char page=1;
    lcd_clear();

    while (1)
        {     
        if (DN==0)
            {
            while (DN==0);
            page++;
            if (page>4) page=1;
            lcd_clear();
            }
        if (UP==0)
            {
            while (UP==0);
            page--;
            if (page<1) page=4;
            lcd_clear();
            }
        if (page==1)      // ultra()   
            { 
            interupt_enable=0;
            lcd_gotoxy(0,0);
            lcd_puts("ultrasonic");

            sprintf(lcd,"%4d  %4d  %4d",FL,FF,FR);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);
            }
        else if (page==4)      //  SILVER
            { 
            interupt_enable=1;
            sprintf(lcd,"SDf: %1.1f %1.1f %1.1f ",VSDFL,PTC,VSDFR);
            lcd_gotoxy(0,0);
            lcd_puts(lcd);
            
            sprintf(lcd,"    SDB=%1.1f   ",VSDB);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);

            sprintf(lcd,"  SILVER=%1.1f   ",silver);
            lcd_gotoxy(0,2);
            lcd_puts(lcd);

            sprintf(lcd,"  Black=%1.1f   ",black);
            lcd_gotoxy(0,3);
            lcd_puts(lcd);

            if (DN==0) 
                {
                delay_ms(100); 
                silver-=0.1;    
                }
            if (UP==0) 
                {
                delay_ms(100); 
                silver+=0.1;    
                }
            }
        else if (page==5)      // MLX 
            {
            masdoom_enable=0;
            lcd_gotoxy(0,0);
            lcd_puts("Temp:");
//            sprintf(lcd,"%3d    high=%2d   %3d",MLXFL,dama_high,MLXFR);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);
            
//            sprintf(lcd,"%3d    low=%2d    %3d",MLXBL,dama_low,MLXBR);
            lcd_gotoxy(0,2);
            lcd_puts(lcd); 
            
            delay_ms(100);
            while (DN==0)
                { 
                dama_low--;
                delay_ms(80);    
                }
            while (UP==0)
                { 
                dama_low++;
                delay_ms(80);    
                }
            while (SFL==0)
                { 
                dama_high--;
                delay_ms(80);    
                }
            while (SFR==0)
                { 
                dama_high++;
                delay_ms(80);    
                }
            }
        else if (page==2)      //  ENC
            {
            interupt_enable=0;               
//            sprintf(lcd,"ENCL=%d=%3d TL=%d %d ",ENCL,TCNTL,TL,TCNT3L);
//            lcd_gotoxy(0,0);
//            lcd_puts(lcd);

            sprintf(lcd,"ENCR=%d=%3d  ",ENCR,TCNTR);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);
            if (OK==0) 
                {
                while (OK==0); 
                Treset;
                }
            }
        else if (page==3)      //  SWITCH
            {               
            sprintf(lcd,"SFL=%d   SFR=%d ",SFL,SFR);
            lcd_gotoxy(0,0);
            lcd_puts(lcd);

            sprintf(lcd,"SBL=%d   SBR=%d ",SBL,SBR);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);

//            sprintf(lcd,"wall sen=%d ",wall_sens);
//            lcd_gotoxy(0,2);
//            lcd_puts(lcd);
            }
        }
    }

void setup (void)
    {
    char page=1;
    lcd_clear();
    while (1)
        {
        if (UP==0)
            {
            while (UP==0);
            page++;
            if (page>4) page=1;
            lcd_clear();
            }
        if (DN==0)
            {
            while (DN==0);
            page--;
            if (page<1) page=4;
            lcd_clear();
            }
        else if (page==1)      //   M30
            { 
            sprintf(lcd,"30 sant=%3d ",m30);
            lcd_gotoxy(0,0);
            lcd_puts(lcd);
            lcd_gotoxy(0,1);
            lcd_puts("pres SFR -> test");

            if (SFR==0) 
                {
                delay_ms(100); 
                m30-=5;    
                }
            if (SFL==0) 
                {
                delay_ms(100); 
                m30+=5;    
                }
            if (OK==0) 
                { 
                while (OK==0);
                delay_ms(200);
                mostaghim();    
                go(0,0,0);
                }
            }
        else if (page==2)      //  M90
            { 
            sprintf(lcd,"90 daraje R=%3d ",m90);
            lcd_gotoxy(0,0);
            lcd_puts(lcd);
            lcd_gotoxy(0,1);
            lcd_puts("pres SFR -> test");

            if (SFR==0) 
                {
                delay_ms(100); 
                m90-=5;    
                }
            if (SFL==0) 
                {
                delay_ms(100); 
                m90+=5;    
                }
            if (OK==0) 
                { 
                while (OK==0);
                delay_ms(200);
                Treset;
                while (TCNTR<m90)
                    {
                    if (TCNTR<m90*0.2 || TCNTR>m90*0.8)
                        go(100,-100,0);
                    else 
                        go(255,-255,0);
                    }    
                go(0,0,0);  
            sprintf(lcd,"TCNTR=%d < %3d ",TCNTR,m90);
            lcd_gotoxy(0,0);
            lcd_puts(lcd); 
            delay_ms(1000);
                
                }
            }
        else if (page==3)      //  ML90
            { 
            sprintf(lcd,"90 daraje L=%3d ",mL90);
            lcd_gotoxy(0,0);
            lcd_puts(lcd);
            lcd_gotoxy(0,1);
            lcd_puts("pres SFR -> test");

            if (SFR==0) 
                {
                delay_ms(100); 
                mL90-=5;    
                }
            if (SFL==0) 
                {
                delay_ms(100); 
                mL90+=5;    
                }
            if (OK==0) 
                { 
                while (OK==0);
                delay_ms(200);
                Treset;
                while (TCNTR<mL90)
                    {
                    if (TCNTR<mL90*0.2 || TCNTR>mL90*0.8)
                        go(-100,100,0);
                    else 
                        go(-255,255,0);
                    }    
                go(0,0,0);  
            sprintf(lcd,"TCNTR=%d < %3d ",TCNTR,mL90);
            lcd_gotoxy(0,0);
            lcd_puts(lcd); 
            delay_ms(1000);
                
                }
            }
        else if (page==4)      // M180 
            { 
            interupt_enable=1;
            sprintf(lcd,"180 daraje=%3d ",m180);
            lcd_gotoxy(0,0);
            lcd_puts(lcd);
            lcd_gotoxy(0,1);
            lcd_puts("pres SFR -> test");

            if (SFR==0) 
                {
                delay_ms(100); 
                m180-=10;    
                }
            if (SFL==0) 
                {
                delay_ms(100); 
                m180+=10;    
                }
            if (OK==0) 
                { 
                while (OK==0); 
                delay_ms(200);
                Treset;
                while (TCNTR<m180)
                    {
                    if (TCNTR<m180*0.2 || TCNTR>m180*0.8)
                        go(-100,100,0);
                    else 
                        go(-255,255,0);
                    }    
                go(0,0,0);
                }
            }
        /*
        else if (page==4)      // finish_enable
            { 
            if (SFR==0)
                finish_enable=1;  
            else if (SFL==0)
                finish_enable=0;  
            lcd_gotoxy(0,0);
            if (finish_enable==1)
                lcd_puts(" finish enabled "); 
            else 
                lcd_puts(" finish disabled "); 

            }
        else if (page==5)     //Xd Yd
            {
            sprintf(lcd,"Xd=%d      Yd=%d",Xd,Yd,); 
            lcd_gotoxy(0,0);
            lcd_puts(lcd);
            sprintf(lcd,"XS=%d      YS=%d",XS,YS);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);

            lcd_gotoxy(0,3);
            lcd_puts("  Press DN to set   "); 
            if (SBR==0) 
                {
                while(1)
                    { 
                    if(SBR==0) Yd+=1;
                    if(SBL==0) Yd-=1;
                    if(SFR==0) Xd+=1;
                    if(SFL==0) Xd-=1;
                    if(OK==0)  break;
                    sprintf(lcd,"Xd=%d      Yd=%d",Xd,Yd); 
                    lcd_gotoxy(0,0);
                    lcd_puts(lcd);
                    delay_ms(190);
                    lcd_gotoxy(0,0);
                    lcd_puts("                   ");                 
                    delay_ms(80);
                    lcd_gotoxy(0,3);
                    lcd_puts("  Press OK to exit  "); 

                    }    
                }
            }
        else if (page==6)     // masdoom va khune minimum
            {
            sprintf(lcd,"masdoom_min=%2d    ",masdoom_min); 
            lcd_gotoxy(0,0);
            lcd_puts(lcd);
            sprintf(lcd,"khune_min=%2d   ",khune_min);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);

            lcd_gotoxy(0,3);
            lcd_puts("  Press DN to set   "); 
            if (SBR==0) 
                {
                while(1)
                    { 
                    if(SBL==0) masdoom_min-=1;
                    if(SBR==0) masdoom_min+=1;
                    if(SFR==0) khune_min+=1;
                    if(SFL==0) khune_min-=1;
                    if(OK==0)  break;
                    sprintf(lcd,"masdoom_min=%2d    ",masdoom_min); 
                    lcd_gotoxy(0,0);
                    lcd_puts(lcd);
                    sprintf(lcd,"khune_min=%2d   ",khune_min);
                    lcd_gotoxy(0,1);
                    lcd_puts(lcd);
                    delay_ms(190);
                    lcd_gotoxy(0,0);
                    lcd_puts("                   ");
                    lcd_gotoxy(0,1);
                    lcd_puts("                   ");                 
                    delay_ms(80);
                    lcd_gotoxy(0,3);
                    lcd_puts("  Press OK to exit  "); 

                    }    
                }
            }
        */
        }
    }

void chap(void)
    {
    char divar=0;
    mode_harekat=2;  // dar hale charkhesh
    if (FR <200)    divar=1; 
    Treset;
    while (TCNTR<mL90)
        {
        if (TCNTR<mL90*0.2 || TCNTR>mL90*0.8)
            go(-100,100,0);
        else 
            go(-255,255,0);
        }    
    go(0,0,0);
//    if (posht==1)
//        eslahaghab();
    if (divar==1)
        {
        go(-150,-150,0); 
        delay_ms(600);
        go(200,200,m30/5);
        }
    if (jahat==1)             jahat=4;
    else if (jahat==2)        jahat=1;
    else if (jahat==3)        jahat=2;
    else if (jahat==4)        jahat=3;

    mostaghim();
    }
void rast(void)
    {   
    bit divar=0;
//    bit posht;
//     
//    if (FL<250)  
//        posht=1; // yani bad az charkhesh poshte robat divar khahad bood va mitavanad eslah az aghab konad
//    else 
//        posht=0;
    if (FL<200)
        divar=1;
    mode_harekat=2;  // dar hale charkhesh
          
    Treset;
    while (TCNTR<m90)
        {
        if (TCNTR<m90*0.2 || TCNTR>m90*0.8)
            go(100,-100,0);
        else 
            go(255,-255,0);
        }    
    if (divar==1)
        {
        go(-150,-150,0); 
        delay_ms(600);
        go(200,200,m30/5);
        }
    go(0,0,0);
    if (jahat==1)             jahat=2;
    else if (jahat==2)        jahat=3;
    else if (jahat==3)        jahat=4;
    else if (jahat==4)        jahat=1;

//    if (posht==1)
//        eslahaghab();
    mostaghim();
    }
void ch180(void)
    { 
    mode_harekat=2;  // dar hale charkhesh
     
    Treset;
    while (TCNTR<m180)
        {
        if (TCNTR<m180*0.2 || TCNTR>m180*0.8)
            go(-100,100,0);
        else 
            go(-255,255,0);
        } 
    go(0,0,0);
    Treset; 
//    if (posht==1)
//        eslahaghab();

    if (jahat==1)             jahat=3;
    else if (jahat==2)        jahat=4;
    else if (jahat==3)        jahat=1;
    else if (jahat==4)        jahat=2;

    mostaghim();
    }

void mohasebat (void)
    {
        if (jahat==1)        
            {  
            jahat=1;
            HF=H[x][y+1];
            HL=H[x-1][y];
            HR=H[x+1][y];
            DF=(Xd-x)     * (Xd-x)       +    (Yd-(y+1))*(Yd-(y+1)) ;
            DR=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)*(Yd-y);
            DL=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)*(Yd-y);
            }
        else if (jahat==2 )
            {  
            jahat=2;
            HF=H[x+1][y] ;
            HL=H[x][y+1];
            HR=H[x][y-1];
            DF=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)    *(Yd-y);
            DR=(Xd-x)     * (Xd-x)       +    (Yd-(y-1))*(Yd-(y-1));
            DL=(Xd-x)     * (Xd-x)       +    (Yd-(y+1))*(Yd-(y+1));
            }
      
        else if (jahat==3)
            {
            jahat=4;
            HF=H[x-1][y] ;
            HL=H[x][y-1];
            HR=H[x][y+1];
            DF=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)     *(Yd-y);
            DR=(Xd-x)     * (Xd-x)       +    (Yd-(y+1)) *(Yd-(y+1));
            DL=(Xd-x)     * (Xd-x)       +    (Yd-(y-1)) *(Yd-(y-1));
            } 
            
        else if (jahat==4)  
            { 

            jahat=3;
            HF=H[x][y-1] ;
            HL=H[x+1][y];
            HR=H[x-1][y];
            DF=(Xd-x)     * (Xd-x)       +    (Yd-(y-1))*(Yd-(y-1));
            DR=(Xd-(x-1)) * (Xd-(x-1))   +    (Yd-y)    *(Yd-y);
            DL=(Xd-(x+1)) * (Xd-(x+1))   +    (Yd-y)    *(Yd-y);  
            }
    }    

void eslah(char accuracy)
    {
    signed int speed,zarib;
    int error,time=0;
    char t=0;
    /*cmps();
    if     (shib1>20&&shib1<40&&dir==4)     // sar bala ee = 227
        {
        go(250,250);
        TCNT=0;
        while(TCNT<5);
        cmps();
        if (shib1>20&&shib1<40&&dir==4)
            sarbalaee();
        go(0,0);

        }
    else if(shib1>200&&shib1<230&&dir==2 )   // sar paeeni = 15
        {
        go(250,250);
        TCNT=0;
        while(TCNT<5);
        cmps();
        if (shib1>200&&shib1<230&&dir==2 )
            sarpaeeni();
        go(0,0);
        }
   else  if (sarbala==0 && sarpaeen==0)
        {       */
    go(0,0,0);
        t=0;time=0;
        while(t<3 && time<2000)     
            {  
            delay_ms(1);          
            time++;
            if (FR<200 && BR<200)
                {
                error=FR-BR;
                zarib=abs(error)*0.5;
                if (zarib>50)    zarib=50;
                speed=40+zarib;
                if (error>5)
                    go(speed,-speed,0);
                if (error<-5)
                    go(-speed,speed,0);
                }
            else if (FL<200 && BL<200)
                {
                error=FL-BL;
                zarib=abs(error)*0.5;
                if (zarib>60)    zarib=60;
                speed=40+zarib;
                if (error>5)
                    go(-speed,speed,0);
                if (error<-5)
                    go(speed,-speed,0);
                }
            else if (FR<500 && BR<500 && FR-BR<200 && FR-BR>-200  )
                {
                error=FR-BR;
                zarib=abs(error)*0.5;
                if (zarib>50)    zarib=50;
                speed=40+zarib;
                if (error>5)
                    go(speed,-speed,0);
                if (error<-5)
                    go(-speed,speed,0);
                }
            else if (FL<500 && BL<500 && (FL-BL)<200 && (FL-BL)>-200 )
                {
                error=FL-BL;
                zarib=abs(error)*0.5;
                if (zarib>60)    zarib=60;
                speed=40+zarib;
                if (error>5)
                    go(-speed,speed,0);
                if (error<-5)
                    go(speed,-speed,0);
                }
            else if (FR-BR<20 && FR-BR>-200  )
                {
                error=FR-BR;
                zarib=abs(error)*0.5;
                if (zarib>50)    zarib=50;
                speed=40+zarib;
                if (error>5)
                    go(speed,-speed,0);
                if (error<-5)
                    go(-speed,speed,0);
                }
            else if ((FL-BL)<20 && (FL-BL)>-200 )
                {
                error=FL-BL;
                zarib=abs(error)*0.5;
                if (zarib>60)    zarib=60;
                speed=40+zarib;
                if (error>5)
                    go(-speed,speed,0);
                if (error<-5)
                    go(speed,-speed,0);
                }

            if (error<accuracy && error >-accuracy)
                {
                go(0,0,0);
                t++;
                delay_ms(10);
                }
            else    t=0;
            }
        go(0,0,0);            
        t=0; time=0;
        while (t<5 && FF<500 && time<2000)
            { 
            delay_ms(1);          
            time++;
            ultra_number=3;// yani faghat ultra jolo refresh beshe
            if (FF<250)         error=FF-80;
            else if (FF<500)    error=FF-380;
            //else if (FF<800)    error=FF-680;
            if (error < -30 )         go(-100,-100,0);
            else if (error < 0 )      go(-35,-35,0);
            else if (error < 30 )     go(35,35,0);
            else if (error > 30 )     go(100,100,0);
            if (error<accuracy && error>-accuracy)
                {
                go(0,0,0);
                t++;
                delay_ms(20);
                }
            else    t=0;
    //        sprintf(text,"FF=%3d  sp=%3d   ",FF,speed);
    //        lcd_gotoxy(0,0);
    //        lcd_puts(text);
    //        sprintf(text,"time=%3d   ",time);
    //        lcd_gotoxy(0,1);
    //        lcd_puts(text);
            } 
        go(0,0,0);            
       // }
    }
    
float vsens (char num)
    { 
    float v;
    if (num==0)  {v=read_adc(0); v=v*5/1023;}  
    if (num==1)  {v=read_adc(1); v=v*5/1023;}
    if (num==2)  {v=read_adc(2); v=v*5/1023;}
    if (num==3)  {v=read_adc(3); v=v*5/1023;}
    
    return v;
    }
        
void eslahaghab (void)
    {      
    int time=0;
    Treset;
    go(-200,-200,0);
    while(1)
        {
        if (SBL==1 && SBR==1)
            go(-150,-150,0);
        if (SBL==0 && SBR==1)
            go(0,-150,0);
        if (SBL==1 && SBR==0)
            go(-150,0,0);
        if (SBL==0 && SBR==0)
             break;
        delay_ms(1);  
        time++;
        if (time>2000)
            break;
        }
    go(0,0,0);
    go(200,200,30);
    go(0,0,0);

    delay_ms(100); 
    }
    
void eslahjolo (void)
    {  
    int time=0;
    Treset; 
    while(1)
        {
        if (SFL==1 && SFR==1)
            go(150,150,0);
        else if (SFL==0 && SFR==1)
            go(0,150,0);
        else if (SFL==1 && SFR==0)
            go(150,0,0);
        else if (SFL==0 && SFR==0)
             break;  
        delay_ms(1);  
        time++;
        if (time>2000)
            break;
        if (SDFL==1 && SDFR==1 && SDB==1)
            {
            lcd_clear();
            lcd_puts("black room");
            break;                 
            }
        }
    go(150,150,0);
    delay_ms(300);
    go(0,0,0);

    go(-150,-150,m30/4);
    }

void masdoom (void)
    { 
    /*
    if (masdoom_enable==1)
        {
        char mFL=MLXFL;
        char mFR=MLXFR;
        char mBL=MLXBL;
        char mBR=MLXBR;    

        if ( ((mFL>=mFR+dama_low || mFL>=mBR+dama_low) && FL<200)  || ((mBL>=mFR+dama_low || mBL>=mBR+dama_low)&& BL<200 ) )
            {
            //if ((mode_harekat==2 && vic[x][y]==0) || (mode_harekat==1 && TCNTR<=m30/2 && vic[x][y]==0 ))    // age dar hale charkhidan tashkhis bedeh ya avalaye 
            if ((vic[x][y]==0 && (mode_harekat==2  || (mode_harekat==1 && TCNTR<=m30/2))))    
                {
                int tcnt=TCNTR;
                int spL=global_speedL;
                int spR=global_speedR;
                
                masdoom_enable=0;
                lcd_gotoxy(0,3);
                lcd_puts(" vic left ");

                go(0,0,0);
                compas();
                for(i=0;i<10;i++)
                    {                                 
                    LED=1;
                    delay_ms(50);
                    LED=0; 
                    delay_ms(50);
                    }
                if ((shib<40 && shib >15) || (shib<240 && shib >220))    // age tooye ramp bood nacharkhe
                    {
                    go(20,20,0);
                    MV1=0;
                    MV2=1;
                    delay_ms(1300);
                    MV1=1;
                    MV2=0;
                    delay_ms(2000);
                    MV1=0;
                    MV2=0;
                    TL=tcnt/256;  TCNT3L=tcnt%256;   //  TCNTR=tcnt;
                    for(i=20;i<160;i++)
                        {
                        go(i,i,0); 
                        delay_ms(8);
                        }
                    }
                else
                    {
                    go(180,-180,m90);
                    MV1=0;
                    MV2=1;
                    delay_ms(1300);
                    MV1=1;
                    MV2=0;
                    delay_ms(2000);
                    MV1=0;
                    MV2=0;        
                    go(-180,180,m90);
                    TL=tcnt/256;  TCNT3L=tcnt%256;   //  TCNTR=tcnt;
                    go(spL,spR,0);
                    }
                vic[x][y]=1;
                }
            }
        if ( ((mFR>=mFL+dama_low || mFR>=mBL+dama_low) && FR<200)  || ((mBR>=mFL+dama_low || mBR>=mBL+dama_low) && BR<200 ) )
            {
            if ((vic[x][y]==0 && (mode_harekat==2  || (mode_harekat==1 && TCNTR<=m30/2))))    // age dar hale charkhidan tashkhis bedeh ya avalaye 
                {
                int tcnt=TCNTR;
                int spL=global_speedL;
                int spR=global_speedR;
                masdoom_enable=0;      
                lcd_gotoxy(0,3);
                lcd_puts(" vic right ");

                go(0,0,0); 
                compas();
                for(i=0;i<10;i++)
                    {                                 
                    LED=1;
                    delay_ms(50);
                    LED=0; 
                    delay_ms(50);
                    }
                if ((shib<40 && shib >15) || (shib<240 && shib >220))    // age tooye ramp bood nacharkhe
                    {
                    go(20,20,0);
                    MV1=0;
                    MV2=1;
                    delay_ms(1300);
                    MV1=1;
                    MV2=0;
                    delay_ms(2000);
                    MV1=0;
                    MV2=0;
                    TL=tcnt/256;  TCNT3L=tcnt%256;   //  TCNTR=tcnt;
                    for(i=20;i<160;i++)
                        {
                        go(i,i,0); 
                        delay_ms(8);
                        }
                    }
                else
                    {
                    go(-180,180,m90);
                    MV1=0;
                    MV2=1;
                    delay_ms(1300);
                    MV1=1;
                    MV2=0;
                    delay_ms(2000);
                    MV1=0;
                    MV2=0;        
                    go(180,-180,m90);
                    TL=tcnt/256;  TCNT3L=tcnt%256;   //  TCNTR=tcnt;
                    go(spL,spR,0);
                    }
                vic[x][y]=1;
                interupt_enable=0;
                }
            }
        } 
    */             
    }   

void mostaghim(void)
    {
    signed int error,error1=0,error2;
    masdoom_enable=1; 
    mode_harekat=1;
    Treset;
    go (100,100,0);
    while (1)
        {
        //lcd_clear();
          
        lcd_gotoxy(18,3);lcd_puts("  ");
        error1=0;error2=0;error=0;
        if (FL<200 )
            { 
            //error1=(FL-BL);
            error2=(FL-100);  
            lcd_gotoxy(13,1);lcd_puts("LN");
            }
        else if (FR<200)
            {
            //error1=(BR-FR);    // chap & rast bar aks ham hastand
            error2=(100-FR)/2;
            lcd_gotoxy(13,1);lcd_puts("RN");
            }
        else if (FL<500)
            {
            //error1=(FL-BL);
            error2=(FL-400)/2;  
            lcd_gotoxy(13,1);lcd_puts("LF");
            }
        else if (FR<500 )
            {
            //error1=(BR-FR);    // chap & rast bar aks ham hastand
            error2=(400-FR)/2;  
            lcd_gotoxy(13,1);lcd_puts("RF");
            }

        if (error2>15)       error2=15;
        if (error2<-15)      error2=-15;
        error=error1+error2;

        if(error>150)         error=150;
        if(error<-150)        error=-150;
        if(error>-5 && error<5)     error=0;

        if(TCNTR>m30 || FF<110)
            {
            //lcd_clear();
            //sprintf(lcd,"FF=%3d TCNT=%3d",FF,TCNTR);
            //lcd_gotoxy(0,1);
            //lcd_puts(lcd); 
            if (FF<110)
                eslahjolo();
            go(0,0,0);
            break;    
            }
        if (SFR==0 || SFL==0) 
            {
                if (SFR==0 && SFL==1) 
                    {
                   // tcnt1=TL;

                    Treset; 
                    go(0,-200,0); 
                    delay_ms(300);
                            
                    Treset;
                    go(-200,0,0);
                    delay_ms(300);

                    go(0,0,0);
                    //delay_ms(50);
                    //eslah(5);
                            
                    Treset;
                    go(150,150,0);
                    delay_ms(300);

                    Treset;    
                    //TL=tcnt1;
                    }
                else if (SFR==1 && SFL==0)
                    {
                    //tcnt1=TL;
                            
                    Treset;
                    go(-200,0,0);
                    delay_ms(300);
                            
                    Treset;
                    go(0,-200,0);
                    delay_ms(300);                
                        
                    go(0,0,0);
                    //delay_ms(50);
                   // eslah(5);
                            
                    Treset;
                    go(150,150,0);
                    delay_ms(300);

                    Treset;    
                    //TL=tcnt1;
                    }
                else if (SFR==0 && SFL==0)
                    break;    
            }

        else if (TCNTR<m30*0.15  || TCNTR>m30*0.85)
            {
           // if(error>=0)
            //    go(100-error*1.3,100+error,0);
           // if(error<0)
                go(100-error,100+error,0);
            }
        else   
            {
            //if(error>=0)
            //    go(160-error*1.3,160+error,0);
           // if(error<0)
                go(160-error,160+error,0);
            }                

        } 
lcd_clear();

    /*
    if (VSDFL>black && VSDFR>black && VSDB>black)
        {
        go(0,0,0);
        delay_ms(100);
        Treset;
        go(-170,-170,0); 
        //while(VSDFL>black || VSDFR>black || VSDB>black);
        while(1)
            {
            if (FL-BL<150  && FL-BL>-150  && FL<200 && BL<200 )
                { 
                error1=(BL-FL);
                error2=BL-80;  
                error=error1+error2;
                }
            else if (FR-BR<150  && FR-BR>-150  && FR<200 && BR<200 )
                {
                error1=(FR-BR);    // chap & rast bar aks ham hastand
                error2=80-BR;  
                error=error1+error2;
                }
            else error=0;

            if(error>60)     error=60;
            if(error<-60)    error=-60;
                 
            if(TCNTR>m30 )
                break;     
                
            else if (TCNTR<m30*0.15  || TCNTR>m30*0.85)
                go(-100+error,-100-error,0);
            else   
                go(-160+error,-160-error,0);
            }
            
        while (FR<60)
            {
            go(0,150,20);
            go(150,0,20);
            go(0,-150,20);
            go(-150,0,20);
                 
            }    
             
        while (FL<60)
            {
            go(150,0,20);
            go(0,150,20);
            go(-150,0,20);
            go(0,-150,20);
                 
            }    

        go(-200,200,m180); 

        mohasebat();
        if      (jahat==1)   y--;        
        else if (jahat==2)   x--; 
        else if (jahat==3)   y++;
        else if (jahat==4)   x++;
        //break;
        } 
    */

        mohasebat();
        if      (jahat==1)   y++;        
        else if (jahat==2)   x++; 
        else if (jahat==3)   y--;
        else if (jahat==4)   x--;
        ramp=0;

    go(0,0,0);
    H[x][y]++;   
    }

void main(void)
{
    {
    DDRA=0b10000000;PORTA=0b10000000;
    DDRB=0b11110000;PORTB=0b00001111;
    DDRC=0b01111110;PORTC=0b10000011;
    DDRD=0b00001000;PORTD=0b11111111;
    DDRE=0b01100111;PORTE=0b00000000;
    DDRF=0b00000000;PORTF=0b00000000;
    DDRG=0b00000;   PORTG=0b00000;

    ASSR=0x08;
    TCCR0=0x01;
    OCR0=1;

    ASSR=0x08;
    TCCR0=0x01;    // encoder R
    TCCR1A=0xA1;   // PWM
    TCCR1B=0x09;
    TCCR2=0x02;    // timer baraye ultra
    TCCR3A=0x01;   // ENC L
    TCCR3B=0x0E;

    TIMSK=0x42;
    ETIMSK=0x04;

    ADMUX=0x00 & 0xff;
    ADCSRA=0x83;

    lcd_init(16);
    i2c_init();
    
#asm("sei")
    LED=1;                     
    delay_ms(100);
    LED=0; 
    delay_ms(100);
    }
 
lcd_puts("ya mahdi");

   
// menu
    {
    signed char page=0,erase=0;
    masdoom_enable=0;
    interupt_enable=1;
    lcd_clear(); 
    while(SBR==0);
    while (1)
        {
        if (UP==0)
            {
            while (UP==0);
            page++;
            if (page>5) page=0;
            lcd_clear();
            }
        if (DN==0)
            {
            while (DN==0);
            page--;
            if (page<0) page=5;
            lcd_clear();
            }

        if (page==0)      // start 
            {     
            lcd_gotoxy(0,0);
            lcd_puts("start ");
            if (OK==0)
                {
                while(OK==0);
                break;
                }            
            }
        else if (page==1)      // sensor checkup 
            {     
            lcd_gotoxy(0,0);
            lcd_puts("sensor checkup ");
            if (OK==0)
                {
                while(OK==0);
                sensor_checkup();
                }            
            }
        else if (page==2)      //  setup 
            {     
            lcd_gotoxy(0,0);
            lcd_puts("Robot setup");
            if (OK==0)
                {
                while(OK==0);
                setup();
                }            
            }
        else if (page==3)     //clear memory
            {
            lcd_gotoxy(0,0);
            lcd_puts("clear memory ");
            if (OK==0) 
                {
                lcd_clear();
                while(OK==0);
                erase=1;
                }
            }
        if (m30==-1 || erase==1)
            {
            lcd_gotoxy(0,0);
            lcd_puts("earasing"); 
            erase=0; 
            lcd_clear();
            detect_error=0;
            first_check=0;
            lcd_gotoxy(0,1);
            for (y=0;y<20;y++)
                {
                for (x=0;x<20;x++)
                    {
                    H[x][y]=0; 
                    //vic[x][y]=0; 
                    }
                lcd_puts("."); 

                }
            H[XS][YS]=1;
            lcd_clear();
            if (m30==255 || m30==-1)  //faghat moghe program kardan
                {
                khune_min=35;
                masdoom_min=4;
                Xd=40; 
                Yd=10;
                silver=1; 
                black=4;
                dama_high=5;
                dama_low=3;
                m90=524;
                m180=1000;   
                m30=460;
                m45=60;
                finish_enable=1; 
                ekhtelaf1=351;    
                ekhtelaf2=283;    
                ekhtelaf3=232;    
                ekhtelaf4=158;    
                }   
            lcd_puts("memory cleard ");
            delay_ms(1000);
            page=1;
            Xshib=0;
            Yshib=0;
            xsil=XS,ysil=YS;
            }
        }
    }        

interupt_enable=0;
x=10,y=10;
masdoom_enable=1;

//MV1=1;
//MV2=0;
//delay_ms(1000);
//MV1=0;
//MV2=0;

lcd_gotoxy(0,0);
sprintf(lcd,"A(%2d,%2d)=%2d j=%d",x,y,H[x][y],jahat);
lcd_puts(lcd); 

lcd_gotoxy(0,1);
sprintf(lcd,"S(%2d,%2d)   ",xsil,ysil);
lcd_puts(lcd);


mostaghim();
#asm("sei")
while(1) 
    {   
    mohasebat();   
    lcd_clear();
    lcd_gotoxy(0,0);
    sprintf(lcd,"A(%2d,%2d)=%2d J=%d ",x,y,H[x][y],jahat);
    lcd_puts(lcd); 

    sprintf(lcd,"%4d  %4d  %4d",FL,FF,FR);
    lcd_gotoxy(0,1);
    lcd_puts(lcd);
    delay_ms(1000);
     
//    sprintf(lcd,"FL:%3d %3d %3d %3d",MLXFL,MLXBL,MLXFR,MLXBR);
//    lcd_gotoxy(0,2);
//    lcd_puts(lcd);
//                        
     
    P=0;       
    if(FF<200)    P+=10;
    if(FL<200)    P+=100;
    if(FR<200)    P+=1; 
    
    if (P==101)
            mostaghim();
    else if (P==110)
            rast(); 
    else if (P==11)
            chap();
    else if(P==111) 
            ch180(); 
            
    else if (P==1) 
            {
            if (HL<HF)
                chap();
            else if (HL>HF)
                mostaghim();
            else 
                
                {
                if (HL==0 || HF==0)
                    {
                    if (DL>DF)
                        mostaghim();
                    else
                        chap();
                    }
                else 
                    {
                    if (DF>DL)
                        chap();
                    else
                        mostaghim();
                    }
                }
            }
    else if (P==10) 
            {
            if (HL<HR)
                   chap();
            else if (HL>HR)
                   rast();
            else 
                {
                if (HL==0 || HR==0)
                    {
                    if (DL>DR)
                        rast();
                    else
                        chap();
                    }
                else 
                    {
                    if (DL<DR)
                        chap();
                    else
                        rast();
                    }
                }
            }
    else if (P==100) 
            {
            if (HF<HR)
                   mostaghim();
            else if (HF>HR)
                   rast();
            else 
                {
                if (HF==0 || HR==0)
                    {
                    if (DR>DF)
                           mostaghim();
                    else
                           rast();
                    }
                else 
                    {
                    if (DR<DF)
                           rast();
                    else
                           mostaghim();
                    }
                }
            }         
    else if (P==0) 
            {
            if (HF<HR && HF<HL)
                   mostaghim();
            else if (HR<HF && HR<HL)
                   rast();                                                                                      
            else if (HL<HR && HL<HF)
                   chap();
            else if (HL==HF && HF!=HR)
                    {
                    if (DL>DF) 
                              mostaghim();
                    else 
                              chap();                    
                    }
            else if (HR==HF && HF!=HL)
                    {
                    if (DR>DF)
                               mostaghim();
                    else 
                               rast();     
                    } 
            else if (HR==HL && HL!=HF)
                    {
                    if (DR>DL)
                                  chap();
                    else 
                                  rast();
                    }        
            else   
                {
                if (HL==0)
                    {
                    if (DF<DR && DF<DL)
                    mostaghim();
                    else if (DR<DF && DR<DL)
                    rast();                                                                                      
                    else if (DL<DR && DL<DF)
                    chap();
                    else if (DF>DR && DF>DL)
                    rast();
                    else if (DR>DF && DR>DL)
                    mostaghim();                                                                                      
                    else if (DL>DR && DL>DF)
                    rast();
                    else
                    mostaghim();       
                    }  
                else 
                    {
                    if (DF<DR && DF<DL)
                    mostaghim();
                    else if (DR>DF && DR>DL)
                    rast();                                                                                      
                    else if (DL>DR && DL>DF)
                    chap();
                    else if (DF<DR && DF<DL)
                    rast();
                    else if (DR<DF && DR<DL)
                    mostaghim();                                                                                      
                    else if (DL<DR && DL<DF)
                    rast();
                    else
                    mostaghim();       
                    }  
                }
                                                       
            }

    for (k=0;k<40;k++)
        for (j=0;j<40;j++)
            {
            if (H[k][j]>0)
                tedad_khune++;
            if (vic[k][j]>0)
                tedad_masdoom++;
            }  
    /*
    if(tedad_khune>45)
        {
        Xd=XS;
        Yd=YS;                      
        }
        
    if ( (VSDFL<silver && VSDFL>0.2) || (VSDFR<silver && VSDFR>0.2) || (VSDB<silver && VSDB>0.2) )
        { 
        go(100,100,m90*0.2);
        if ( (VSDFL<silver && VSDFL>0.2) || (VSDFR<silver && VSDFR>0.2) || (VSDB<silver && VSDB>0.2) )
            {  
            go(0,0,0);
            lcd_gotoxy(0,3);
            lcd_puts(" silver "); 
            xsil=x;
            ysil=y;

            sprintf(lcd,"sil=(%2d,%d)",xsil,ysil);
            lcd_gotoxy(0,1);                                               
            lcd_puts(lcd);
            delay_ms(500);

            if ((x==XS || x==XS+1 || x==XS-1) && (y==YS || y==YS+1 || y==YS-1))
                {       

                lcd_clear();
                lcd_puts("start room"); 
                sprintf(lcd,"finish en=%d",finish_enable);
                lcd_gotoxy(0,1);
                lcd_puts(lcd);  
                  
                sprintf(lcd," t_k=%2d  t_m=%2d    ",tedad_khune,tedad_masdoom);
                lcd_gotoxy(0,2);
                lcd_puts(lcd);       
                if (finish_enable==1 && tedad_khune>khune_min && tedad_masdoom>masdoom_min)
                    {
                    go(0,0,0);
                    lcd_gotoxy(0,0);
                    lcd_puts("     Finish  ");
                    while(1);
                    }   
                delay_ms(1000);
                }
            }
        
        }*/

    }

}

