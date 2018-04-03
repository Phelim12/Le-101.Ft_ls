/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bonus_d.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/19 15:45:10 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/19 15:45:10 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_check_char_file(t_ls file, char *option)
{
	if (!(ft_strchr(option, 'F')))
		return (0);
	if (file.type == 4)
		return ('/');
	if (file.type == 1)
		return ('|');
	if (file.type == 2)
		return ('%');
	if (file.type == 10)
		return ('@');
	if (file.type == 12)
		return ('=');
	if (file.exec == 1)
		return ('*');
	if (file.type == 8)
		return (0);
	return ('/');
}

char	*ft_check_color(t_ls file)
{
	if (file.type == 4)
		return ("\033[1;36;40m");
	if (file.type == 1)
		return ("\033[0;33;40m");
	if (file.type == 2)
		return ("\033[0;32;40m");
	if (file.type == 6)
		return ("\033[0;33;40m");
	if (file.type == 10)
		return ("\033[0;35;40m");
	if (file.type == 12)
		return ("\033[0;32;40m");
	if (file.exec == 1)
		return ("\033[0;31;40m");
	if (file.type == 8)
		return (NULL);
	return ("\033[1;36;40m");
}

void	ft_print_bonus_d(t_ls *file, char *name, char *opt, char *sp)
{
	char	**tab;
	int		cur;

	if (file == NULL)
	{
		cur = 0;
		tab = malloc(sizeof(char *) * 2);
		while (opt[cur])
		{
			if (opt[cur] == 'd')
				opt[cur] = '~';
			cur++;
		}
		tab[1] = NULL;
		tab[0] = ft_strdup(name);
		ft_ls_argv(ft_find_files_argv(tab, opt), opt, 0, 1);
		free(tab[0]);
		free(tab);
	}
	else if (ft_strchr(opt, 'l'))
		ft_print_line_start(*file, sp, opt);
	else
		ft_print_color_ls(*file, opt, -1, 1);
}

void	ft_print_color_ls(t_ls file, char *opt, int space, int enter)
{
	char	*color;
	char	*str;
	t_stat	stat;
	char	type;

	str = NULL;
	color = ft_check_color(file);
	space -= (ft_strlen(file.name) - 1);
	type = ft_check_char_file(file, opt);
	lstat(file.path, &stat);
	if (ft_strchr(opt, 'i') && !(ft_strchr(opt, 'l')))
		ft_printf("%s ", (str = ft_imaxtoa((intmax_t)stat.st_ino)));
	ft_strdel(&str);
	if (ft_strchr(opt, 'p') && file.type == 4)
		type = '/';
	if (ft_strchr(opt, 'G') && color)
		ft_printf("%s%s\033[0m", color, file.name);
	else
		ft_printf("%s", file.name);
	if (type)
		ft_putchar(type);
	if (enter)
		ft_putchar('\n');
	while (space-- > 0)
		ft_putchar(' ');
}
