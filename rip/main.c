#include <unistd.h>
#include <stdio.h> // puts(s)

typedef struct s_lst
{
	char *s;
	char p;
	int min;
	int	end;

}				t_lst;

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

int	count_part(char *s, char c, int end)
{
	int i = 0;
	int count = 0;

	while (i < end)
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	valid_filled(t_lst *lst)
{
	int i = 0;
	while (lst->s[i] == '_')
		i++;
	if (lst->s[i] == ')')
		return 0;
	return 1;
}


void	solver(t_lst *lst, int i, int filled)
{
	int end = lst->end;
	char *s = lst->s;
	if (i > end - 1)
		return ;
	if (filled == lst->min)
	{
		if (valid_filled(lst))
			printf("%s\n", lst->s);
		return ;
	}
	if (s[i] == lst->p)
	{
		s[i] = '_';
		filled++;
	}
	solver(lst, i + 1, filled);
	if (i > 0 && s[i - 1] == '_')
	{
		s[i - 1] = lst->p;
		filled--;
	}
	solver(lst, i, filled);
}

int	check_min(t_lst *lst)
{
	char *s = lst->s;
	int end = lst->end;
	int left = count_part(s, '(', end);
	int	right = count_part(s, ')', end);
	if (left > right)
	{
		lst->p = '(';
		return (left - right);
	}
	else if (left < right)
	{
		lst->p = ')';
		return (right - left);
	}
	else
		return (0);
}

int remove_left_end(char *s)
{
	int len = ft_strlen(s) - 1;
	while (len >= 0 && s[len] == '(')
	{
		s[len] = '_';
		len--;
	}
	if (len < 0)
		return (0);
	return (len + 1);
}

int	find_start(t_lst *lst)
{
	int i = 0;
	if (lst->p == '(')
		return (i);
	while (lst->s[i] == '(')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	int	i = 0;
	while (argv[1][i] == ')')
		i++;
	t_lst lst;
	lst.s = argv[1] + i;
	lst.end = remove_left_end(lst.s);
	if (!lst.end)
		return 1;
	lst.min = check_min(&lst);
	if (lst.min == -1)
		return 1;
	if (lst.min == 0)
	{
		puts(lst.s);
		return 0; 
	}
	int start = find_start(&lst);
	printf("start = %d, end = %d, min = %d \n", start, lst.end, lst.min);
	solver(&lst, start, 0);
	return (0);
}