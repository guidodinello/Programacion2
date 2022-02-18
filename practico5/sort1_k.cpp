#include <stdio.h>

void imp(int *a,int n) {
	printf("[ ");
	for (int i=0;i<n;i++)
		printf("%i ",a[i]);
	printf("]\n");
}

void sort1_k(int *a, int n, int k) { 
//ordena un arreglo de tamano n, que posee elemntos en el rango 1..k
	int *cuenta = new int[k];
	for (int i=0;i<k;i++) cuenta[i]=0;
	for (int i=0;i<n;i++) cuenta[a[i]-1]=cuenta[a[i]-1]+1;
	int pos = 0;
	for (int i=1;i<=k;i++) //se mueve por cuenta[]
		for (int j=0;j<cuenta[i-1];j++) { //se mueve por a[]
			a[pos]=i;
			pos = pos + 1;
		}

}

int main() {
	int arr[9]={1,4,2,4,3,7,3,2,6};

	sort1_k(arr,9,7);
	imp(arr,9);
}