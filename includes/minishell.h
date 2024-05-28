#ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>

typedef struct s_token t_token;


/*  im using neg numbers bcs this are not single chars, and like this they do not mix up with ramdom ascii values */
typedef enum e_type
{
	WORD = -1, // any word string that does not goes to the other types, (cmds, files, etc)
	HEREDOC = -2, // << 
	DREDIREC = -3, // >>
	REDIR_IN = '<',
	REDIR_OUT = '>',
	SPACE_BAR = ' ', // will be used for space bar(32 on ascii) && tab ('\t')/(10 on ascii); 
	NEW_LINE = '\n',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	SCAPE = '\\',
	ENV = '$',
	PIPE = '|',
} t_type;

typedef enum e_placing
{
	IN_SQ, // inside single quotes
	IN_DQ, // inside double quotes
	DEFAULT,
} t_placing;



typedef struct s_token
{
	char		*token;
	int			len;
	t_type		type;
	t_placing	placing;
	t_token		*next;
	t_token		*prev;
}t_token;

typedef struct s_lexer
{
	t_token *head;
	t_token *tail;
	int			size;
}t_lexer;

typedef struct s_shell
{
	char *cmd_line;
	char *prompt;
	t_lexer *token_list;
	char **env;
	int n_dquotes;
	int n_squotes;
}t_shell;

/* ====================================================================================================== */

/* ANALISE.C */
void		analise_cmd_line(t_shell *shell, char *cmdline);
void		fill_list(t_shell *shell, char *cmdl);

/* LIST_UTILS.C */
t_token		*ft_lstlast(t_token *head);
t_token		*new_node(char *token, t_type type, t_placing placing);
void		delete_lst(t_token **head, int size);
int			lst_size(t_token **head);
void		add_to_list(t_lexer *token_list, char *word, t_type type, t_placing placing);


/* TOKEN_UTILS.C */
int			get_word(char *cmdl, int i, t_shell *sh, t_placing placing);
int			get_space(char *cmdl, int i, t_shell *sh, t_placing placing);
int 		get_quote(t_shell *sh, t_placing placing, char quote_type);
int			get_env_var(char *cmdl, int i, t_shell *sh, t_placing placing);
int			get_pipe(t_shell *sh, t_placing placing);
int			get_redirect_var(char *cmdl, int i, t_shell *sh, t_placing placing);
/* organize var type is a secundary funct for get_redirect_var (on another words its an extension)*/
void		organize_var_type(t_shell *sh, char *token, t_placing placing);
int			special_char(char c);
int			is_space(int c);

#endif