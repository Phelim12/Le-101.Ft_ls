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

t_option	ft_option_to_zero()
{
	t_option	syn;

	syn.a = FALSE;
	syn.t = FALSE;
	syn.l = FALSE;
	syn.u_r = FALSE;
	syn.l_r = FALSE;
	syn.error = FALSE;
	return (syn);
}

t_option	ft_check_params(char *str, int a)
{
	t_option	syn;

	syn = ft_option_to_zero();
	while (str[a])
	{
		if (str[a] == 'a')
			syn.a = TRUE;
		if (str[a] == 'R')
			syn.u_r = TRUE;
		if (str[a] == 'r')
			syn.l_r = TRUE;
		if (str[a] == 't')
			syn.t = TRUE;
		if (str[a] == 'l')
			syn.l = TRUE;
		if (str[a] != 'l' && str[a] != 'R' && str[a] != 'r' && str[a] != 't' 
			&& str[a] != 'a')
		{
			ft_putstr("./ft_ls: illegal option -- ");
			ft_putchar(str[a]);
			ft_putstr("\nusage: ./ft_ls [-Ralrt] [file ...]\n");
			syn.error = TRUE;
		}
		a++;
	}
	return (syn);
}

void	ft_check_file(char **argv, t_option syn)
{
	DIR				*repo;
	char			*tmp1;
	char			*tmp2;
	int				a;

	a = 0;
	while (argv[a])
	{
		repo = opendir(argv[a]);
		if (repo == NULL)
		{
			tmp2 = ft_strjoin(argv[a], ": ");
			tmp1 = ft_strjoin("./ft_ls: ", tmp2);
			ft_putstr(tmp1);
			perror("");
			free(tmp2);
		}
		else
		{
			if (argv[a][ft_strlen(argv[a]) - 1] == '/')
				tmp1 = ft_strdup(argv[a]);
			else
				tmp1 = ft_strjoin(argv[a], "/");
			closedir(repo);
			ft_ls(tmp1, syn);
		}
		a++;
		free(tmp1);
	}
}

int			main(int argc, char const *argv[])
{
	char		*def;
	t_option 	syn;

	def = ft_strdup("./");
	syn = ft_option_to_zero();
	if (argc >= 2 && argv[1][0] == '-')
	{
		syn = ft_check_params((char *)argv[1], 1);
		ft_check_file((char **)argv + 2, syn);
		if (argc == 2 && argv[1][1] != 0 && syn.error == FALSE)
			ft_ls(def, syn);
	}
	else if (argc > 1 && argv[1][0] != '-')
		ft_check_file((char **)argv + 1, syn);
	else
		ft_ls(def, syn);
	free(def);
	return 0;
}