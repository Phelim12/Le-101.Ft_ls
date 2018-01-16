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

int			ft_check_type(mode_t st_mode, int lst)
{
	if (lst == -1)
		return (-1);
	if (S_ISFIFO(st_mode))
		return (1);
	if (S_ISCHR(st_mode))
		return (2);
	if (S_ISDIR(st_mode))
		return (4);
	if (S_ISBLK(st_mode))
		return (6);
	if (S_ISREG(st_mode))
		return (8);
	if (S_ISLNK(st_mode))
		return (10);
	if (S_ISSOCK(st_mode))
		return (12);
	return (0);
}

void		ft_fill_argv(t_ls *file, char *str, char *option)
{
	char		buf[1024];
	int			check;
	t_stat 		stat;

	check = lstat(str, &stat);
	file->time = stat.st_mtime;
	file->name = ft_strdup(str);
	file->path = ft_strdup(str);
	file->type = ft_check_type(stat.st_mode, check);
	if (file->type == 10 && !(ft_strchr(option, 'l')))
	{
		readlink(file->name, buf, 1024);
		check = lstat(buf, &stat);
		if (ft_check_type(stat.st_mode, check) == 4)
			file->type = 4;
	}
}

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


t_ls		*ft_find_argv(char **argv, char *option)
{
	t_stat		stat;
	t_ls		*file;
	int			cur;

	cur = 0;
	while (argv[cur])
		cur++;
	if (!(file = malloc(sizeof(t_ls) * (cur + 1))))
		return (NULL);
	file->nb = 0;
	file->nb_blocks = 0;
	while (*argv)
	{
		cur = lstat(*argv, &stat);
		ft_fill_argv(&file[file->nb++], *argv, option);
		file->nb_blocks += stat.st_blocks;
		argv++;
	}
	return (file);
}

int			ft_print_reg_argv(t_ls *file, char *option, char *space, int cur)
{
	space = ft_find_space_argv(file, ft_strnew(10), cur);
	while (cur < file->nb)
	{
		if (file[cur].type != 4 && file[cur].type > 0)
		{
			if (ft_strchr(option, 'l'))
				ft_print_line_start(file[cur], space);
			else
				ft_printf("%s\n", file[cur].name);
			space[10] = 1;
		}
		else if (file[cur].type != -1)
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
			ft_sort_time(file, 1, 0);
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
			if (file[cur1].type == -1)
				ft_print_error(file[cur1].name);
			cur1++;
		}
	}
	free(file);
}
