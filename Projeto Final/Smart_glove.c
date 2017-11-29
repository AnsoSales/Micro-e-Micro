#include <msp430g2553.h>
#define CANAIS_ADC 6

unsigned int amostras[CANAIS_ADC];
unsigned int POLEGAR, MEDIO, MINDINHO, INDICADOR;

// Acelerômetro
unsigned char RX_Data[6];
unsigned char TX_Data[2];
unsigned char RX_ByteCtr;
unsigned char TX_ByteCtr;
int xAccel;
int sel_xAccel;
int yAccel;
int sel_yAccel;
int zAccel;
int sel_zAccel;
unsigned char slaveAddress = 0x68;    // Seta endereço para a MPU-6050
                   // 0x68 para ADD pin=0
                   // 0x69 para ADD pin=1

const unsigned char PWR_MGMT_1   = 0x6B;    // MPU-6050 registrador de endereço
const unsigned char ACCEL_XOUT_H = 0x3B;    // MPU-6050 registrador de endereço
const unsigned char ACCEL_XOUT_L = 0x3C;    // MPU-6050 registrador de endereço
const unsigned char ACCEL_YOUT_H = 0x3D;    // MPU-6050 registrador de endereço
const unsigned char ACCEL_YOUT_L = 0x3E;    // MPU-6050 registrador de endereço
const unsigned char ACCEL_ZOUT_H = 0x3F;    // MPU-6050 registrador de endereço
const unsigned char ACCEL_ZOUT_L = 0x40;    // MPU-6050 registrador de endereço

//Funções do Acelerômetro

void i2cInit(void);
void i2cWrite(unsigned char);
void i2cRead(unsigned char);
void coleta_valores_mpu(void);
int coleta_valores_MPU(int sel_xAccel,int sel_yAccel,int sel_zAccel);

void ConfigureAdc(void)

   {

      ADC10CTL1 |= INCH_5 + CONSEQ_3 + ADC10SSEL_3;// tamanho 6, multiplas conversões sucessivas, modo de conversão de multi canais
      ADC10CTL0 |= SREF_0 + ADC10SHT_0 + MSC + ADC10ON + ADC10IE;
      ADC10AE0 |= BIT5 +BIT4+BIT3+BIT0;// bits correspondentes a cada pino da MSP
      ADC10DTC1 = CANAIS_ADC; //4 canais
      ADC10CTL0 |= ENC + ADC10SC; // inicializa a conversão
   }

