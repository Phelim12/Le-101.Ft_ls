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

char	*ft_find_color(t_ls file)
{
	t_stat		statbuf;

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
	if ((stat(file.path, &statbuf)) >= 0 && (statbuf.st_mode > 0) &&
		(S_IEXEC & statbuf.st_mode))
		return ("\033[0;31;40m");
	if (file.type == 8)
		return (NULL);
	return ("\033[1;36;40m");
}

void	ft_print_color_ls(t_ls file, char *option, int space, int enter)
{
	char *color;

	color = ft_find_color(file);
	if (ft_strchr(option, 'G') && color)
		ft_putstr(color);
	if (space != -1)
		ft_printf("%-*s ", space, file.name);
	else if (enter)
		ft_printf("%s\n", file.name);
	else
		ft_printf("%s", file.name);
	if (ft_strchr(option, 'G') && color)
		ft_putstr("\033[0m");
}
