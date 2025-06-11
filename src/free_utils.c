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
	if (cmd->infile > 0)
		close(cmd->infile);
	if (cmd->outfile > 0)
		close(cmd->outfile);
	if (cmd->str)
		free(cmd->str);
}

void	free_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = data->cmd;
	while (cmd)
	{
		next = cmd->next;
		// free(cmd->str);
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
		if (data->cmd)
			free_cmd(data);
		if (data->token)
			free_token(data);
	}
}