void main(void)
{
   WDTCTL = WDTPW + WDTHOLD;                   //Parar o WDT
// clock de 1Mhz
DCOCTL = 0;
BCSCTL1 = CALBC1_1MHZ;
DCOCTL = CALDCO_1MHZ;

P1SEL |= BIT1 + BIT2 + BIT6 + BIT7; //P1.1TX e P1.2RX
P1SEL2 |= BIT1 + BIT2+ BIT6 + BIT7;
P1DIR &=~BIT2;
P1DIR &=~BIT1;
// setar a baud rate para 9800bps
UCA0CTL1 |= UCSSEL_2;
UCA0BR0 = 104;
UCA0BR1 = 0;
UCA0MCTL = UCBRS0;
UCA0CTL1 &= ~UCSWRST;
ConfigureAdc(); // configura o adc

while (1)
{
   // carrega as amostras para as variáveis correspondentes a cada dedo.
   POLEGAR = amostras[0];
   INDICADOR = amostras[1];
   MEDIO = amostras[2];
   MINDINHO = amostras[5];
       ADC10CTL0 &= ~ENC; // Encerra a conversão AD
       while (ADC10CTL1 & BUSY); // garante que o conversor AD não esteja ocupado para iniciar novas conversões
       ADC10SA = (unsigned int)amostras; // ADC10SA recebe o endereço da variável amostra, que no fim receberá também os valores da conversão AD
       ADC10CTL0 |= ENC + ADC10SC;

    __bis_SR_register(CPUOFF + GIE);
//Coleta os Valores do MPU, Acelerometro
       sel_xAccel=1;
       sel_yAccel=0;
       sel_zAccel=0;
       xAccel = coleta_valores_MPU(sel_xAccel,sel_yAccel,sel_zAccel);

       sel_xAccel=0;
       sel_yAccel=1;
       sel_zAccel=0;
       yAccel = coleta_valores_MPU(sel_xAccel,sel_yAccel,sel_zAccel);

       sel_xAccel=0;
       sel_yAccel=0;
       sel_zAccel=1;
       zAccel = coleta_valores_MPU(sel_xAccel,sel_yAccel,sel_zAccel);

//Logica de saída para as letras

   if  ( (POLEGAR >490) && (INDICADOR < 300)&&(MEDIO < 200 ) &&(MINDINHO< 200))
   {
     UCA0TXBUF = 'A';
   }
   else if ( (POLEGAR < 360) && (INDICADOR > 400)&&(MEDIO > 319) && (MINDINHO > 400))
   {
     UCA0TXBUF = 'B';
   }
   else if ( (POLEGAR > 490) && ((INDICADOR >= 300) && (INDICADOR <= 400)) && ((MEDIO >= 200) && (MEDIO  <= 319)) &&((MINDINHO <= 400) && (MINDINHO >= 200)) && (xAccel < 0) )
   {
     UCA0TXBUF = 'C';
   }
   else if ( ((POLEGAR >= 360 && POLEGAR<=490)) && (INDICADOR > 400) && ((MEDIO >= 200) && (MEDIO  <= 319)) &&((MINDINHO <= 400) && (MINDINHO >= 200)))
   {
     UCA0TXBUF = 'D';
   }
   else if ( (POLEGAR < 360) && (INDICADOR < 300)&& (MEDIO < 200 ) &&(MINDINHO< 200) && (xAccel > 0))
   {
     UCA0TXBUF = 'E';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && ((INDICADOR >= 300) && (INDICADOR <= 400)) && (MEDIO > 319) &&(MINDINHO > 400) && (xAccel > 0) )
   {
     UCA0TXBUF = 'F';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR > 400) && (MEDIO < 200 ) &&(MINDINHO< 200))
   {
     UCA0TXBUF = 'G';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR > 400) &&(((MEDIO >= 200) && (MEDIO  <= 319))) &&(MINDINHO< 200) && (xAccel < 0) && (yAccel< 0) && (zAccel< 0))
   {
     UCA0TXBUF = 'H'; //USAR O GIROSCOPIO PARA DIFERENCIAR
   }
   else if ( (POLEGAR < 360) && (INDICADOR < 300) && (MEDIO < 200 ) &&(MINDINHO > 400))
   {
     UCA0TXBUF = 'I';
   }
   else if ( (POLEGAR < 360) && (INDICADOR < 300) && (MEDIO < 200 ) &&((MINDINHO <= 400) && (MINDINHO >= 200)))
   {
     UCA0TXBUF = 'J';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR< 300) &&((MEDIO >= 200) && (MEDIO  <= 319)) &&(MINDINHO< 200))
   {
     UCA0TXBUF = 'K'; // USAR O GIROSCOPIO PARA DIFERENCIAR
   }
   else if ( (POLEGAR > 490) && (INDICADOR > 400) && (MEDIO < 200 ) &&(MINDINHO< 200))
   {
     UCA0TXBUF = 'L';
   }
   else  if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR > 400) && (MEDIO > 319) &&(MINDINHO< 200) && (yAccel < 0) && (zAccel < 0))
   {
     UCA0TXBUF = 'M';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR > 400) && (MEDIO > 319) &&(MINDINHO< 200) && (yAccel > 0) && (zAccel > 0))
   {
     UCA0TXBUF = 'N';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && ((INDICADOR >= 300) && (INDICADOR <= 400)) &&((MEDIO >= 200) && (MEDIO  <= 319)) && ((MINDINHO <= 400) && (MINDINHO >= 200)))
   {
     UCA0TXBUF = 'O';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR > 400)&& ((MEDIO >= 200) && (MEDIO  <= 319)) &&(MINDINHO< 200) && (xAccel < 0) && (yAccel > 0) && (zAccel > 0))
   {
     UCA0TXBUF = 'P'; // USAR O GIROSCOPIO PARA DIFRENCIAR
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR > 400) && (MEDIO < 200 ) && (MINDINHO< 200))
   {
     UCA0TXBUF = 'Q';
   }
   else if ( (POLEGAR < 360) && (INDICADOR > 400) && ((MEDIO > 264) && (MEDIO  <= 380)) &&(MINDINHO< 200))
   {
     UCA0TXBUF = 'R';
   }
   else if ( (POLEGAR < 360) && (INDICADOR < 300) && (MEDIO < 200 ) && (MINDINHO< 200) && (xAccel < 0))
   {
     UCA0TXBUF = 'S';
   }
   else if ( (POLEGAR >= 360 && POLEGAR<=490) && (INDICADOR < 300)&& (MEDIO > 319) &&(MINDINHO > 400)  && (xAccel < 0))
   {
     UCA0TXBUF = 'T';
   }
   else if ( (POLEGAR < 360) && (INDICADOR > 400) && (MEDIO > 319) && (MINDINHO< 200) && (xAccel < 0) && (yAccel< 0) && (zAccel< 0))
   {
     UCA0TXBUF = 'U';
   }
   else if ((POLEGAR < 360) && (INDICADOR > 400) && (MEDIO > 319) &&(MINDINHO< 200) && (xAccel > 0) && (yAccel < 0 ) && (zAccel < 0))
   {
     UCA0TXBUF = 'V';
   }
   else if ( (POLEGAR < 360) && ((INDICADOR >= 300) && (INDICADOR <= 400))&&(MEDIO < 200 ) &&(MINDINHO< 200))
   {
     UCA0TXBUF = 'X';
   }
   else if ((POLEGAR < 360) && (INDICADOR > 400) && (MEDIO > 319) &&(MINDINHO > 400)  && (xAccel < 0) && (yAccel > 0) && (zAccel > 0))
   {
     UCA0TXBUF = 'W';
   }
   else if ( (POLEGAR > 490) && (INDICADOR < 300)&& (MEDIO < 200 ) && (MINDINHO > 400))
   {
     UCA0TXBUF = 'Y';
   }
   else if ((POLEGAR < 360) && (INDICADOR > 400) && (MEDIO < 200 ) &&(MINDINHO< 200))
   {
     UCA0TXBUF = 'Z';
   }
   else if ( (POLEGAR > 490) && ((INDICADOR <= 670) && (INDICADOR > 498)) && ((MEDIO >= 200) && (MEDIO  <= 319)) && ((MINDINHO <= 400) && (MINDINHO >= 200))  && (xAccel > 0))
   {
     UCA0TXBUF = 'Ç';
   }
  else {
     UCA0TXBUF = '.';
   }

 }

}
#pragma vector = ADC10_VECTOR    //Interrupção do ADC
__interrupt void ADC10_ISR(void)
{
   UCA0TXBUF = 0x00; //escreve 0 no TXBUF para evitar que a conversão AD jogue algum lixo aqui.

 __bic_SR_register_on_exit(CPUOFF);
}

