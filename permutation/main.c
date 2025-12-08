#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return i;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *s)
{
	char *res;

	res = NULL;
	if (!s)
		return (res);
	int len = ft_strlen(s);
	res = calloc(len + 1, 1);
	if (!res)
		return (NULL);
	int i = 0;
	while (*s)
	{
		res[i] = *s;
		s++;
		i++;
	}
	return (res);
}

int	in_str(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	append_to_s(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	s[i] = c;
}

void remove_c(char *s, char c)
{
	int i = 0;
	//printf("remove %c\n", c);
	while (s[i])
	{
		if (s[i] == c)
		{
			s[i] = 0;
			return ;
		}
		i++;
	}
}

void	add_to_box(char *s, char **box)
{
	int	i = 0;
	while (box[i] != 0)
		i++;
	box[i] = s;
}

int solve(char *s, int i, char *arr, char **box)
{
	int len = ft_strlen(arr);
	int	j = 0;

	if (!s)
	{
		s = calloc(len + 1, 1);
		if (!s)
			return (0);
	}
	if (i == len)
	{
		add_to_box(s, box);
		return 1;
	}
	while (j < len)
	{
		if (!in_str(s, arr[j]))
		{
			append_to_s(s, arr[j]);
			if (!solve(s, i + 1, arr, box))
				return (0);
			remove_c(s, arr[j]);
		}
		j++;
	}
	return (1);
}

int	ft_cal_perm(int size)
{
	if (size <= 1)
		return (1);
	return (size * ft_cal_perm(size - 1));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	sort_box(char **box, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (ft_strcmp(box[i], box[j]) > 0)
			{
				char *tmp = box[i];
				box[i] = box[j];
				box[j] = tmp;
			}
		}
	}
}
int	main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	int len = ft_strlen(argv[1]);
	char *s;
	char **box;

	int size = ft_cal_perm(len);
	box = calloc(size + 1, sizeof(char*));
	s = NULL;
	char *mes = "malloc error\n";
	if (!solve(s, 0, argv[1], box))
		return (write(2, mes, ft_strlen(mes)));
	sort_box(box, size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < len; j++)
		{
			printf("%c", box[i][j]);
			if (j == len)
				break ;
			printf (" ");
		}
		printf("\n");
	}
	return 0;
}