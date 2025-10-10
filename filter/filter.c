#define _GNU_SOURCE
#include <stdlib.h> // realloc, malloc, calloc, free
#include <unistd.h> //read, write
#include <string.h> //strlen, memmem, memmove
#include <stdio.h> // printf, fprintf, stdout, stderr, perror
#include <errno.h> // perror->int errno?

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int	main(int argc, char **argv)
{
	ssize_t	byte;
	ssize_t prev;
	char	*tmp;
	char	*content;

	if (argc != 2)
		return (1);

	//var for filter 

	//Initialization--------------------------
	byte = 1;
	content = calloc(1, sizeof(char));
	prev = 0;
	if (!content)
	{
		perror("calloc fail at creating content.");
		return 1;
	}
	tmp = calloc(BUFFER_SIZE, sizeof(char));
	if (!tmp)
	{
		perror("calloc fail at creating tmp buffer.");
		return 1;
	}
	
	//Read from stdin------------------------------
	while (byte > 0)
	{
		byte = read(0, tmp, BUFFER_SIZE);
		if (byte == -1)
		{
			perror("read from stdin.");
			free(content);
			free(tmp);
			return (1);
		}
		content = realloc(content, prev + byte);
		if (!content)
		{
			perror("realloc fail at content.");
			free(content);
			free(tmp);
			return 1;
		}
		memmove(content + prev, tmp, byte);
		prev += byte;
		content[prev] = '\0';
	}
	free(tmp);

	//filter--------------------------------------------
	ssize_t	len;
	char	*start;
	len = strlen(argv[1]);
	char	*sign_str;
	int		i = 0;

	sign_str = calloc(len + 1, sizeof(char));
	if (!sign_str)
	{
		perror("calloc fail at creating sign string.");
		free(content);
		free(tmp);
		return (1);
	}
	while (len > 0)
		sign_str[--len] = '*';
	len = strlen(sign_str);
	size_t content_len = prev;
	while (i < content_len)
	{
		start = memmem(content + i, content_len - i, argv[1], len);
		if (!start)
		{
			//printf("after checking memme. and it doesnt exist\nstrlen=%lu, argv[1]=%s, len=%lu\n", strlen(content), argv[1], len);
			write(1, content + i, strlen(content + i));
			break;
		}
		while (content[i] && &(content[i]) != start)
		{
			printf("in content[i]loop\n");
			write(1, content + i, 1);
			i++;
		}
//		printf("%s\n", sign_str);
		write(1, sign_str, len);
		i += len;
	}
	free(content);
	free(sign_str);
	return (0);
}