#include <stdio.h>
int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int	min_move(char *s)
{
	int left = 0;
	int right = 0;
	int	i = 0;
	while (s[i])
	{
		if (s[i] == '(')
			left++;
		else if (s[i] == ')')
		{
			if (left > 0)
				left--;
			else
				right++;
		}
		i++;
	}
	return (left + right);
}

void	solver(int cur, int min, char *s, int replaced)
{
	if (replaced == min && !min_move(s))
	{
		puts(s);
		return ;
	}
	if (replaced > min || cur >= ft_strlen(s))
		return ;
	char tmp = s[cur];
	s[cur] = ' ';
	solver(cur+1, min, s, replaced+1);
	s[cur] = tmp;
	solver(cur+1, min, s, replaced);
}

int main(int ac, char *argv[])
{
	if (ac != 2)
		return (1);

	int min = min_move(argv[1]);
	if (min == 0)
		return (puts(argv[1]));
	solver(0, min, argv[1], 0);
	return (0);
}