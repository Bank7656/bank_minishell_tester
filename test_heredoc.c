#include "tester.h"

static void single_heredoc(int *n, char **envp);
static void first_heredoc_with_pipe(int *n, char **envp);
static void second_heredoc_with_pipe(int *n, char **envp);
static void multiple_heredoc(int *n, char **envp);
static void second_multi_heredoc_with_pipe(int *n, char **envp);

void  test_heredoc(int *n, char **envp)
{
  print_catagory("Check heredoc");
  single_heredoc(n, envp);
  multiple_heredoc(n, envp);
  //first_heredoc_with_pipe(n, envp);
  //second_heredoc_with_pipe(n, envp);
}

static void single_heredoc(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
    
  create_redir_node(node_1, HEREDOC, NULL, "EOF", O_RDONLY);
  t_group *group = create_group(node_1);
  print_test(n, "<< EOF cat -e");
  run_test(group, node_1); 
}

static void multiple_heredoc(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_1, HEREDOC, NULL, "EOF", O_RDONLY);
  create_redir_node(node_1, HEREDOC, NULL, "END", O_RDONLY);
  t_group *group = create_group(node_1);
  print_test(n, "<< EOF cat -e");
  run_test(group, node_1); 
}
