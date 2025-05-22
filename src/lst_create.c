#include "../header/minishell.h"

void set_lst_

	void
	set_lst_null(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->arg = NULL;
	cmd->opt = NULL;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->delim = 0;
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
