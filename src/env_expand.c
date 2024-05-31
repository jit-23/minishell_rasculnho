/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 00:04:43 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/31 02:08:21 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/env.h"

char *get_env_value(char *env_var)
{
    int i;
    char *s;
    char *t;
    
    i = 0;
    s = malloc(sizeof(char) * 1);
    t = malloc(sizeof(char) * 2);
    s[0] = '\0';
    t[1] = '\0';
    while(env_var[i] != '=')
        i++;
    i++;
    while(env_var[i])
    {
        t[0] = env_var[i];
        s = ft_strjoin(s,t);
        i++;
    }
    return (s);
}

char *get_name(char *env_var)
{
    int i;

    i = 0;
    char *s;
    char *t;
    s = malloc(sizeof(char) * 1);
    t = malloc(sizeof(char) * 2);
    s[0] = '\0';
    t[1] = '\0';
    while(env_var[i] != '=')
    {
        t[0] = env_var[i];
        s = ft_strjoin(s,t);
        i++;
    }
    return(s);
}

t_env *new_env_node(char *env) // prev e definido na funcao na qual este e chamada
{
    t_env *new_node;
	
    new_node = (t_env *)s_malloc(sizeof(t_env));
	new_node->env_name = get_name(env);
	new_node->env_value = get_env_value(env);
    new_node->next = NULL;
    return (new_node);    
}

t_env *expand_env(t_shell *shell, char **env)
{
    t_env *ptr;
    t_env *a;
    t_env *head;
    int i;

    i = -1;
    while(env[++i])
    {
        if (i == 0)
        {
            ptr = new_env_node(env[i]);
            head = ptr;
            ptr->prev = NULL;
        }
        else
        {
            ptr->next = new_env_node(env[i]);
            a = ptr;
            ptr = ptr->next;
            ptr->prev = a;
        }
    }
    ptr->next = NULL;
    return (head);
}
