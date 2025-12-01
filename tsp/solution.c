#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

typedef struct s_sol
{
	int **sol;
	int size;
}				t_sol;

void	free_exit(t_sol *sol, int *perm)//, float (*arr)[2])
{
	if (sol->sol)
	{
		for (int i = 0; i < sol->size; i++)
			free(sol->sol[i]);
		free(sol->sol);
	}
	if (perm)
		free(perm);
	//free(arr);
	exit(EXIT_FAILURE);
}

int	calculate_permutation(int size)
{
	int res = 1;
	for (int i = 2; i <= size; i++)
		res *= i;
	return res;
}

int	*copy_perm(int *perm, int size)
{
	int *copy = malloc(sizeof(int) * size);
	if (!copy)
		return (NULL);
	for (int i = 0; i < size; i++)
		copy[i] = perm[i];
	return (copy);
}

int	append_to_sol(int *perm, t_sol *sol, int size)
{
	int i = 0;
	int *copy = copy_perm(perm, size);
	if (!copy)
		return (0);
	for (int j = 0; j < size; j++)
		printf("%d ", copy[j]);
	printf("end copy\n");
	while (i < sol->size && sol->sol[i] != 0)
		i++;
	if (i < sol->size)
		sol->sol[i] = copy;
	return 1;
}

int	in_perm(int *perm, int j, int size)
{
	int i = 0;
	while (i < size)
	{
		if (perm[i] == j)
			return (1);
		i++;
	}
	return (0);
}

int	permutation_routes(int size, int *perm, t_sol *sol, int i)
{
	if (i == size)
	{
		if (!append_to_sol(perm, sol, size))
			return 0;
		return 1;
	}
	int j = 0;
	while (j < size)
	{
		if (!in_perm(perm, j, size))
		{
			//append_to_perm(perm, j, size);
			perm[i] = j;
			if (!permutation_routes(size, perm, sol, i + 1))
				return (0);
			//for (int p = 0; p < size; p++)
			//	printf("%d, ", perm[p]);
			//printf("\n");
			//remove_from_perm(perm, j, size);
			perm[i] = -1;
		}
		j++;
	}
	return (1);
}

int main(void)
{
	t_sol	sol;
	ssize_t	size = 4;
    
	int *perm = malloc(size * sizeof(int));
	sol.size = calculate_permutation((int)size);
	sol.sol = calloc(sol.size, sizeof(int *));
	if (!perm || !(sol.sol))
	{
		if (perm)
			free(perm);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size; i++)
		perm[i] = -1;
	if (!permutation_routes((int)size, perm, &sol, 0))
		free_exit(&sol, perm);//, array);
	for (int i = 0; i < sol.size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", sol.sol[i][j]);
		printf("%d\n", i);
	}	
}