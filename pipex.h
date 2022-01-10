/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 02:57:53 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/10 02:48:58 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
#define  PIPE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>
#include <errno.h>

#include "includes/libft/libft.h"

typedef struct s_pipe
{
    int     *pipe_fd;
    char    **command;
    char    *path_command;
    int     *fd;
}               t_pipe;


//handle command

int get_index_path_var(char **env);
char **get_paths(char **env);
char *get_path_cmd(char *command,char **paths_exec_cmd);

//handle error

void	command_not_found(char *command);
int	ft_open(char *file_name, int permission);
void	args_not_valid(void);

#endif