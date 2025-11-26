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

int solve(char *s, int i, char *arr)
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
		write(1, s, len);
		write(1, "\n", 1);
		return 1;
	}
	while (j < len)
	{
		if (!in_str(s, arr[j]))
		{
			append_to_s(s, arr[j]);
			if (!solve(s, i + 1, arr))
				return (0);
			remove_c(s, arr[j]);
		}
		j++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	int len = ft_strlen(argv[1]);
	char *s;

	s = NULL;
	char *mes = "malloc error\n";
	if (!solve(s, 0, argv[1]))
		return (write(2, mes, ft_strlen(mes)));
	return 0;
}