/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:00:04 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/25 01:20:22 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"




int	special_char(char c)
{
    if (c == '>' || c == '<' \
    	|| c == '\n' || c == '\'' || c == '\"' || c == '$' || c == '|')
			return (1);
	return (0);
}

int	get_word(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int k;
	int j;

	j = i;
	k = 0;
	char *og_word;
	char *to_stick;
	to_stick = (char *)s_malloc(sizeof(char) * 2);
	to_stick[1] = '\0';
	og_word = (char *)s_malloc(sizeof(char));
	og_word[0] = '\0';
	while (cmdl[j] && !special_char(cmdl[j]))
	{
		to_stick[0] = cmdl[j];
		og_word = ft_strjoin(og_word, to_stick);
		j++;
	}
	add_to_list(sh->token_list, og_word, WORD, placing);
	
	return (j - i);
}
