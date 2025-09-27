#include "tester.h"

static void test_stop_random(int *n, char **envp);

void  test_random(int *n, char **envp)
{
  print_catagory("Unlimited Random");
  test_stop_random(n , envp);
}

static void test_stop_random(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "/dev/random", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/head", (char *[]){"head", "-n", "2", NULL}, envp);
  create_redir_node(node_2, REDIR_OUTPUT, "out.txt", NULL, O_WRONLY | O_CREAT | O_TRUNC);

  print_test(n, "cat /dev/random | head -n 2");
  t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2); 
  t_group *group = create_group(pipe_node1);
  run_test(group, pipe_node1);
}
