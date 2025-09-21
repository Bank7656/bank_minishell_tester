#include "tester.h"


static void test_first_finish(int *n, char **envp);
static void test_last_finish(int *n, char **envp);
static void test_middle_finish(int *n, char **envp);

void  test_zombie(int *n, char **envp)
{
  print_catagory("Zombie process");
  test_first_finish(n, envp);
  test_middle_finish(n, envp);
  test_last_finish(n, envp);
}

static void test_first_finish(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "7", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "5", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "3", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
  t_group *group = create_group(pipe_node2);

  print_test(n, "sleep 7 | sleep 5 | sleep 3");

  run_test(group, pipe_node2);
}

static void test_last_finish(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "3", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "5", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "7", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
  t_group *group = create_group(pipe_node2);

  print_test(n, "sleep 3 | sleep 5 | sleep 7");
  
  run_test(group, pipe_node2);
}

static void test_middle_finish(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "3", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "7", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "5", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
  t_group *group = create_group(pipe_node2);

  print_test(n, "sleep 3 | sleep 7 | sleep 5");
  run_test(group, pipe_node2);
}


