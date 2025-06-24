#include "../header/minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	t_cmd	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			ptr = ft_cmdlast(*lst);
			ptr->next = new;
		}
	}
}

t_cmd	*ft_cmdnew(t_data *data)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		exit_failure(data, "minishell : memory allocation failed\n");
	new->infile = -2;
	new->outfile = -2;
	new->next = NULL;
	return (new);
}
