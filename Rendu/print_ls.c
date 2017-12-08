/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_ls.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/07 17:29:49 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/07 17:29:49 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_alignment(char *str, int before, int after, int pick)
{
	if (pick == 1)
		before -= ft_strlen(str);
	if (pick == 2)
		after -= ft_strlen(str);
	while (before-- > 0)
		ft_putchar(' ');
	ft_putstr(str);
	while (after-- > 0)
		ft_putchar(' ');
}

void	ft_print_special(t_ls file, t_space space, t_option syn, int way)
{
	if (way == 1)
	{
		if (S_ISBLK(file.mode) || S_ISCHR(file.mode))
		{
			ft_alignment(ft_itoa(file.major), space.major, 0, 1);
			ft_putstr(", ");
			ft_alignment(ft_itoa(file.minor), space.minor, 0, 1);
		}
		else if (syn.a == TRUE)
			ft_alignment(ft_itoa(file.size), space.size + space.minor, 0, 1);
		else if (file.special == FALSE)
			ft_alignment(ft_itoa(file.size), space.size + 1, 0, 1);
		else
			ft_alignment(ft_itoa(file.size), space.size + space.minor + 
				space.major + 1, 0, 1);
	}
	else
	{
		ft_putstr(file.name);
		ft_putstr(" -> ");
		ft_putendl(file.ptr_link);
		return ;
	}
}

void	ft_print_file_rev(t_ls *file, t_option syn, int a)
{
	t_space	space;

	if (syn.l == TRUE)
		space = ft_fill_len_params(file, syn);
	space.name = ft_max_lenchar(file, syn, 2);
	while (a >= 0)
	{
		while (a >= 0 && syn.a == FALSE && file[a].name[0] == '.')
			a--;
		if (a < 0)
			break ;
		ft_print_stat(file[a], space, syn);
		a--;
	}
}

void	ft_print_file(t_ls *file, t_option syn, int a)
{
	t_space	space;

	if (syn.l == TRUE)
		space = ft_fill_len_params(file, syn);
	space.name = ft_max_lenchar(file, syn, 2);
	while (a < file[0].nb_file)
	{
		while (a < file[0].nb_file && syn.a == FALSE && file[a].name[0] == '.')
			a++;
		if (a >= file[0].nb_file)
			break ;
		ft_print_stat(file[a], space, syn);
		a++;
	}
}

void	ft_print_stat(t_ls file, t_space space, t_option syn)
{
	if (syn.l == TRUE)
	{
		file.tmp = ft_strsub(ctime(&file.time), 3, 13);
		ft_alignment(file.law, 0, 0, 0);
		ft_alignment(ft_itoa(file.nb_link), space.link + 1, 0, 1);
		ft_alignment(file.user, 1, space.user, 2);
		ft_alignment(file.group, 2, space.group + 1, 2);
		ft_print_special(file, space, syn, 1);
		ft_alignment(file.tmp, 0, 1, 0);
		if (S_ISLNK(file.mode))
			ft_print_special(file, space, syn, 0);
		else
			ft_putendl(file.name);
	}
	else
		ft_putendl(file.name);
}
