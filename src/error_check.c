#include "../header/minishell.h"

void	operator_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '|')
		{
			if (i == 0 || !data->token[i + 1].tab || is_operator(data->token[i
					+ 1].tab))
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
	}
}
