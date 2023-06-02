//----------------------------------------------------------------------------

//RC-5 Tester - главный модуль, заголовочный файл

//----------------------------------------------------------------------------

#ifndef MainH
#define MainH

//----------------------------------------------------------------------------

#include <iom8.h>
#include <intrinsics.h>
#include <stdbool.h>

//----------------------------- Константы: -----------------------------------

#define	F_CLK 8.000  //тактовая частота, МГц
#define T_SYS 1000.0 //системный интервал, мкс

//------------------------- Описание портов: ---------------------------------

//I - вход
//O - выход
//B - двунаправленный вывод

//L - низкий активный уровень
//H - высокий активный уровень
//X - активный уровень не определен
//A - аналоговый сигнал

//------------------------------- Порт B: ------------------------------------

#define NC_PB0 (1 << PB0) //IL - не используется
#define NC_PB1 (1 << PB1) //IL - не используется
#define SEG_F  (1 << PB2) //OL - сегмент индикатора F
#define SEG_A  (1 << PB3) //OL - сегмент индикатора A
#define SCAN1  (1 << PB4) //OH - линия сканирования 1
#define SCAN2  (1 << PB5) //OH - линия сканирования 2
#define NC_PB6 (1 << PB6) //IL - не используется
#define NC_PB7 (1 << PB7) //IL - не используется

//Направление:
#define I_DDRB  (SEG_F | SEG_A | SCAN1 | SCAN2)
//Подтягивающие резисторы (in) или начальное состояние (out):
#define I_PORTB (NC_PB0 | NC_PB1 | SEG_F | SEG_A | NC_PB6 | NC_PB7)
//Макроопределения для работы с портами:
#define Port_SEG_F_0 (PORTB &= ~SEG_F)
#define Port_SEG_F_1 (PORTB |= SEG_F)
#define Port_SEG_A_0 (PORTB &= ~SEG_A)
#define Port_SEG_A_1 (PORTB |= SEG_A)
#define Port_SCAN1_0 (PORTB &= ~SCAN1)
#define Port_SCAN1_1 (PORTB |= SCAN1)
#define Port_SCAN2_0 (PORTB &= ~SCAN2)
#define Port_SCAN2_1 (PORTB |= SCAN2)

//------------------------------- Порт C: ------------------------------------

#define SCAN3  (1 << PC0) //OH - линия сканирования 3
#define SEG_B  (1 << PC1) //OL - сегмент индикатора B
#define SEG_E  (1 << PC2) //OL - сегмент индикатора E
#define SEG_D  (1 << PC3) //OL - сегмент индикатора D
#define SEG_H  (1 << PC4) //OL - сегмент индикатора H
#define SEG_C  (1 << PC5) //OL - сегмент индикатора C
#define NC_PC6 (1 << PC6) //IL - не используется

//Направление:
#define I_DDRC  (SCAN3 | SEG_B | SEG_E | SEG_D | SEG_H | SEG_C)
//Подтягивающие резисторы (in) или начальное состояние (out):
#define I_PORTC (SEG_B | SEG_E | SEG_D | SEG_H | SEG_C | NC_PC6)
//Макроопределения для работы с портами:
#define Port_SCAN3_0 (PORTC &= ~SCAN3)
#define Port_SCAN3_1 (PORTC |= SCAN3)
#define Port_SEG_B_0 (PORTC &= ~SEG_B)
#define Port_SEG_B_1 (PORTC |= SEG_B)
#define Port_SEG_E_0 (PORTC &= ~SEG_E)
#define Port_SEG_E_1 (PORTC |= SEG_E)
#define Port_SEG_D_0 (PORTC &= ~SEG_D)
#define Port_SEG_D_1 (PORTC |= SEG_D)
#define Port_SEG_H_0 (PORTC &= ~SEG_H)
#define Port_SEG_H_1 (PORTC |= SEG_H)
#define Port_SEG_C_0 (PORTC &= ~SEG_C)
#define Port_SEG_C_1 (PORTC |= SEG_C)

//------------------------------- Порт D: ------------------------------------

#define SEG_G  (1 << PD0) //OL - сегмент индикатора G
#define SCAN4  (1 << PD1) //OH - линия сканирования 4
#define RC5    (1 << PD2) //IH - вход декодера RC-5
#define NC_PD3 (1 << PD3) //IL - не используется
#define NC_PD4 (1 << PD4) //IL - не используется
#define NC_PD5 (1 << PD5) //IL - не используется
#define LED    (1 << PD6) //OH - выход светодиода
#define NC_PD7 (1 << PD7) //IL - не используется

//Направление:
#define I_DDRD  (SEG_G | SCAN4 | LED)
//Подтягивающие резисторы (in) или начальное состояние (out):
#define I_PORTD (SEG_G | RC5 | NC_PD3 | NC_PD4 | NC_PD5 | NC_PD7)
//Макроопределения для работы с портами:
#define Port_SEG_G_0 (PORTD &= ~SEG_G)
#define Port_SEG_G_1 (PORTD |= SEG_G)
#define Port_SCAN4_0 (PORTD &= ~SCAN4)
#define Port_SCAN4_1 (PORTD |= SCAN4)
#define Pin_RC5      (PIND & RC5)
#define Port_LED_0   (PORTD &= ~LED)
#define Port_LED_1   (PORTD |= LED)

//-------------------------- Макроопределения: -------------------------------

#define HI(x) ((x >> 8) & 0xFF)
#define LO(x) (x & 0xFF)
#define WORD(lo, hi) (((unsigned int)hi << 8) | lo)
#define Delay_us(x) __delay_cycles(x * FCLK + 0.5)
#define ms2sys(x) (1E3 * x / TSYS)

//----------------------------------------------------------------------------

#endif
