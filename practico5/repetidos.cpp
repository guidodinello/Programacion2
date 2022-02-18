#include <stdio.h>

bool repetidos(int *a, int n) {
	bool aux[n];
	for (int i=0;i<n;i++)
		aux[i]=false;
	int j;
	for (j=0;j<n && aux[a[j]]==false;j++)
		aux[a[j]]=true;
	return j==n;
}

bool inversos(int *a, int *b, int n) {
	int i;
	for (i=0;i<n && a[i]==b[n-1-i]; i++);
	return i==n;
}

int main() {
	int arr[5] = {2,1,0,3,4};
	int arr2[5] = {4,3,0,1,2};

	if (repetidos(arr,5)) printf("no hay repetidos\n");
	else printf("hay repetidos\n");  

	if (inversos(arr,arr2,5)) printf("son inversos\n");
	else printf("no son inversos\n");  
}