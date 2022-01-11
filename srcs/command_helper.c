/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 03:37:57 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/11 02:46:40 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int get_index_path_var(char **env)
{
    int i;
    char *name_env_var;

    i = 0;
    while (env[i])
    {
        name_env_var = ft_substr(env[i],0,4);
        if (ft_strncmp("PATH",name_env_var,4) == 0)
            return (i);
        free(name_env_var);
        i++;
    }
    return (-1);
}

char **get_paths(char **env)
{
    int i;
    int index_path_var;
    char **paths;
    char *temp;

    paths = NULL;
    index_path_var = get_index_path_var(env);
    if (index_path_var != -1)
    {
        paths = ft_split(env[index_path_var] + 5,':');
        i = -1;
        while (paths[++i])
        {
            temp = paths[i];
            paths[i] = ft_strjoin(paths[i],"/");
            free(temp);
        }
    }
    return (paths);
}


char *get_path_cmd(char *command,char **paths_exec_cmd)
{
    int i;
    char *path_cmd;

    i = -1;
    while (paths_exec_cmd[++i])
    {
        path_cmd = ft_strjoin(paths_exec_cmd[i],command);
        if (access(path_cmd,X_OK) == 0)
            return (path_cmd);
        free(path_cmd);
    }
    return (ft_substr(command,0,ft_strlen(command)));
}