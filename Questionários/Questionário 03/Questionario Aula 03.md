1. Dada uma variável `a` do tipo `char` (um byte), escreva os trechos de código em C para:
	(a) Somente setar o bit menos significativo de `a`.
	 - A = A + BIT0; 
	 
	(b) Somente setar dois bits de `a`: o menos significativo e o segundo menos significativo.	
	 - A = A + (BIT0+BIT1);
	   
	(c) Somente zerar o terceiro bit menos significativo de `a`.
	 - A &= ~(BIT0+BIT1);
	 
	(d) Somente zerar o terceiro e o quarto bits menos significativo de `a`.
	 - A &= ~(BIT3+BIT2);
	 
	(e) Somente inverter o bit mais significativo de `a`.
	 - A = A ^= (BIT3 + BIT5 +BIT8);
	 
	(f) Inverter o nibble mais significativo de `a`, e setar o nibble menos significativo de `a`. 
         - A ^= (BIT9=BIT6);
	   A = (BIT4 +BIT2 + BIT0);
	   
2. Considerando a placa Launchpad do MSP430, escreva o código em C para piscar os dois LEDs ininterruptamente.
 
    ```C	
 	#include <msp430g2553.h>
	#define LED1 BIT0
	#define LED2 BIT6
	#define SAIDA (LED1|LED2)
	
		int segs;
		int main(void)
			{
				WDTCTL = WDTPW | WDTHOLD;
				P1DIR = SAIDA;
				
				while (1)
				{
				 P1OUT = SAIDA;	
				 __delay_cycles(1000000)
				 P1OUT = 0;
				 __delay_cycles(1000000);
				
				}
			}```
			
3. Considerando a placa Launchpad do MSP430, escreva o código em C para piscar duas vezes os dois LEDs sempre que o usuário pressionar o botão.
 
    ```C
		#include <msp430.h>
		#include <msp430g2553.h>
		#define LED1 BIT0
		#define LED2 BIT6
		#define SAIDA (LED1|LED2)
		#define botao BIT3
		/**
		* main.c
		*/
		int main(void)
		{
			WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
			P1DIR |= SAIDA;
			P1OUT |= SAIDA;
			P1DIR &= ~botao;
			P1REN |= botao;
			P1OUT |= botao;
			while (1)

		 {
		   if ((P1IN & botao) == 0 )
		   {
			P1OUT = SAIDA + botao;
			__delay_cycles(1000000);
			P1OUT &= ~SAIDA;
			__delay_cycles(1000000);
			P1OUT = SAIDA + botao;
			__delay_cycles(1000000);
			P1OUT &= ~SAIDA;
		    }else{
		 	P1OUT &= ~SAIDA;
		    }
		  }
		}
```
4. Considerando a placa Launchpad do MSP430, faça uma função em C que pisca os dois LEDs uma vez.

	```C
	    void pisca(P1OUT,segs,SAIDA)
		       {
			 for(segs = 0; segs=100000; segs++)
			 {
			 P1OUT = SAIDA;	
			 }
			 for(segs = 0; segs=100000; segs++)
			 {
			 P1OUT = 0;
			 }
			}
		      }```
 	
5. Reescreva o código da questão 2 usando a função da questão 4.
 -
6. Reescreva o código da questão 3 usando a função da questão 4.
 -
