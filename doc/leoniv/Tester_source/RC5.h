//----------------------------------------------------------------------------

//������� RC-5, ������������ ����

//----------------------------------------------------------------------------

#ifndef RC5H
#define RC5H

//-------------------------- ��������� �������: ------------------------------

void RC5_Init(void);   //������������� ������ ��������
void RC5_Exe(bool s);  //��������� ��������� ����
char RC5_GetSys(void); //������ ������ �������
char RC5_GetCom(void); //������ ���� �������

//----------------------------------------------------------------------------

#endif