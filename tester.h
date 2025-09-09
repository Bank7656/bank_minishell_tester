#ifndef TESTER_H
# define TESTER_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

# include "../include/execute.h"
# include "../libft/libft.h"

void  print_test(int *n, char *cmd);
void  print_catagory(char *cmd);
void  test(char **envp);
t_ast_node	*create_ast_node(char *cmd, char **args, char **envp);
t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right);

#endif
