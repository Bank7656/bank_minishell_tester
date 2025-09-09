/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:50:19 by thacharo          #+#    #+#             */
/*   Updated: 2025/08/24 18:06:42 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "tester.h"


static char **get_dummy_args(char **args);

t_group *create_group(t_ast_node *node)
{
  t_group *group;

  group = (t_group *)malloc(sizeof(t_group));
  group -> ast_root = node;

  return (group);
}

t_ast_node	*create_ast_node(char *cmd, char **args, char **envp)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node -> type = NODE_COMMAND;
	node -> data.exec.commands = strdup(cmd);
	node -> data.exec.arguments = get_dummy_args(args);
	node -> data.exec.envp = envp;
  node -> data.exec.redir_input = NULL;
  node -> data.exec.redir_output = NULL;
	return (node);
}

t_ast_node *create_redir_node(t_ast_node *node, t_redir_type type, char *name, char *delim, int mode)
{
  t_list  *lst;
  t_redir *redir;

  redir = (t_redir *)malloc(sizeof(t_redir));
  redir -> type = type;
  redir -> filename = name;
  if (redir -> type == HEREDOC)
    redir -> delimeter = delim;
  else
    redir -> delimeter = NULL;
  redir -> mode = mode;
  lst = ft_lstnew(redir);

  if (type == REDIR_INPUT || type == HEREDOC)
    ft_lstadd_back(&(node -> data.exec.redir_input), lst);
  else if (type == REDIR_OUTPUT || type == APPEND)
    ft_lstadd_back(&(node -> data.exec.redir_output), lst);
  return (node);
}

static char **get_dummy_args(char **args)
{
	int		i;
	int		len;
	char	**lst;

	i = 0;
	len = 0;
	while (args[len] != NULL)
		len++;
	lst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!lst)
		return (NULL);
	while (i < len)	
	{
		lst[i] = strdup(args[i]);
		i++;
	}
	lst[i] = NULL;
	return (lst);
}


t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node -> type = NODE_PIPELINE;
	node -> data.tree.left = left;
	node -> data.tree.right = right;
	return (node);
}

void  print_test(int *n, char *cmd)
{
  printf("%s[Test %i]: %s%s\n", GREEN, *n, cmd, RESET);
  (*n)++;
  return ;
}

void  print_catagory(char *cmd)
{
  printf("%s%12s%s test%s%s\n\n", GREEN, "[",cmd, "]", RESET);
  return ;
}
