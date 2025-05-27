#include "../header/minishell.h"

void	set_cmd_lst(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	set_infile(data);
	set_outfile(data);
	set_heredoc(data);
	while (data->token[i].tab && data->token[i].type != PIPE)
	{
		if (data->token[i].type == CMD)
			cmd->cmd = data->token[i].tab;
		if (data->token[i].type == CMD_BI)
			cmd->cmd_bi = data->token[i].tab;
		if (data->token[i].type == ARG)
			cmd->arg = data->token[i].tab;
		if (data->token[i].type == FLAG)
			cmd->flag = data->token[i].tab;
		// if (data->token[i].type == INFILE)
		// 	find_infile(data);
		// if (data->token[i].type == OUTFILE)
		// 	find_outfile(data);
		// if (data->token[i].type == DELIM)
		// 	cmd->delim = data->token[i].tab;
		i++;
		if (data->token[i].type == PIPE)
		{
			i++;
			cmd = data->cmd->next;
		}
	}
}

void	set_lst_null(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->cmd_bi = NULL;
	cmd->arg = NULL;
	cmd->flag = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->delim = NULL;
	cmd->next = NULL;
}

void	create_cmd_lst(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 1;
	while (i <= data->cmd_count)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			exit(EXIT_FAILURE); // gestion erreur
		ft_lstadd_back(data->cmd, ft_lstnew(cmd));
		set_lst_null(data->cmd);
	}
	set_cmd_lst(data);
}
