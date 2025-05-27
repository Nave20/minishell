#include "../header/minishell.h"

void	open_heredoc(t_data *data, char *delim)
{
	char	*input;
	int		fd;

	input = read_line("heredoc> ");
	fd = open();
	while (ft_strncmp(input, delim, ft_strlen(delim)) != 0)
	{
		free(input);
		input = read_line("heredoc> ");
	}
}

void	set_heredoc(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].type == HEREDOC)
		{
			if (data->token[i + 1].type == DELIM)
				open_heredoc(data, data->token[i + 1].tab);
			else
				return ; // pas de delim, erreur
		}
	}
}
