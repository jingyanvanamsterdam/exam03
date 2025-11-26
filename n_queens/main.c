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
				fprintf(stdout, "%d", i);
				break;
			}	
		}
		if (j != (l - 1))
			fprintf(stdout, " ");
		else
			fprintf(stdout, "\n");
	}
}

int	check_grid(int l, int grid[l][l], int i, int j)
{
	int	up;
	int	left;
	int	right;

	for (up = 0; up < i; up++)
		if (grid[up][j] == 1)
			return (0);

	up = i - 1;
	left = j - 1;
	while (up >= 0 && left >= 0)
	{
		if (grid[up][left] == 1)
			return 0;
		up--;
		left--;
	}
	up = i - 1;
	right = j + 1;
	while (up >= 0 && right < l)
	{
		if (grid[up][right] == 1)
			return 0;
		up--;
		right++;
	}
	return (1);
}

void solve_queens(int l, int grid[l][l], int i)
{
	int	j = 0;
	if (i == l)
	{
		handle_solution(l, grid);
		return ;
	}
	while (j < l)
	{
		if (check_grid(l, grid, i, j))
		{
			grid[i][j] = 1;
			solve_queens(l, grid, i + 1);
		}
		grid[i][j] = 0;
		j++;
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

	init_grid(l, grid);
	solve_queens(l, grid, 0);
	return (0);
}