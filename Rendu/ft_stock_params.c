/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_stock_params.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 16:01:42 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/30 16:01:42 by clcreuso    ###    #+. /#+    ###.fr     */
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

char	*ft_find_permission(mode_t law_b10, char type)
{
	char	*str;
	int		law;
	
	str = ft_strnew(10);
	str[0] = ft_check_type_char(type);
	law = (ft_convert_base(law_b10, 8) % 1000);
	str = ft_strjoin(str, ft_check_rwx(law / 100));
	str = ft_strjoin(str, ft_check_rwx((law % 100) / 10));
	str = ft_strjoin(str, ft_check_rwx(law % 10));
	return (str);
}

t_ls	ft_fill_one_file(struct dirent *ptr_file, struct stat statbuf, char l)
{
	struct passwd 	*user;
 	struct group 	*grps;
	t_ls			file;

	file.name = ft_strdup(ptr_file->d_name);
	file.time = statbuf.st_mtime;
	file.type = ptr_file->d_type;
	if (l == TRUE)
	{	
		user = getpwuid(statbuf.st_uid);
		grps = getgrgid(statbuf.st_gid);
		file.law = ft_find_permission(statbuf.st_mode, file.type);
		file.nb_link = statbuf.st_nlink;
		file.nb_byte = statbuf.st_size;
		file.group = ft_strdup(grps->gr_name);
		file.user = ft_strdup(user->pw_name);
	}
	return (file);
}

t_ls	*ft_fill_all_files(char *str, t_option syn)
{
    struct dirent	*ptr_file;
    struct stat     statbuf;
    t_ls			*file;
	int				nb_file;
	DIR				*repo;

	nb_file = 0;
    ptr_file = NULL;
	repo = opendir(str);
	file = malloc(sizeof(t_ls) * ft_count_file(str));
	while ((ptr_file = readdir(repo)) != NULL)
	{
		stat(ptr_file->d_name, &statbuf);
		file[nb_file] = ft_fill_one_file(ptr_file, statbuf, syn.l);
		nb_file++;
	}
	file[0].nb_file = nb_file;
	return (file);
}
