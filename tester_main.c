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

volatile sig_atomic_t should_exit = 0;

int	main(int argc, char **argv, char **envp)
{
  

  (void)argc;
  (void)argv;
  test(envp);

	return (0);
}




