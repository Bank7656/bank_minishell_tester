#include "tester.h"

static void single_cmd(int *n, char **envp);
static void single_cmd_with_option(int *n, char **envp);
static void test_single_pipe(int *n, char **envp);
static void test_multiple_pipe(int *n, char **envp);

void  test_simple_cmd(int *n, char **envp)
{
  print_catagory("Simple Commands");
  single_cmd(n, envp);
  single_cmd_with_option(n, envp);
}

static void single_cmd(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/bin/ls", (char *[]){"ls", NULL}, envp);

  t_group *group = create_group(node_1);

  print_test(n, "ls -la");
  run_test(group, node_1);
}

static void single_cmd_with_option(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/bin/ls", (char *[]){"ls", "-la", NULL}, envp);

  t_group *group = create_group(node_1);

  print_test(n, "ls");
  run_test(group, node_1);
}


