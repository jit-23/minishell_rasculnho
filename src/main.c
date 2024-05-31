/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/31 02:01:09 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/env.h"


static void get_prompt(t_shell *shell)
{
    char *dir;

    dir = NULL;
    dir = getcwd(dir, 100);
    shell->prompt= ft_strjoin(dir, "$ ");
    shell->cmd_line = readline(shell->prompt);
    if (shell->cmd_line)
        add_history(shell->cmd_line);
    free(dir);
}

int main(int ac,char **av ,char **ev)
{
	t_shell shell;
    if (ac != 1)
        return (1); // msg erro
    shell.ev = expand_env(&shell,ev); //list of env var, separated the val and the designated name.
    while(1)
    {
        get_prompt(&shell);
        if (shell.cmd_line)
        {
            analise_cmd_line(&shell, shell.cmd_line);
        }
    }
    return 0;
}
