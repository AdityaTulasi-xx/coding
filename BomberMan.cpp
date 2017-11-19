#include <stdio.h>

void blast(int grid[][200], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j] == 3)
			{
				// blast neighbors
				if (i != 0 && grid[i - 1][j] != 3)
				{
					grid[i - 1][j] = -1;
				}
				if (i < (rows - 1) && grid[i + 1][j] != 3)
				{
					grid[i + 1][j] = -1;
				}
				if (j != 0 && grid[i][j - 1] != 3)
				{
					grid[i][j - 1] = -1;
				}
				if (j < (cols - 1) && grid[i][j + 1] != 3)
				{
					grid[i][j + 1] = -1;
				}
			}
		}
	}
	
	
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (grid[i][j] == 3)
				grid[i][j] = -1;
}

void increment(int grid[][200], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			grid[i][j]++;
}

void plantBombs(int grid[][200], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (grid[i][j] ==  -1)
				grid[i][j] = 0;
}

void copyArray(int grid[][200], int grid1[][200], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			grid1[i][j] = grid[i][j];
}

void printArray(int grid[][200], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//printf(" %d ", grid[i][j]);
			if (grid[i][j] <= -1)
			{
				printf(".");
			}
			else
			{
				printf("O");
			}
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	int rows, cols, iter;
	scanf("%d %d %d", &rows, &cols, &iter);
	
	int grid[200][200];
	int grid1[200][200];
	int grid2[200][200];
	int grid3[200][200];
	int grid4[200][200];
	int grid5[200][200];
	char inpChar;
	
	scanf("%c", &inpChar);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			scanf("%c", &inpChar);
			if (inpChar == '.')
			{
				grid[i][j] = -2;
			}
			else
			{
				grid[i][j] = 0;
			}
		}
		// read new line char
		scanf("%c", &inpChar);
	}

	// run a couple of iterations
	increment(grid, rows, cols); // 1st second
	copyArray(grid, grid1, rows, cols);
	
	increment(grid, rows, cols); // 2nd second
	copyArray(grid, grid2, rows, cols);
	
	increment(grid, rows, cols); // 3rd second
	blast(grid, rows, cols);
	copyArray(grid, grid3, rows, cols);
	
	increment(grid, rows, cols); // 4th second
	copyArray(grid, grid4, rows, cols);
	
	increment(grid, rows, cols); // 5th second
	blast(grid, rows, cols);
	copyArray(grid, grid5, rows, cols);
	
	increment(grid, rows, cols); // 6th second
	
	if (iter < 3)
	{
		if (iter == 1)
			printArray(grid1, rows, cols);
		else
			printArray(grid2, rows, cols);
	}
	else
	{
		iter -= 3;
		iter %= 4;
		if (iter == 0)
			printArray(grid3, rows, cols);
		else if (iter == 1)
			printArray(grid4, rows, cols);
		else if (iter == 2)
			printArray(grid5, rows, cols);
		else
			printArray(grid, rows, cols);
	}
	
	return 0;
}
