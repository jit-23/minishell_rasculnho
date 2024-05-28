/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:42 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/26 21:03:19 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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

static void  init_env(t_shell *shell, char **ev) // change the name to init_shell to use this funct to put inf on the struct
{
    /*  
     *  
     */ 
}

int main(int ac, char *ev[])
{
	t_shell shell;
    if (ac != 1)
        return (1); // msg erro
    ft_memset(&shell, 0 , sizeof(t_shell));
    init_env(&shell, ev); // put the env on a link list
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
