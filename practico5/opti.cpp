#include <stdio.h>
//--------------------------------//
bool F(int *A,int n){  //O(n²)
	bool b = false;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			b=b||(A[i]==A[j]&&i!=j);
	return b;
}
bool F(int *A,int n){  //O(n²) 
//no se puede lograr en menor orden dado que el nro de cn es de orden (n²)
	
	cn = ((n-1)n)/2; //comparaciones_necesarias
	bool igualdades[cn];
	for (int i=0; i<cn; i++) igualdades[i]=false;
	int pos = 0;
	int b = true;
	for (int i=n; i>=1 && b; i--)
		for (int j=n-1; j>=0 && b; j--) {
			igualdades[pos] = A[i]==A[j];
			b = igualdades[pos];			
			pos = pos + 1;
		}
	return b;
}
bool F(int *A,int n){ //asumiendo arreglo ordenado de menor a mayor

}

//--------------------------------//
//--------------------------------//
bool F2(int *A,int n){ //O(n²)
	bool b = true;
	for(int i=0;i<n;i++)
		for(int j=n-1;j> -1;j--) {
			b=b && (A[i]==A[j]);
		}
	return b;
}
//optimizacion
bool F2(int *A,int n){  //O(n)
	int val = a[0];
	for (int i=i; i<n && a[i]==val; i++);
	return i==n;
}
//--------------------------------//

int main() {
	int A[3] = {0,1,2};
	if (F(A,3))
		printf("hay repetidos\n");
	else printf("no hay repetidos\n");
printf("\n");
	if (F2(A,3))
		printf("todos iguales\n");
	else printf("no todos iguales\n");


}
