#include <stdio.h>


void imp(int n, int* a) {
	for (int i=0;i<n;i++)
		printf("%i, ",a[i]);
	printf("\n");
}

int* insertSort(int* a, int n)
{
	int *res = new int[n];
	int j;

	for(int i = 0 ; i < n ; i++)
	{
		int val = a[i];
		for ( j = i - 1; j >= 0 && a[j] > val; j--)
			res[j + 1] = res[j];	
		res[j+1] = val;
	}
	return res;
}


int main() {
	int arr[3] = {3,4,2};
	int n = 3;

	imp(3,arr);
	int *arr_sol = insertSort(arr,3);
	imp(3,arr_sol);
}