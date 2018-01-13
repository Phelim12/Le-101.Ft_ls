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

char	ft_find_acl(char *path)
{
	acl_t 	acl;
	char	ret;

	if ((listxattr(path, NULL, 1, XATTR_NOFOLLOW)) > 0)
		ret = '@';
	else if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
		ret = '+';
	else
		ret = ' ';
	if (ret == '+')
		acl_free(acl);
	return (ret);
}

char	*ft_find_permission(char *path, mode_t law_b10, char type)
{
	char			*ret;
	char			*tmp;
	char			*law;

	ret = ft_strnew(11);
	ret[0] = ft_check_type_char(type);
	tmp = ft_umaxtoa_base((uintmax_t)law_b10, "01234567");
	law = ft_strsub(tmp, ft_strlen(tmp) - 3, ft_strlen(tmp));
	ft_strcat(ret, ft_check_rwx(law[0] - 48));
	ft_strcat(ret, ft_check_rwx(law[1] - 48));
	ft_strcat(ret, ft_check_rwx(law[2] - 48));
	ret[10] = ft_find_acl(path);
	free(law);
	free(tmp);
	return (ret);
}

char		*ft_find_space(t_ls *file, char *space, int cur)
{
	t_stat		stat;
	t_group		*grps;
	t_passwd	*user;

	while (cur < file->nb)
	{
		lstat(file[cur].path, &stat);
		user = getpwuid(stat.st_uid);
		grps = getgrgid(stat.st_gid);
		FT_MAX_A(space[0], ft_ulen(stat.st_nlink));
		FT_MAX_A(space[1], ft_strlen(user->pw_name));
		FT_MAX_A(space[2], ft_strlen(grps->gr_name));
		FT_MAX_A(space[3], ft_ilen(stat.st_size));
		if (S_ISBLK(stat.st_mode) || S_ISCHR(stat.st_mode))
		{
			FT_MAX_A(space[4], ft_ilen(minor(stat.st_rdev)));
			FT_MAX_A(space[5], ft_ilen(major(stat.st_rdev)));
			space[6] = TRUE;
		}
		cur++;
	}
	return (space);
}

char		*ft_find_option(char *str)
{
	char	*option;
	char	*ret;

	option = ft_strnew(10);
	ret = option;
	while (*str)
	{
		if (ft_strchr("alRrt", *str) && !(ft_strchr(option, *str)))
		{
			*option = *str;
			option++;
		}
		if (!(ft_strchr("alRrt", *str)))
		{
			ft_printf("ft_ls: illegal option -- %c\n", *str);
			ft_printf("usage: ft_ls [-Ralrt] [file ...]\n", *str);
			return (ft_strdup("error"));
		}
		str++;
	}
	return (ret);
}

t_ls	*ft_find_files(char *str, char *option)
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
	{
		if ((ptr->d_name[0] == '.' && ft_strchr(option, 'a')) || (ptr->d_name[0] != '.'))
		{
			file[file->nb].name = ft_strdup(ptr->d_name);
			file[file->nb].path = ft_strjoin(str, file[file->nb].name );
			lstat(file[file->nb].path, &stat);
			file[file->nb].type = ptr->d_type;
			file[file->nb].time = stat.st_mtime;
			file->nb_blocks += stat.st_blocks;
			file->nb++;
		}
	}
	closedir(repo);
	return (file);
}