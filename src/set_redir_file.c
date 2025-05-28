#include "../header/minishell.h"

static int	set_append_file(t_data *data, int fd, int *i)
{
	if (data->token[*i].tab)
	{
		if (fd)
			close(fd);
		fd = open(data->token[++(*i)].tab, O_WRONLY | O_CREAT | O_APPEND);
		data->cmd->outfile = fd;
	}
	else
		return (-1);
	return (0);
}

static int	set_redir_out(t_data *data, int fd, int *i)
{
	if (data->token[*i].tab)
	{
		if (fd)
			close(fd);
		fd = open(data->token[++(*i)].tab, O_WRONLY | O_CREAT | O_TRUNC);
		data->cmd->outfile = fd;
	}
	else
		return (-1);
	return (0);
}

void	set_outfile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		fd;

	i = 0;
	fd = 0;
	cmd = data->cmd;
	while (data->token[i].tab && data->token[i].type != PIPE)
	{
		if (data->token[i].type == REDIR_OUT)
		{
			if (set_redir_out(data, fd, &i) == -1)
				return ; // pas de fichier redirout, erreur
		}
		if (data->token[i].type == APPEND)
		{
			if (set_append_file(data, fd, &i) == -1)
				return ; // pas de fihicer append, erreur
		}
		i++;
		if (data->token[i].type == PIPE)
		{
			i++;
			cmd = data->cmd->next;
		}
	}
}

static int	set_redir_in(t_data *data, int fd, int *i, int hrdc)
{
	if (data->token[*i + 1].tab)
	{
		if (fd)
			close(fd);
		fd = open(data->token[++(*i)].tab, O_RDONLY);
		if (hrdc == 0)
			data->cmd->infile = fd;
	}
	else
		return (-1);
	return (0);
}

void	set_infile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		fd;
	int		is_outf_hrdc;

	i = 0;
	is_outf_hrdc = 1;
	fd = 0;
	cmd = data->cmd;
	if (!cmd->hrdc_path)
		is_outf_hrdc = 0;
	while (data->token[i].tab && data->token[i].type != PIPE)
	{
		if (data->token[i].type == REDIR_IN)
		{
			if (set_redir_in(data, fd, &i, is_outf_hrdc) == -1)
				return ; // pas de fichier redirin, erreur
		}
		i++;
		if (data->token[i].type == PIPE)
		{
			i++;
			cmd = data->cmd->next;
		}
	}
}
