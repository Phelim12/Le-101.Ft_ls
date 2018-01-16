/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_ls.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 21:42:04 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/12 21:42:04 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_free_files(t_ls *file)
{
	free(file->name);
	free(file->path);
}

char		*ft_cut_name(char *dir)
{
	int cur;

	cur = ft_strlen(dir) - 1;
	if (dir[cur] == '/')
		dir[cur--] = 0;
	while (dir[cur] && dir[cur] != '/')
		cur--;
	if (cur < 0)
		cur = 0;
	return (dir + cur);
}

int			ft_count_file(char *str)
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

void		ft_safe_space(t_stat stat, char **space)
{
	t_group		*grps;
	t_passwd	*user;

	if ((user = getpwuid(stat.st_uid)) == NULL)
		FT_MAX_A((*space)[1], ft_strlen(ft_itoa((int)stat.st_uid)));
	else
		FT_MAX_A((*space)[1], ft_strlen(user->pw_name));
	if ((grps = getgrgid(stat.st_gid)) == NULL)
		FT_MAX_A((*space)[2], ft_strlen(ft_itoa((int)stat.st_gid)));
	else
		FT_MAX_A((*space)[2], ft_strlen(grps->gr_name));
}