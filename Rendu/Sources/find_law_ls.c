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
	return ('d');
}

void	ft_modify_law(char **ret, char *path, char c)
{
	acl_t	acl;

	if (ft_strchr("4567", c) && (*ret)[3] == 'x')
		(*ret)[3] = 's';
	else if (ft_strchr("4567", c) && (*ret)[3] != 'x')
		(*ret)[3] = 'S';
	if (ft_strchr("2367", c) && (*ret)[6] == 'x')
		(*ret)[6] = 's';
	else if (ft_strchr("2367", c) && (*ret)[6] != 'x')
		(*ret)[6] = 'S';
	if (ft_strchr("1357", c) && (*ret)[9] == 'x')
		(*ret)[9] = 't';
	else if (ft_strchr("1357", c) && (*ret)[9] != 'x')
		(*ret)[9] = 'T';
	if ((listxattr(path, NULL, 1, XATTR_NOFOLLOW)) > 0)
		(*ret)[10] = '@';
	else if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		(*ret)[10] = '+';
		acl_free(acl);
	}
	else
		(*ret)[10] = ' ';
}

char	*ft_find_law(char *path, mode_t law_b10, char type)
{
	char	*ret;
	char	*tmp;
	char	*law;

	ret = ft_strnew(11);
	ret[0] = ft_check_type_char(type);
	tmp = ft_umaxtoa_base((uintmax_t)law_b10, "01234567");
	law = ft_strsub(tmp, ft_strlen(tmp) - 4, ft_strlen(tmp));
	ft_strcat(ret, ft_check_rwx(law[1] - 48));
	ft_strcat(ret, ft_check_rwx(law[2] - 48));
	ft_strcat(ret, ft_check_rwx(law[3] - 48));
	ft_modify_law(&ret, path, law[0]);
	free(law);
	free(tmp);
	return (ret);
}
