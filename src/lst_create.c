#include "../header/minishell.h"

static void	set_cmd_lst(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	// set_heredoc(data);
	// set_infile(data);
	// set_outfile(data);
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
		i++;
		if (data->token[i].type == PIPE)
		{
			i++;
			cmd = data->cmd->next;
		}
	}
}

static void	set_lst_null(t_cmd *cmd)
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
