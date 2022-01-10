/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 04:25:59 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/10 05:49:06 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


int	ft_open(char *file_name, int permission)
{
	int		fd;
	char	*error;

	fd = open (file_name, permission, 0777);
	if (fd < 0)
	{
		error = strerror (errno);
		ft_putstr_fd (error, 2);
		ft_putstr_fd (": ", 2);
		ft_putendl_fd (file_name, 2);
		exit (1);
	}
	return (fd);
}