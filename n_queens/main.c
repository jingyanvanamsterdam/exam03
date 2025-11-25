#include <stdio.h> // printf
#include <stdlib.h>
#include <unistd.h>

void	handle_solution(int l, int grid[l][l])
{
	for (int j = 0; j < l; j++)
	{
		for (int i = 0; i < l; i++)
		{
			if (grid[i][j] == 1)
			{
				fprintf(1, "%d", i);
				break;
			}	
		}
		if (j == (l - 1))
			write(1, "\n", 1);
		else
			write(1, " ", 1);
	}
}

int	check_grid(int l, int grid[l][l], int i, int j)
{
	int	x;
	int	y;

	for (x = 0; x <= i; x++)
	{
		for (y = 0; y < j; y++)
		{
			if (grid[x][y] == 1)
			{
				if (x == i )
			}
		}
	}
}
/**
 * return 1 is solved,
 * return 0 is not.
 */
int solve_queens(int l, int grid[l][l], int i, int j)
{
	if (i == l && j == l)
		return (0);
	while (i < l)
	{
		while (j < l)
		{
			grid[i][j] = 1;
			if (check_grid(l, grid, i, j))
			{
				j++;
				continue;
			}
			else
			{
				grid[i][j] = 0;
				if (j + 1 == l)
				{
					if (solve_queens(l, grid, i - 1, j))
						handle_solution(l, grid);
				}
				grid[i][j] = 0;
				j++;
			}
		}
		i++;
	}
}

void print_grid(int l, int grid[l][l])
{
	for (int i = 0; i < l; i++)
	{
		for (int j= 0; j < l; j++)
			printf("%d ", grid[i][j]);
		printf("\n");
	}
}

void	init_grid(int l, int grid[l][l])
{
	for (int i = 0; i < l; i++)
		for (int j= 0; j < l; j++)
			grid[i][j] = 0;
}

int	main(int argc, char **argv)
{
	int	l;

	if (argc != 2)
		return (write(2, "error\n", 6));
	l = atoi(argv[1]);
	if (l < 4)
		return (write(1, "\n", 1));
	
	//create l * lgrid
	int	grid[l][l];
	int res;
	int	x = 0;
	int y = 0;

	init_grid(l, grid);
	res = solve_queens(l, grid, x, y);
	if (!res)
		return (write(1, "\n", 1));
	return (0);
}