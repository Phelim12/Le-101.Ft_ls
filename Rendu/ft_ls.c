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
		if (max_len < ft_lenint(file[a].nb_link) && choice == 1)
			max_len = ft_lenint(file[a].nb_link);
		if (max_len < ft_lenint(major(file[a].rdev)) && choice == 2)
			max_len = ft_lenint(major(file[a].rdev));
		if (max_len < ft_lenint(minor(file[a].rdev)) && choice == 3)
			max_len = ft_lenint(minor(file[a].rdev));
		a++;
	}
	return (max_len);
}

int		ft_max_lenchar(t_ls *file, t_option syn, int choice)
{
	int max_len;
	int a;

	a = 0;
	max_len = 0;
	while (a < file[0].nb_file)
	{
		while (syn.a == FALSE && file[a].name[0] == '.')
			a++;
		if (max_len < ft_strlen(file[a].user) && !choice)
			max_len = ft_strlen(file[a].user);
		if (max_len < ft_strlen(file[a].group) && choice)
			max_len = ft_strlen(file[a].group);
		a++;
	}
	return (max_len);
}

void	ft_print_file_rev(t_ls *file, t_option syn, int a)
{
	if (syn.l == TRUE)
	{
		ft_putstr("total ");
		ft_putnbr(file[0].nb_blocks);
		ft_putchar('\n');
		file[0].len_size = ft_max_lenint(file, syn, 0);
		file[0].len_link = ft_max_lenint(file, syn, 1);
		file[0].len_major = ft_max_lenint(file, syn, 2);
		file[0].len_minor = ft_max_lenint(file, syn, 3);
		file[0].len_user = ft_max_lenchar(file, syn, 0);
		file[0].len_group = ft_max_lenchar(file, syn, 1);
	}
	while (a >= 0)
	{
		while (syn.a == FALSE && file[a].name[0] == '.')
			a--;
		ft_print_stat(file[a], file[0], syn);
		a--;
	}
}

void	ft_print_file(t_ls *file, t_option syn, int a)
{
	if (syn.l == TRUE)
	{
		ft_putstr("total ");
		ft_putnbr(file[0].nb_blocks);
		ft_putchar('\n');
		file[0].len_size = ft_max_lenint(file, syn, 0);
		file[0].len_link = ft_max_lenint(file, syn, 1);
		file[0].len_major = ft_max_lenint(file, syn, 2);
		file[0].len_minor = ft_max_lenint(file, syn, 3);
		file[0].len_user = ft_max_lenchar(file, syn, 0);
		file[0].len_group = ft_max_lenchar(file, syn, 1);
	}
	while (a < file[0].nb_file)
	{
		while (syn.a == FALSE && file[a].name[0] == '.')
			a++;
		ft_print_stat(file[a], file[0], syn);
		a++;
	}
}

void	ft_alignment(int len, char *str, int nb)
{
	if (nb == 0 && str)
		ft_putstr(str);
	while (len-- > 0)
		ft_putchar(' ');
	if (str == NULL && nb >= 0)
		ft_putnbr(nb);
}

void	ft_print_stat(t_ls file, t_ls space, t_option syn)
{
	char *tmp;
	if (syn.l == TRUE)
	{
		ft_putstr(ft_strcat(file.law, " "));
		ft_alignment((space.len_link - ft_lenint(file.nb_link)), NULL, file.nb_link);
		ft_putchar(' ');
		ft_alignment((space.len_user - ft_strlen(file.user) + 2), file.user, 0);
		ft_alignment((space.len_group - ft_strlen(file.group) + 1), file.group, 0);
		if (!(file.rdev) && file.law[0] != 'c')
			ft_alignment(space.len_size + space.len_minor - ft_lenint(file.nb_byte), NULL, file.nb_byte);
		else
		{
			ft_alignment(space.len_major - ft_lenint(major(file.rdev)), NULL, major(file.rdev));
			ft_putstr(", ");
			ft_alignment(space.len_minor - ft_lenint(minor(file.rdev)), NULL, minor(file.rdev));
		}
		ft_putstr(tmp = ft_strsub(ctime(&file.time), 3, 13));
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
	int len;

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
		return ;
	ft_sort_ascii(file, 0, 0);
	if (syn.t == TRUE)
		ft_sort_time(file, 0, 0);
	if (syn.l_r == TRUE && (syn.a == TRUE && file[0].nb_file >= 2))
		ft_print_file_rev(file, syn, (file[0].nb_file - 1));
	if (syn.l_r == FALSE && (syn.a == TRUE && file[0].nb_file >= 2))
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













