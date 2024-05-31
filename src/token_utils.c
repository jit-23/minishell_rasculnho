/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:00:04 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/31 02:52:14 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);	
}

int	special_char(char c)
{
    if (c == '>' || c == '<' \
    	|| c == '\n' || c == '\'' || c == '\"' || c == '$' || c == '|')
			return (1);
	return (0);
}


/* put all the fill_list functions on a file named "fill_list_utils.c" */
/*							 |
							 V 											*/
int	get_space(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int j;

	j = 0;

	char *og_space;
	og_space = s_malloc(sizeof(char) * 2);
	og_space[1] = '\0';
	og_space[0] = cmdl[i];
	add_to_list(sh->token_list, og_space, SPACE_BAR, placing);
	return (1);
}

int	get_quote(t_shell *sh, t_placing placing, char quote_type)
{
	char *quote_token;

	quote_token = (char *)s_malloc(sizeof(char) * 2);
	quote_token[1] = '\0';
	if (quote_type == '\'')
	{
		printf("-----------------------SQ\n");
		quote_token[0] = '\'';
		add_to_list(sh->token_list, quote_token, S_QUOTE, placing);	
	}
	else
	{
		printf("-----------------------DQ\n");
		quote_token[0] = '\"';
		add_to_list(sh->token_list, quote_token, D_QUOTE, placing);	
	}
	return (1);
}

int	get_word(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int j;

	j = i;
	char *og_word;
	char *to_stick;
	to_stick = (char *)s_malloc(sizeof(char) * 2);
	to_stick[1] = '\0';
	og_word = (char *)s_malloc(sizeof(char));
	og_word[0] = '\0';
	while (cmdl[j] && !special_char(cmdl[j]) && !is_space(cmdl[j]))
	{
		to_stick[0] = cmdl[j];
		og_word = ft_strjoin(og_word, to_stick);
		j++;
	}
	add_to_list(sh->token_list, og_word, WORD, placing);
	return (j - i);
}
int	get_env_var(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int j;

	j = i + 1;
	char *env_var;
	char *to_stick;
	to_stick = (char *)s_malloc(sizeof(char) * 2);
	to_stick[1] = '\0';
	env_var = (char *)s_malloc(sizeof(char) * 2);
	env_var[0] = '$';
	env_var[1] = '\0';
	while(cmdl[j] && !special_char(cmdl[j]) && !is_space(cmdl[j]))
	{
		to_stick[0] = cmdl[j];
		env_var = ft_strjoin(env_var, to_stick);
		j++;
	}
	add_to_list(sh->token_list, env_var, ENV, placing);
	return (j - i);
}

int get_pipe(t_shell *sh, t_placing placing)
{
	char *pipe_var;

	pipe_var = (char *)s_malloc(sizeof(sizeof(char) * 2));
	pipe_var[1] = '\0';
	pipe_var[0] = '|';
	add_to_list(sh->token_list, pipe_var, PIPE, placing);
	return (1);
}

void organize_var_type(t_shell *sh, char *token, t_placing placing)
{
	if (!ft_strncmp(token, ">>", ft_strlen(">>")))
		add_to_list(sh->token_list, token, DREDIREC, placing);
	else if (!ft_strncmp(token, "<<", ft_strlen("<<")))
		add_to_list(sh->token_list, token, HEREDOC, placing);
	else if (!ft_strncmp(token, "<", ft_strlen("<")))
		add_to_list(sh->token_list, token, REDIR_IN, placing);
	else if (!ft_strncmp(token, ">", ft_strlen(">")))
		add_to_list(sh->token_list, token, REDIR_OUT, placing);
	else
		perror("ERROR ON '<' OR '>' parsing");
}

int get_redirect_var(char *cmdl, int i, t_shell *sh, t_placing placing)
{
	int j;
	char var;
	char *token;
	char *to_stick;

	
	token = (char *)s_malloc(sizeof(char ) * 2);
	token[0] = var;
	token[1] = '\0';
	to_stick = (char *)s_malloc(sizeof(char)  * 2);
	to_stick[1] = '\0';
	var = cmdl[i];
	j = i;
	while(cmdl[j] == var && j < (i + 2))
	{
		to_stick[0] = cmdl[j];
		token = ft_strjoin(token , to_stick);
		j++;
	}
	organize_var_type(sh, token, placing);
	return (j - i);
}
