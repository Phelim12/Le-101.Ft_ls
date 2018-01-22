/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_ls.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/17 17:57:26 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/17 17:57:26 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_print_error_usage(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ft_ls [-ACFGRSTUacdfgilnoprtux1] [file ...]\n", 2);
	return (ft_strdup("error"));
}

void	ft_print_error(char *name)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

int		ft_print_empty_argv(char **argv)
{
	int cur;

	cur = -1;
	while (argv[++cur])
	{
		if (argv[cur][0] == 0)
		{
			ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
			return (0);
		}
	}
	return (1);
}

char	**ft_print_error_argv(char **argv, int ac, int cur1, int cur2)
{
	t_stat		stat;
	DIR			*repo;
	char		**tab;

	if (ft_print_empty_argv(argv) == 0)
		return (NULL);
	ft_sort_tab_ascii(&argv);
	tab = (char **)malloc(sizeof(char *) * ac);
	while (argv[++cur1])
	{
		if ((repo = opendir(argv[cur1])) == NULL)
		{
			if ((lstat(argv[cur1], &stat)) == -1)
				ft_print_error(ft_cut_name(argv[cur1]));
			else
				tab[cur2++] = argv[cur1];
		}
		else
		{
			tab[cur2++] = argv[cur1];
			closedir(repo);
		}
	}
	tab[cur2] = NULL;
	return (tab);
}