void i2cInit(void)
{
   // set up I2C module
   UCB0CTL1 |= UCSWRST;                // Habilita reset SW
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;            // I2C Master, modo síncrono
   UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
   UCB0BR0 = 10;                    // fSCL = SMCLK/12 = ~100kHz
   UCB0BR1 = 0;
   UCB0CTL1 &= ~UCSWRST;                // Clear SW reset, resume operation
}

void i2cWrite(unsigned char address)
{
   //__disable_interrupt();
   UCB0I2CSA = address;                // Carregar endereço do escravo
   IE2 |= UCB0TXIE;                // Habilita a interrupção do TX
   while(UCB0CTL1 & UCTXSTP);            // garante que a condição de parada seja mandada
   UCB0CTL1 |= UCTR + UCTXSTT;            // modo TX e condição de start
   __bis_SR_register(CPUOFF + GIE);        // dorme enquanto UCB0TXIFG é setado
}

void i2cRead(unsigned char address)
{
   __disable_interrupt();
   UCB0I2CSA = address;                // Carregar endereço do escravo
   IE2 |= UCB0RXIE;                // Habilita a interrupção do RX
   while(UCB0CTL1 & UCTXSTP);            // garante que a condição de parada seja mandada
   UCB0CTL1 &= ~UCTR;                // modo RX
   UCB0CTL1 |= UCTXSTT;                // Condição de Start
   __bis_SR_register(CPUOFF + GIE);        // dorme enquanto UCB0RXIFG é setado
}
// USCIAB0TX_ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
   if(UCB0CTL1 & UCTR)                    // modo TX (UCTR == 1)
   {
       if (TX_ByteCtr)                        // Verdadeiro se tiver bytes
       {
           TX_ByteCtr--;                // Decrementa RX_ByteCtr
           UCB0TXBUF = TX_Data[TX_ByteCtr];    // Carrega o TX buffer
       }
       else                        // nenhum byte para mandar
       {
           UCB0CTL1 |= UCTXSTP;            // I2C stop condition
           IFG2 &= ~UCB0TXIFG;            // Limpar a flat int USCI_B0 TX
           __bic_SR_register_on_exit(CPUOFF);    // Sair do LPM0
       }
   }
   else // (UCTR == 0)                    // modo RX
   {
       RX_ByteCtr--;                        // Decrementa RX_ByteCtr
       if (RX_ByteCtr)                        // RxByteCtr != 0
       {
           RX_Data[RX_ByteCtr] = UCB0RXBUF;    // gravar o byte recebido
           if (RX_ByteCtr == 1)            // Apenas um byte sobrando?
           UCB0CTL1 |= UCTXSTP;            // Gerar uma condição de parada para I2C
       }
       else                        // RxByteCtr == 0
       {
           RX_Data[RX_ByteCtr] = UCB0RXBUF;    // Pegar o último bit recebido
           __bic_SR_register_on_exit(CPUOFF);    // Sair do LPM0
       }
   }
}

