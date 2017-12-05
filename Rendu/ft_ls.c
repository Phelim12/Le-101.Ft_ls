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

void	ft_sort_ascii(t_ls *file, int a, int b)
{
	int	save_nb_file;
	int	save_nb_blocks;
	t_ls swap;

	save_nb_file = file[0].nb_file;
	save_nb_blocks = file[0].nb_blocks;
	while (a < save_nb_file)
	{
		b = 0;
		while (b < save_nb_file)
		{
			if (ft_strcmp(file[a].name, file[b].name) < 0)
			{
				swap = file[a];
				file[a] = file[b];
				file[b] = swap;
			}
			b++;
		}
		a++;
	}
	file[0].nb_file = save_nb_file;
	file[0].nb_blocks = save_nb_blocks;
}

void	ft_sort_time(t_ls *file, int a, int b)
{
	int	save_nb_file;
	int	save_nb_blocks;
	t_ls swap;

	save_nb_file = file[0].nb_file;
	save_nb_blocks = file[0].nb_blocks;
	while (a < save_nb_file)
	{
		b = 0;
		while (b < save_nb_file)
		{
			if (file[a].time > file[b].time)
			{
				swap = file[a];
				file[a] = file[b];
				file[b] = swap;
			}
			b++;
		}
		a++;
	}
	file[0].nb_file = save_nb_file;
	file[0].nb_blocks = save_nb_blocks;
}

int		ft_max_lenint(t_ls *file, t_option syn, int choice)
{
	int max_len;
	int a;

	a = 0;
	max_len = 0;
	while (a < file[0].nb_file)
	{
		while (syn.a == FALSE && file[a].name[0] == '.')
			a++;
		if (max_len < ft_lenint(file[a].nb_byte) && !choice)
			max_len = ft_lenint(file[a].nb_byte);
		if (max_len < ft_lenint(file[a].nb_link) && choice)
			max_len = ft_lenint(file[a].nb_link);
		a++;
	}
	return (max_len);
}


void	ft_print_file_rev(t_ls *file, t_option syn, int a)
{
	int		len_byte;
	int		len_link;

	if (syn.l == TRUE)
	{
		ft_putstr("total ");
		ft_putnbr(file[0].nb_blocks);
		ft_putchar('\n');
		len_byte = ft_max_lenint(file, syn, 0);
		len_link = ft_max_lenint(file, syn, 1);
	}
	while (a >= 0)
	{
		if (syn.a == TRUE && file[a].name[0] == '.')
			ft_print_stat(file[a], syn, len_link, len_byte);
		if (file[a].name[0] != '.')
			ft_print_stat(file[a], syn, len_link, len_byte);
		a--;
	}
}

void	ft_print_file(t_ls *file, t_option syn, int a)
{
	int		len_byte;
	int		len_link;

	if (syn.l == TRUE)
	{
		ft_putstr("total ");
		ft_putnbr(file[0].nb_blocks);
		ft_putchar('\n');
		len_byte = ft_max_lenint(file, syn, 0);
		len_link = ft_max_lenint(file, syn, 1);
	}
	while (a < file[0].nb_file)
	{
		while (syn.a == FALSE && file[a].name[0] == '.')
			a++;
		ft_print_stat(file[a], syn, len_link, len_byte);
		a++;
	}
}

void	ft_putnbr_alignment(int len_nb, int len_max, int nb)
{
	while (len_nb != len_max)
	{
		ft_putchar(' ');
		len_max--;
	}
	ft_putnbr(nb);
}

void	ft_print_stat(t_ls file, t_option syn, int len_link, int len_byte)
{
	char *tmp;
	if (syn.l == TRUE)
	{
		ft_putstr(file.law);
		ft_putstr("  ");
		ft_putnbr_alignment(ft_lenint(file.nb_link), len_link, file.nb_link);
		ft_putchar(' ');
		ft_putstr(file.user);
		ft_putstr("  ");
		ft_putstr(file.group);
		ft_putstr("  ");
		ft_putnbr_alignment(ft_lenint(file.nb_byte), len_byte, file.nb_byte);
		ft_putchar(' ');
		ft_putstr(tmp = ft_strsub(ctime(&file.time), 4, 12));
		ft_putchar(' ');
		ft_putendl(file.name);
		free(file.law);	
		free(file.user);	
		free(file.group);	
		free(tmp);
	}
	else
		ft_putendl(file.name);
}

void	ft_join_all_free(t_ls_r *params, char **name, char *str, int choice)
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

void	ft_ls_R(t_ls *file, t_option syn, char *str, int a)
{
	t_ls_r params;

	while (a < file[0].nb_file)
	{
		while ((a < file[0].nb_file) && (ft_strcmp(file[a].name, ".") == 0 || ft_strcmp(file[a].name, "..") == 0))
			free(file[a++].name);
		if (a >= file[0].nb_file)
			break;
		ft_join_all_free(&params, &file[a].name, str, TRUE);
		if (syn.u_r == TRUE && file[a].type == 4)
		{
			while (syn.a == FALSE && file[a].name[0] == '.')
				a++;
			ft_putchar('\n');
			ft_putendl(params.tmp1);
			ft_ls(params.tmp2, syn);
		}
		ft_join_all_free(&params, &file[a].name, str, FALSE);
		a++;
	}
}

void	ft_ls(char *str, t_option syn)
{
	t_ls			*file;

	file = ft_fill_all_files(str, syn);
	if (file == NULL)
		return;
	ft_sort_ascii(file, 0, 0);
	if (syn.t == TRUE)
		ft_sort_time(file, 0, 0);
	if (syn.l_r == TRUE)
		ft_print_file_rev(file, syn, (file[0].nb_file - 1));
	if (syn.l_r == FALSE)
		ft_print_file(file, syn, 0);
	if (file[0].nb_file > 2)
		ft_ls_R(file, syn, str, 0);
	else
	{
		free(file[0].name);
		free(file[1].name);
	}
	free(file);
}













