#include "../header/minishell.h"

static int	open_redir_in(t_data *data, t_cmd *cmd, int *i, int hrdc)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		fd = open(data->token[++(*i)].tab, O_RDONLY);
		if (hrdc == 0 && cmd->err_status != HRDC_ERR)
			cmd->infile_name = ft_strdup(data->token[*i].tab);
		if (fd == -1)
		{
			cmd->err_status = INF_ERR;
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

static int	set_redir_in(t_data *data, t_cmd *cmd, int *i, int is_outf_hrdc)
{
	int	ret;

	if (data->token[*i].type == REDIR_IN)
	{
		ret = open_redir_in(data, cmd, i, is_outf_hrdc);
		if (ret == -1)
			return (-1);
		else if (ret == 2)
		{
			while (data->token[*i].tab && data->token[*i].type != PIPE)
				(*i)++;
			if (!data->token[*i].tab)
				return (0);
		}
	}
	return (0);
}

int	set_infile(t_data *data)
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
		if (set_redir_in(data, cmd, &i, is_outf_hrdc) == -1)
			return (-1);
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		if (data->token[i].tab)
			i++;
	}
	return (0);
}
