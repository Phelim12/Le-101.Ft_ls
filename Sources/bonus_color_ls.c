/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bonus_color_ls.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/19 17:52:38 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/19 17:52:38 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_print_char_file(t_ls file, char *option)
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

char	*ft_find_color(t_ls file)
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

void	ft_print_color_ls(t_ls file, char *option, int space, int enter)
{
	char	*color;
	t_stat	stat;
	char	type;

	color = ft_find_color(file);
	space -= (ft_strlen(file.name) - 1);
	type = ft_print_char_file(file, option);
	lstat(file.path, &stat);
	if (ft_strchr(option, 'i') && !(ft_strchr(option, 'l')))
		ft_printf("%s ", ft_imaxtoa((intmax_t)stat.st_ino));
	if (ft_strchr(option, 'p') && file.type == 4)
		type = '/';
	if (ft_strchr(option, 'G') && color)
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
