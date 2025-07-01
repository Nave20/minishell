#include "../header/minishell.h"

static int	open_hrdc(t_data *data, t_cmd *cmd, int *i, int hrdc_nb)
{
	int		fd;
	char	*hrdc;
	char	*nb;

	nb = ft_itoa(hrdc_nb);
	if (data->token[*i + 1].tab)
	{
		(*i)++;
		hrdc = ft_strjoin("/tmp/heredoc", nb);
		free(nb);
		fd = open(hrdc, O_RDONLY);
		if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
			cmd->hrdc_path = hrdc;
		if (fd == -1)
		{
			if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
				cmd->err_inf = HRDC_ERR;
		}
		else
			close(fd);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	return (0);
}

static int	open_redir_in(t_data *data, t_cmd *cmd, int *i)
{
	int	fd;

	if (data->token[*i + 1].tab)
	{
		fd = open(data->token[++(*i)].tab, O_RDONLY);
		if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
			cmd->infile_name = ft_strdup(data->token[*i].tab);
		if (fd == -1)
		{
			if (cmd->err_inf != HRDC_ERR && cmd->err_inf != INF_ERR)
				cmd->err_inf = INF_ERR;
		}
		else
			close(fd);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	return (0);
}

int	set_infile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		hrdc_nb;

	i = 0;
	hrdc_nb = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == REDIR_IN)
			if (open_redir_in(data, cmd, &i) == -1)
				return (-1);
		if (data->token[i].type == HEREDOC)
		{
			if (open_hrdc(data, cmd, &i, hrdc_nb) == -1)
				return (-1);
			hrdc_nb++;
		}
		if (data->token[i].type == PIPE)
			cmd = cmd->next;
		if (data->token[i].tab)
			i++;
	}
	return (0);
}
