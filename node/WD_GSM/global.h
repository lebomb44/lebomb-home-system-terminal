/****************************************************************************
 Titre	:   Parametres globaux
 Auteur:    LeBomb
 Date:      02/09/2004
 Software:  WinAVR
 Cible:     Microcontroleur Atmel AT90S4414/8515/Mega

 DESCRIPTION
       Definit et declare tous les parametres globaux relatifs a l'application
 UTILISATION
       Definir la valeur du QUARTZ
	   Choix du microcontroleur utilise:
		   librairy <avr/iomXX.h>
		   dans le makefile MCU = atmegaXX
*****************************************************************************/

#ifndef _GLOBAL_
#define _GLOBAL_

typedef unsigned char  u08;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed char  s08;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

#define QUARTZ 8000 // frequence du quartz en KHz, sert pour les fonctions d'attente

#define GCC33

// includes generaux
#include <avr/io.h>
#include <avr/iom8.h>  // definition du processeur
#include <avr/interrupt.h>
//#include <avr/signal.h>
#include <stdlib.h>

#define extr16_08_0(i) (*(char *)(&i))
#define extr16_08_1(i) (*((char *)(&i)+1))

#define extr32_16_0(i) (*(int *)(&i)) // poids faible
#define extr32_16_1(i) (* (((int *)(&i)) +1)) //poids fort
#define extr32_16_23(i) (*((int *)((char *)(&i)+1))) // les 2 octets du milieu

#define extr32_08_0(i) (*(char *)(&i))
#define extr32_08_1(i) (*((char *)(&i)+1))
#define extr32_08_2(i) (*((char *)(&i)+2))
#define extr32_08_3(i) (*((char *)(&i)+3))

#define sbi(reg,bit) { reg = reg |   (1<<bit) ; }
#define cbi(reg,bit) { reg = reg & (~(1<<bit)); }
#define nop() __asm__ __volatile__ ("NOP");
#define rien() __asm__ __volatile__ (" ");
#define sleep() __asm__ __volatile__ ("SLEEP");

#endif
