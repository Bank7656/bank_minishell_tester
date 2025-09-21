#include "tester.h"

static void test_first_error(int *n, char **envp);
static void test_last_error(int *n, char **envp);
static void test_middle_error(int *n, char **envp);

void  test_exit_code(int *n, char **envp)
{
  print_catagory("Check Exit code");
  test_first_error(n, envp);
  test_middle_error(n, envp);
  test_last_error(n, envp);
}

static void test_first_error(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/cat", (char *[]){"cat", "-w", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "World", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "Test", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
  t_group *group = create_group(pipe_node2);

  print_test(n, "cat -w | echo World | echo Test");
  run_test(group, pipe_node2);
  
}

static void test_middle_error(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "Hello", NULL}, envp);
  t_ast_node *node_2 = create_ast_node("/usr/bin/cat", (char *[]){"cat", "-w", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "Test", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
  t_group *group = create_group(pipe_node2);

  print_test(n, "echo Hello | cat -w | echo Test");
  run_test(group, pipe_node2);
  
}

static void test_last_error(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "Hello", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "World", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/cat", (char *[]){"cat", "-w", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
  t_group *group = create_group(pipe_node2);

  print_test(n, "echo Hello | echo World | cat -w");
  run_test(group, pipe_node2);
}


