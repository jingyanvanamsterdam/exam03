#include <stdlib.h>
#include <stdio.h>

typedef struct	s_set
{
	int	*set;
	int	count;
	int	num;
}				t_set;

void	print_set(int *arr, int count)
{
	int	 i = 0;
	printf("set is: ");
	while (i < count)
	{
		printf("%d", arr[i]);
		if (i == count - 1)
			printf("\n");
		else
			printf(" ");
		i++;
	}
}

int	calculate_sum(int *arr, int count)
{
	int	i = 0;
	int	sum = 0;
	while (i < count)
	{
		sum += arr[i];
		i++;
	}
	return (sum);
}

void	powerset(t_set *set, int i, int j, int *arr)
{
	if (i == set->count)
	{
		if (j > 0 && calculate_sum(arr, j) == set->num)
			print_set(arr, j);
		else if (j == 0 && set->num == 0)
			printf("\n");
		return;
	}
	arr[j] = set->set[i];
	powerset(set, i + 1, j + 1, arr);
	powerset(set, i + 1, j, arr);
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	int	*arr = calloc(argc - 2, sizeof(int));
	if (!arr)
		return (1);
	t_set	set;
	set.set = calloc(argc - 2, sizeof(int));
	if (!set.set)
		return 1;
	int i;
	for (i = 0; i < argc - 2; i++)
		set.set[i] = atoi(argv[i + 2]);
	set.num = atoi(argv[1]);
	set.count = i;
	powerset(&set, 0, 0, arr);
	if (set.set)
		free(set.set);
	free(arr);
	return (0);
}