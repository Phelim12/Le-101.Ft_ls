/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_ls_01.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/22 19:30:01 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 19:30:01 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_check_type(mode_t st_mode, int lst)
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

int		ft_count_file(char *str)
{
	t_dirent	*ptr_file;
	int			nb_file;
	DIR			*repo;

	nb_file = 0;
	ptr_file = NULL;
	repo = opendir(str);
	while ((ptr_file = readdir(repo)) != NULL)
		nb_file++;
	closedir(repo);
	return (nb_file);
}

void	ft_safe_space(t_stat stat, char **space, char *option)
{
	char		*uid;
	char		*gid;
	t_group		*grps;
	t_passwd	*user;

	uid = ft_itoa((int)stat.st_uid);
	gid = ft_itoa((int)stat.st_gid);
	if ((user = getpwuid(stat.st_uid)) == NULL || ft_strchr(option, 'n'))
		FT_MAX_A((*space)[1], ft_strlen(uid));
	else
		FT_MAX_A((*space)[1], ft_strlen(user->pw_name));
	ft_strdel(&uid);
	if ((grps = getgrgid(stat.st_gid)) == NULL || ft_strchr(option, 'n'))
		FT_MAX_A((*space)[2], ft_strlen(gid));
	else
		FT_MAX_A((*space)[2], ft_strlen(grps->gr_name));
	ft_strdel(&gid);
}
