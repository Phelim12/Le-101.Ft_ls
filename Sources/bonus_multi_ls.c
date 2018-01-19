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
		ft_ls_argv(ft_find_argv(tab, opt), opt, 0, 1);
		free(tab[1]);
		free(tab);
	}
	else if (ft_strchr(opt, 'l'))
		ft_print_line_start(*file, sp, opt);
	else
		ft_print_color_ls(*file, opt, -1, 1);
}

void	ft_modify_option(char **option, char **ptr, char c)
{
	int cur;

	cur = 0;
	if ((c == 'g' || c == 'o') && !(ft_strchr((*option), 'l')))
	{
		**ptr = 'l';
		(*ptr)++;
	}
	if (c == '1')
		while ((*option)[cur])
		{
			if ((*option)[cur] == 'l')
				(*option)[cur] = '1';
			cur++;
		}
}
