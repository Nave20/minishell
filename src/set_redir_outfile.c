#include "../header/minishell.h"

static int	set_append_file(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		fd = open(data->token[++(*i)].tab, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->err_outf != OUTF_ERR)
			cmd->outfile_name = ft_strdup(data->token[*i].tab);
		if (fd == -1)
		{
			if (cmd->err_outf != OUTF_ERR)
				cmd->err_outf = OUTF_ERR;
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
		if (cmd->err_outf != OUTF_ERR)
			cmd->outfile_name = ft_strdup(data->token[*i].tab);
		if (fd == -1)
		{
			if (cmd->err_outf != OUTF_ERR)
				cmd->err_outf = OUTF_ERR;
		}
		else
			close(fd);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
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
			if (set_redir_out(data, cmd, &i) == -1)
				return (-1);
		}
		if (data->token[i].type == APPEND)
		{
			if (set_append_file(data, cmd, &i) == -1)
				return (-1);
		}
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		if (data->token[i].tab)
			i++;
	}
	return (0);
}
