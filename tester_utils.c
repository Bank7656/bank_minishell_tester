#include "tester.h"

void  run_test(t_group *group, t_ast_node *root)
{
  execution(group, root);
  printf("\n");

  clear_ast(group -> ast_root);
  free(group);
}
