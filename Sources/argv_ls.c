/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   argv_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/15 19:52:55 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/15 19:52:55 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_find_space_argv(t_ls *file, char *space, int cur)
{
	t_stat		stat;

	while (++cur < file->nb)
	{
		while (file[cur].type == 4)
			cur++;
		if (cur >= file->nb)
			break ;
		lstat(file[cur].path, &stat);
		ft_safe_space(stat, &space);
		FT_MAX_A(space[0], ft_ulen(stat.st_nlink));
		FT_MAX_A(space[3], ft_ilen(stat.st_size));
		if (S_ISBLK(stat.st_mode) || S_ISCHR(stat.st_mode))
		{
			FT_MAX_A(space[4], ft_ilen(minor(stat.st_rdev)));
			FT_MAX_A(space[5], ft_ilen(major(stat.st_rdev)));
			space[6] = TRUE;
		}
	}
	return (space);
}

void		ft_fill_argv(t_ls *file, char *str, int *ptr2)
{
	t_stat		stat;

	file->name = ft_strdup(str);
	file->path = ft_strdup(str);
	lstat(file->path, &stat);
	file->time = stat.st_mtime;
	*ptr2 += stat.st_blocks;
	file->type = 0;
	if (S_ISREG(stat.st_mode))
		file->type = 8;
	if (S_ISDIR(stat.st_mode))
		file->type = 4;
	if (S_ISCHR(stat.st_mode))
		file->type = 2;
	if (S_ISBLK(stat.st_mode))
		file->type = 6;
	if (S_ISFIFO(stat.st_mode))
		file->type = 1;
	if (S_ISLNK(stat.st_mode))
		file->type = 10;
	if (S_ISSOCK(stat.st_mode))
		file->type = 12;
}

t_ls		*ft_find_argv(char **argv, char *option)
{
	t_dirent	*ptr;
	t_stat		stat;
	t_ls		*file;
	int			len;

	len = 0;
	while (argv[len])
		len++;
	if (!(file = malloc(sizeof(t_ls) * (len + 1))))
		return (NULL);
	file->nb = 0;
	file->nb_blocks = 0;
	while (*argv)
	{
		if (((*argv)[0] == '.' && ft_strchr(option, 'a')) ||
			((*argv)[0] != '.') || ((*argv)[0] == '.' && (*argv)[1] == '/'))
			ft_fill_argv(&file[file->nb++], *argv, &file->nb_blocks);
		argv++;
	}
	return (file);
}

int			ft_print_reg_argv(t_ls *file, char *option, char *space, int cur)
{
	space = ft_find_space_argv(file, ft_strnew(10), cur);
	while (cur < file->nb)
	{
		if (file[cur].type != 4)
		{
			if (ft_strchr(option, 'l'))
				ft_print_line_start(file[cur], space);
			else
				ft_printf("%s\n", file[cur].name);
			space[10] = 1;
		}
		else
			space[9]++;
		cur++;
	}
	if (space[9] > 0)
	{
		free(space);
		if (space[10] == 1)
			ft_putchar('\n');
		return ((int)space[9]);
	}	
	free(space);
	return (0);
}

void		ft_ls_argv(char **argv, char *option, int cur1, int cur2)
{
	t_ls	*file;
	t_stat	stat;

	if ((file = ft_find_argv(argv, option)))
	{
		ft_sort_ascii(file, 0, 0);
		if (ft_strchr(option, 't'))
			ft_sort_time(file, 0, 0);
		if (ft_strchr(option, 'r'))
			ft_sort_rev(file, 0);
		cur2 = ft_print_reg_argv(file, option, NULL, 0);
		while (cur1 < file->nb)
		{
			if (file[cur1].type == 4)
			{
				if (file->nb > 1)
					ft_printf("%s:\n", file[cur1].path);
				ft_ls(file[cur1].path, option, 0);
				if (--cur2 > 0)
					ft_putchar('\n');
			}
			cur1++;
		}
	}
	free(file);
}
