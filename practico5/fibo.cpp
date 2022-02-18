#include <stdio.h>

//iterativo O(n) n= 1 000 000 tarda 4 sg.
int fibo(int n) {
	if (n==0) return 0;
	else if (n==1) return 1;
	else {
		int ant_ant = 0;
		int ant = 1;
		int res = 0;
		for (int i=1;i<n;i++) {
			res = ant + ant_ant;
			ant_ant = ant;
			ant = res;
		}
		return res;
	}
}

//recursivo O(2^n) n=40 tarda como 5 sg.
int fibor(int n) {
	if (n==0) return 0;
	else if (n==1) return 1;
	else return fibor(n-1) + fibor(n-2);
}

int main() {
	int n;
	printf("Inserte un nro para calcular su termino de fibonacci: "); 
	scanf("%i",&n);
	printf("fibonacci(%i) = %i \n",n,fibo(n));
}