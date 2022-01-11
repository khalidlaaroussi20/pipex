/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 04:25:59 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/11 06:49:55 by klaarous         ###   ########.fr       */
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

void wait_execution(int *p_ids,int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        waitpid(p_ids[i],0,0);
        i++;
    }
}

void delete_file(const char *filename)
{
    int fd;

    if (access(filename,R_OK) != -1)
        unlink(filename);
}

void free_list_str(char **str)
{
    int i;

    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}

void initalize_s_pipe(int ac,char **av,char **env,t_pipex *pipex_struct,int is_here_doc)
{
    char **paths;
    char **command;
    int *fd;
    int i;

    i = -1;
    paths = get_paths(env);
    fd = malloc(2 * sizeof(int));
    // if (is_here_doc)
    //     fd[1] = ft_open(av[ac - 1],O_WRONLY | O_CREAT | O_TRUNC | O_APPEND);
    // else
    // {
    //}
    if (is_here_doc == 1)
    {
        fd[0] = ft_open ("/tmp/.temp", O_RDWR | O_CREAT);
        fd[1] = ft_open(av[ac - 1],O_WRONLY | O_CREAT | O_APPEND);
    }
    else
    {
        fd[0] = ft_open(av[1],O_RDONLY);
         fd[1] = ft_open(av[ac - 1],O_WRONLY | O_CREAT | O_TRUNC);
    }
    while (++i < ac - 3 - is_here_doc)
    {
        command = ft_split(av[i + 2 + is_here_doc],' ');
        pipex_struct[i].command = command;
        pipex_struct[i].path_command = get_path_cmd(command[0],paths);
        pipex_struct[i].fd = fd;
        //printf("path command = %s\n", pipex_struct[i].path_command);
    }
    pipex_struct[0].length = i;
    pipex_struct[0].is_doc = is_here_doc;
    //printf("length = %d\n",pipex_struct[0].length);
    free_list_str(paths);
}


void free_s_pipex(t_pipex *pipex_struct,int len)
{
    int i;

    i = 0;
    free(pipex_struct[0].fd);
    while (i < len)
    {
        free(pipex_struct[i].command);
        free(pipex_struct[i].path_command);
        i++;
    }
    exit (0);
}