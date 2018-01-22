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
	t_ls	save;

	save_nb_file = file->nb;
	save_nb_blocks = file->nb_blocks;
	while (a < save_nb_file)
	{
		b = a;
		save = file[a];
		while (b > 0 && file[b - 1].time < save.time)
		{
			file[b] = file[b - 1];
			b--;
		}
		file[b] = save;
		a++;
	}
	file->nb = save_nb_file;
	file->nb_blocks = save_nb_blocks;
}

void	ft_sort_size(t_ls *file, int a, int b)
{
	int		save_nb_file;
	int		save_nb_blocks;
	t_ls	save;

	save_nb_file = file->nb;
	save_nb_blocks = file->nb_blocks;
	while (a < save_nb_file)
	{
		b = a;
		save = file[a];
		while (b > 0 && file[b - 1].size < save.size)
		{
			file[b] = file[b - 1];
			b--;
		}
		file[b] = save;
		a++;
	}
	file->nb = save_nb_file;
	file->nb_blocks = save_nb_blocks;
}

void	ft_sort_files(t_ls *file, char *option)
{
	if (ft_strchr(option, 'f'))
		return ;
	ft_sort_ascii(file, 0, 0);
	if (ft_strchr(option, 't') && !(ft_strchr(option, 'S')))
		ft_sort_time(file, 1, 0);
	if (ft_strchr(option, 'S'))
		ft_sort_size(file, 1, 0);
	if (ft_strchr(option, 'r'))
		ft_sort_rev(file, 0);
}
