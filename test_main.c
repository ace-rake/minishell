#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

char	*get_dir(void)
{
	size_t n = 200;
	char str[200];
	char *retval;

	str[0] = '\0';
	retval = getcwd(str, n);

	printf("retval [%s] : str [%s]\n", retval, str);
	return (retval);
}

void	dir_change_test()
{
	char *str = get_dir();
	printf("retval [%i]\n",chdir("/nfs/homes/vdenisse"));
	perror("test");
	get_dir();
}

void	dir_open_test()
{
	DIR *dir = opendir(".");
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
		printf("%s\n", entry->d_name);

	closedir(dir);

}

int	main(void)
{
	dir_open_test();
	return (0);
}
