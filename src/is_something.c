#include "../header/minishell.h"

bool	is_simple_cmd(t_data *data, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (data->token[i].type == REDIR_IN || data->token[i].type == REDIR_OUT
			|| data->token[i].type == APPEND || data->token[i].type == HEREDOC)
			return (false);
		i++;
	}
	return (true);
}

bool	is_build_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0 || ft_strncmp(cmd,
			"cd", ft_strlen("cd") + 1) == 0 || ft_strncmp(cmd, "export",
			ft_strlen("export") + 1) == 0 || ft_strncmp(cmd, "unset",
			ft_strlen("unset") + 1) == 0 || ft_strncmp(cmd, "env",
			ft_strlen("env") + 1) == 0 || ft_strncmp(cmd, "exit",
			ft_strlen("exit") + 1) == 0 || ft_strncmp(cmd, "pwd",
			ft_strlen("pwd") + 1) == 0)
		return (true);
	else
		return (false);
}

bool	is_locked(char *tab, int c)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		if (tab[i] == c)
			return (true);
		i++;
	}
	return (false);
}
