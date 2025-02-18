#include "../../include/minishell.h"

typedef struct s_env
{
	char			*name;
	char			*data;
	struct	s_env	*next;
}					t_env;

int	env_cmd(char **env)
{
	update_env(env);
}

void	update_env(char **env)
{

}

void	fetch_env(char **env)
{

}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;

	return (0);
}