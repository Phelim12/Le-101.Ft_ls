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

void	ft_print_file_rev(t_ls *file, t_option syn, int a)
{
	t_space	space;

	if (syn.l == TRUE)
		space = ft_fill_len_params(file, syn);
	space.len_name = ft_max_lenchar(file, syn, 2);
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
	space.len_name = ft_max_lenchar(file, syn, 2);
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
	char *tmp;

	if (syn.l == TRUE)
	{
		tmp = ft_strsub(ctime(&file.time), 3, 13);
		ft_alignment(file.law, 0, 0, 0);
		ft_alignment(ft_itoa(file.nb_link), space.len_link + 1, 0, 1);
		ft_alignment(file.user, 1, space.len_user, 2);
		ft_alignment(file.group, 2, space.len_group + 1, 2);
		ft_alignment(ft_itoa(file.nb_byte), space.len_size + 1, 0, 1);
		ft_alignment(tmp, 0, 1, 0);
		if (file.ptr_link && )
		{
			ft_putstr(file.name);
			ft_putstr(" -> ");
			ft_putendl(file.ptr_link);
		}
		else
			ft_putendl(file.name);

	}
	else
		ft_putendl(file.name);
}
