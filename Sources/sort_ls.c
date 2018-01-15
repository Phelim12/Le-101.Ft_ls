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

void	ft_sort_rev(t_ls *file, int a)
{
	int		save_nb_file;
	int		save_nb_blocks;
	t_ls	swap;

	save_nb_file = file->nb;
	save_nb_blocks = file->nb_blocks;
	while (a < save_nb_file / 2)
	{
		swap = file[save_nb_file - (a + 1)];
		file[save_nb_file - (a + 1)] = file[a];
		file[a] = swap;
		a++;
	}
	file->nb = save_nb_file;
	file->nb_blocks = save_nb_blocks;
}

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
	file->nb = save_nb_file;
	file->nb_blocks = save_nb_blocks;
}

void	ft_sort_time(t_ls *file, int a, int b)
{
	int		save_nb_file;
	int		save_nb_blocks;
	t_ls	swap;

	save_nb_file = file->nb;
	save_nb_blocks = file->nb_blocks;
	while (b < (save_nb_file * 5))
	{
		if ((a + 1) < save_nb_file && file[a].time < file[a + 1].time)
		{
			swap = file[a];
			file[a] = file[a + 1];
			file[a + 1] = swap;
			a++;
		}
		a++;
		if (a >= save_nb_file)
		{
			b++;
			a = 0;
		}
	}
	file->nb = save_nb_file;
	file->nb_blocks = save_nb_blocks;
}

void	ft_sort_time_argc(char ***av)
{
	char		*swap;
	t_stat		stat1;
	t_stat		stat2;
	int			a;
	int			b;

	a = -1;
	while ((*av)[++a])
	{
		b = -1;
		lstat((*av)[a], &stat1);
		while ((*av)[++b])
		{
			lstat((*av)[b], &stat2);
			if (stat1.st_mtime > stat2.st_mtime)
			{
				swap = (*av)[a];
				(*av)[a] = (*av)[b];
				(*av)[b] = swap;
			}
		}
	}
	(*av)[++a] = NULL;
}