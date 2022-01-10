/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 03:40:32 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/10 04:03:51 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	command_not_found(char *command)
{
	ft_putstr_fd ("command not found: ", 2);
	ft_putendl_fd (command, 2);
	exit (0);
}

void	args_not_valid(void)
{
	ft_putstr_fd ("\033[0;31m", 2);
	ft_putendl_fd ("Args number is invalid !", 2);
	exit (0);
}