int coleta_valores_MPU(int sel_xAccel,int sel_yAccel,int sel_zAccel){



       // Inicializa a I2C
    i2cInit();

    // Acorda the MPU-6050
    slaveAddress = 0x68;                    // Endereço da MPU-6050
    TX_Data[1] = 0x6B;                        // Endereço do registrador PWR_MGMT_1
    TX_Data[0] = 0x00;                        // Setar o registrador para 0 (acorda a MPU-6050)
    TX_ByteCtr = 2;
    i2cWrite(slaveAddress);


        // apontar para o registrador ACCEL_ZOUT_H na MPU-6050
        slaveAddress = 0x68;                    // Endereço da MPU-6050
        TX_Data[0] = 0x3B;
        TX_ByteCtr = 1;
        i2cWrite(slaveAddress);

        // Lê os dois bytes do data e armazena eles nos eixos
        slaveAddress = 0x68;                    // Endereço da MPU-6050
        RX_ByteCtr = 6;
        i2cRead(slaveAddress);
        xAccel  = RX_Data[5] << 8;                // MSB
        xAccel |= RX_Data[4];                    // LSB
        yAccel  = RX_Data[3] << 8;                // MSB
        yAccel |= RX_Data[2];                    // LSB
        zAccel  = RX_Data[1] << 8;                // MSB
        zAccel |= RX_Data[0];                    // LSB



        __no_operation();                       // Setar o breakpoint >>aqui<< e ler

       //Lógica para retorno de valor da função
       if((sel_xAccel==1) && (sel_yAccel==0) && (sel_zAccel==0)){
       return xAccel;
       }
       else if((sel_xAccel==0) && (sel_yAccel==1) && (sel_zAccel==0)){
       return yAccel;
       }
       else if((sel_xAccel==0) && (sel_yAccel==0) && (sel_zAccel==1)){
       return zAccel;
       }


return 0;
}
