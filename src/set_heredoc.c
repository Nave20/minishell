#include "../header/minishell.h"

static int	open_and_fill_hrdc(int fd, char *delim, char *input, char *f_name)
{
	fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(input);
		return (-1); // inclure ce fichier dans cmd
	}
	while (ft_strncmp(input, delim, ft_strlen(delim)) != 0)
	{
		ft_putstr_fd(input, fd);
		free(input);
		input = readline("heredoc> ");
	}
	free(input);
	close(fd);
	return (0);
}

static int	create_heredoc(t_data *data, t_cmd *cmd, char *delim, int i_hrdc)
{
	char	*input;
	char	*str;
	char	*f_name;
	char	*hrdc_nbr;

	update_heredoc(cmd);
	input = readline("heredoc> ");
	str = "/tmp/heredoc";
	hrdc_nbr = ft_itoa(i_hrdc);
	if (!hrdc_nbr)
		err_return(data, "minishell : memory allocation failed\n, 1", 1);
	f_name = ft_strjoin(str, hrdc_nbr);
	free(hrdc_nbr);
	hrdc_nbr = NULL;
	if (!f_name)
		err_return(data, "minishell : memory allocation failed\n", 1);
	if (cmd->err_status != HRDC_ERR)
		cmd->hrdc_path = ft_strdup(f_name);
	free(f_name);
	if (open_and_fill_hrdc(0, delim, input, cmd->hrdc_path) == -1)
	{
		cmd->err_status = HRDC_ERR;
		return (0);
	}
	return (0);
}

void	handle_cmd_ending(t_data *data, t_cmd **cmd, int *i, int *j)
{
	if (!is_last_inf_hrdc(data, *j, *i))
	{
		if ((*cmd)->hrdc_path)
		{
			unlink((*cmd)->hrdc_path);
			free((*cmd)->hrdc_path);
		}
		(*cmd)->hrdc_path = NULL;
	}
	if (data->token[*i].type == PIPE)
	{
		*j = *i;
		*cmd = (*cmd)->next;
	}
}

static int	handle_heredoc(t_data *data, t_cmd *cmd, int i)
{
	static int	i_hrdc;

	if (data->token[i + 1].type == DELIM)
	{
		if (create_heredoc(data, cmd, data->token[i + 1].tab, i_hrdc) == -1)
			return (-1);
	}
	else
		return (err_return(data,
				"minishell: syntax error near unexpected token `newline'", 2));
	i_hrdc++;
	return (0);
}

int	set_heredoc(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == HEREDOC)
		{
			if (handle_heredoc(data, cmd, i) == -1)
				return (-1);
		}
		if (data->token[i].type == PIPE || !data->token[i].tab)
			handle_cmd_ending(data, &cmd, &i, &j);
		i++;
	}
	return (0);
}
