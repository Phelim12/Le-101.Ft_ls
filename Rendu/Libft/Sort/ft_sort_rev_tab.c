/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_rev_tab.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/14 18:51:48 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/14 18:51:48 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_rev_tab(char ***av)
{
	char	*swap;
	int		size;
	int		a;

	a = 0;
	size = 0;
	while ((*av)[size])
		size++;
	while (a < size / 2)
	{
		swap = (*av)[size - (a + 1)];
		(*av)[size - (a + 1)] = (*av)[a];
		(*av)[a] = swap;
		a++;
	}
}
