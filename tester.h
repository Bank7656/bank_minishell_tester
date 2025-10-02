#ifndef TESTER_H
# define TESTER_H

# define INFILE_1 "data/infile1.txt"
# define INFILE_2 "data/infile2.txt"
# define INFILE_3 "data/infile3.txt"
# define INFILE_4 "data/infile4.txt"
# define OUTFILE_1 "data/outfile1.txt"
# define OUTFILE_2 "data/outfile2.txt"
# define APPENDFILE_1 "data/appendfile1.txt"
# define APPENDFILE_2 "data/appendfile2.txt"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

# include <time.h>

# include "../include/execute.h"
# include "../libft/libft.h"

void  print_test(int *n, char *cmd);
void  print_catagory(char *cmd);
void  test(char **envp);
t_ast_node	*create_ast_node(char *cmd, char **args, char **envp);
t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right);
t_ast_node *create_redir_node(t_ast_node *node, t_redir_type type, char *name, char *delim, int mode);

void  test(char **envp);
t_ast_node	*create_dummy_ast(char **envp);
t_group *create_group(t_ast_node *node);

void  test_simple_cmd(int *n, char **envp);
void  test_pipeline(int *n, char **envp);
void  test_zombie(int *n, char **evnp);
void  test_exit_code(int *n, char **envp);
void  test_redir_input(int *n, char **envp);
void  test_redir_output(int *n, char **envp);
void  test_append(int *n, char **envp);
void  test_heredoc(int *n, char **envp);
void  test_random(int *n, char **envp);
void  run_test(t_group *group, t_ast_node *root);


#endif
