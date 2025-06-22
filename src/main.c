#include "../header/minishell.h"

int	main(void)
{
	t_data	data;
	int		nbword;

	while (1)
	{
		data.input = readline("minishell> ");
		if (data.input)
		{
			add_history(data.input);
			nbword = word_count(data.input);
			data.token = ft_calloc(nbword + 1, sizeof(t_token));
			if (!data.token)
				exit_failure(&data, "minishell : memory allocation failed\n");
			if (tokenize_input(&data, data.input) == -1)
			{
				ft_putstr_fd("minishell : unclosed quotes\n", 2);
				data.err_code = 2;
				return (2); // gestion erreur
			}
			free(data.input);
			data.input = NULL;
			operator_check(&data);
			data.cmd_count = 1;
			print_token(&data);
			define_token(&data, 0);
			print_token(&data);
			create_cmd_lst(&data);
			free_data(&data);
		}
	}
	return (0);
}
