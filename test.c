#include "tester.h"

static void test_0(int *n, char **envp);
static void test_1(int *n, char **envp);
static void test_2(int *n, char **envp);
static void test_3(int *n, char **envp);
static void test_4(int *n, char **envp);
static void test_5(int *n, char **envp);
static void test_6(int *n, char **envp);

void  test(char **envp)
{
  int n = 1;

  //print_catagory("Simple Commands");
  //test_0(&n, envp);
  //test_1(&n, envp);

  //print_catagory("Zombie process");
  //test_2(&n, envp);
  //test_3(&n, envp);
  //test_4(&n, envp);

  //print_catagory("Check Exit code");
  //test_5(&n, envp);
  test_6(&n, envp);
}

static void test_0(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/bin/ls", (char *[]){"ls", "-la", NULL}, envp);

  t_group *group = create_group(node_1);

  print_test(n, "ls -la");
  execution(group, node_1);
  printf("\n");

  clear_ast(group -> ast_root);
  free(group);

}
static void test_1(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "dockerfile", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);

  t_group *group = create_group(pipe_node2);

  print_test(n, "cat -e dockerfile | cat -e | cat -e");
  execution(group, pipe_node2);
  printf("\n");

  clear_ast(group -> ast_root);
  free(group);

}

static void test_2(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "1", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "3", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "5", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
   t_group *group = create_group(pipe_node2);

  print_test(n, "sleep 1 | sleep 3 | sleep 5");
  execution(group, pipe_node2);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}

static void test_3(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "1", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "5", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "3", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
   t_group *group = create_group(pipe_node2);

  print_test(n, "sleep 1 | sleep 5 | sleep 3");
  execution(group, pipe_node2);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}

static void test_4(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "10", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "5", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/usr/bin/sleep", (char *[]){"sleep", "1", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
   t_group *group = create_group(pipe_node2);

  print_test(n, "sleep 5 | sleep 3 | sleep 1");
  execution(group, pipe_node2);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}

static void test_5(int *n, char **envp)
{
  t_ast_node *node_1 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "Hello", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/usr/bin/echo", (char *[]){"echo", "World", NULL}, envp);
	t_ast_node *node_3 = create_ast_node("/bin/cat", (char *[]){"cat", "-w", "Test", NULL}, envp);
	t_ast_node *pipe_node1 = create_pipeline_node(node_2, node_3);
	t_ast_node *pipe_node2 = create_pipeline_node(node_1, pipe_node1);
   t_group *group = create_group(pipe_node2);

  print_test(n, "echo Hello | echo World | cat -w");
  execution(group, pipe_node2);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}


static void test_6(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
    
  create_redir_node(node_1, REDIR_INPUT, "Makefile", NULL, O_RDONLY);

  t_group *group = create_group(node_1);
  print_test(n, "< Makefile cat -e");
  execution(group, node_1);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}
