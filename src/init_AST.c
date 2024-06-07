/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:47:31 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/06/07 23:25:49 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int peek_token(t_token *checker,int var_nbr, ...)
{
    va_list ptr;
    int flag;
    int i;
    char *token;

    i = 0;
    flag = 1;
    token = checker->token;
    va_start(ptr, var_nbr);
    
    while(i < var_nbr)
    {
        flag = ft_strncmp(token , va_arg(ptr, char *), ft_strlen(token));
        if (flag == 0)
            return (1);
        i++;
    }
    va_end(ptr);
    return (0);
}

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



int peek_future_tokens_type(t_token *head, t_type type)
{
    t_token *tmp;

    tmp = head;
    while(tmp)
    {
        //printf("type token %s\n", tmp->token);
        if (tmp->type == type) 
            return (1);
        tmp = tmp->next; 
    }
    return (0);
}

/* LS -L | WC */
 //tmp = LS;
 
t_cmd *exec_parse(t_shell*sh, t_exec *exec_struct)
{
    printf("===exec parse function===\n");
    t_token *tmp;
    int i;

    i = 0;
    tmp = sh->token_list->head;
    if (sh->token_list->head->prev == NULL)
        sh->root = (t_cmd *)exec_struct;
    while(tmp && (peek_token(tmp, 1, "|") == 0))
    {
        if (peek_token(tmp, 2 , " ", "\t") == 1)
            tmp = tmp->next;
        else
        {
            exec_struct->args[i] = ft_strdup(tmp->token);
            tmp = tmp->next;
            i++;
        }
    }
    exec_struct->args[i] = NULL;
    sh->token_list->head = tmp;
    return ((t_cmd *)exec_struct);
}

t_cmd   *pipe_parse(t_shell *sh, t_cmd *left)
{
    t_pipe *pipe_struct;

    pipe_struct = init_pipe();
    pipe_struct->left = left;
    sh->root = (t_cmd *)pipe_struct;
    if (sh->token_list->head->next)
        sh->token_list->head = sh->token_list->head->next;
//    printf("token no qual comeca a procurar se tem pipes a frente %s.%s.%s\n",sh->token_list->head->prev->token,sh->token_list->head->token, sh->token_list->head->next->token);
    if (peek_future_tokens_type(sh->token_list->head, PIPE))
    {
        pipe_struct->right = exec_parse(sh, init_exec());
        pipe_parse(sh ,(t_cmd *)sh->root);
    }
    else if (peek_future_tokens_type(sh->token_list->head, WORD))
        pipe_struct->right = exec_parse(sh, init_exec());
    return ((t_cmd *)pipe_struct);
}

void    init_AST(t_shell *sh)
{
    if (sh->token_list->head->type == WORD)
        exec_parse(sh, init_exec());
    if (sh->token_list->head == NULL)
        return ;
    pipe_parse(sh, sh->root);
}

void print_tree(t_cmd *root)
{
    static int j;
    t_exec *ex;
    t_pipe *pp;
    if (root == NULL)
        return ;
    if (root->type == _EXEC)
    {
        ex = (t_exec *)root;
        for (int i = 0; ex->args[i]; i++)
        {
            printf("%d - args - %s\n",j ,ex->args[i]);
        }
        j++;
    }
    else if (root->type == _PIPE)
    {
        pp = (t_pipe *)root;
        printf("%d pipe - | \n", j);
        j++;
        print_tree((t_cmd *)pp->left);
        print_tree((t_cmd *)pp->right);
    }
}
