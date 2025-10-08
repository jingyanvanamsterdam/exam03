#include "height.h"

int height_binary(t_btree *root)
{
	int left = 1;
	int right = 1;

	if (!root)
		return (0);
	left += height_binary(root->left);
	right += height_binary(root->right);
	if (right > left)
		return (right);
	return (left);
}
	