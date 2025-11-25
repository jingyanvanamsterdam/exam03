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
	if (j == 0)
	{
		if (i == 0)
			return (1);
		else
		{
			while (i >= 0)
			{
				if (grid[i - 1][j] == 1)
					return (0);
				else
					i--;
			}
			return (1);
		}
	}
	else
	{
		
	}

}
/**
 * return 1 is solved,
 * return 0 is not.
 */
int solve_queens(int l, int grid[l][l], int i)
{
	int	j = 0;
	if (i == l)
		return (0);
	while (j < l)
	{
		grid[i][j] = 1;
		if (check_grid(l, grid, i, j))
		{
			if (i == l - 1)
				return (1);
			else if (solve_queens(l, grid, i + 1))
				return (1);
		}
		else
		{
			grid[i][j] = 0;
			j++;
		}
	}
	return (0);
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

	init_grid(l, grid);
	res = solve_queens(l, grid, x);
	if (!res)
		return (write(1, "\n", 1));
	else
		handle_solution(l, grid);
	return (0);
}