#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    char input[100];
    scanf("%s", input);

    int len = strlen(input);
    int rows = (int)sqrt(len);
    int upper_root = rows;

    if ((rows * rows) < len)
    {
        upper_root = rows + 1;
    }
    int cols = 0;

    for (rows; rows <= upper_root; rows++)
    {
        for (cols = rows; cols <= upper_root; cols++)
        {
            if ((rows * cols) >= len)
            {
                break;
            }
        }
    }

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if ((j * cols) + i < len)
            {
                printf("%c", input[(j * cols) + i]);
            }
        }
        printf(" ");
    }

    return 0;
}
