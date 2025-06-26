#include "../header/minishell.h"

int	err_return_token(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	free(data->input);
	free_token(data);
	return (-1);
}

int	err_return(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	free_data(data);
	return (-1);
}

int	operator_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '|' && (!data->token[i + 1].tab
				|| data->token[i + 1].tab[0] == '|' || i == 0 || data->token[i
				+ 1].tab[0] == '\0'))
			return (err_return_token(data,
					"minishell: syntax error near unexpected token '|'\n"));
		if (data->token[i].tab[0] == '<' && (!data->token[i + 1].tab
				|| is_operator(data->token[i + 1].tab) || (data->token[i
					+ 1].tab[0] == '\0')))
			return (err_return_token(data,
					"minishell: syntax error near unexpected token `newline'\n"));
		if (data->token[i].tab[0] == '>' && (!data->token[i + 1].tab
				|| is_operator(data->token[i + 1].tab) || (data->token[i
					+ 1].tab[0] == '\0')))
			return (err_return_token(data,
					"minishell: syntax error near unexpected token `newline'\n"));
		i++;
	}
	return (0);
}
