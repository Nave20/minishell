#include "../header/minishell.h"

static int	set_append_file(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i].tab)
	{
		if (cmd->outfile)
			close(cmd->outfile);
		fd = open(data->token[++(*i)].tab, O_WRONLY | O_CREAT | O_APPEND, 0644);
		cmd->outfile = fd;
		cmd->outfile_name = data->token[*i].tab;
		if (fd == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

static int	set_redir_out(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i].tab)
	{
		if (cmd->outfile)
			close(cmd->outfile);
		fd = open(data->token[++(*i)].tab, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd->outfile = fd;
		cmd->outfile_name = data->token[*i].tab;
		if (fd == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

void	set_outfile(t_data *data)
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
				return ;
		}
		if (data->token[i].type == APPEND)
		{
			if (set_append_file(data, cmd, &i) == -1)
				return ;
		}
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		i++;
	}
}

static int	set_redir_in(t_data *data, t_cmd *cmd, int *i, int hrdc)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		if (cmd->infile)
			close(cmd->infile);
		fd = open(data->token[++(*i)].tab, O_RDONLY);
		cmd->infile_name = data->token[*i].tab;
		if (hrdc == 0)
			cmd->infile = fd;
		if (fd == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

void	set_infile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		is_outf_hrdc;

	i = 0;
	is_outf_hrdc = 1;
	cmd = data->cmd;
	if (!cmd->hrdc_path)
		is_outf_hrdc = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == REDIR_IN)
		{
			if (set_redir_in(data, cmd, &i, is_outf_hrdc) == -1)
				return ;
		}
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		i++;
	}
}
