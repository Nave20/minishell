/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:44:18 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/27 11:44:18 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	exec_two(t_all all)
{

}

void	exec_one(t_all all)
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*cmd;
	pid_t	pid;

	prev_fd = -2;
	cmd = all.cmd;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			if (cmd->infile != -2)
				dup2(cmd->infile, STDIN_FILENO);
			else if (prev_fd != -2)
				dup2(prev_fd, STDIN_FILENO);
			if (cmd->outfile != -2)
				dup2(cmd->outfile, STDOUT_FILENO);
			else if (cmd->next)
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (pipe_fd[0])
				close(pipe_fd[0]);
			if (pipe_fd[1])
				close(pipe_fd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd)
			{

			}
			else
				hub(all);
		}
	}
}

int	cmd_nbr(t_cmd *cmd)
{
	int		i;
	t_cmd	*ptr;

	i = 1;
	ptr = cmd->next;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}