// ATMEGA 32
// 1397/08/18
#pragma used+

// mega 16 
//#define M_UCSRA     UCSRA
//#define M_UCSRB     UCSRB
//#define M_UCSRC     UCSRC
//#define M_UDR       UDR
//#define M_UBRRL     UBRRL
//#define M_UBRRH     UBRRH
//#define M_TX_PIN    DDRD.1

// mega 128 
#define M_UCSRA     UCSR1A
#define M_UCSRB     UCSR1B
#define M_UCSRC     UCSR1C
#define M_UDR       UDR1
#define M_UBRRL     UBRR1L
#define M_UBRRH     UBRR1H
#define M_TX_PIN    DDRD.3

#include <delay.h>
#define INST_REG_WRITE      0x04
#define INST_WRITE          0x03
#define P_CW_ANGLE_LIMIT_L  6
#define P_TORQUE_ENABLE     24
#define P_GOAL_POSITION_L   30   // 0x1E
#define P_GOAL_SPEED_L      32
#define Rmot      1
#define Lmot      2

#define bit_is_set(REG8,BITNUM) ((REG8&(1<<BITNUM))!=0)
#define TXD_READY  bit_is_set(M_UCSRA,5)

#define CHECK_TXD_FINISH  bit_is_set(M_UCSRA,6)
#define sbi(REG8,BITNUM) REG8|=_BV(BITNUM)
#define _BV(BITNUM)      (1<<BITNUM)

#define cnt (TCNT0+puls_cnt*255)/75
unsigned int puls_cnt;

