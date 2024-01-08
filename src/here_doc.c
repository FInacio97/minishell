/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:27:31 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/08 19:27:20 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
*	@brief The name says it all: simulates a here_doc. It does it by reading from
*	the standard input, within the command itself and the limiter word.
*/
static void	here_doc(t_redirection *rdir, int fd[2])
{
	char	*s;
	int		len;
	
	set_signals(HNDLR_CHILD_HD);
	len = ft_strlen(rdir->key_wrd);
	while (1)
	{
		s = readline(">");
		if (g_signal == SIGINT || (ft_strncmp(rdir->key_wrd, s, len)
			== 0 && len == (int)(ft_strlen(s))))
			break ;
		write(fd[1], s, ft_strlen(s));
		free (s);
	}
	free (s);
	close(fd[0]);
	close(fd[1]);
	//All the memory has to be cleared here!
	exit(0);
}

/*
* @brief Checks if theres any here_doc in the redirections of each command
* and executes them, in case of it's existence.
*/
static void	here_doc_check(t_commands *cmd)
{
	int				fd[2];
	pid_t			pid;
	t_redirection	*redir;

	set_signals(HNDLR_LOOP); 	// apparently redundant, already done 
								// after prompt is valid on main
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type != RDIR_HDOC)
		{
			redir = redir->next;
			continue ;
		}
		to_close(cmd->hd_fd);
		if (pipe(fd) == 1)
			ft_printf("Error\n");	//	Error treatment!
		pid = fork();
		if (pid == 0)
			here_doc(redir, fd);
		wait(NULL);
		fd[1] = to_close(fd[1]);
		cmd->hd_fd = fd[0];
		redir = redir->next;
	}
}

/*
* @brief Manages all here_docs
*/
void	here_doc_manager(void)
{
	t_envp		*shell;
	t_commands	*current;

	shell = get_env_struct();
	current = shell->first_cmd_struct;
	while (current && g_signal == 0)
	{
		if (current->redirects)
			here_doc_check(current);
		current = current->next;
	}
	set_signals(HNDLR_LOOP); //probably needs to be HNDLR_LOOP
}
