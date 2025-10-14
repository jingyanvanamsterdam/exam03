#include <stdlib.h>
#include <stdio.h>

typedef struct	s_set
{
	int	*set;
	int	count;
	int	sum;
}				t_set;

void	print_set(t_set *set)
{
	int	 i = 0;

	while (i < set->count)
	{
		printf("%d", set->set[i]);
		if (i == set->count - 1)
			printf("\n");
		else
			printf(" ");
		i++;
	}
}

void reset_set(t_set *set)
{
	if (set->set)
		free(set->set);
	set->set = NULL;
	set->count = 0;
	set->sum = 0;
}

int	powerset(int *arr, int elements, int num, t_set *set)
{
	int	i = 0;

	while (i < elements) // elements - 1 or elements
	{
		printf("i = %d\n", i);
		printf("set: ");
		for (int j = 0; j < set->count; j++)
		{
			printf("%d ", set->set[j]);
		}
		printf("\n");
		printf("elements = %d\n", elements);
		set->sum += arr[i];
		set->count ++;
		if (set->sum <= num)
		{
			set->set = realloc(set->set, sizeof(int) *(set->count));
			if (!set->set)
				return (reset_set(set), 1);
			set->set[set->count - 1] = arr[i];
			if (set->sum == num)
			{
				print_set(set);
				reset_set(set);
				i++;
			}
			else if (powerset(&arr[i + 1], (elements - 1 - i), num, set) == 0)
			{
				set->sum -= arr[i];
				set->count --;
				i++;
			}	
		}
		else
		{
			set->sum -= arr[i];
			set->count --;
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	
	int	num = atoi(argv[1]);
	int	*arr = calloc(argc - 2, sizeof(int));
	if (!arr)
		return (1);
	int i;
	for (i = 0; i < argc - 2; i++)
	{
		arr[i] = atoi(argv[i + 2]);
	}
	t_set	*set;
	set = malloc(sizeof(t_set));
	if (!set)
		return (1);
	set->count = 0;
	set->set = NULL;
	set->sum = 0;
	int	j = 0;
	while (powerset(&arr[j + 1], i - 1 - j, num, set) == 0 && j < i)
	{
		reset_set(set);
		j++;
	}
	if (j == i)
	{
		reset_set(set);
		free(arr);
		return 0;
	}
	free(arr);
	return (0);
}