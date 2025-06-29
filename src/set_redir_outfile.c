#include "../header/minishell.h"

static int	set_append_file(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		fd = open(data->token[++(*i)].tab, O_WRONLY | O_CREAT | O_APPEND, 0644);
		cmd->outfile_name = ft_strdup(data->token[*i].tab);
		if (fd == -1)
		{
			cmd->err_status = OUTF_ERR;
			return (2); // inclure ce fichier dans cmd
		}
		else
			close(fd);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	return (0);
}

static int	set_redir_out(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		fd = open(data->token[++(*i)].tab, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd->outfile_name = ft_strdup(data->token[*i].tab);
		if (fd == -1)
		{
			cmd->err_status = OUTF_ERR;
			return (2); // inclure ce fichier dans cmd
		}
		else
			close(fd);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	return (0);
}

int	handle_return(int ret, t_data *data, int *i)
{
	if (ret == -1)
		return (-1);
	else if (ret == 2)
	{
		while (data->token[*i].tab && data->token[*i].type != PIPE)
			(*i)++;
	}
	return (0);
}

int	set_outfile(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == REDIR_OUT)
		{
			if (handle_return(set_redir_out(data, cmd, &i), data, &i) == -1)
				return (-1);
		}
		if (data->token[i].type == APPEND)
		{
			if (handle_return(set_append_file(data, cmd, &i), data, &i) == -1)
				return (-1);
		}
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		if (data->token[i].tab)
			i++;
	}
	return (0);
}
