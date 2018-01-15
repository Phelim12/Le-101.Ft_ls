/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 14:34:34 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/30 14:34:34 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_dir(t_ls *file, char *option)
{
	int cur;

	cur = 0;
	while (cur < file->nb)
	{
		while (cur < file->nb && ((ft_strcmp(".", file[cur].name) == 0) ||
				(ft_strcmp("..", file[cur].name) == 0)))
			ft_free_files(&file[cur++]);
		if (cur >= file->nb)
			break ;
		if (file[cur].type == 4)
		{
			ft_printf("\n%s:\n", file[cur].path);
			ft_ls(file[cur].path, option, 0);
		}
		ft_free_files(&file[cur++]);
	}
}

void		ft_ls(char *dir, char *option, int release)
{
	t_ls	*file;

	if (dir[ft_strlen(dir) - 1] != '/' && ++release)
		dir = ft_strjoin(dir, "/");
	if ((file = ft_find_files(dir, option)))
	{
		ft_sort_ascii(file, 0, 0);
		if (ft_strchr(option, 't'))
			ft_sort_time(file, 0, 0);
		if (ft_strchr(option, 'r'))
			ft_sort_rev(file, 0);
		ft_print_ls(file, option);
		if (ft_strchr(option, 'R'))
			ft_ls_dir(file, option);
	}
	else
		ft_print_error(ft_cut_name(dir));
	if (release)
		free(dir);
	free(file);
}

int			main(int argc, char const *argv[])
{
	char *option;
	char **av;

	av = (char **)argv;
	if (argc == 1)
		ft_ls(".", "-", 0);
	else
	{
		option = ft_find_option(&av, NULL, 1, 0);
		if (ft_strcmp(option, "error") == 0)
		{
			free(option);
			return (1);
		}
		if (*av)
			ft_ls_argv(av, option, 0, 0);
		else
			ft_ls(".", option, 0);
		free(option);
	}
	return (0);
}
