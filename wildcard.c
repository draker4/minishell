#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char	*wildcard_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == NULL)
		return (free(s1), perror("Gnl_strjoin - Malloc"), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	if (i > 0)
		new[i++] = ' ';
	j = 0;
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	if (s1)
		free(s1);
	return (new);
}

int	main(void)
{
	DIR				*dirp;
	char			*wildcard;
	struct dirent 	*file;

	dirp = opendir(".");
	wildcard = NULL;
	file = readdir(dirp);
	while (file)
	{
		wildcard = wildcard_strjoin(wildcard, file->d_name);
		file = readdir(dirp);
	}
	printf("%s\n", wildcard);
	closedir(dirp);
}
