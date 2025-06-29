#include "../header/minishell.h"

void	free_double_tab(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	free_cmd_content(t_cmd *cmd)
{
	if (cmd->hrdc_path)
	{
		if (access(cmd->hrdc_path, F_OK) != -1)
			unlink(cmd->hrdc_path);
		free(cmd->hrdc_path);
		cmd->hrdc_path = NULL;
	}
	if (cmd->infile_name)
	{
		free(cmd->infile_name);
		cmd->infile_name = NULL;
	}
	if (cmd->outfile_name)
	{
		free(cmd->outfile_name);
		cmd->outfile_name = NULL;
	}
	if (cmd->str)
	{
		free_double_tab(cmd->str);
		cmd->str = NULL;
	}
}

void	free_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = data->cmd;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->cmd)
		{
			free(cmd->cmd);
			cmd->cmd = NULL;
		}
		if (cmd->cmd_bi)
		{
			free(cmd->cmd_bi);
			cmd->cmd_bi = NULL;
		}
		free_cmd_content(cmd);
		free(cmd);
		cmd = next;
	}
}

void	free_token(t_data *data)
{
	int	i;

	i = 0;
	if (data->token)
	{
		while (data->token[i].tab)
		{
			if (data->token[i].tab)
				free(data->token[i].tab);
			data->token[i].tab = NULL;
			i++;
		}
		free(data->token);
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->input)
			free(data->input);
		if (data->token)
			free_token(data);
		if (data->cmd)
			free_cmd(data);
		data->cmd_count = 0;
	}
}
