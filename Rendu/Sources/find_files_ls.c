/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   params_ls.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/22 18:58:47 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 18:58:47 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_fill_file(t_ls *file, char *str, char *option, int *ptr)
{
	t_stat	stat;
	int		check;

	file->exec = 0;
	file->path = ft_strjoin(str, file->name);
	check = lstat(file->path, &stat);
	*ptr += stat.st_blocks;
	file->size = stat.st_size;
	file->time = ft_find_good_time(option, stat);
	if (S_ISREG(stat.st_mode) && (S_IXUGO & stat.st_mode))
		file->exec = 1;
}

void	ft_fill_file_argv(t_ls *file, char *str, char *option)
{
	int			check;
	t_stat		statbuf;

	file->exec = 0;
	if (ft_strchr(option, 'l'))
		check = lstat(str, &statbuf);
	else
		check = stat(str, &statbuf);
	if (check == -1)
		check = lstat(str, &statbuf);
	file->size = statbuf.st_size;
	file->name = ft_strdup(str);
	file->path = ft_strdup(str);
	file->time = ft_find_good_time(option, statbuf);
	file->type = ft_check_type(statbuf.st_mode, check);
	if (S_ISREG(statbuf.st_mode) && (S_IXUGO & statbuf.st_mode))
		file->exec = 1;
}

t_ls	*ft_find_files_argv(char **argv, char *option)
{
	t_stat		stat;
	t_ls		*file;
	int			argc;
	int			cur;

	argc = ft_count_argv(argv);
	if (!(file = malloc(sizeof(t_ls) * (argc + 1))))
		return (NULL);
	cur = 0;
	file->nb = 0;
	file->nb_blocks = 0;
	while (cur < argc)
	{
		lstat(argv[cur], &stat);
		file->nb_blocks += stat.st_blocks;
		ft_fill_file_argv(&file[file->nb++], argv[cur], option);
		cur++;
	}
	return (file);
}

t_ls	*ft_find_files(char *str, char *option)
{
	t_dirent	*ptr;
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
			(ptr->d_name[0] != '.') || (ft_strchr(option, 'A') &&
			ft_strcmp(".", ptr->d_name) && ft_strcmp("..", ptr->d_name)))
		{
			file[file->nb].type = ptr->d_type;
			file[file->nb].name = ft_strdup(ptr->d_name);
			ft_fill_file(&file[file->nb++], str, option, &file->nb_blocks);
		}
	closedir(repo);
	return (file);
}
