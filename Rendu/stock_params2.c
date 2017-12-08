/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock_params2.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/07 18:40:00 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/07 18:40:00 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_fill_special(t_ls *file, char *path)
{
	char		buf[1024];
	int			ret;

	if (S_ISLNK(file->mode))
	{
		if ((ret = readlink(path, buf, 1024)) < 0)
			file->ptr_link = NULL;
		else
		{
			buf[ret] = '\0';
			file->ptr_link = ft_strdup(buf);
		}
	}
	if (S_ISBLK(file->mode) || S_ISCHR(file->mode))
	{
		file->minor = minor(file->rdev);
		file->major = major(file->rdev);
	}
}

int		ft_max_lenint(t_ls *file, t_option syn, int choice)
{
	int max_len;
	int a;

	a = 0;
	max_len = 0;
	while (a < file[0].nb_file)
	{
		while ((a < file[0].nb_file) && !(syn.a) && file[a].name[0] == '.')
			a++;
		if ((a >= file[0].nb_file))
			break ;
		if (choice == 0 && max_len < ft_lenint(file[a].size))
			max_len = ft_lenint(file[a].size);
		if (choice == 1 && max_len < ft_lenint(file[a].nb_link))
			max_len = ft_lenint(file[a].nb_link);
		if (choice == 2 && max_len < ft_lenint(file[a].major))
			max_len = ft_lenint(file[a].major);
		if (choice == 3 && max_len < ft_lenint(file[a].minor))
			max_len = ft_lenint(file[a].minor);
		a++;
	}
	return (max_len);
}

int		ft_max_lenchar(t_ls *file, t_option syn, int choice)
{
	int max_len;
	int a;

	a = 0;
	max_len = 0;
	while (a < file[0].nb_file)
	{
		while ((a < file[0].nb_file) && !(syn.a) && file[a].name[0] == '.')
			a++;
		if ((a >= file[0].nb_file))
			break ;
		if (choice == 0 && max_len < ft_strlen(file[a].user))
			max_len = ft_strlen(file[a].user);
		if (choice == 1 && max_len < ft_strlen(file[a].group))
			max_len = ft_strlen(file[a].group);
		if (choice == 2 && max_len < ft_strlen(file[a].name))
			max_len = ft_strlen(file[a].name);
		a++;
	}
	return (max_len);
}

int		ft_print_total(t_ls *file, t_option syn)
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (a < file[0].nb_file)
	{
		if (file[a].name[0] == '.')
			b++;
		if (file[a].name[0] != '.')
			return (1);
		a++;
	}
	if (syn.a == TRUE)
		return (b - 2);
	return (0);
}

t_space	ft_fill_len_params(t_ls *file, t_option syn)
{
	t_space	space;

	if (ft_print_total(file, syn) > 0)
	{
		ft_putstr("total ");
		ft_putnbr(file[0].nb_blocks);
		ft_putchar('\n');
	}
	space.size = ft_max_lenint(file, syn, 0);
	space.link = ft_max_lenint(file, syn, 1);
	space.major = ft_max_lenint(file, syn, 2);
	space.minor = ft_max_lenint(file, syn, 3);
	space.user = ft_max_lenchar(file, syn, 0);
	space.group = ft_max_lenchar(file, syn, 1);
	return (space);
}
