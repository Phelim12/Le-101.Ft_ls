/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   option_ls.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/22 17:15:55 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/22 17:15:55 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_modify_option(char **option, char **ptr, char c)
{
	int	cur;

	cur = -1;
	if (c == 'f' && !(ft_strchr((*option), 'a')))
		**ptr = 'a';
	if (ft_strchr(LARGE, c) && !(ft_strchr((*option), 'l')))
		**ptr = 'l';
	if (**ptr != 0)
		(*ptr)++;
	ft_modify_option_next(option, c);
}

void	ft_modify_option_end(char **option, char c)
{
	int	cur;

	cur = -1;
	while (ft_strchr(COL, c) && (*option)[++cur])
		if (((*option)[cur]) == 'x')
			(*option)[cur] -= 127;
	while (ft_strchr(COL, c) && (*option)[++cur])
		if (ft_strchr(COL, ((*option)[cur]) + 127))
			(*option)[cur] += 127;
	while (ft_strchr(LINE, c) && (*option)[++cur])
		if (ft_strchr(LINE, ((*option)[cur]) + 127))
			(*option)[cur] += 127;
	while (ft_strchr(LARGE, c) && (*option)[++cur])
		if (ft_strchr(LARGE, ((*option)[cur]) + 127))
			(*option)[cur] += 127;
	while (ft_strchr(NOLARGE, c) && (*option)[++cur])
		if (ft_strchr(NOLARGE, ((*option)[cur]) + 127))
			(*option)[cur] += 127;
}

void	ft_modify_option_next(char **option, char c)
{
	int	cur;

	cur = -1;
	while (c == 'F' && (*option)[++cur])
		if (((*option)[cur]) == 'p')
			(*option)[cur] -= 127;
	while (c == 'p' && (*option)[++cur])
		if (((*option)[cur]) == 'F')
			(*option)[cur] -= 127;
	while (ft_strchr(COL, c) && (*option)[++cur])
		if (ft_strchr(LINE, (*option)[cur]))
			(*option)[cur] -= 127;
	while (ft_strchr(LINE, c) && (*option)[++cur])
		if (ft_strchr(COL, (*option)[cur]))
			(*option)[cur] -= 127;
	while (ft_strchr(LARGE, c) && (*option)[++cur])
		if (ft_strchr(NOLARGE, (*option)[cur]))
			(*option)[cur] -= 127;
	while (ft_strchr(NOLARGE, c) && (*option)[++cur])
		if (ft_strchr(LARGE, (*option)[cur]))
			(*option)[cur] -= 127;
	ft_modify_option_end(option, c);
}

char	*ft_find_option(char ***argv, char *option, int y, int x)
{
	char	*ret;

	ret = option;
	while ((*argv)[y] && (*argv)[y][0] == '-' && (*argv)[y][1] != 0)
	{
		x = 0;
		if ((*argv)[y] && ft_strcmp((*argv)[y], "--") == 0 && ++y)
			break ;
		while ((*argv)[y][++x])
		{
			ft_modify_option(&ret, &option, (*argv)[y][x]);
			if (ft_strchr("ACFGRSTUacdfgilnoprtux1", (*argv)[y][x]) &&
				!(ft_strchr(option, (*argv)[y][x])))
				*option++ = (*argv)[y][x];
			if (!(ft_strchr("ACFGRSTUacdfgilnoprtux1", (*argv)[y][x])))
			{
				free(ret);
				return (ft_print_error_usage((*argv)[y][x]));
			}
		}
		y++;
	}
	*argv += y;
	return (ret);
}
