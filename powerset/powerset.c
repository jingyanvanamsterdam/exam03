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
	while (i <= count)
	{
		printf("%d", arr[i]);
		if (i == count)
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
	while (i <= count)
	{
		sum += arr[i];
		i++;
	}
	return (sum);
}

void	powerset(t_set *set, int i, int j, int *arr)
{
	if (i >= set->count)
		return ;
	arr[j] = set->set[i];
	if (calculate_sum(arr, j) == set->num)
		print_set(arr, j);
	powerset(set, i + 1, j + 1, arr);
	arr[j] = 0;
	powerset(set, i + 1, j, arr);
	return ;
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