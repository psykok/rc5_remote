//----------------------------------------------------------------------------

//RC-5 Tester - ������ ��������� LED-�������, ������������ ����

//----------------------------------------------------------------------------

#ifndef DisplayH
#define DisplayH

//----------------------------- ���������: -----------------------------------

#define POINT 0x80        //����������� �����

//-------------------------- ��������� �������: ------------------------------

void Display_Init(void);  //������������� �������
void Display_Exe(bool t); //������������ �������
void Display_RC5(bool t); //����� ��������

//----------------------------------------------------------------------------

#endif