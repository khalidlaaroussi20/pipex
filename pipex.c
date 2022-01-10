/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 02:56:49 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/10 05:45:25 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_command(t_pipe pipe_struct,char **env,int input_fd,int output_fd)
{
    int error;

    dup2(input_fd,0);
    dup2(output_fd,1);
    error = execve(pipe_struct.path_command,pipe_struct.command,env);
    if (error == -1)
        command_not_found(pipe_struct.command[0]);
}

void excute_proccess(int ac,char **av,char **env,t_pipe *pipe_struct)
{
    int pipe_fd[ac - 4][2];
    int ids[ac - 3];
    int i;

    i = 0;
    open_pipes(pipe_fd,ac - 4);
    while (i < ac - 3)
    {
        ids[i] = fork();
        if (ids[i] == 0)
        {
            close_pipes(pipe_fd,ac - 4,i);
            if (i == 0)
                execute_command(pipe_struct[i],env,pipe_struct[0].fd[0],pipe_fd[i][1]);
            else if (i == ac - 4)
                execute_command(pipe_struct[i],env,pipe_fd[i - 1][0],pipe_struct[0].fd[1]);
            else
                execute_command(pipe_struct[i],env,pipe_fd[i - 1][0],pipe_fd[i][1]);
        }
        i++;
    }
    close_all_pipes(pipe_fd,ac - 4);
    i = 0;
    while (i < ac - 3)
        waitpid(ids[i++],0,0);
    exit(0);
}

void initalize_s_pipe(int ac,char **av,char **env,t_pipe *pipe_struct)
{
    char **paths;
    char **command;
    int *fd;
    int i;

    paths = get_paths(env);
    fd = malloc(2 * sizeof(int));
    fd[0] = ft_open(av[1],O_RDONLY);
    fd[1] = ft_open(av[ac - 1],O_WRONLY | O_CREAT | O_TRUNC);
    i = -1;
    while (++i < ac - 3)
    {
        command = ft_split(av[i + 2],' ');
        pipe_struct[i].command = command;
        pipe_struct[i].path_command = get_path_cmd(command[0],paths);
        pipe_struct[i].fd = fd;
    }
}

int main(int ac,char **av,char **env)
{
    t_pipe  pipe_struct[ac - 3];
    if (ac >= 5)
    {
        initalize_s_pipe(ac,av,env,pipe_struct);
        excute_proccess(ac,av,env,pipe_struct);
    }
    args_not_valid();
}