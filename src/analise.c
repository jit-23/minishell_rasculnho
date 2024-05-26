/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/25 19:56:50 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* missing \n and \\ - idk how or what to do */
void	fill_list(t_shell *shell, char *cmdl)
{
	int i;
	int t_loops = 0;
	t_placing place;
	
	i = 0;
	place = DEFAULT;
	while(cmdl[i])
	{
		if 	(cmdl[i] == '\"')
		{
			shell->n_dquotes++;
			if (shell->n_dquotes % 2)
				place = IN_DQ;
			i += get_quote(shell, place, '\"');
		}
		else if (cmdl[i] == '\'')
		{
			shell->n_squotes++;
			if (shell->n_squotes % 2)
				place = IN_SQ;
			i +=  get_quote(shell, place, '\"');
		}
		else if (cmdl[i] && !special_char(cmdl[i]) && !is_space(cmdl[i]))
			i += get_word(cmdl, i, shell, place);
		else if(cmdl[i] && is_space(cmdl[i]))
			i += get_space(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '$')
			i += get_env_var(cmdl, i, shell, place);
		else if (cmdl[i] && cmdl[i] == '|')
			i += get_pipe(shell, place);
		else if (cmdl[i] && cmdl[i] == '>' || cmdl[i] == '<')
			i += get_redirect_var(cmdl, i, shell, place);
	}
}

void	analise_cmd_line(t_shell *shell, char *cmdline)
{
	t_token *tmp;

	// trim edges on cmdline for = (' ' ; '\t');
	shell->token_list = (t_lexer *)s_malloc(sizeof(t_lexer));
	ft_memset(shell->token_list, 0, sizeof(t_lexer));
	fill_list(shell, cmdline);
	tmp = shell->token_list->head;
	while(tmp)
	{
		printf("===================\n");
		printf("token   = %s.\n", tmp->token);
		printf("Placing = %u.\n", tmp->placing);
		printf("Type    = %d.\n", tmp->type);
		tmp = tmp->next;
	}
}
