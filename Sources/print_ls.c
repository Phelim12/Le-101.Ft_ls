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

void		ft_print_error(char *name)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void		ft_print_error_argv(char **argv)
{
	t_stat		stat;
	DIR			*repo;
	int			cur;

	cur = -1;
	while (argv[++cur])
	{
		if ((repo = opendir(argv[cur])) == NULL)
		{
			if ((lstat(argv[cur], &stat)) == -1)
				ft_print_error(ft_cut_name(argv[cur]));
		}
		else
			closedir(repo);
	}
}

void		ft_print_line_end(t_ls file, t_stat stat, char *space)
{
	char		buf[1024];
	char		*time;
	int			ret;

	time = ft_find_time(stat.st_mtime);
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
	free(time);
}

void		ft_print_line_start(t_ls file, char *space)
{
	t_passwd	*user;
	t_group		*grps;
	t_stat		stat;
	char		*law;

	lstat(file.path, &stat);
	user = getpwuid(stat.st_uid);
	grps = getgrgid(stat.st_gid);
	law = ft_check_permission(file.path, stat.st_mode, file.type);
	ft_printf("%s %*d ", law, space[0], stat.st_nlink);
	if (user == NULL)
		ft_printf("%-*s  ", space[1], ft_itoa((int)stat.st_uid));
	else
		ft_printf("%-*s  ", space[1], user->pw_name);
	if (grps == NULL)
		ft_printf("%-*s  ", space[1], ft_itoa((int)stat.st_gid));
	else
		ft_printf("%-*s ", space[2], grps->gr_name);
	ft_print_line_end(file, stat, space);
	free(law);
}

void		ft_print_ls(t_ls *file, char *option)
{
	char		*space;
	int			cur;

	cur = 0;
	space = ft_find_space(file, ft_strnew(7), -1);
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
