#include <stdlib.h>
#include <stdio.h>

typedef struct	s_subset
{
	int	*set;
	int	elements;
}				t_subset;

void	free_subsets(t_subset *subsets, int count)
{
	int	i = 0;
	while (i < count)
	{
		if (subsets[i].set)
			free(subsets[i].set);
		i++;
	}
}

int	powerset(int *arr, int elements, int num)
{
	t_subset *subsets = NULL;
	int		i = 0;
	int		count = 0;
	while (i < elements - 1)
	{
		subsets = realloc(subsets, sizeof(t_subset) * (count + 1)); // firstly create 1 more subset;
		if (!subsets)
			return (free_subsets(subsets, count), 1);
		// init the set with first number of cur
		subsets[count].set = realloc(subsets[count].set, sizeof(int));
		if (!subsets[count].set)
			return (free_subsets(subsets, count), 1);
		int cur = arr[i]; // assign the first number in the arr to check the combos later
		subsets[count].set[0] = cur;
		subsets[count].elements = 1;
		if (cur == num)
		{
			i++;
			count++;
		}
		else if (cur > num)
		{
			free(subsets[count].set);
			subsets[count].set = NULL;
			subsets[count].elements = 0;
			i++;
		}
		else
		{
			//recursion?
			powerset(arr, elements, num);
			if (count_subset_sum(&subsets[count]) != num)
			{
				free(subsets[count].set);
				subsets[count].set = NULL;
				subsets[count].elements = 0;
				i++;
			}
			else
			{
				i++;
				count++;
			}
		}
		
		
	}
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
		arr[i] = atoi(argv[i + 2]);
	if (!powerset(arr, i, num))
		return (1);
	return (0);
}