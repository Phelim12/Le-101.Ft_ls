/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_R.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 15:36:59 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/30 15:36:59 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_params(t_ls_r *params, char **name, char *str, int choice)
{
	if (choice == TRUE)
	{
		params->tmp3 = ft_strjoin(*name, ":");
		params->tmp4 = ft_strjoin(*name, "/");
		params->tmp1 = ft_strjoin(str, params->tmp3);
		params->tmp2 = ft_strjoin(str, params->tmp4);
	}
	else
	{
		free(params->tmp1);
		free(params->tmp2);
		free(params->tmp3);
		free(params->tmp4);
		free(*name);
	}
}

void	ft_ls_r_rev(t_ls *file, t_option syn, char *str, int a)
{
	t_ls_r params;

	while (a >= 0)
	{
		while ((a >= 0) && (ft_strcmp(file[a].name, ".") == 0 ||
			ft_strcmp(file[a].name, "..") == 0))
			a--;
		while ((a >= 0) && syn.a == FALSE && file[a].name[0] == '.')
			a--;
		if (a < 0)
			break ;
		ft_free_params(&params, &file[a].name, str, TRUE);
		if (syn.u_r == TRUE && file[a].type == 4)
		{
			ft_putchar('\n');
			ft_putendl(params.tmp1);
			ft_ls(params.tmp2, syn);
		}
		ft_free_params(&params, &file[a].name, str, FALSE);
		a--;
	}
}

void	ft_ls_r(t_ls *file, t_option syn, char *str, int a)
{
	t_ls_r params;

	while (a < file[0].nb_file)
	{
		while ((a < file[0].nb_file) && (ft_strcmp(file[a].name, ".") == 0 ||
		ft_strcmp(file[a].name, "..") == 0))
			a++;
		while ((a < file[0].nb_file) && !(syn.a) && file[a].name[0] == '.')
			a++;
		if (a >= file[0].nb_file)
			break ;
		ft_free_params(&params, &file[a].name, str, TRUE);
		if (syn.u_r == TRUE && file[a].type == 4)
		{
			ft_putchar('\n');
			ft_putendl(params.tmp1);
			ft_ls(params.tmp2, syn);
		}
		ft_free_params(&params, &file[a].name, str, FALSE);
		a++;
	}
}

void	ft_ls(char *str, t_option syn)
{
	t_ls			*file;

	if ((file = ft_fill_all_files(str, syn, 0, 0)) == NULL)
		return (ft_error(str));
	if (syn.a == FALSE && (file[0].nb_file == 2))
		return ;
	ft_sort_ascii(file, 0, 0);
	if (syn.t == TRUE)
		ft_sort_time(file, 0, 0);
	if (syn.l_r == TRUE)
		ft_print_file_rev(file, syn, (file[0].nb_file - 1));
	if (syn.l_r == FALSE)
		ft_print_file(file, syn, 0);
	if (syn.u_r == TRUE && syn.l_r == TRUE)
		ft_ls_r_rev(file, syn, str, (file[0].nb_file - 1));
	if (syn.u_r == TRUE && syn.l_r == FALSE)
		ft_ls_r(file, syn, str, 0);
	free(file);
}
