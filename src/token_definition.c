#include "../header/minishell.h"

static void	handle_redirout_cmd(t_data *data, int *i)
{
	if (data->token[*i].type == REDIR_OUT)
	{
		data->token[*i + 1].type = OUTFILE;
		(*i) += 2;
		if (!data->token[*i].type)
			data->token[*i].type = CMD;
	}
	if (data->token[*i].type == APPEND)
	{
		data->token[*i + 1].type = OUTFILE;
		i += 2;
		if (!data->token[*i].type)
			data->token[*i].type = CMD;
	}
}

static void	handle_redir_cmd(t_data *data, int end)
{
	int	i;

	i = 0;
	if (!data->token[i].type)
		data->token[i].type = CMD;
	while (i < end)
	{
		if (data->token[i].type == REDIR_IN)
		{
			data->token[i + 1].type = INFILE;
			i += 2;
			if (!data->token[i].type)
				data->token[i].type = CMD;
		}
		if (data->token[i].type == HEREDOC)
		{
			data->token[i + 1].type = DELIM;
			i += 2;
			if (!data->token[i].type)
				data->token[i].type = CMD;
		}
		handle_redirout_cmd(data, &i);
		i++;
	}
}

static void	handle_simple_cmd(t_data *data, int end)
{
	int	i;

	i = 1;
	data->token[0].type = CMD;
	while (i < end)
	{
		if (data->token[i].tab[0] == '-')
			data->token[i].type = FLAG;
		else
			data->token[i].type = ARG;
		i++;
	}
}

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

void	define_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '-')
			data->token[i].type = FLAG;
		i++;
	}
	i = 0;
	while (data->token[i].tab)
	{
		while (data->token[i].tab && data->token[i].tab[0] != '|')
			i++;
		if (is_simple_cmd(data, i))
			handle_simple_cmd(data, i);
		else
			handle_redir_cmd(data, i);
		if (data->token[i].tab)
		{
			i++;
			data->cmd_count++;
		}
	}
	define_build_in(data);
}
