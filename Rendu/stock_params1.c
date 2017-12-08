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

char	*ft_check_rwx(int law)
{
	if (law == 7)
		return ("rwx");
	if (law == 6)
		return ("rw-");
	if (law == 5)
		return ("r-x");
	if (law == 4)
		return ("r--");
	if (law == 3)
		return ("-wx");
	if (law == 2)
		return ("-w-");
	if (law == 1)
		return ("--x");
	return ("---");
}

char	ft_check_type_char(char type)
{
	if (type == 1)
		return ('p');
	if (type == 2)
		return ('c');
	if (type == 4)
		return ('d');
	if (type == 6)
		return ('b');
	if (type == 8)
		return ('-');
	if (type == 10)
		return ('l');
	if (type == 12)
		return ('s');
	return ('?');
}

char	*ft_find_permission(char *path, mode_t law_b10, char type)
{
	char	*ret;
	int		law;

	ret = ft_strnew(11);
	ret[0] = ft_check_type_char(type);
	law = (ft_convert_base(law_b10, 8) % 1000);
	ft_strcat(ret, ft_check_rwx(law / 100));
	ft_strcat(ret, ft_check_rwx((law % 100) / 10));
	ft_strcat(ret, ft_check_rwx(law % 10));
	if ((listxattr(path, NULL, 1, XATTR_NOFOLLOW)) > 0)
		ret[10] = '@';
	else
		ret[10] = ' ';
	free(path);
	return (ret);
}

t_ls	ft_fill_one(char *path, t_dirent *ptr, t_stat stat, t_option syn)
{
	t_passwd	*user;
	t_group		*grps;
	t_ls		file;

	file.minor = 0;
	file.major = 0;
	file.rdev = stat.st_rdev;
	file.mode = stat.st_mode;
	file.type = ptr->d_type;
	file.time = stat.st_mtime;
	file.name = ft_strdup(ptr->d_name);
	if (syn.l == TRUE)
	{
		if (S_ISLNK(file.mode) || S_ISBLK(file.mode) || S_ISCHR(file.mode))
			ft_fill_special(&file, path);
		file.size = stat.st_size;
		user = getpwuid(stat.st_uid);
		grps = getgrgid(stat.st_gid);
		file.nb_link = stat.st_nlink;
		file.user = ft_strdup(user->pw_name);
		file.group = ft_strdup(grps->gr_name);
		file.law = ft_find_permission(path, stat.st_mode, file.type);
	}
	return (file);
}

t_ls	*ft_fill_all_files(char *str, t_option syn, int nb_file, int nb_blocks)
{
	t_dirent		*ptr;
	t_stat			stat;
	t_ls			*file;
	DIR				*repo;

	if ((repo = opendir(str)) == NULL)
		return (NULL);
	if ((file = malloc(sizeof(t_ls) * ft_count_file(str))) == NULL)
		return (NULL);
	while ((ptr = readdir(repo)) != NULL)
	{
		file[nb_file].tmp = ft_strjoin(str, ptr->d_name);
		lstat(file[nb_file].tmp, &stat);
		if ((ptr->d_name[0] == '.' && syn.a == TRUE) || (ptr->d_name[0] != '.'))
		{
			nb_blocks += stat.st_blocks;
			file[nb_file] = ft_fill_one(file[nb_file].tmp, ptr, stat, syn);
			nb_file++;
		}
	}
	file[0].nb_blocks = nb_blocks;
	file[0].nb_file = nb_file;
	closedir(repo);
	return (file);
}
