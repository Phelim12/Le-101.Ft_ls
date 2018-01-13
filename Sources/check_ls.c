/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_ls.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 21:43:14 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/12 21:43:14 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_check_rwx(int law)
{
	if (law == 7)
		return ("rwx");
	if (law == 6)
		return ("rw-");
	if (law == 5)
		return ("r-x");
	if (law == 4)
		return ("r--");
	if (law == 3)
		return ("-wx");
	if (law == 2)
		return ("-w-");
	if (law == 1)
		return ("--x");
	return ("---");
}

char	ft_check_type_char(char type)
{
	if (type == 1)
		return ('p');
	if (type == 2)
		return ('c');
	if (type == 4)
		return ('d');
	if (type == 6)
		return ('b');
	if (type == 8)
		return ('-');
	if (type == 10)
		return ('l');
	if (type == 12)
		return ('s');
	return ('?');
}