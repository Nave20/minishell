#include "../header/minishell.h"

// void	define_cmd(t_data *data)
// {
// 	int	i;

// 	i = 1;
// 	data->token[0].type = CMD;
// 	while (data->token[i].tab)
// 	{
// 		i++;
// 		if (data->token[i].type == PIPE)
// 		{
// 			i++;
// 			if (data->token[i].tab)
// 			{
// 				if (!data->token[i].type)
// 					data->token[i].type = CMD;
// 				else
// 					exit(EXIT_FAILURE); // gestion erreur
// 			}
// 		}
// 	}
// }

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

static void	handle_simple_cmd(t_data *data)
{
	int	i;

	i = 1;
	if (is_build_in(data->token[0].tab))
		data->token[0].type = CMD_BI;
	else
		data->token[0].type = CMD;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '-')
			data->token[i].type = FLAG;
		else
			data->token[i].type = ARG;
		i++;
	}
}

static bool	is_simple_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == PIPE || data->token[i].type == REDIR_IN
			|| data->token[i].type == REDIR_OUT || data->token[i].type == APPEND
			|| data->token[i].type == HEREDOC)
			return (false);
		i++;
	}
	return (true);
}

void	define_token(t_data *data)
// classer types cmd : avec ou sans pipe et/ou redirection
{
	if (is_simple_cmd(data))
		handle_simple_cmd(data);
}
