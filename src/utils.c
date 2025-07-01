#include "../header/minishell.h"

void	print_lst(t_data *data)
{
	t_cmd	*cmd;
	int		i;
	int		len;

	len = 0;
	i = 0;
	cmd = data->cmd;
	while (data->cmd != NULL)
	{
		printf("\\\\\\\tCMD\t\\\\\\\ncmd = %s\ncmd_bi = %s\n", cmd->cmd,
			cmd->cmd_bi);
		if (cmd->str)
		{
			while (cmd->str[len])
				len++;
			while (i < len)
			{
				if (cmd->str[i][0] == '\0')
					printf("str = \"\"\n");
				else
					printf("str = %s\n", cmd->str[i]);
				i++;
			}
		}
		i = 0;
		len = 0;
		if (cmd->cmd_tab)
		{
			while (cmd->cmd_tab[len])
				len++;
			while (i < len)
			{
				if (cmd->cmd_tab[i][0] == '\0')
					printf("cmd_tab = \"\"\n");
				else
					printf("cmd_tab = %s\n", cmd->cmd_tab[i]);
				i++;
			}
		}
		printf("hrdc_path = %s\ninfile  = %s\noutfile = %s\n", cmd->hrdc_path,
			cmd->infile_name, cmd->outfile_name);
		i = 0;
		len = 0;
		if (!cmd->next)
			return ;
		cmd = cmd->next;
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

bool	ft_isspace(char c)
{
	if (c >= 9 && c <= 13)
		return (true);
	else
		return (false);
}

// int	create_env_tab(t_all *all)
// {
// 	char	**env_tab;
// 	t_env	*env;
// }
