#include "tester.h"

static void single_heredoc(int *n, char **envp);
static void first_heredoc_with_pipe(int *n, char **envp);
static void second_heredoc_with_pipe(int *n, char **envp);
static void multiple_heredoc(int *n, char **envp);
static void second_multi_heredoc_with_pipe(int *n, char **envp);
static void multiple_pipe_with_multiple_heredoc(int *n, char **envp);

void  test_heredoc(int *n, char **envp)
{
  print_catagory("Check heredoc");
  //single_heredoc(n, envp);
  //multiple_heredoc(n, envp);
  //first_heredoc_with_pipe(n, envp);
  //second_heredoc_with_pipe(n, envp);
  multiple_pipe_with_multiple_heredoc(n, envp);
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

static void first_heredoc_with_pipe(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_1, HEREDOC, NULL, "EOF", O_RDONLY);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2);
  t_group *group = create_group(pipe_node1);
  print_test(n, "<< EOF cat -e | cat -e");
  run_test(group, pipe_node1);
}

static void second_heredoc_with_pipe(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/ls", (char *[]){"ls", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_2, HEREDOC, NULL, "EOF", O_RDONLY);
	t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2);
  t_group *group = create_group(pipe_node1);
  print_test(n, "ls | << EOF cat -e");
  run_test(group, pipe_node1);
}

  
static void multiple_pipe_with_multiple_heredoc(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_1, HEREDOC, NULL, "END1", O_RDONLY);
  create_redir_node(node_1, HEREDOC, NULL, "END2", O_RDONLY);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_2, HEREDOC, NULL, "END3", O_RDONLY);
  create_redir_node(node_2, HEREDOC, NULL, "END4", O_RDONLY);
	t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2);
  t_group *group = create_group(pipe_node1);
  print_test(n, "<< END1 << END2 cat -e | << END3 << END4 cat -e");
  run_test(group, pipe_node1);
}