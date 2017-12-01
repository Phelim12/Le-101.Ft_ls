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

void	ft_ls(char *str)
{
    struct dirent	*ptr_file;
	t_ls			*file;
	DIR				*repo;
	int				x;

	x = 2;
    ptr_file = NULL;
	repo = opendir(str);
	file = ft_fill_all_files(str);
}
