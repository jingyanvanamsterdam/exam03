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

void	free_exit(t_sol *sol, int *perm, float (*arr)[2])
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
			perm[i] = j;
			if (!permutation_routes(size, perm, sol, i + 1))
				return (0);
			perm[i] = -1;
		}
		j++;
	}
	return (1);
}

float	*calculate_distance(t_sol *sol, float (*arr)[2], int size, float *dis)
{
	int 	a;
	int		b;
	float	res = 0;
	
	dis = malloc(sizeof(float) * sol->size);
	if (!dis)
		return (NULL);
	for (int i = 0; i < sol->size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			a = sol->sol[i][j];
			if (j == size - 1)
				b = sol->sol[i][0];
			else
				b = sol->sol[i][j + 1];
			res += distance(a, b); 
		}
		dis[i] = res;
	}
	return (dis);
}

float	find_best_distance(float *distance, int size)
{
	float smal = distance[0];
	for (int i = 0; i < size; i++)
	{
		if (distance[i] < smal)
			smal = distance[i];
	}
	return (smal);
}

// compute the distance between two points
float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

float tsp(float (*array)[2], ssize_t size)
{
    float best_distance;
	t_sol	sol;
    
	int *perm = malloc(size * sizeof(int));
	sol.size = calculate_permutation((int)size);
	sol.sol = calloc(sol.size, sizeof(int *));
	if (!perm || !(sol.sol))
	{
		if (perm)
			free(perm);
		free(array);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size; i++)
		perm[i] = -1;
	if (!permutation_routes((int)size, perm, &sol, 0))
		free_exit(&sol, perm, array);
	float *distances = calculate_distances(sol, array, size);
	if (!distances)
		free_exit(&sol, perm, array);
	best_distance = find_best_distance(distances, sol.size);
	for (int i = 0; i < sol.size; i++)
		free(sol.sol[i]);
	free(sol.sol);
	free(perm);
    return (best_distance);
}

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    printf("%.2f\n", tsp(array, size));
    free(array);
    return (0);
}