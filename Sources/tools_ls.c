/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_ls.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 21:42:04 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/12 21:42:04 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_count_file(char *str)
{
	t_dirent	*ptr_file;
	int			nb_file;
	DIR			*repo;

	nb_file = 0;
	ptr_file = NULL;
	repo = opendir(str);
	while ((ptr_file = readdir(repo)) != NULL)
		nb_file++;
	closedir(repo);
	return (nb_file);
}

