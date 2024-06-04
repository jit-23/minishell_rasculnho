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
#include <stdarg.h>

#include "env.h"

//#define BLUE 			\033 [0;34m
//#define default_colour	\033 [0m

#define _PIPE	1
#define _EXEC	2
#define _REDIR	3

typedef struct s_token t_token;

typedef struct s_cmd t_cmd;
typedef struct s_exec t_exec;
typedef struct s_pipe t_pipe;
typedef struct s_redir t_redir;

struct s_cmd
{
	int type;
};

struct s_exec
{
	int type;
	char **args;
};

struct s_pipe
{
	int type;
	t_cmd *left;
	t_cmd *right;
};

struct s_redir
{
	int type;
	t_cmd *cmd;
	char *file;
	int mode;
	int fd;
};

typedef enum e_placing
{
	IN_SQ, // inside single quotes
	IN_DQ, // inside double quotes
	DEFAULT,
} t_placing;



/*  im using neg numbers bcs this are not single chars, and like this they do not mix up with ramdom ascii values */
typedef enum e_type
{
	WORD = -1, // any word string that does not goes to the other types, (cmds, files, etc)
	HEREDOC = -2, // << 
	DREDIREC = -3, // >>
	REDIR_IN = '<',
	REDIR_OUT = '>',
	SPACE_BAR = ' ', // will be used for space bar(32) && tab ('\t')/(10); 
	NEW_LINE = '\n',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	SCAPE = '\\',
	ENV = '$',
	PIPE = '|',
} t_type;

typedef struct s_token
{
	char		*token;
	t_type		type;
	int			len;
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
	t_env *ev;
	t_cmd *root;
}t_shell;

/* ====================================================================================================== */

/* ANALISE.C */
void		analise_cmd_line(t_shell *shell, char *cmdline);
void		fill_first_list(t_shell *shell, char *cmdl);

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
char		*expand_env_var(char *env_var , t_env *head);
int			valid_env(char *env_var ,t_env *env_head);
char 		*get_env_str(char *cmdl, int i);
int			get_pipe(t_shell *sh, t_placing placing);
int			get_redirect_var(char *cmdl, int i, t_shell *sh, t_placing placing);
/* organize var type is a secundary funct for get_redirect_var (on another words its an extension)*/
void		organize_var_type(t_shell *sh, char *token, t_placing placing);
int			special_char(char c);
int			is_space(int c);

/* init_tree.c */
//int peek_spaces(t_token *checker);
//
//void    init_tree(t_shell *sh, char *cmdl, t_token *head);
////t_cmd *create_branches(t_shell *sh, t_token **checker, t_cmd **root);
//t_cmd *parse_pipe(t_shell *sh, t_token **checker);
//t_cmd *parse_exec(t_shell *sh, t_token **checker);
//int peek_token(t_token *checker,int var_nbr, ...);

/* INIT_AST.c */
void    init_AST(t_shell *sh);
int 	peek_future_tokens_type(t_token *head, t_type type);
t_cmd   *pipe_parse(t_shell *sh, t_cmd *left);
t_cmd 	*exec_parse(t_shell*sh, t_exec *exec_struct);
t_pipe *init_pipe();
t_exec *init_exec();
int peek_token(t_token *checker,int var_nbr, ...);

void print_tree(t_cmd *root);
#endif