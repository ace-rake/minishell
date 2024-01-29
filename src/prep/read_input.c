#include "../../inc/minishell.h"

int	read_heredoc(t_token *token)
{
	char *str;
	int	filedes[2];

	if (pipe(filedes) == -1)
		return (1);
	token->input = filedes[0];
	str = readline(">");
	while (ft_strcmp(str, (const char *)token->right->value) != 0)
	{
		ft_putendl_fd(str, filedes[1]);
		str = readline(">");
	}
	ft_putchar_fd('\0', filedes[1]);
	close(filedes[1]);
	return (0);
}

int	exec_heredocs(t_token *head)
{
	if (head->left)
		exec_heredocs(head->left);
	if (head->right)
		exec_heredocs(head->right);
	if (head->type == REDIR_HEREDOC)
		read_heredoc(head);
	return (0);
}


/*
 * read line
 * check if VALUE
 * if not value
 * 		write \n for prev line 
 * 		and write own line
 */
