/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:47:31 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/04 02:28:37 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec *init_exec()
{
    t_exec *exec;

    exec = (t_exec *)malloc(sizeof(t_exec));
    if (!exec)
    {
        ft_putstr_fd("error on malloc\n", 2);
        return (NULL);
    }
    exec->type = _EXEC;
    exec->args = (char **)malloc(sizeof(char *) * 20);
    return (exec);
}

t_pipe *init_pipe()
{
    t_pipe *pipe;

    pipe = (t_pipe *)malloc(sizeof(t_pipe));
    if (!pipe)
    {
        ft_putstr_fd("error on malloc\n", 2);
        return (NULL);
    }
    pipe->type = _PIPE;
    pipe->left = NULL;
    pipe->right = NULL;
    return (pipe);
}

t_cmd *exec_parse(t_shell*sh, t_exec *exec_struct)
{
    t_token *tmp;
    int i;

    i = 0;
    tmp = sh->token_list->head;
    if (sh->token_list->head->prev == NULL)
        sh->root = (t_cmd *)exec_struct;
    while(tmp && peek_token(tmp, 1, "|") == 0)
    {
        exec_struct->args[i++] = ft_strdup(tmp->token);
        tmp = tmp->next;
    }
    exec_struct->args[i] = NULL;
    sh->token_list->head = tmp;
    return ((t_cmd *)exec_struct);
}

int peek_future_tokens(t_token *head, t_type type)
{
    t_token *tmp;

    tmp = head;
    while(head)
    {
        if ()
    }
}

t_cmd   *pipe_parse(t_shell *sh, t_cmd *left)
{
    t_pipe *pipe_struct;

    pipe_struct = init_pipe();
    pipe_struct->left = left;
    sh->root = (t_cmd *)pipe_struct;
    if (peek_future_tokens(sh->token_list->head, PIPE))
        pipe_struct->right =  pipe_parse(sh, sh->root);
    else if (peek_future_tokens(sh->token_list->head, WORD))
        pipe_struct->right = exec_parse(sh, init_exec());
}

void    init_AST(t_shell *sh)
{
    if (sh->token_list->head->type == WORD)
        parse_exec(sh, init_exec());
    if (sh->token_list->head == NULL)
        return ;
    parse_pipe(sh, sh->root);
}
