/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:18:06 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/26 01:50:46 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *new_node(char *token, t_type type, t_placing placing) // prev e definido na funcao na qual este e chamada
{
    t_token *new_node;
	
    new_node = (t_token *)s_malloc(sizeof(t_token));
	new_node->token = (char *)s_malloc(sizeof(char));
	new_node->token[0] = '\0';
    new_node->token = ft_strjoin(new_node->token, token);
	new_node->type = type;
    new_node->placing = placing;
    new_node->next = NULL;
    return (new_node);    
}

void	delete_lst(t_token **head, int size)
{
	t_token	*del;

	auto int i = -1;
 	del = (*head);
	while (++i < size)
	{
		del = del->next;
		free(*head);
		(*head) = del;
	}
}

t_token	*ft_lstlast(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

int	lst_size(t_token **head)
{
	t_token	*node;
	int		size;

	if (!(*head))
		return (0);
	node = (*head);
	size = 0;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

void	add_to_list(t_lexer *token_list, char *word, t_type type, t_placing placing)
{
	t_token *head;
	t_token *prev;
	t_token *last;
	//printf("ADD_TO_LIST :\n");
	//printf("word - %s\n",word);
	//printf("type - %d\n",type);
	//printf("placing - %u\n",placing);

	if (!token_list->head)
	{
		token_list->head = new_node(word, type, placing);
		token_list->head->prev = NULL;
		return ;
	}
	head = token_list->head;
	last = ft_lstlast(head);
	last->next = new_node(word, type, placing);
	prev = last;
	last = last->next;
	last->prev = prev;
}