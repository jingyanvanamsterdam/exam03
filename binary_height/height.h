#ifndef HEIGHT_H
# define HEIGHT_H

typedef struct s_btree
{
	int	val;
	t_btree *left;
	t_btree *right;
}		t_btree;

#endif