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

int		ft_check_time(time_t event)
{
	time_t	now;

	now = time(&now);
	if (now - event >= 0 && now - event <= 6 * 365 / 12 * 24 * 60 * 60)
		return (1);
	else
		return (0);
}

char	ft_check_acl(char *path)
{
	acl_t	acl;
	char	ret;

	if ((listxattr(path, NULL, 1, XATTR_NOFOLLOW)) > 0)
		ret = '@';
	else if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
		ret = '+';
	else
		ret = ' ';
	if (ret == '+')
		acl_free(acl);
	return (ret);
}

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

char	*ft_check_permission(char *path, mode_t law_b10, char type)
{
	char			*ret;
	char			*tmp;
	char			*law;

	ret = ft_strnew(11);
	ret[0] = ft_check_type_char(type);
	tmp = ft_umaxtoa_base((uintmax_t)law_b10, "01234567");
	law = ft_strsub(tmp, ft_strlen(tmp) - 4, ft_strlen(tmp));
	ft_strcat(ret, ft_check_rwx(law[1] - 48));
	ft_strcat(ret, ft_check_rwx(law[2] - 48));
	ft_strcat(ret, ft_check_rwx(law[3] - 48));
	ret[10] = ft_check_acl(path);
	if (law[0] == '4')
		ret[3] = 's';
	if (law[0] == '2')
		ret[6] = 's';
	if (law[0] == '1')
		ret[9] = 't';
	free(law);
	free(tmp);
	return (ret);
}
