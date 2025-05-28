#include "../header/minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	t_cmd	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			ptr = ft_cmdlast(*lst);
			ptr->next = new;
		}
	}
}

void	print_lst(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (data->cmd != NULL)
	{
		printf("cmd = %s\ncmd_bi = %s\nhrdc_path = %s, delim = %s\n", cmd->cmd,
			cmd->cmd_bi, cmd->hrdc_path, cmd->delim);
		printf("infile fd = %d\noutfile fd = %d", cmd->infile, cmd->outfile);
	}
}

static void	set_cmd_lst(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	cmd = data->cmd;
	set_heredoc(data);
	set_infile(data);
	set_outfile(data);
	while (data->token[i].tab && data->token[i].type != PIPE)
	{
		if (data->token[i].type == CMD)
			cmd->cmd = data->token[i].tab;
		if (data->token[i].type == CMD_BI)
			cmd->cmd_bi = data->token[i].tab;
		if (data->token[i].type == STR)
			cmd->str[j] = data->token[i].tab;
		i++;
		if (data->token[i].type == PIPE)
		{
			i++;
			cmd = data->cmd->next;
		}
	}
}

void	create_cmd_lst(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	data->cmd = NULL;
	while (i <= data->cmd_count)
	{
		cmd = ft_cmdnew();
		if (!cmd)
			exit(EXIT_FAILURE); // gestion erreur
		ft_cmdadd_back(&data->cmd, cmd);
		i++;
	}
	set_cmd_lst(data);
}
