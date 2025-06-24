#include "../header/minishell.h"

void	exit_failure(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	free_data(data);
	exit(EXIT_FAILURE);
}

void	operator_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '|')
		{
			if (!data->token[i + 1].tab || data->token[i + 1].tab[0] == '|'
				|| i == 0)
				return ; // bash: syntax error near unexpected token `|'
		}
		if (data->token[i].tab[0] == '<')
		{
			if (!data->token[i + 1].tab || is_operator(data->token[i + 1].tab))
				return ; // bash: syntax error near unexpected token `newline'
		}
		if (data->token[i].tab[0] == '>')
		{
			if (!data->token[i + 1].tab || is_operator(data->token[i + 1].tab))
				return ; // bash: syntax error near unexpected token `newline'
		}
		i++;
	}
}
