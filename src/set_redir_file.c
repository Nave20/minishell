#include "../header/minishell.h"

void	set_outfile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		fd;

	i = 0;
	cmd = data->cmd;
	while (data->token[i].tab && data->token[i].type != PIPE)
	{
		if (data->token[i].type == REDIR_OUT || data->token[i].type == APPEND)
		{
			if (data->token[i].tab)
			{
				fd = open(data->token[++i].tab, O_RDWR | O_CREAT);
				data->cmd->outfile = fd;
			}
			else
				return ;
		}
		i++;
		if (data->token[i].type == PIPE)
		{
			i++;
			cmd = data->cmd->next;
		}
	}
}

void	set_infile(t_data *data)
{
	int		i;
	t_cmd	*cmd;
	int		fd;

	i = 0;
	cmd = data->cmd;
	while (data->token[i].tab && data->token[i].type != PIPE)
	{
		if (data->token[i].type == REDIR_IN)
		{
			if (data->token[i + 1].tab)
			{
				fd = open(data->token[++i].tab, O_RDWR);
				data->cmd->infile = fd;
			}
			else
				return ;
		}
		i++;
		if (data->token[i].type == PIPE)
		{
			i++;
			cmd = data->cmd->next;
		}
	}
}
