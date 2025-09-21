#include "tester.h"


static void test_single_pipe(int *n, char **envp);
static void test_multiple_pipe(int *n, char **envp);

void  test_pipeline(int *n, char **envp)
{
  print_catagory("Pipeline");
  test_single_pipe(n, envp);
  test_multiple_pipe(n, envp);
}

static void test_single_pipe(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "dockerfile", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2);

  t_group *group = create_group(pipe_node1);

  print_test(n, "cat -e dockerfile | cat -e");
  run_test(group, pipe_node1);
}

static void test_multiple_pipe(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "dockerfile", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);

  t_group *group = create_group(pipe_node2);

  print_test(n, "cat -e dockerfile | cat -e | cat -e");
  run_test(group, pipe_node2);
}
