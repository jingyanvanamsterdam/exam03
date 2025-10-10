#include <stdlib.h>
#include <stdio.h>

int	powerset(int *arr, int elements, int num)
{
	int		i = 0;
	int		count = 0;
	int		*set = NULL;

	while (i < elements - 1)
	{
		set = malloc(sizeof(int));
		if (!set)
			return (1);
		int cur = arr[i]; // assign the first number in the arr to check the combos later
		set[0] = cur;
		count = 1;
		//printf("out loop i = %d\n", i);
		if (cur == num)
		{
			printf("%d", set[0]);
			printf("\n");
			i++;
		}
		else if (cur > num)
			i++;
		else
		{
			int	j = i + 1;
			int	sum = cur;
			while (j < elements)
			{
				sum += arr[j];
				if (sum <= num)
				{
					set = realloc(set, sizeof(int) * (count + 1));
					if (!set)
						return (free(set), 1);
					set[j] = arr[j];
					count++;
				}
				else
					sum -= arr[j];
				j++;
			}
			//printf("sum = %d\n", sum);
			if (sum != num)
			{
				free(set);
				set = NULL;
			}
			else if (sum == num)
			{
				for (int p = 0; p < count; p++)
				{
					printf("%d", set[p]);
					if (p != count - 1)
						printf(" ");
					else
						printf("\n");
				}
			}
			i++;
		}
	}
	free(set);
	free(arr);
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
	if (!powerset(arr, i, num))
		return (1);
	return (0);
}