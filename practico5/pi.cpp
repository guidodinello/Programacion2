#include <stdio.h>

double aprox_pi(int n) {
	double acum = 0;
	int sg = 1;
	for (int i = 0; i < n; i++) {
		acum = acum + sg * (4.0 / (2*i + 1));
		sg = sg * (-1);
	}
	return acum;
}

int main () {
	int op;
	printf("Nro de terminos de la reducida enesima para aproximar : ");
	scanf("%i",&op);

	printf("pi ≃ %f\n",aprox_pi(op));
}