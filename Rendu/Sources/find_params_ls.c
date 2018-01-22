/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   find_params_ls.c.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/22 20:39:18 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 20:39:18 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

intmax_t	ft_find_good_time(char *option, t_stat stat)
{
	intmax_t	ret;
	int			cur;

	ret = 0;
	cur = -1;
	ret = stat.st_mtime;
	while (option[++cur])
	{
		if (option[cur] == 'u')
			ret = stat.st_atime;
		if (option[cur] == 'c')
			ret = stat.st_ctime;
		if (option[cur] == 'U')
			ret = stat.st_birthtime;
	}
	return (ret);
}

char		*ft_find_time(time_t time, char *option)
{
	char *year;
	char *date;
	char *tmp;
	char *ret;

	date = ctime(&time);
	date[ft_strlen(date) - 1] = 0;
	if (ft_strchr(option, 'T'))
		return (ft_strsub(date, 3, 21));
	if (ft_check_time(time))
		return (ft_strsub(date, 3, 13));
	else
	{
		year = ft_isdigit(date[20]) ?
		ft_strsub(date, 19, 5) : ft_strsub(date, 23, 6);
		tmp = ft_strsub(date, 3, 8);
		ret = ft_strjoin(tmp, year);
		free(year);
		free(tmp);
		return (ret);
	}
}

char		*ft_find_space_argv(t_ls *file, char *opt)
{
	char		*space;
	t_stat		stat;
	int			cur;

	cur = -1;
	space = ft_strnew(10);
	while (++cur < file->nb)
	{
		while (file[cur].type == 4)
			cur++;
		if (cur >= file->nb)
			break ;
		lstat(file[cur].path, &stat);
		ft_safe_space(stat, &space, opt);
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

char		*ft_find_space(t_ls *file, char *space, char *option, int cur)
{
	t_stat		stat;

	while (++cur < file->nb)
	{
		lstat(file[cur].path, &stat);
		ft_safe_space(stat, &space, option);
		FT_MAX_A(space[0], ft_ulen(stat.st_nlink));
		FT_MAX_A(space[3], ft_ilen(stat.st_size));
		if ((S_ISBLK(stat.st_mode) || S_ISCHR(stat.st_mode)) && ++space[6])
		{
			FT_MAX_A(space[4], ft_ilen(minor(stat.st_rdev)));
			FT_MAX_A(space[5], ft_ilen(major(stat.st_rdev)));
		}
	}
	return (space);
}
