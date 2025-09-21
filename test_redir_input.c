#include "tester.h"

static void single_redir_input(int *n, char **envp);
static void single_redir_input_with_pipe(int *n, char **envp);
static void second_redir_input_with_pipe(int *n, char **envp);
static void multiple_redir_input(int *n, char **envp);
static void second_multi_redir_input_with_pipe(int *n, char **envp);

void  test_redir_input(int *n, char **envp)
{
  print_catagory("Check Redirect input");
  single_redir_input(n, envp);
  single_redir_input_with_pipe(n, envp);
  second_redir_input_with_pipe(n, envp);
  multiple_redir_input(n, envp);
  second_multi_redir_input_with_pipe(n, envp);
}

static void single_redir_input(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
    
  create_redir_node(node_1, REDIR_INPUT, INFILE_1, NULL, O_RDONLY);
  t_group *group = create_group(node_1);
  print_test(n, "< data/infile1.txt cat -e");
  run_test(group, node_1); 
}

static void single_redir_input_with_pipe(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_1, REDIR_INPUT, INFILE_1, NULL, O_RDONLY);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2); 

  t_group *group = create_group(pipe_node1);
  print_test(n, "< data/infile1.txt cat -e | cat -e");
  run_test(group, pipe_node1); 
}

static void second_redir_input_with_pipe(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_2, REDIR_INPUT, INFILE_1, NULL, O_RDONLY);
  t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2); 
  t_group *group = create_group(pipe_node1);
  print_test(n, "cat -e | < data/infile1.txt cat -e");
  run_test(group, pipe_node1); 
}

static void multiple_redir_input(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
    
  create_redir_node(node_1, REDIR_INPUT, INFILE_1, NULL, O_RDONLY);
  create_redir_node(node_1, REDIR_INPUT, INFILE_2, NULL, O_RDONLY);

  t_group *group = create_group(node_1);
  print_test(n, "< data/infile1.txt < data/infile2.txt cat -e");
  run_test(group, node_1); 
}

static void second_multi_redir_input_with_pipe(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/ls", (char *[]){"ls",  NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
  create_redir_node(node_2, REDIR_INPUT, INFILE_1, NULL, O_RDONLY);
  create_redir_node(node_2, REDIR_INPUT, INFILE_2, NULL, O_RDONLY);
  t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2); 

  t_group *group = create_group(pipe_node1);
  print_test(n, "ls | < data/infile1.txt < data/infile2.txt cat -e");

  run_test(group, pipe_node1); 
}

static void test_7(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "Makefile", NULL}, envp);
    
  create_redir_node(node_1, REDIR_OUTPUT, "./tester/test7.txt", NULL, O_WRONLY | O_CREAT | O_TRUNC);

  t_group *group = create_group(node_1);
  print_test(n, "cat -e Makefile > ./tester/test7.txt");
  execution(group, node_1);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}
