#include "../header/minishell.h"

static void	set_cmd_str(t_data *data)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	cmd = data->cmd;
	while (data->token[i].tab)
	{
		if (data->token[i].type == CMD)
			cmd->cmd = data->token[i].tab;
		else if (data->token[i].type == CMD_BI)
			cmd->cmd_bi = data->token[i].tab;
		else if (data->token[i].type == STR)
		{
			cmd->str[j] = data->token[i].tab;
			j++;
		}
		else if (data->token[i].type == PIPE)
		{
			j = 0;
			cmd = cmd->next;
		}
		i++;
	}
}

static void	create_str_tab(t_data *data, t_cmd *cmd, int str_count)
{
	if (str_count)
	{
		printf("strcount = %d\n", str_count);
		cmd->str = ft_calloc(str_count + 1, sizeof(char *));
		if (!cmd->str)
			err_return(data, "minishell : memory allocation failed\n");
		str_count = 0;
		cmd = cmd->next;
	}
}

static void	set_str(t_data *data)
{
	int		i;
	int		str_count;
	t_cmd	*cmd;

	i = 0;
	cmd = data->cmd;
	str_count = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == STR)
			str_count++;
		if (data->token[i].type == PIPE)
		{
			create_str_tab(data, cmd, str_count);
			str_count = 0;
			cmd = cmd->next;
			// if (str_count)
			// {
			// 	cmd->str = ft_calloc(str_count + 1, sizeof(char *));
			// 	if (!cmd->str)
			// 		err_return(data,
			// 			"minishell : memory allocation failed\n");
			// 	str_count = 0;
			// 	cmd = cmd->next;
			// }
		}
		i++;
	}
	create_str_tab(data, cmd, str_count);
	// if (str_count)
	// {
	// 	cmd->str = ft_calloc(str_count + 1, sizeof(char *));
	// 	if (!cmd->str)
	// 		err_return(data, "minishell : memory allocation failed\n");
	// }
}

static void	set_cmd_lst(t_data *data)
{
	set_heredoc(data);
	set_infile(data);
	set_outfile(data);
	set_str(data);
	set_cmd_str(data);
	print_lst(data);
}

int	create_cmd_lst(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	data->cmd = NULL;
	while (i < data->cmd_count)
	{
		cmd = ft_cmdnew(data);
		if (!cmd)
		{
			free_data(data);
			data->err_code = 1;
			return (err_return(data, "minishell : memory allocation failed\n"));
				// gestion erreur
		}
		ft_cmdadd_back(&data->cmd, cmd);
		i++;
	}
	set_cmd_lst(data);
	return (0);
}
