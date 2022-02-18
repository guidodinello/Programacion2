#include <stdio.h>

/* O(logn)
x^n = (x*x)^(n/2),   si n es par
x^n = x*(x*x)^(n/2), si n es impar
*/

unsigned int potencia(unsigned i,unsigned int x) { //devuelve x^i costo O(log n)
	if (i == 0) return 1;
	else if (i%2==0) return potencia(i/2,x*x);
	else return x*potencia(i/2,x*x);
}

int potencia_r(int i,int x) { //devuelve x^i
	if (i == 1) return x;
	else if (i%2==0) {
		int res = potencia(i/2,x);
		return res * res;
	} else {
		int res = potencia(i-1,x);
		return x * res;
	}
}

int main() {
	unsigned int b,exp;
	printf("inserte base: ");
	scanf("%i",&b);
	printf("\n");
	printf("inserte exponente: ");
	scanf("%i",&exp);
	printf("\n");

	printf("resultado = %i \n",potencia(exp,b));
}