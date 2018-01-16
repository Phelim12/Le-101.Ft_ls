/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock_params1.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/08 16:17:34 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/08 16:17:34 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_fill_file(t_ls *file, t_dirent *ptr1, char *str, int *ptr2)
{
	t_stat		stat;

	file->name = ft_strdup(ptr1->d_name);
	file->path = ft_strjoin(str, file->name);
	lstat(file->path, &stat);
	file->type = ptr1->d_type;
	file->time = stat.st_mtime;
	*ptr2 += stat.st_blocks;
}

char		*ft_find_time(time_t time)
{
	char *year;
	char *date;
	char *tmp;
	char *ret;

	date = ctime(&time);
	date[ft_strlen(date) - 1] = 0;
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

char		*ft_find_space(t_ls *file, char *space, int cur)
{
	t_stat		stat;
	t_group		*grps;
	t_passwd	*user;

	while (++cur < file->nb)
	{
		lstat(file[cur].path, &stat);
		FT_MAX_A(space[0], ft_ulen(stat.st_nlink));
		if ((user = getpwuid(stat.st_uid)) == NULL)
			FT_MAX_A(space[1], ft_strlen(ft_itoa((int)stat.st_uid)));
		else
			FT_MAX_A(space[1], ft_strlen(user->pw_name));
		if ((grps = getgrgid(stat.st_gid)) == NULL)
			FT_MAX_A(space[2], ft_strlen(ft_itoa((int)stat.st_gid)));
		else
			FT_MAX_A(space[2], ft_strlen(grps->gr_name));
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

t_ls		*ft_find_files(char *str, char *option)
{
	t_dirent	*ptr;
	t_stat		stat;
	t_ls		*file;
	DIR			*repo;

	if ((repo = opendir(str)) == NULL)
		return (NULL);
	if (!(file = malloc(sizeof(t_ls) * ft_count_file(str))))
		return (NULL);
	file->nb = 0;
	file->nb_blocks = 0;
	while ((ptr = readdir(repo)) != NULL)
		if ((ptr->d_name[0] == '.' && ft_strchr(option, 'a')) ||
			(ptr->d_name[0] != '.'))
			ft_fill_file(&file[file->nb++], ptr, str, &file->nb_blocks);
	closedir(repo);
	return (file);
}

char		*ft_find_option(char ***argv, char *ret, int y, int x)
{
	char	*option;

	option = ft_strnew(10);
	ret = option;
	while ((*argv)[y] && (*argv)[y][0] == '-' && (*argv)[y][1] != 0)
	{
		x = 0;
		if ((*argv)[y] && ft_strcmp((*argv)[y], "--") == 0 && ++y)
			break ;
		while ((*argv)[y][++x])
		{
			if (ft_strchr("alRrt", (*argv)[y][x]) &&
				!(ft_strchr(option, (*argv)[y][x])))
				*option++ = (*argv)[y][x];
			if (!(ft_strchr("1alRrt", (*argv)[y][x])))
			{
				ft_putstr_fd("ft_ls: illegal option -- ", 2);
				ft_putchar_fd((*argv)[y][x], 2);
				ft_putstr_fd("\nusage: ft_ls [-Ralrt] [file ...]\n", 2);
				return (ft_strdup("error"));
			}
		}
		y++;
	}
	*argv += y;
	return (ret);
}
