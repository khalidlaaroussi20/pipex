/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 02:56:49 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/11 06:49:34 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_command(t_pipex pipex_struct,char **env,int input_fd,int output_fd)
{
    int error;

    dup2(input_fd,0);
    dup2(output_fd,1);
    error = execve(pipex_struct.path_command,pipex_struct.command,env);
    if (error == -1)
        command_not_found(pipex_struct.command[0]);
}

void excute_proccess(int ac,char **av,char **env,t_pipex *pipex_struct)
{
    int length = pipex_struct[0].length;
    int pipe_fd[length - 1][2];
    int p_ids[length];
    int i;

    i = -1;
    open_pipes(pipe_fd,length - 1);
    while (++i < length)
    {
        p_ids[i] = fork();
        if (p_ids[i] == 0)
        {
            close_pipes(pipe_fd,length - 1,i);
            if (i == 0)
                execute_command(pipex_struct[i],env,pipex_struct[0].fd[0],pipe_fd[i][1]);
            else if (i == length - 1)
                execute_command(pipex_struct[i],env,pipe_fd[i - 1][0],pipex_struct[0].fd[1]);
            else
                execute_command(pipex_struct[i],env,pipe_fd[i - 1][0],pipe_fd[i][1]);
        }
    }
    close_all_pipes(pipe_fd,length - 1);
    wait_execution(p_ids,length);
    free_s_pipex(pipex_struct,length);
}

void  ft_limiter(char *limiter)
{
    char    *line;
    int     fd;

    unlink ("/tmp/.temp");
	fd = ft_open ("/tmp/.temp", O_RDWR | O_CREAT);
    while (1)
    {
        write(0,">",1);
        line = get_next_line(0);
        if (!ft_strncmp(line,limiter,ft_strlen(line) - 1))
            break ;
        ft_putendl_fd(line,fd);
        free(line);
    }
    close(fd);
}

int main(int ac,char **av,char **env)
{
    t_pipex pipex_struct[ac - 3];
    int     is_here_doc;

    is_here_doc = 0;
    if (ac >= 5)
    {
        if (!ft_strncmp(av[1],HERE_DOC,ft_strlen(av[1])))
        {
            if (ac == 5)
                args_not_valid();
            is_here_doc = 1;
            ft_limiter(av[2]);       
        }
        initalize_s_pipe(ac,av,env,pipex_struct,is_here_doc);
        //return 0;
        excute_proccess(ac,av,env,pipex_struct);
    }
    args_not_valid();
}