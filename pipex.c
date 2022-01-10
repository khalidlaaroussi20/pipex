/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 02:56:49 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/10 04:05:43 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


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
    int pipe_fd[2];
    int ids[2];
    int i;

    i = 0;
    pipe(pipe_fd);
    while (i < ac - 3)
    {
        ids[i] = fork();
        if (ids[i] == 0)
        {
            if (i == 0)
            {
                close(pipe_fd[0]);
                execute_command(pipe_struct[i],env,pipe_struct[0].fd[0],pipe_fd[1]);
            }
            else if (i == ac - 4)
            {
                close(pipe_fd[1]);
                execute_command(pipe_struct[i],env,pipe_fd[0],pipe_struct[0].fd[1]);
            }
            else
            {
                
            }
        }
        i++;
    }
    i = 0;
    while (i < ac - 3)
    {
        close(pipe_fd[i]);
        waitpid(ids[i],0,0);
        i++;
    }
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
    if (ac == 5)
    {
        initalize_s_pipe(ac,av,env,pipe_struct);
        excute_proccess(ac,av,env,pipe_struct);
    }
    args_not_valid();
}