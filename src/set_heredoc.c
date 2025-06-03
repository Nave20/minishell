#include "../header/minishell.h"

static void	open_heredoc(t_data *data, t_cmd *cmd, char *delim, int i_hrdc)
{
	char		*input;
	static int	fd;
	char		*str;
	char		*f_name;
	char		*hrdc_nbr;

	(void)data;
	if (cmd->infile != 0)
	{
		close(fd);
		fd = 0;
		unlink(cmd->hrdc_path);
		free(cmd->hrdc_path);
		cmd->hrdc_path = NULL;
	}
	input = readline("heredoc> ");
	str = "/tmp/heredoc";
	hrdc_nbr = ft_itoa(i_hrdc);
	f_name = ft_strjoin(str, hrdc_nbr);
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
	free(input);
	cmd->infile = fd;
}

void	set_heredoc(t_data *data)
{
	int		i;
	int		j;
	int		i_hrdc;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	i_hrdc = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == HEREDOC)
		{
			if (data->token[i + 1].type == DELIM)
				open_heredoc(data, cmd, data->token[i + 1].tab, i_hrdc);
			else
				return ; // pas de delim, erreur
			i_hrdc++;
		}
		if (data->token[i].type == PIPE || !data->token[i].tab)
		{
			if (!is_last_inf_hrdc(data, j, i))
			{
				close(cmd->infile); // protection
				cmd->infile = 0;
				if (cmd->hrdc_path)
				{
					unlink(cmd->hrdc_path);
					free(cmd->hrdc_path);
				}
				cmd->hrdc_path = NULL;
			}
			if (data->token[i].type == PIPE)
			{
				j = i;
				cmd = cmd->next;
			}
		}
		i++;
	}
}
