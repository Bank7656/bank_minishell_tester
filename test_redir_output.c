#include "tester.h"

static void single_redir_output(int *n, char **envp);
static void single_redir_output_with_pipe(int *n, char **envp);
static void second_redir_output_with_pipe(int *n, char **envp);
static void multiple_redir_output(int *n, char **envp);

void  test_redir_output(int *n, char **envp)
{
  print_catagory("Check Redirect output");
  single_redir_output(n, envp);
  single_redir_output_with_pipe(n, envp);
  second_redir_output_with_pipe(n, envp);
  multiple_redir_output(n, envp);
}

static void single_redir_output(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "data/infile1.txt", NULL}, envp);
  create_redir_node(node_1, REDIR_OUTPUT, OUTFILE_1, NULL, O_WRONLY | O_CREAT | O_TRUNC);
  t_group *group = create_group(node_1);
  print_test(n, "cat -e data/infile1.txt > data/outfile1.txt");
  run_test(group, node_1); 
}

static void single_redir_output_with_pipe(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "data/infile1.txt", NULL}, envp);
  create_redir_node(node_1, REDIR_OUTPUT, OUTFILE_1, NULL, O_WRONLY | O_CREAT | O_TRUNC);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "data/infile2.txt", NULL}, envp);
  t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2); 
  t_group *group = create_group(pipe_node1);
  print_test(n, "cat -e data/infile1.txt > data/outfile1.txt | cat -e data/infile2");
  run_test(group, pipe_node1); 
}

static void second_redir_output_with_pipe(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "data/infile1.txt", NULL}, envp);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "data/infile2.txt", NULL}, envp);
  create_redir_node(node_2, REDIR_OUTPUT, OUTFILE_2, NULL, O_WRONLY | O_CREAT | O_TRUNC);
  t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2); 
  t_group *group = create_group(pipe_node1);
  print_test(n, "cat -e data/infile1.txt | cat -e data/infile2 > data/outfile2.txt");
  run_test(group, pipe_node1); 
}

static void multiple_redir_output(int *n, char **envp)
{
	t_ast_node *node_1 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "data/infile1.txt", NULL}, envp);
  create_redir_node(node_1, REDIR_OUTPUT, OUTFILE_1, NULL, O_WRONLY | O_CREAT | O_TRUNC);
	t_ast_node *node_2 = create_ast_node("/bin/cat", (char *[]){"cat", "-e", "data/infile2.txt", NULL}, envp);
  create_redir_node(node_2, REDIR_OUTPUT, OUTFILE_2, NULL, O_WRONLY | O_CREAT | O_TRUNC);
  t_ast_node *pipe_node1 = create_pipeline_node(node_1, node_2); 
  t_group *group = create_group(pipe_node1);
  print_test(n, "cat -e data/infile1.txt > data/outfile1.txt | cat -e data/infile2 > data/outfile2.txt");
  run_test(group, pipe_node1); 
}
