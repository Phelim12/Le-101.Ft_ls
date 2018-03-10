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

int		ft_print_reg_argv(t_ls *file, char *opt, int cur)
{
	char	*space;
	int		ret;

	ret = 0;
	space = ft_find_space_argv(file, opt);
	while (++cur < file->nb)
	{
		if (ft_strchr(opt, 'd') || ft_strchr(opt, '~'))
			ft_print_bonus_d(&file[cur], NULL, opt, space);
		else if (file[cur].type != 4 && file[cur].type > 0)
		{
			if (ft_strchr(opt, 'l'))
				ft_print_line_start(file[cur], space, opt);
			else
				ft_print_color_ls(file[cur], opt, -1, 1);
			space[10] = 1;
		}
		else if (file[cur].type != -1)
			ret++;
	}
	if (ret > 0 && space[10] == 1)
		ft_putchar('\n');
	free(space);
	return (ret);
}

void	ft_print_line_end(t_ls file, t_stat stat, char *sp, char *opt)
{
	char		buf[1024];
	char		*time;
	int			ret;

	time = ft_find_time(file.time, opt);
	if (S_ISBLK(stat.st_mode) || S_ISCHR(stat.st_mode))
	{
		ft_printf("%*d, ", sp[4] + 1, major(stat.st_rdev));
		ft_printf("%*d", sp[5] + 1, minor(stat.st_rdev));
	}
	else if (sp[6] > 0)
		ft_printf("%*d", sp[4] + sp[5] + 4, stat.st_size);
	else
		ft_printf("%*d", sp[3], stat.st_size);
	ft_printf("%s ", time);
	if (S_ISLNK(stat.st_mode) && (ret = readlink(file.path, buf, 1024)) > 0)
	{
		buf[ret] = 0;
		ft_print_color_ls(file, opt, -1, 0);
		ft_printf(" -> %s\n", buf);
	}
	else
		ft_print_color_ls(file, opt, -1, 1);
	free(time);
}

void	ft_print_uid_gid(t_stat stat, char *option, char *space)
{
	char		*str;
	t_passwd	*user;
	t_group		*grps;

	str = NULL;
	user = getpwuid(stat.st_uid);
	grps = getgrgid(stat.st_gid);
	if ((user == NULL || ft_strchr(option, 'n')) && !(ft_strchr(option, 'g')))
		ft_printf("%-*s  ", space[1], (str = ft_itoa((int)stat.st_uid)));
	else if (!(ft_strchr(option, 'g')) && !(ft_strchr(option, 'n')))
		ft_printf("%-*s  ", space[1], user->pw_name);
	ft_strdel(&str);
	if ((grps == NULL || ft_strchr(option, 'n')) && !(ft_strchr(option, 'o')))
		ft_printf("%-*s  ", space[2], (str = ft_itoa((int)stat.st_gid)));
	else if (!(ft_strchr(option, 'o')) && !(ft_strchr(option, 'n')))
		ft_printf("%-*s  ", space[2], grps->gr_name);
	ft_strdel(&str);
}

void	ft_print_line_start(t_ls file, char *space, char *option)
{
	char		*str;
	char		*law;
	t_stat		stat;

	str = NULL;
	lstat(file.path, &stat);
	law = ft_find_law(file.path, stat.st_mode, file.type);
	if (ft_strchr(option, 'i'))
		ft_printf("%s ", (str = ft_imaxtoa((intmax_t)stat.st_ino)));
	ft_printf("%s %*d ", law, space[0], stat.st_nlink);
	if (ft_strchr(option, 'g') && ft_strchr(option, 'o'))
		ft_putstr("  ");
	ft_print_uid_gid(stat, option, space);
	ft_print_line_end(file, stat, space, option);
	ft_strdel(&str);
	free(law);
}

void	ft_print_files(t_ls *file, char *option)
{
	char		*space;
	int			cur;

	cur = 0;
	space = ft_find_space(file, ft_strnew(7), option, -1);
	if (ft_strchr(option, 'l') && file->nb > 0)
		ft_printf("total %d\n", file->nb_blocks);
	while (cur < file->nb)
	{
		if (ft_strchr(option, 'l'))
			ft_print_line_start(file[cur], space, option);
		else
			ft_print_color_ls(file[cur], option, -1, 1);
		if (!(ft_strchr(option, 'R')))
			ft_free_files(&file[cur]);
		cur++;
	}
	free(space);
}
