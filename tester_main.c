/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:39:17 by thacharo          #+#    #+#             */
/*   Updated: 2025/08/22 17:21:13 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

int	main(int argc, char **argv, char **envp)
{
  (void)argc;
  (void)argv;
  test(envp);
	//t_ast_node *root_node = create_dummy_ast(envp);

  //t_group *group = create_group(root_node);
	//execution(group, root_node);

  //clear_and_exit(group, "NONE");

	return (0);
}




