/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bonus_column_ls.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 16:44:00 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/18 16:44:00 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_nb_col()
{
	t_winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return ((int)w.ws_col);
}

int			ft_ceil(float a, float b)
{
	int 	ret;
	float 	test;

	test = (a / b);
	ret = test;
	if (ret == test)
		return (ret);
	return (ret + 1);
}

int			ft_space_name(t_ls *file)
{
	int	cur;
	int ret;

	cur = 0;
	ret = 0;
	while (cur < file->nb)
	{
		if (ft_strlen(file[cur].name) > ret)
			ret = ft_strlen(file[cur].name);
		cur++;
	}
	return (ret);
}

int			ft_words_line(int nb_file, int max_name)
{
	int nb_col;
	int check;
	int cur;
	int ret;

	cur = 1;
	check = 1;
	nb_col = ft_nb_col();
	while ((cur * max_name) < nb_col)
	{
		if ((nb_file % cur) == 0)
			ret = cur;
		cur++;
	}
	while (check < (cur - 2))
	{
		if ((ret * check) == nb_file)
			return (ret);
		check++;
	}
	if ((cur - 1) > 0)
		return (cur - 1);
	return (1);
}

void		ft_print_line(t_ls *file, char *option, int space)
{
	int	cur;

	cur = 0;
	while (cur < file->nb)
	{
		if ((cur + 1) == file->nb)
			ft_printf("%s\n", file[cur].name);
		else
			ft_printf("%-*s", space + 1, file[cur].name);
		cur++;
	}
}

void		ft_print_column(t_ls *file, char *option)
{
	int	cur;
	int	ptr;
	int	space;
	int	nfile;
	int	nline;

	cur = 0;
	space = ft_space_name(file);
	nfile = ft_words_line(file->nb, (space + 1));
	nline = ft_ceil((float)file->nb, (float)nfile);
	if (nline == 1)
		ft_print_line(file, option, space);
	while (nline > 1 && cur < (nline * nfile))
	{
		ptr = (((cur % nfile) * nline) + (cur / nfile));
		if ((ptr < file->nb) && (cur + 1) % nfile && cur + 1 < (nline * nfile))
			ft_printf("%-*s ", space, file[ptr].name);
		else if (ptr < file->nb)
			ft_printf("%s", file[ptr].name);
		if (!(ft_strchr(option, 'R')) && ptr < file->nb)
			ft_free_files(&file[ptr]);
		if ((cur / nfile) < ((cur + 1) / nfile))
			ft_putchar('\n');
		cur++;
	}
}
/*
00 01 02 03 04

10 11 12 13 

20 21 22 23 

 0  3  6  9 12
 1  4  7 10 
 2  5  8 11 */






