/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/25 01:43:08 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_list(t_shell *shell, char *cmdl)
{
	int i;
	t_placing place;

	place = DEFAULT;
	while(cmdl[i])
	{
		if 	(cmdl[i] == '\"')
		{
			place = IN_DQ;
			i++;
		}
		else if (cmdl[i] == '\'')
		{
			place = IN_SQ;
			i++;
		}
		if (cmdl[i] && !special_char(cmdl[i]))
		{
			
			i += get_word(cmdl, i, shell, place);
		}
		//else if (cmdl[i] == '<')
		//{
		//	// i += get_word(cmdl[i], i);
		//}	
		//t_token *tmp;
		//tmp = shell->token_list->head;
		
	}
}


void	analise_cmd_line(t_shell *shell, char *cmdline)
{
	t_token *tmp;

    if (cmdline)
        ft_strtrim(cmdline, " \t");
	shell->token_list = (t_lexer *)s_malloc(sizeof(t_lexer));
	ft_memset(shell->token_list, 0, sizeof(t_lexer));
	fill_list(shell, cmdline);
	tmp = shell->token_list->head;
	while(tmp)
	{
		printf("%s\n", tmp->token);
		tmp = tmp->next;
	}
}
