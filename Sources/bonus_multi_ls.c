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

int			ft_check_time(time_t event)
{
	time_t	now;

	now = time(&now);
	if (now - event >= 0 && now - event <= 6 * 365 / 12 * 24 * 60 * 60)
		return (1);
	else
		return (0);
}

intmax_t	ft_good_time(char *option, t_stat stat)
{
	intmax_t	ret;
	int			cur;

	ret = 0;
	cur = -1;
	ret = stat.st_mtime;
	while (option[++cur])
	{
		if (option[cur] == 'u')
			ret = stat.st_atime;
		if (option[cur] == 'c')
			ret = stat.st_ctime;
		if (option[cur] == 'U')
			ret = stat.st_birthtime;
	}
	return (ret);
}

void		ft_print_bonus_d(t_ls *file, char *name, char *opt, char *sp)
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
		ft_ls_argv(ft_find_argv(tab, opt), opt, 0, 1);
		free(tab[1]);
		free(tab);
	}
	else if (ft_strchr(opt, 'l'))
		ft_print_line_start(*file, sp, opt);
	else
		ft_print_color_ls(*file, opt, -1, 1);
}

void		ft_modify_option_next(char **option, char **ptr, char c, int cur)
{
	if (c == 'C' && cur == -1)
		while ((*option)[++cur])
			if ((*option)[cur] == '1')
				(*option)[cur] = 'C';
}

void		ft_modify_option(char **option, char **ptr, char c)
{
	int	cur;

	cur = -1;
	if (c == 'f' && !(ft_strchr((*option), 'a')))
		**ptr = 'a';
	if ((c == 'g' || c == 'o') && !(ft_strchr((*option), 'l')))
		**ptr = 'l';
	if (**ptr != 0)
		(*ptr)++;
	if (c == '1' && cur == -1)
		while ((*option)[++cur])
			if ((*option)[cur] == 'l')
				(*option)[cur] = '1';
	if (c == 'F' && cur == -1)
		while ((*option)[++cur])
			if ((*option)[cur] == 'p')
				(*option)[cur] = 'F';
	if (c == 'p' && cur == -1)
		while ((*option)[++cur])
			if ((*option)[cur] == 'F')
				(*option)[cur] = 'p';
	ft_modify_option_next(option, ptr, c, cur);
}
