//----------------------------------------------------------------------------

//RC-5 Tester - ������ ��������� LED-�������

//----------------------------------------------------------------------------

//������� ���������� 7-���������� LED-���������� � ����� ������.
//���������� ����������� ������� ���������������� ��������.
//�������� ���������� � ������ SEG_A�SEG_H, ����� ��������� -
//� ������ SCAN1�SCAN3. ������� ������������ ����������� Display_Scan()
//������ ���������� � �������������� ������������.
//��� ������ ����� ���������� � 7-����������� ����, �����������
//� ������� ������� Conv(), �������� ��������� POINT.

//----------------------------------------------------------------------------

#include "Main.h"
#include "Display.h"
#include "RC5.h"

//----------------------------- ���������: -----------------------------------

#define DIGS 4     //���������� ��������
#define MINUS 0x10 //��� ������� "�����"

//������������ ��������� �� ����������:
//
//    -- A --
//   |       |
//   F       B
//   |       |
//    -- G --
//   |       |
//   E       C
//   |       |
//    -- D --  (H)

#define _A_ 0x01
#define _B_ 0x02
#define _C_ 0x04
#define _D_ 0x08
#define _E_ 0x10
#define _F_ 0x20
#define _G_ 0x40
#define _H_ 0x80

//----------------------------- ����������: ----------------------------------

static char SegData[DIGS]; //������ ����� ��������� ����������

//-------------------------- ��������� �������: ------------------------------

char Conv(char d); //�������������� ���� ������� � 7-���������� ���

//------------ �������������� ���� ������� � 7-���������� ���: ---------------

char Conv(char d)
{
  static char __flash Font[]= //���������������� �������
  {
    _A_ | _B_ | _C_ | _D_ | _E_ | _F_,       //��� 00H, ������ "0"
    _B_ | _C_,                               //��� 01H, ������ "1"
    _A_ | _B_ | _G_ | _E_ | _D_,             //��� 02H, ������ "2"
    _A_ | _B_ | _C_ | _D_ | _G_,             //��� 03H, ������ "3"
    _F_ | _G_ | _B_ | _C_ ,                  //��� 04H, ������ "4"
    _A_ | _F_ | _G_ | _C_ | _D_,             //��� 05H, ������ "5"
    _A_ | _F_ | _G_ | _C_ | _D_ | _E_,       //��� 06H, ������ "6"
    _A_ | _B_ | _C_,                         //��� 07H, ������ "7"
    _A_ | _B_ | _C_ | _D_ | _E_ | _F_ | _G_, //��� 08H, ������ "8"
    _A_ | _B_ | _C_ | _D_ | _F_ | _G_,       //��� 09H, ������ "9"
    _A_ | _B_ | _C_ | _E_ | _F_ | _G_,       //��� 0AH, ������ "A"
    _C_ | _D_ | _E_ | _F_ | _G_,             //��� 0BH, ������ "b"
    _A_ | _D_ | _E_ | _F_,                   //��� 0CH, ������ "C"
    _B_ | _C_ | _D_ | _E_ | _G_,             //��� 0DH, ������ "d"
    _A_ | _D_ | _E_ | _F_ | _G_,             //��� 0EH, ������ "E"
    _A_ | _E_ | _F_ | _G_,                   //��� OFH, ������ "F"
    _G_                                      //��� 10H, ������ "-"
  };
  if(d > 0x0F) d = MINUS; //������ "-", ���� ����������� ���
  return(Font[d]);        //7-���������� ��� ��� �������
}

//------------------------- ������������� �������: ---------------------------

void Display_Init(void)
{
  for(char i = 0; i < DIGS; i++)
    SegData[i] = Conv(MINUS);    //������� �������
}

//------------------------- ������������ �������: ----------------------------

void Display_Exe(bool t)
{
  static char Phase = 0;
  if(t)
  {
    //���������� ���� ����-�����:
    Port_SCAN1_0;
    Port_SCAN2_0;
    Port_SCAN3_0;
    Port_SCAN4_0;
    char s = SegData[Phase];
    //��������� ������ ���������:
    (s & 0x01)? Port_SEG_A_0 : Port_SEG_A_1;
    (s & 0x02)? Port_SEG_B_0 : Port_SEG_B_1;
    (s & 0x04)? Port_SEG_C_0 : Port_SEG_C_1;
    (s & 0x08)? Port_SEG_D_0 : Port_SEG_D_1;
    (s & 0x10)? Port_SEG_E_0 : Port_SEG_E_1;
    (s & 0x20)? Port_SEG_F_0 : Port_SEG_F_1;
    (s & 0x40)? Port_SEG_G_0 : Port_SEG_G_1;
    (s & 0x80)? Port_SEG_H_0 : Port_SEG_H_1;
    //��������� ������ ����-�����:
    (Phase == 0)? Port_SCAN1_1 : Port_SCAN1_0;
    (Phase == 1)? Port_SCAN2_1 : Port_SCAN2_0;
    (Phase == 2)? Port_SCAN3_1 : Port_SCAN3_0;
    (Phase == 3)? Port_SCAN4_1 : Port_SCAN4_0;
    //��������� ���� ������������:
    if(++Phase == DIGS) Phase = 0;
  }
}

//---------------------------- ����� ��������: -------------------------------

void Display_RC5(bool t)
{
  static char sys = 0xFF;    //�������������� ��� �������
  static char com = 0xFF;    //�������������� ��� �������
  if(t)
  {
    char s = RC5_GetSys();   //������ ������ �������
    char c = RC5_GetCom();   //������ ������ �������
    if(s != sys || c != com) //���� ���� ���������, ��
    {
      sys = s;               //���������� ����� �������
      com = c;               //���������� ����� �������
      //����� �������� ������� �������:
      SegData[0] = Conv((s & 0x1F) / 16);
      //����� �������� ������� ������� � ����� (������������ ����):
      SegData[1] = Conv((s & 0x1F) % 16) + ((s & 0x20)? POINT : 0);
      //����� �������� ������� �������:
      SegData[2] = Conv(c / 16);
      //����� �������� ������� �������:
      SegData[3] = Conv(c % 16);
    }
  }
}

//----------------------------------------------------------------------------