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

char *ft_find_name(char *dir)
{
	int cur;

	cur = ft_strlen(dir) - 1;
	if (dir[cur] == '/')
		dir[cur--] = 0;
	while (dir[cur] && dir[cur] != '/')
		cur--;
	cur++;
	return (dir + cur);
}

void		ft_ls_argv(const char **argv, char *option)
{
	int cur;

	cur = 0;
	while (argv[cur])
	{
		ft_ls((char *)argv[cur], option);
		cur++;
	}
}

void		ft_free_files(t_ls *file)
{
	free(file->name);
	free(file->path);
}

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
			ft_ls(file[cur].path, option);
		}
		ft_free_files(&file[cur++]);
	}
}

void		ft_ls(char *dir, char *option)
{
	t_ls	*file;
	int		test;

	test = 0;
	if (dir[ft_strlen(dir) - 1] != '/' && ++test)
		dir = ft_strjoin(dir, "/");
	if ((file = ft_find_files(dir, option)))
	{
		if (ft_strchr(option, 't'))
			ft_sort_time(file, 0, 0);
		else
			ft_sort_ascii(file, 0, 0);
		ft_print_ls(file, option);
		if (ft_strchr(option, 'R'))
			ft_ls_dir(file, option);
	}
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(ft_find_name(dir), 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	if (test)
		free(dir);
	free(file);
	return ;
}

int			main(int argc, char const *argv[])
{
	char *option;

	if (argc == 1)
		ft_ls(".", "-");
	if (argc >= 2 && argv[1][0] == '-' && argv[1][1] != '\0')
	{
		option = ft_find_option((char *)(argv[1] + 1));
		if (ft_strcmp(option, "error") == 0)
			return (0);
		if (argc == 2)
			ft_ls(".", option);
		else
			ft_ls_argv((argv + 2), option);
		free(option);
	}
	else
		ft_ls_argv((argv + 1), "-");
}
