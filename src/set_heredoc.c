#include "../header/minishell.h"

static void	update_heredoc(t_cmd *cmd, int fd)
{
	if (cmd->infile != 0)
	{
		close(fd);
		fd = 0;
		unlink(cmd->hrdc_path);
		free(cmd->hrdc_path);
		cmd->hrdc_path = NULL;
	}
}

static void	open_heredoc(t_data *data, t_cmd *cmd, char *delim, int i_hrdc)
{
	char		*input;
	static int	fd;
	char		*str;
	char		*f_name;
	char		*hrdc_nbr;

	(void)data;
	update_heredoc(cmd, fd);
	input = readline("heredoc> ");
	str = "/tmp/heredoc";
	hrdc_nbr = ft_itoa(i_hrdc);
	f_name = ft_strjoin(str, ft_itoa(i_hrdc));
	free(hrdc_nbr);
	if (!f_name)
		return ; // erreur malloc
	fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	while (ft_strncmp(input, delim, ft_strlen(delim)) != 0)
	{
		ft_putstr_fd(input, fd);
		free(input);
		input = readline("heredoc> ");
	}
	cmd->hrdc_path = f_name;
	cmd->infile = fd;
	free(input);
}

void	handle_cmd_ending(t_data *data, t_cmd **cmd, int *i, int *j)
{
	if (!is_last_inf_hrdc(data, *j, *i))
	{
		close((*cmd)->infile); // protection
		(*cmd)->infile = 0;
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

void	handle_heredoc(t_data *data, t_cmd *cmd, int i)
{
	static int	i_hrdc;

	if (data->token[i + 1].type == DELIM)
		open_heredoc(data, cmd, data->token[i + 1].tab, i_hrdc);
	else
		return ; // pas de delim, erreur
	i_hrdc++;
}

void	set_heredoc(t_data *data)
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
			handle_heredoc(data, cmd, i);
		if (data->token[i].type == PIPE || !data->token[i].tab)
			handle_cmd_ending(data, &cmd, &i, &j);
		i++;
	}
}
