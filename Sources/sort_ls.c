/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/07 17:29:19 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/07 17:29:19 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_sort_ascii(t_ls *file, int a, int b)
{
	int		save_nb_file;
	int		save_nb_blocks;
	t_ls	swap;

	save_nb_file = file->nb;
	save_nb_blocks = file->nb_blocks;
	while (a < save_nb_file)
	{
		b = 0;
		while (b < save_nb_file)
		{
			if (ft_strcmp(file[a].name, file[b].name) < 0)
			{
				swap = file[a];
				file[a] = file[b];
				file[b] = swap;
			}
			b++;
		}
		a++;
	}
	file[0].nb = save_nb_file;
	file[0].nb_blocks = save_nb_blocks;
}

void	ft_sort_time(t_ls *file, int a, int b)
{
	int		save_nb_file;
	int		save_nb_blocks;
	t_ls	swap;

	save_nb_file = file->nb;
	save_nb_blocks = file->nb_blocks;
	while (a < save_nb_file)
	{
		b = 0;
		while (b < save_nb_file)
		{
			if (file[a].time > file[b].time)
			{
				swap = file[a];
				file[a] = file[b];
				file[b] = swap;
			}
			b++;
		}
		a++;
	}
	file->nb = save_nb_file;
	file->nb_blocks = save_nb_blocks;
}
