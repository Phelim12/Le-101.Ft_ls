/* ************************************************************************** */
/*														  LE - /			*/
/*															  /			 */
/*   ft_stock_params.c								.::	.:/ .	  .::   */
/*												 +:+:+   +:	+:  +:+:+	*/
/*   By: clcreuso <clcreuso@student.le-101.fr>	  +:+   +:	+:	+:+	 */
/*												 #+#   #+	#+	#+#	  */
/*   Created: 2017/11/30 16:01:42 by clcreuso	 #+#   ##	##	#+#	   */
/*   Updated: 2017/11/30 16:01:42 by clcreuso	###	#+. /#+	###.fr	 */
/*														 /				  */
/*														/				   */
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

t_ls	ft_fill_one_file(t_dirent *ptr_file, t_stat statbuf, char *str, t_option syn)
{
	t_passwd	*user;
 	t_group		*grps;
	t_ls		file;
 	char		*path;
	char		buf[1024];
 	int ret;

	file.type = ptr_file->d_type;
	file.time = statbuf.st_mtime;
	file.name = ft_strdup(ptr_file->d_name);
	path = ft_strjoin(str, "/");
	path = ft_strjoin(path, file.name);
	file.ptr_link = NULL;
	if (syn.l == TRUE)
	{
		if (S_ISLNK(statbuf.st_mode))
		{
			ret = readlink(path, buf, 1024);
			buf[ret] = '\0';	
			file.ptr_link = ft_strdup(buf);
		}
		file.nb_byte = statbuf.st_size;
		user = getpwuid(statbuf.st_uid);
		grps = getgrgid(statbuf.st_gid);
		file.nb_link = statbuf.st_nlink;
		file.user = ft_strdup(user->pw_name);
		file.group = ft_strdup(grps->gr_name);
		file.law = ft_find_permission(path, statbuf.st_mode, file.type);
	}
	return (file);
}

t_ls	*ft_fill_all_files(char *str, t_option syn, int nb_file, int nb_blocks)
{
	t_dirent		*ptr_file;
	t_stat			statbuf;
	t_ls			*file;
	DIR				*repo;
	char			*tmp;

	if ((repo = opendir(str)) == NULL)
		return (NULL);
	if ((file = malloc(sizeof(t_ls) * ft_count_file(str))) == NULL)
		return (NULL);
	while ((ptr_file = readdir(repo)) != NULL)
	{
		tmp = ft_strjoin(str, ptr_file->d_name);
		lstat(tmp, &statbuf);
		nb_blocks += statbuf.st_blocks;
		file[nb_file] = ft_fill_one_file(ptr_file, statbuf, str, syn);
		nb_file++;
		free(tmp);
	}
	file[0].nb_blocks = nb_blocks;
	file[0].nb_file = nb_file;
	closedir(repo);
	return (file);
}
