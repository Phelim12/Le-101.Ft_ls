/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_R.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 15:36:59 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/30 15:36:59 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_sort_ascii(t_ls *file, int a, int b)
{
	int	save_nb_file;
	t_ls swap;

	save_nb_file = file[0].nb_file;
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
	 file[0].nb_file = save_nb_file;
}

void	ft_sort_time(t_ls *file, int a, int b)
{
	int	save_nb_file;
	t_ls swap;

	save_nb_file = file[0].nb_file;
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
	file[0].nb_file = save_nb_file;
}

void	ft_print_file(t_ls *file, t_option syn)
{
	int a;

	a = 0;
	if (syn.l_r == FALSE)
		while (a < file[0].nb_file)
		{
			while (syn.a == FALSE && file[a].name[0] == '.')
				a++;
			ft_putendl(file[a].name);
			a++;
		}
	else
	{
		a = (file[0].nb_file - 1);
		while (a >= 0)
		{
			if (syn.a == TRUE && file[a].name[0] == '.')
				ft_putendl(file[a].name);
			if (file[a].name[0] != '.')
				ft_putendl(file[a].name);
			a--;
		}
	}
}

void	ft_ls(char *str, t_option syn)
{
    struct dirent	*ptr_file;
	t_ls			*file;
	DIR				*repo;

    ptr_file = NULL;
	repo = opendir(str);
	file = ft_fill_all_files(str, syn);
	ft_sort_ascii(file, 0, 0);
	if (syn.t == TRUE)
		ft_sort_time(file, 0, 0);
	ft_print_file(file, syn);
}
