#include "../header/minishell.h"

void	handle_redirout_cmd(t_data *data, int *i)
{
	if (data->token[*i].type == REDIR_OUT)
	{
		data->token[*i + 1].type = OUTFILE;
		(*i) += 2;
		if (!data->token[*i].type)
			data->token[*i].type = CMD;
	}
	if (data->token[*i].type == APPEND)
	{
		data->token[*i + 1].type = OUTFILE;
		i += 2;
		if (!data->token[*i].type)
			data->token[*i].type = CMD;
	}
}

void	handle_redir_cmd(t_data *data, int end)
{
	int	i;

	i = 0;
	if (!data->token[i].type)
		data->token[i].type = CMD;
	while (i < end)
	{
		if (data->token[i].type == REDIR_IN)
		{
			data->token[i + 1].type = INFILE;
			i += 2;
			if (!data->token[i].type)
				data->token[i].type = CMD;
		}
		if (data->token[i].type == HEREDOC)
		{
			data->token[i + 1].type = DELIM;
			i += 2;
			if (!data->token[i].type)
				data->token[i].type = CMD;
		}
		handle_redirout_cmd(data, &i);
		i++;
	}
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

static void	handle_simple_cmd(t_data *data, int end)
{
	int	i;

	i = 1;
	data->token[0].type = CMD;
	while (i < end)
	{
		if (data->token[i].tab[0] == '-')
			data->token[i].type = FLAG;
		else
			data->token[i].type = ARG;
		i++;
	}
}

static bool	is_simple_cmd(t_data *data, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (data->token[i].type == PIPE || data->token[i].type == REDIR_IN
			|| data->token[i].type == REDIR_OUT || data->token[i].type == APPEND
			|| data->token[i].type == HEREDOC)
			return (false);
		i++;
	}
	return (true);
}

void	define_build_in(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == CMD && is_build_in(data->token[i].tab))
			data->token[i].type = CMD_BI;
		i++;
	}
}

void	define_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '-')
			data->token[i].type = FLAG;
		i++;
	}
	i = 0;
	while (data->token[i].tab)
	{
		while (data->token[i].tab && data->token[i].tab[0] != '|')
			i++;
		if (is_simple_cmd(data, i))
			handle_simple_cmd(data, i);
		else
			handle_redir_cmd(data, i);
		if (data->token[i].tab)
			i++;
	}
	define_build_in(data);
}
