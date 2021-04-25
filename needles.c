#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_array(char **array)
{
	int i = 0;
	while (array && array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

char *substr(char *src, int start, int len)
{
	char *new;
	int i = 0;
	
	new = (char*)malloc(sizeof(char) * (len + 1));
	new[len] = 0;
	while(i < len)
	{
		new[i] = src[start + i];
		i++;
	}
	return (new);
}

int chunk_has_needle(char *str, char c)
{
	int i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char **cut_in_half(char **chunks, int i)
{
	int size = 0;
	int j = 0;
	char **new_chunks;

	while (chunks && chunks[size])
		size++;
	new_chunks = (char **)malloc(sizeof(char *) * (size + 2));
	new_chunks[size + 1] = NULL;
	while (j < i)
	{
		new_chunks[j] = strdup(chunks[j]);
		j++;
	}
	if (strlen(chunks[i]) > 2)
	{
		new_chunks[j] = substr(chunks[i], 0, strlen(chunks[i]) / 2);
		j++;
		new_chunks[j] = substr(chunks[i], strlen(chunks[i]) / 2, strlen(chunks[i]) - strlen(chunks[i]) / 2);
		j++;
	}
	else
	{
		new_chunks[j] = substr(chunks[i], 0, 1);
		j++;
		new_chunks[j] = substr(chunks[i], 1, 1);
		j++;
	}
	while (j < size + 1)
	{
		new_chunks[j] = strdup(chunks[j - 1]);
		j++;
	}
	return (new_chunks);
}

char	**discard(char **chunks, int i)
{
	int size = 0;
	char	**new_chunks;
	int j = 0;
	int x = 0;

	while (chunks[size])
		size++;
	new_chunks = (char **)malloc(sizeof(char*) * size);
	new_chunks[size - 1] = NULL;
	while (j < size - 1)
	{
		if (j == i && x == 0)
			x = 1;
		else
		{
			new_chunks[j] = strdup(chunks[j + x]);
			j++;
		}
	}
	return (new_chunks);
}

int main(int argc, char **argv)
{
	char needle = 'i';
	int nb_of_needle = 0;
	int i = 0;

	if (argc != 2)
		return (0);
	char **chunks = (char **)malloc(sizeof(char *) * 2);
	chunks[0] = strdup(argv[1]);
	chunks[1] = NULL;
	while (chunks[i])
	{
		// Check haystack weight for needles
		if (chunk_has_needle(chunks[i], needle))
		{
			// check haystack volume if == 1cm3
			if (strlen(chunks[i]) > 1)
			{
				// Cut haystack in two
				printf("CUT\n");
				chunks = cut_in_half(chunks, i);
			}
			else
				i++;
		}
		else
			chunks = discard(chunks, i);
	}
	i = 0;
	while (chunks[i])
	{
		if (chunks[i][0] == needle)
			nb_of_needle++;
		i++;
	}
//	printf("There are %d volumes of needles in this haystack\n", nb_of_needle);
	return 0;
}

// If there are needles in everyon 1 cm3 volume, the number of operation is (n - 1) volumes
// n = k	operations
// 5		4
// 10		9
// 20		19
// 50		49
// 250		249
// 1000		999
// 10000	9999

// If there is 1 needle
// (k = 1)
// && n = 	operations
// 5		2
// 10		3
// 20		4
// 50		5
// 250		7
// 1000		9
// 10000	13
