/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaarous <klaarous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 05:30:31 by klaarous          #+#    #+#             */
/*   Updated: 2022/01/10 05:55:46 by klaarous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void open_pipes(int (*pipes)[2],int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        pipe(pipes[i]);
        i++;
    }
}

void close_pipes(int (*pipes)[2],int len,int index_process)
{
    int i;

    i = 0;
    while (i < len)
    {
        if (i != index_process - 1)
            close(pipes[i][0]);
        if (i != index_process)
            close(pipes[i][1]);
        i++;
    }
}

void close_all_pipes(int (*pipes)[2],int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}