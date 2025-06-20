#include "../header/minishell.h"

static void	define_build_in(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == CMD && is_build_in(data->token[i].tab))
			data->token[i].type = CMD_BI;
		i++;
	}
}

static void	define_str(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (!data->token[i].type)
			data->token[i].type = STR;
		i++;
	}
}

void	define_token(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[i].tab)
	{
		while (data->token[i].tab && data->token[i].tab[0] != '|')
			i++;
		if (is_simple_cmd(data, i))
			handle_simple_cmd(data, j, i);
		else
			handle_redir_cmd(data, j, i);
		if (data->token[i].tab)
		{
			i++;
			j = i;
			data->cmd_count++;
		}
	}
	define_str(data);
	define_build_in(data);
	print_token(data);
	set_env_var(data);
}
