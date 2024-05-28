/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:09:12 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/29 00:27:33 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* t_cmd *init_exec(t_shell *sh)
{
    t_cmd *cmd;

    cmd = (t_exec *)malloc(sizeof(t_exec));
    cmd->type = _EXEC;
    return ((t_cmd *)cmd);
}

t_cmd *init_redir(t_shell *sh)
{
    t_cmd   *cmd;

    cmd = (t_redir *)malloc(sizeof(t_redir));
    cmd->type = _EXEC;
    return ((t_cmd *)cmd);
}

t_cmd *init_redir(t_shell *sh)
{
    t_cmd   *cmd;

    cmd = (t_redir *)malloc(sizeof(t_redir));
    cmd->type = _REDIR;
    return ((t_cmd *)cmd);
}

t_cmd *init_pipe(t_shell *sh)
{
    t_cmd   *cmd;

    cmd = (t_pipe *)malloc(sizeof(t_pipe));
    cmd->type = _PIPE;
    return ((t_cmd *)cmd);
}


void    init_tree(t_shell *sh)
{
    int type;

    type = 
} */