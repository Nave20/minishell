#include "../header/minishell.h"

static void	handle_redirout_cmd(t_data *data, int *i)
{
	if (data->token[*i].type == REDIR_OUT)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = OUTFILE;
			if (data->token[*i + 1].tab && !data->token[(*i) + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
	if (data->token[*i].type == APPEND)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = OUTFILE;
			if (data->token[*i + 1].tab && !data->token[(*i) + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
}

static void	handle_redirin_cmd(t_data *data, int *i)
{
	if (data->token[*i].type == REDIR_IN)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = INFILE;
			if (data->token[*i + 1].tab && !data->token[*i + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
	if (data->token[*i].type == HEREDOC)
	{
		if (data->token[*i + 1].tab)
		{
			data->token[++(*i)].type = DELIM;
			if (data->token[*i + 1].tab && !data->token[*i + 1].type)
				data->token[++(*i)].type = CMD;
		}
	}
}

static void	handle_redir_cmd(t_data *data, int start, int end)
{
	if (!data->token[start].type)
		data->token[start].type = CMD;
	while (start < end)
	{
		handle_redirin_cmd(data, &start);
		handle_redirout_cmd(data, &start);
		start++;
	}
}

static void	handle_simple_cmd(t_data *data, int start, int end)
{
	data->token[start].type = CMD;
	start++;
	while (start < end)
	{
		data->token[start].type = STR;
		start++;
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
	i = 0;
	while (data->token[i].tab)
	{
		if (!data->token[i].type)
			data->token[i].type = STR;
		i++;
	}
	define_build_in(data);
}
