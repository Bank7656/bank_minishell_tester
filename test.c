#include "tester.h"

void  test(char **envp)
{
  int n = 0;

  //test_simple_cmd(&n, envp);
  //test_pipeline(&n, envp);
  //test_zombie(&n, envp); 
  //test_exit_code(&n, envp);
  //test_redir_input(&n, envp);
  test_redir_output(&n, envp);
  //test_8(&n, envp);
  //test_9(&n, envp);
  test_random(&n, envp);
}



static void test_8(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", NULL}, envp);
    
  create_redir_node(node_1, HEREDOC, NULL, "EOF", O_RDONLY);
  t_group *group = create_group(node_1);
  print_test(n, "<< EOF cat -e");
  execution(group, node_1);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}

static void test_9(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/ls", (char *[]){"ls",  NULL}, envp);
    
  t_group *group = create_group(node_1);
  print_test(n, "cd tester");
  execution(group, node_1);
  printf("\n");
  clear_ast(group -> ast_root);
  free(group);
}
