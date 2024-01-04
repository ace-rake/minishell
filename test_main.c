#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

void	execve_test_with_option_no_arg(char *env[])
{
	int fd = open("test_main.c", O_RDONLY);
	dup2(fd, 0);
	char *path = "/bin/wc";
	char *args[] = {"wc","-l",  NULL};

	execve(path, args, env);
}

int	main(int argc, char *argv[], char *env[])
{
	execve_test_with_option_no_arg(env);

	return (0);
}
