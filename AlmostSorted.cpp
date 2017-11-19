#include<stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	int arr[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	// find the first inversion
	int inv1 = -1, inv2 = -1, invElem1, invElem2;
	int i;
	
	for (i = 0; i < n - 1; i++)
	{
		if (arr[i + 1] < arr[i])
		{
			inv1 = i;
			invElem1 = arr[i];
			break;
		}
	}
	
	if (inv1 == -1)
	{
		printf("yes");
		return 0;
	}
	
	// find the expected end of inversion
	for (; i < n; i++)
	{
		if (arr[i] > invElem1)
		{
			inv2 = i - 1;
			invElem2 = arr[i - 1];
			break;
		}
	}
	
	if (inv2 == -1)
	{
		// must be end of the array
		inv2 = n - 1;
		invElem2 = arr[n - 1];
	}
	
	// validate increasing or decreasing of inversion range
	int isDecreasing = 1;
	for (i = inv1 + 1; i < (inv2 - 1); i++)
	{
		if (arr[i] < arr[i + 1])
		{
			isDecreasing = 0;
			break;
		}
	}
	
	int isIncreasing = 1;
	for (i = inv1 + 1; i < (inv2 - 1); i++)
	{
		if (arr[i] > arr[i + 1])
		{
			isIncreasing = 0;
			break;
		}
	}
	
	if (isDecreasing == 0 && isIncreasing == 0)
	{
		printf("no");
		return 0;
	}
	
	int noMoreInversions = 1;
	for (i = inv2; i < n - 1; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			noMoreInversions = 0;
			break;
		}
	}
	
	if (noMoreInversions == 0)
	{
		printf("no");
		return 0;
	}
	
	if (isIncreasing == 1)
	{
		if (arr[inv1 - 1] > arr[inv2])
		{
			printf("no");
			return 0;
		}
		
		if (arr[inv1 + 1] < arr[inv2])
		{
			printf("no");
			return 0;
		}
			
		if (noMoreInversions)
		{
			printf("yes\nswap %d %d\n", (inv1 + 1), (inv2 + 1));
			return 0;
		}
	}
	
	if (isDecreasing == 1)
	{
		if (arr[inv1 - 1] > arr[inv2])
		{
			printf("no");
			return 0;
		}
		
		if (noMoreInversions)
		{
			// we can reverse this part of array
			printf("yes\nreverse %d %d\n", (inv1 + 1), (inv2 + 1));
			return 0;
		}
	}
	
	return 0;
}