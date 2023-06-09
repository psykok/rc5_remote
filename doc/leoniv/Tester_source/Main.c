//----------------------------------------------------------------------------

//Project:  RC-5 Tester - ������� ������
//Compiler: IAR EWAVR 4.21A
//Target:   ATmega8

//----------------------------------------------------------------------------

//Fuses:

//SPI Enable
//Int RCosc, Frequency 8MHz
//Startup: 64 ms + 6 CK,
//No BOD function

//WDTON = 1, OCDEN = 1, SPIEN = 0, EESAVE = 1,
//BOOTSZ = 00, BOOTRST = 1, CKOPT = 1,
//BODLEVEL = 1, BODEN = 1, CKSEL = 0100, SUT = 10

//----------------------------------------------------------------------------

#include "Main.h"
#include "Display.h"
#include "RC5.h"

//----------------------------- ����������: ----------------------------------

volatile bool fTick;               //���� ���������� ���������� �������
static bool tick;                  //���� ������ ������ ���������� ���������

//-------------------------- ��������� �������: ------------------------------

void main(void);                   //�������� ���������
void Main_Wdt_Init(void);          //������������� watchdog-�������
void Main_Rst_Wdt(bool t);         //������� watchdog-�������
void Main_Ports_Init(void);        //������������� ������
void Main_Timer_Init(void);        //������������� ���������� �������
bool Main_GetTick(void);           //����� ���������� �������
#pragma vector = TIMER1_COMPA_vect
__interrupt void Timer(void);      //���������� ���������� �������

//----------------------------------------------------------------------------
//-------------------------- �������� ���������: -----------------------------
//----------------------------------------------------------------------------

void main(void)
{
  Main_Wdt_Init();                 //������������� watchdog �������
  Main_Ports_Init();               //������������� ������
  Main_Timer_Init();               //������������� ���������� �������
  Display_Init();                  //������������� �������
  RC5_Init();                      //������������� ������ �������� RC-5
  __enable_interrupt();            //���������� ����������

  while(1)                         //�������� ����
  {
    tick = Main_GetTick();         //����� ���������� �������
    Display_Exe(tick);             //������������ �������
    Display_RC5(tick);             //����� ��������
    Main_Rst_Wdt(tick);            //������� watchdog-�������
  }
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//--------------------- ������������� watchdog-�������: ----------------------

void Main_Wdt_Init(void)
{
  WDTCR = (1<<WDCE) | (1<<WDE);    //���������� watchdog-�������,
  WDTCR = (1<<WDE) | (1<<WDP2);    //�������� 260 ��
  __watchdog_reset();
}

//------------------------ ������� watchdog-�������: -------------------------

void Main_Rst_Wdt(bool t)
{
  if(t)                            //���� ����� ��������� ��������,
    __watchdog_reset();            //������� watchdog-�������
}

//------------------------- ������������� ������: ----------------------------

void Main_Ports_Init(void)
{
  DDRB  = I_DDRB;
  PORTB = I_PORTB;
  DDRC  = I_DDRC;
  PORTC = I_PORTC;
  DDRD  = I_DDRD;
  PORTD = I_PORTD;
}

//------------------ ������������� ���������� ������� ------------------------

void Main_Timer_Init(void)
{
  TCCR1A = 0;
  //����� ������� 1: CTC, CK/1
  TCCR1B = (1 << WGM12) | (1 << CS10);
  OCR1A = (F_CLK * T_SYS) - 1;     //�������� �������� ���������
  TIFR = (1 << OCF1A);             //����� ���������� ����������
  TIMSK |= (1 << OCIE1A);          //���������� ���������� �� ����������
  fTick = 1;                       //�������������� ����������
}

//--------------------- �������� ���������� �������: -------------------------

__monitor bool Main_GetTick(void)
{
  if(!fTick) return(0);            //�������� ������ ���������� ���������
  fTick = 0;                       //������� �����
  return(1);                       //����� ��������� ��������
}

//------------------- ���������� ���������� �������: -------------------------

#pragma vector = TIMER1_COMPA_vect
__interrupt void Timer(void)
{
  fTick = 1;                       //����� ��������� ��������
}

//----------------------------------------------------------------------------