char TxBuffer[20];
char gbpTxBuffer[20],gbpParameter[20],packet[30];
unsigned short update_crc(unsigned short crc_accum,unsigned char *data_blk_ptr,unsigned short data_blk_size)
{
unsigned short i,j;
unsigned short crc_table[256] = {
    0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
    0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
    0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
    0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
    0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
    0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
    0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
    0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
    0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
    0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
    0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
    0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
    0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
    0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
    0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
    0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
    0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
    0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
    0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
    0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
    0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
    0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
    0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
    0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
    0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
    0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
    0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
    0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
    0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
    0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
    0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
    0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202};

for(j=0; j < data_blk_size; j++)
    {
    i=((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
    crc_accum=(crc_accum << 8) ^ crc_table[i];
    }
return crc_accum;
}

void DXL_PRO_CHANGE_BAUD (char ID,long NewBaudRate)
    {       
    char Count;
    unsigned short CRC;
    char UBRR1L_save=M_UBRRL,UBRR1H_save=M_UBRRH;

    if (NewBaudRate==9600)          NewBaudRate=0;
    else if (NewBaudRate==57600)    NewBaudRate=1;
    else if (NewBaudRate==115200)   NewBaudRate=2;
    else if (NewBaudRate==1000000)  NewBaudRate=3;

    packet[0]   = 0xFF;
    packet[1]   = 0xFF;
    packet[2]   = 0xFD;
    packet[3]   = 0x00; // RESERVED
    packet[4]   = ID;   // id
    packet[5]   = 4+2;  // packet lengh L  : packet lengh after packet lengh
    packet[6]   = 0;    // packet lengh H
    packet[7]   = 3;    // Instraction
    packet[8]   = 4;   // address L
    packet[9]   = 0;    // address H
    packet[10]  = NewBaudRate;    // parameter

    CRC = update_crc (0, packet, 11) ;
    packet[11] = CRC & 0xFF;        // CRC_L
    packet[12] = (CRC>>8) & 0xFF;   // CRC_H


    M_UBRRL=0x47;    // USART1 Baud Rate: 9600
    for(Count=0; Count < 13; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    delay_ms(20);

    M_UBRRL=0x0B;    // USART1 Baud Rate: 57600
    for(Count=0; Count < 13; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    delay_ms(20);

    M_UBRRL=0x05;    // USART1 Baud Rate: 115200
    for(Count=0; Count < 13; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    delay_ms(20);

    M_UBRRL=UBRR1L_save;
    M_UBRRH=UBRR1H_save;  

    }
void DXL_PRO_LED (char ID,char color)
    {
    char Count;
    unsigned short CRC;

    packet[0]   = 0xFF;
    packet[1]   = 0xFF;
    packet[2]   = 0xFD;
    packet[3]   = 0x00; // RESERVED
    packet[4]   = ID;   // id
    packet[5]   = 4+2;  // packet lengh L  : packet lengh after packet lengh
    packet[6]   = 0;    // packet lengh H
    packet[7]   = 3;    // Instraction
    packet[8]   = 25;   // address L
    packet[9]   = 0;    // address H
    packet[10]  = color;    // parameter

    CRC = update_crc (0, packet, 11) ;
    packet[11] = CRC & 0xFF;        // CRC_L
    packet[12] = (CRC>>8) & 0xFF;   // CRC_H

    for(Count=0; Count < 13; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    
    }
void DXL_PRO_CONTROL_MODE (char ID,char wheel_joint)
    {
    char Count;
    unsigned short CRC;

    packet[0]   = 0xFF;
    packet[1]   = 0xFF;
    packet[2]   = 0xFD;
    packet[3]   = 0x00; // RESERVED
    packet[4]   = ID;   // id
    packet[5]   = 4+2;  // packet lengh L  : packet lengh after packet lengh
    packet[6]   = 0;    // packet lengh H
    packet[7]   = 3;    // Instruction

    packet[8]   = 11;   // address L
    packet[9]   = 0;    // address H
    packet[10]  = wheel_joint;    // 1: wheel mode    2: joint mode

    CRC = update_crc (0, packet, 11) ;
    packet[11] = CRC & 0xFF;        // CRC_L
    packet[12] = (CRC>>8) & 0xFF;   // CRC_H

    for(Count=0; Count < 13; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
        
    }
void XL (char ID,int position, int speed)
    {
    char Count;
    unsigned short CRC;

    packet[0]   = 0xFF;
    packet[1]   = 0xFF;
    packet[2]   = 0xFD;
    packet[3]   = 0x00; // RESERVED
    packet[4]   = ID;   // id
    packet[5]   = 7+2;  // packet lengh L  : packet lengh after packet lengh
    packet[6]   = 0;    // packet lengh H
    packet[7]   = 3;    // Instraction
    packet[8]   = 30;   // address L
    packet[9]   = 0;    // address H
    packet[10]  = position & 255;         // parameter
    packet[11]  = (position>>8) & 255;    // parameter
    packet[12]  =  speed & 255;           // parameter
    packet[13]  = (speed >>8) & 255;      // parameter

    CRC = update_crc (0, packet, 14) ;
    packet[14] = CRC & 0xFF;        // CRC_L
    packet[15] = (CRC>>8) & 0xFF;   // CRC_H

    for(Count=0; Count < 16; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    delay_ms(15);
    }
void DXL_PRO_WHEEL (char ID, int speed)
    {
    char Count;
    unsigned short CRC;

    packet[0]   = 0xFF;
    packet[1]   = 0xFF;
    packet[2]   = 0xFD;
    packet[3]   = 0x00; // RESERVED
    packet[4]   = ID;   // id
    packet[5]   = 5+2;  // packet lengh L  : packet lengh after packet lengh
    packet[6]   = 0;    // packet lengh H
    packet[7]   = 3;    // Instraction
    packet[8]   = 32;   // address L
    packet[9]   = 0;    // address H
    packet[10]  =  speed & 255;           // parameter
    packet[11]  = (speed >>8) & 255;      // parameter

    CRC = update_crc (0, packet, 12) ;
    packet[12] = CRC & 0xFF;        // CRC_L
    packet[13] = (CRC>>8) & 0xFF;   // CRC_H

    for(Count=0; Count < 14; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    
    }
void DXL_PRO_TORQUE (char ID,char torque_enable)
    {
    unsigned short CRC;
    char Count;
    packet[0]   = 0xFF;
    packet[1]   = 0xFF;
    packet[2]   = 0xFD;
    packet[3]   = 0x00; // RESERVED
    packet[4]   = ID;   // id
    packet[5]   = 6 ;  // packet lengh L  : packet lengh after packet lengh
    packet[6]   = 0;    // packet lengh H
    packet[7]   = 3;    // Instraction
    packet[8]   = 24;   // address L
    packet[9]   = 0;    // address H
    packet[10]  = torque_enable;          // parameter

    CRC = update_crc (0, packet, 11) ;
    packet[11] = CRC & 0xFF;        // CRC_L
    packet[12] = (CRC>>8) & 0xFF;   // CRC_H

    for(Count=0; Count < 13; Count++)    
        {
        while(!TXD_READY);
        M_UDR=packet[Count];
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    
    }

char TxPacket(char bID, char bInstruction, char bParameterLength)
    {
    char bCount,bCheckSum,bPacketLength;
    gbpTxBuffer[0] = 0xff;
    gbpTxBuffer[1] = 0xff;
    gbpTxBuffer[2] = bID;
    gbpTxBuffer[3] = bParameterLength+2; //Length(Paramter,Instruction,Checksum)
    gbpTxBuffer[4] = bInstruction;
    for(bCount = 0; bCount < bParameterLength; bCount++)
        {
        gbpTxBuffer[bCount+5] = gbpParameter[bCount];
        }
    bCheckSum = 0;
    bPacketLength = bParameterLength+4+2;
    for(bCount = 2; bCount < bPacketLength-1; bCount++) //except 0xff,checksum
        {
        bCheckSum += gbpTxBuffer[bCount];
        }
    gbpTxBuffer[bCount] = ~bCheckSum; //Writing Checksum with Bit Inversion
    for(bCount = 0; bCount < bPacketLength; bCount++)
        {
        while(!TXD_READY);
        M_UDR =gbpTxBuffer[bCount] ;
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty
    return bPacketLength;
    }
void DXL_POSITION (char bID,int position, int speed)
    {
    gbpParameter[0] = 30; // Address of position
    gbpParameter[1] = position & 255;     // Writing Data P_GOAL_POSITION_L2
    gbpParameter[2] = position >> 8;      // Writing Data P_GOAL_POSITION_H
    gbpParameter[3] = speed & 255;        // Writing Data P_GOAL_SPEED_L2
    gbpParameter[4] = speed >>8;          // Writing Data P_GOAL_SPEED_H
    TxPacket(bID,3,5);
    delay_ms(10);
    }
void DXL_CHANGE_BAUD (char bID,long NewBaudRate)
    {  
    char UBRR1L_save=M_UBRRL,UBRR1H_save=M_UBRRH;

    if (NewBaudRate==9600)        NewBaudRate=207;
    else if (NewBaudRate==38400)  NewBaudRate=51;
    else if (NewBaudRate==57600)  NewBaudRate=34;
    else if (NewBaudRate==115200) NewBaudRate=16;

    M_UBRRL=0x47;    // USART1 Baud Rate: 9600
    gbpParameter[0] = 4; //Address of Firmware Version
    gbpParameter[1] = NewBaudRate;    //Writing new baud rate
    TxPacket(bID,3,2);
    delay_ms(20);

    M_UBRRL=0x11;    // USART1 Baud Rate: 38400
    gbpParameter[0] = 4; //Address of Firmware Version
    gbpParameter[1] = NewBaudRate;    //Writing new baud rate
    TxPacket(bID,3,2);
    delay_ms(20);

    M_UBRRL=0x0B;    // USART1 Baud Rate: 57600
    gbpParameter[0] = 4; //Address of Firmware Version
    gbpParameter[1] = NewBaudRate;    //Writing new baud rate
    TxPacket(bID,3,2);
    delay_ms(20);

    M_UBRRL=0x05;    // USART1 Baud Rate: 115200
    gbpParameter[0] = 4; //Address of Firmware Version
    gbpParameter[1] = NewBaudRate;    //Writing new baud rate
    TxPacket(bID,3,2);
    delay_ms(20);

    M_UBRRL=UBRR1L_save;
    M_UBRRH=UBRR1H_save;

    }





void dxl_init (void)
    { 
    M_TX_PIN=1;
    M_UCSRA=0x00;
    M_UCSRB=0x08;
    M_UCSRC=0x06;
    M_UBRRH=0x00;
    M_UBRRL=0x05;     // USART1 Baud Rate: 115200 Xtall 11.0592 MHz
    //M_UBRRL=0x47;   // USART1 Baud Rate: 9615 Xtall 11.0592 MHz
    //M_UBRRL=0x33;   // USART1 Baud Rate: 9615  Xtall 8 MHz
    sbi(M_UCSRA,6); // SET_TXD0_FINISH; // Note. set 1, then 0 is read    go(0,0);
    }

void _TXsend (char last_TXBuffer)
    {  
    unsigned char CheckSum,Count;
//    TXD;
    DDRD.3=1;
    CheckSum=0;
    for(Count = 2; Count <= last_TXBuffer; Count++) //except 0xff,checksum
        CheckSum += TxBuffer[Count];
    TxBuffer[last_TXBuffer+1] = ~CheckSum; //Writing Checksum with Bit Inversion

    for(Count = 0; Count <= last_TXBuffer+1; Count++)
        {
        while(!TXD_READY);
        M_UDR =TxBuffer[Count] ;
        }
    while(!CHECK_TXD_FINISH); //Wait until TXD Shift register empty

    DDRD.3=0;
    delay_ms(1);  // bayad bashe hatman    hade aghal=10  // 1 bazi vaghta error mideh
//    RXD;
    }
void AX12 (char ID,int position, int speed)
    {
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;   // ID
    TxBuffer[3] = 7;  // Length(Paramter=5,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;    // bInstruction;

    TxBuffer[5] = 30; // Address of speed
    TxBuffer[6] = position & 255;     // Writing Data P_GOAL_POSITION_L2
    TxBuffer[7] = position >> 8;      // Writing Data P_GOAL_POSITION_H
    TxBuffer[8] = speed & 255;        // Writing Data P_GOAL_SPEED_L2
    TxBuffer[9] = speed >> 8;         // Writing Data P_GOAL_SPEED_H

    _TXsend(9);
    }
void ax_change_baud (char ID,long NewBaudRate)
    {
    char UBRRL_save=M_UBRRL,UBRRH_save=M_UBRRH;

    if      (NewBaudRate==9600)   NewBaudRate=207;
    else if (NewBaudRate==38400)  NewBaudRate=51;
    else if (NewBaudRate==57600)  NewBaudRate=34;
    else if (NewBaudRate==115200) NewBaudRate=16;

    M_UBRRL=0x47;    // USART1 Baud Rate: 9600
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;
    TxBuffer[3] = 4;  // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;  // bInstruction;
    TxBuffer[5] = 4;  // Address
    TxBuffer[6] = NewBaudRate;
    _TXsend(6);
    delay_ms(20);


    M_UBRRL=0x11;    // USART1 Baud Rate: 38400
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;
    TxBuffer[3] = 4;  // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;  // bInstruction;
    TxBuffer[5] = 4;  // Address
    TxBuffer[6] = NewBaudRate;
    _TXsend(6);
    delay_ms(20);


    M_UBRRL=0x0B;    // USART1 Baud Rate: 57600
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;
    TxBuffer[3] = 4;  // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;  // bInstruction;
    TxBuffer[5] = 4;  // Address
    TxBuffer[6] = NewBaudRate;
    _TXsend(6);
    delay_ms(20);


    M_UBRRL=0x05;    // USART1 Baud Rate: 115200
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;
    TxBuffer[3] = 4;  // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;  // bInstruction;
    TxBuffer[5] = 4;  // Address
    TxBuffer[6] = NewBaudRate;
    _TXsend(6);
    delay_ms(20);


    M_UBRRL=UBRRL_save;
    M_UBRRH=UBRRH_save;

    }
void ax_mode (char ID,char joint_or_wheel)
    {
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;   // ID
    TxBuffer[3] = 7;  // Length(Paramter=5,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;    // bInstruction;
    TxBuffer[5] = 6; // Address
    if (joint_or_wheel==0)     // joint mode
        {
        TxBuffer[6] = 1;
        TxBuffer[7] = 0;
        TxBuffer[8] = 255;
        TxBuffer[9] = 3;
        }      
    else 
        {
        TxBuffer[6] = 0;
        TxBuffer[7] = 0;
        TxBuffer[8] = 0;
        TxBuffer[9] = 0;
        }
    _TXsend(9);
    }

void _AXstatus (char ID,char st)
    {
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;   // ID
    TxBuffer[3] = 4;    // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;    // bInstruction;
    TxBuffer[5] = 16;   // Address
    TxBuffer[6] = st;   // 0= No return.  1=return Only when read  2=always return

    _TXsend(6);
    }
void ax_torque (char ID,char torque)
    {
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;   // ID
    TxBuffer[3] = 4;    // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;    // bInstruction;
    TxBuffer[5] = 24;   // Address
    TxBuffer[6] = torque;   // 0= off.  1=on

    _TXsend(6);
    }
void ax_reset_alarm (char ID,char alarm)
    {
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;   // ID
    TxBuffer[3] = 4;    // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 3;    // bInstruction;
    TxBuffer[5] = 18;   // Address
    TxBuffer[6] = alarm;   // 0= off.  1=on

    _TXsend(6);
    }
void ax_ping (char ID)
    {
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = ID;   // ID
    TxBuffer[3] = 2;    // Length(Paramter=2,Instruction=1,Checksum=1)
    TxBuffer[4] = 1;    // bInstruction;

    _TXsend(4);

    }


void go_x (int speedL, int speedR,int count)
    {
    unsigned char ID;
    static int lastSPL=0,lastSPR=0;
    //    TXD;
    if (speedL>1000)          speedL=1023;
    else if (speedL<-1000)    speedL=-1023;
    if (speedR>1000)          speedR=1023;
    else if (speedR<-1000)    speedR=-1023;

//    sprintf(text,"go(%4d,%4d)",speedL, speedR);
//    lcd_gotoxy(0,1);
//    lcd_puts(text);

    if (speedL!=lastSPL || speedR!=lastSPR)
        {
        lastSPL=speedL;lastSPR=speedR;

        if (speedL<0)   speedL=1023-speedL;
        if (speedR>0)   speedR=1023+speedR;
        if (speedR<0)   speedR=-speedR;

        for (ID=1;ID<=4;ID++)
            {
            TxBuffer[0] = 0xff;
            TxBuffer[1] = 0xff;
            TxBuffer[2] = ID;   // ID
            TxBuffer[3] = 5;  // Length(Paramter=3,Instruction=1,Checksum=1)
            TxBuffer[4] = 4;    // bInstruction;

            TxBuffer[5] = 32; // Address of speed
            if (ID==1 || ID==2)
                {
                TxBuffer[6] = speedL & 255;       // SPEED_L
                TxBuffer[7] = speedL >> 8;         // SPEED_H
                }
            else if (ID==3 || ID==4)
                {
                TxBuffer[6] = speedR & 255;       // SPEED_L
                TxBuffer[7] = speedR >> 8;         // SPEED_H
                }
            _TXsend(7);

            }
        //   Now ACTION
        TxBuffer[0] = 0xff;
        TxBuffer[1] = 0xff;
        TxBuffer[2] = 0xFE;   // ID
        TxBuffer[3] = 2+0;  // Length(Paramter,Instruction,Checksum)
        TxBuffer[4] = 5;    // bInstruction;

        _TXsend(4);
        }
    if (count>0)
        {
        //delay_ms(count*15);
        #define ENC  PINB.0
        TCNT0=0;puls_cnt=0;
        if(speedL<0 && speedR>0)// speicial condition for seting the left turn equal to right turn
            count-=2;
        while(cnt<count)
            {
            if (ENC==1)
                TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (1<<CS01) | (1<<CS00);
            if (ENC==0)
                TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (1<<CS01) | (0<<CS00);
            }
        for (ID=1;ID<=4;ID++)
            {
            TxBuffer[0] = 0xff;
            TxBuffer[1] = 0xff;
            TxBuffer[2] = ID;   // ID
            TxBuffer[3] = 5;  // Length(Paramter=3,Instruction=1,Checksum=1)
            TxBuffer[4] = 4;    // bInstruction;

            TxBuffer[5] = 32; // Address of speed
            if (ID==1 || ID==2)
                {
                TxBuffer[6] = 0;       // SPEED_L
                TxBuffer[7] = 0;         // SPEED_H
                }
            else if (ID==3 || ID==4)
                {
                TxBuffer[6] = 0;       // SPEED_L
                TxBuffer[7] = 0;         // SPEED_H
                }
            _TXsend(7);

            }
        //   Now ACTION
        TxBuffer[0] = 0xff;
        TxBuffer[1] = 0xff;
        TxBuffer[2] = 0xFE;   // ID
        TxBuffer[3] = 2+0;  // Length(Paramter,Instruction,Checksum)
        TxBuffer[4] = 5;    // bInstruction;

        _TXsend(4);
        delay_ms(5);
        lastSPL=0;lastSPR=0;
        }
    }
