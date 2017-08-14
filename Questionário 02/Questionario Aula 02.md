1. Quais as diferenças entre os barramentos de dados e de endereços?
 - O barramento de dados é o barramento por onde entrará os dados do usuário. Já o barramento de endereço é o que irá selecionar o endereço que o dado será escrito.
 
2. Quais são as diferenças entre as memórias RAM e ROM?
 - A memória RAM é uma memória de acesso randômico, usada para processar os dados e que não deixa o conteúdo gravado após ser desligada. Já a memória ROM é uma memória não-volátil, usada para armazenar informações que não podem ser perdidas e que serão acessadas mais adiante. Na questão da velocidade a memória RAM é mais rápida que a memória ROM.
3. Considere o código abaixo:

```C
#include <stdio.h>
int main(void)
{
	int i;
	printf("Insira um número inteiro: ");
	scanf("%d", &i);
	if(i%2)
		printf("%d eh impar.\n");
	else
		printf("%d eh par.\n");
	return 0;
}
```

Para este código, responda: (a) A variável `i` é armazenada na memória RAM ou ROM? Por quê? (b) O programa compilado a partir deste código é armazenado na memória RAM ou ROM? Por quê?

 - (A) É armazenada na memória RAM, porque é apenas um dado que será processado de acordo com o programa, e que será apagado da memória para dar espaço a outros tipos de informação.
 - (B) O programa é armazenado na memória ROM, porque é na memória ROM que os programas compilados devem ficar pela sua não-volaticidade. Caso ele fique na memória RAM ao desligar a aplicação o programa será perdido.

4. Quais são as diferenças, vantagens e desvantagens das arquiteturas Harvard e Von Neumann?
 - A arquitetura Harvard possui memória de dados e de programa separadas, assim fazendo com que uma aplicação que rode com uma arquitetura Harvard seja consideravelmente mais rápida. Já a arquitetura Von Neumann possui a memória de dados e de programa em um único bloco, assim fazendo com que seja mais lenta do que a arquitetura Harvard.
 
5. Considere a variável inteira `i`, armazenando o valor `0x8051ABCD`. Se `i` é armazenada na memória a partir do endereço `0x0200`, como ficam este byte e os seguintes, considerando que a memória é: (a) Little-endian; (b) Big-endian.
 - (A) 0x0200, 0x2001, 0x2002, 0x2003
       | CD  |   AB  |   51  |  80  |.
 - (B) 0x0200, 0x2001, 0x2002, 0x2003
       |  80  |  51  |	 AB  |  CD  |.
	 
6. Sabendo que o processador do MSP430 tem registradores de 16 bits, como ele soma duas variáveis de 32 bits?
 - Cada uma das variáveis ocupará dois registradores, e mais um par de registradores irá receber o resultado da soma enter esses dois números de 32 bits
