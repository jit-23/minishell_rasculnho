/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:01:30 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/07 23:27:05 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_first_list(t_shell *shell, char *cmdl)
{
	int i;
	int t_loops;
	t_placing place;


	t_loops = 0;
	i = 0;
	place = DEFAULT;
	while(cmdl[i])
	{
		if (cmdl[i] == '\"')
		{
			if (place == DEFAULT)
			{
				i+= get_quote(shell, place, '\"');
				place = IN_DQ;
			}
			else if (place == IN_DQ)
			{
				place = DEFAULT;
				i+= get_quote(shell, place, '\"');
			}
			else if (place == IN_SQ)
			{
				i+= get_quote(shell, place, '\"');
			}
		}
		else if (cmdl[i] == '\'')
		{
			if (place == DEFAULT)
			{
				i += get_quote(shell, place, '\'');
				place = IN_SQ;
			}
			else if (place == IN_DQ)
			{
				i+= get_quote(shell, place, '\'');
			}
			else if (place == IN_SQ)
			{
				place = DEFAULT;
				i+= get_quote(shell, place, '\'');
			}
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


//init_tree(shell, shell->cmd_line, shell->token_list->head);
void	analise_cmd_line(t_shell *shell, char *cmdline)
{
	t_token *head;
	

	// trim edges on cmdline for = (' ' ; '\t');
	shell->token_list = (t_lexer *)s_malloc(sizeof(t_lexer));
	ft_memset(shell->token_list, 0, sizeof(t_lexer));
	fill_first_list(shell, cmdline);
	head = shell->token_list->head;
	//fill_second_list(shell,head);
	//printf("DONE\n");
	
	//while(head)
	//{
	//	printf("===================\n");
	//	printf("token   = %s.\n", head->token);
	//	printf("Placing = %u.\n", head->placing);
	//	printf("Type    = %d.\n", head->type);
	//	head = head->next;
	//}
	
	init_AST(shell);
	printf("root type - %d\n", shell->root->type);
	printf("---print_tree---\n");
	print_tree(shell->root);
	//print_manual(shell->root);
}
