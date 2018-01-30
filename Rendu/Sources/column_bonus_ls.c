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

int		ft_space_name(t_ls *file)
{
	int ret;
	int	cur;

	ret = 0;
	cur = -1;
	while (++cur < file->nb)
		if (ft_strlen(file[cur].name) > ret)
			ret = ft_strlen(file[cur].name);
	return (ret);
}

int		ft_words_line(int nb_file, int max_name)
{
	int			nb_col;
	int			ret;

	ret = 1;
	nb_col = ft_nb_col();
	while ((nb_file * max_name) >= (nb_col * ret))
		ret++;
	return (ft_ceil((float)nb_file / (float)ret));
}

void	ft_print_one_line(t_ls *file, char *option, int space)
{
	int	cur;

	cur = -1;
	while (++cur < file->nb)
	{
		if ((cur + 1) == file->nb)
			ft_print_color_ls(file[cur], option, -1, 1);
		else
			ft_print_color_ls(file[cur], option, space, 0);
		if (!(ft_strchr(option, 'R')))
			ft_free_files(&file[cur]);
	}
}

void	ft_print_column(t_ls *file, char *option, int cur)
{
	int	ptr;
	int	space;
	int	nfile;
	int	nline;

	space = ft_space_name(file);
	nfile = ft_words_line(file->nb, (space + 1));
	nline = ft_ceil((float)file->nb / (float)nfile);
	if (nline == 1)
		ft_print_one_line(file, option, space);
	while (nline > 1 && cur < (nline * nfile))
	{
		ptr = cur;
		if (!(ft_strchr(option, 'x')))
			ptr = (((cur % nfile) * nline) + (cur / nfile));
		if ((ptr < file->nb) && (cur + 1) % nfile && cur + 1 < (nline * nfile))
			ft_print_color_ls(file[ptr], option, space, 0);
		else if (ptr < file->nb)
			ft_print_color_ls(file[ptr], option, -1, 0);
		if (!(ft_strchr(option, 'R')) && ptr < file->nb)
			ft_free_files(&file[ptr]);
		if ((cur / nfile) < ((cur + 1) / nfile))
			ft_putchar('\n');
		cur++;
	}
}
