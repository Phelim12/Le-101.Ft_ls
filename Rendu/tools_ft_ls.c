/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_ft_ls.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/01 18:47:33 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/01 18:47:33 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_count_file(char *str)
{
    struct dirent	*ptr_file;
    int				nb_file;
	DIR				*repo;

	nb_file = 0;
    ptr_file = NULL;
	repo = opendir(str);
	while ((ptr_file = readdir(repo)) != NULL)
		nb_file++;
	closedir(repo);
	return (nb_file);
}

int		ft_convert_base(int nb, int len_base)
{
	int ret;
	int multi;

	ret = 0;
	multi = 1;
	while (nb)
	{
		ret +=	(nb % len_base * multi);
		nb /= len_base;
		multi *= 10;
	}
	return (ret);
}