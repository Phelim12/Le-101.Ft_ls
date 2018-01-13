/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_ls.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 21:41:26 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/12 21:41:26 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_time_isrecent(time_t event)
{
	time_t	now;

	now = time(&now);
	if (now - event >= 0 && now - event <= 6 * 365 / 12 * 24 * 60 * 60)
		return (1);
	else
		return (0);
}

void		ft_print_line_end(t_ls file, t_stat stat, char *space, char *time)
{
	char 		buf[1024];
	int			ret;

	if (S_ISBLK(stat.st_mode) || S_ISCHR(stat.st_mode))
	{
		ft_printf("%*d, ", space[4] + 1, major(stat.st_rdev));
		ft_printf("%*d", space[5] + 1, minor(stat.st_rdev));
	}
	else if (space[6] == TRUE)
		ft_printf("%*d", space[4] + space[5] + 4, stat.st_size);
	else
		ft_printf("%*d", space[3] + 1, stat.st_size);
	if (S_ISLNK(stat.st_mode) && (ret = readlink(file.path, buf, 1024)) > 0)
	{
		buf[ret] = 0;
		ft_printf("%s %s -> %s\n", time, file.name, buf);
	}
	else
		ft_printf("%s %s\n", time, file.name);
}

char		*ft_find_time(time_t time)
{
	char *year;
	char *date;
	char *tmp;
	char *ret;

	date = ctime(&time);
	date[ft_strlen(date) - 1] = 0;
	if (ft_time_isrecent(time))
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

void		ft_print_line_start(t_ls file, char *space)
{
	t_passwd	*user;
	t_group		*grps;
	t_stat		stat;
	char		*time;
	char		*law;

	lstat(file.path, &stat);
	user = getpwuid(stat.st_uid);
	grps = getgrgid(stat.st_gid);
	time = ft_find_time(stat.st_mtime);
	law = ft_find_permission(file.path, stat.st_mode, file.type);
	ft_printf("%s %*d ", law,space[0], stat.st_nlink);
	ft_printf("%-*s  ", space[1], user->pw_name);
	ft_printf("%-*s ", space[2], grps->gr_name);
	ft_print_line_end(file, stat, space, time);
	free(time);
	free(law);
}

void		ft_print_ls(t_ls *file, char *option)
{
	char		*space;
	int			cur;

	cur = 0;
	space = ft_find_space(file, ft_strnew(7), 0);
	if (ft_strchr(option, 'l') && file->nb > 0)
		ft_printf("total %d\n", file->nb_blocks);
	while (cur < file->nb)
	{
		if (ft_strchr(option, 'l'))
			ft_print_line_start(file[cur], space);
		else
			ft_printf("%s\n", file[cur].name);
		if (!(ft_strchr(option, 'R')))
			ft_free_files(&file[cur]);
		cur++;
	}
	free(space);
}
