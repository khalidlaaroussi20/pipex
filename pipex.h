/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 02:57:53 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/11 05:46:44 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define  PIPE_H

# define HERE_DOC "here_doc"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>
#include <errno.h>

#include "includes/libft/libft.h"
#include "includes/get_next_line/get_next_line.h"


typedef struct s_pipex
{
    char    **command;
    char    *path_command;
    int     *fd;
    int     length;
    int     is_doc;
}               t_pipex;

//pipex utils

int	ft_open(char *file_name, int permission);
void wait_execution(int *p_ids,int len);
void delete_file(const char *filename);
void initalize_s_pipe(int ac,char **av,char **env,t_pipex *pipe_struct,int is_here_doc);
void free_list_str(char **str);
void free_s_pipex(t_pipex *pipex_struct,int len);

//handle command

int get_index_path_var(char **env);
char **get_paths(char **env);
char *get_path_cmd(char *command,char **paths_exec_cmd);

//handle error

void	command_not_found(char *command);
void	args_not_valid(void);

//pipes helper

void open_pipes(int (*pipes)[2],int len);
void close_pipes(int (*pipes)[2],int len,int index_process);
void close_all_pipes(int (*pipes)[2],int len);

#endif