#include "../header/minishell.h"

void	print_lst(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->cmd;
	while (data->cmd != NULL)
	{
		printf("\\\\\\\tCMD\t\\\\\\\ncmd = %s\ncmd_bi = %s\nhrdc_path = %s\n",
			cmd->cmd, cmd->cmd_bi, cmd->hrdc_path);
		printf("infile fd = %d\noutfile fd = %d\n", cmd->infile, cmd->outfile);
		if (cmd->str)
		{
			while (cmd->str[i])
			{
				printf("str = %s\n", cmd->str[i]);
				i++;
			}
		}
		i = 0;
		if (!cmd->next)
			return ;
		cmd = cmd->next;
	}
}

char	*put_token(t_data *data, int start, int end)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_calloc(end - start + 2, sizeof(char));
	if (!token)
		exit_failure(data, "minishell : memory allocation failed\n");
	while (start <= end)
	{
		token[i] = data->input[start];
		start++;
		i++;
	}
	token[i] = '\0';
	return (token);
}

void	print_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		printf("\\\\\\\tTOKEN\t\\\\\\\ntoken[%d] = %s, type = %d, quote = %d\n",
			i, data->token[i].tab, data->token[i].type, data->token[i].quote);
		i++;
	}
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
