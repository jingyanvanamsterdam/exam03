#include <unistd.h>
#include <stdio.h> // puts(s)

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

int	next_index_right(char *s, int i)
{
	int j = i + 2;
	while (s[j] && s[j] == ')')
		j++;
	return (j);
}

int next_index_left(char *s, int i)
{
	int j = i + 1;
	while (s[j] && s[j] == '(')
		j++;
	return (j);
}

int	count_part(char *s, char c)
{
	int i = 0;

	while (s[i] == c)
	{
		s[i] = '_';
		i++;
	}
	return (i);
}

int	next_group_i(char *s, int i)
{
	while (s[i] == '(')
		i++;
	if (!s[i])
		return (0);
	while (s[i] == ')')
		i++;
	return (i);
}

void solver(char *s, int i)
{
	if (i == ft_strlen(s))
	{
		puts(s);
		return ;
	}

	int left = count_part(s + i, '(');
	int right = count_part(s + i + left, ')');
	int next = i + left + right;
	if (right == 0)
		solver(s, next);
	else if (left - right > 0)
	{
		int start = i;
		int end = i + 1;
		while (start < i + left - 1)
		{
			s[start] = '(';
			while (end < i + left)
			{
				s[end] = '(';
				solver(s, next);
				s[end] = '_';
				end++;
			}
			solver(s, next);
			s[start] = '_';
			start++;
		}
	}
	else
	{
		int start = i + left;
		int end = start + 1;
		while (start < i + left + right - 1)
		{
			s[start] = ')';
			while (end < i + left + right)
			{
				s[end] = ')';
				solver(s, next);
				s[end] = '_';
				end++;
			}
			solver(s, next);
			s[start] = '_';
			start++;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	int	i = 0;
	while (argv[1][i] == ')')
		i++;
	solver(argv[1] + i, 0);
	return (0);
}