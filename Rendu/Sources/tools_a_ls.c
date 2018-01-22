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

void		ft_free_files(t_ls *file)
{
	free(file->name);
	free(file->path);
}

int			ft_nb_col(void)
{
	t_winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return ((int)w.ws_col);
}

int			ft_count_argv(char **argv)
{
	int ret;

	ret = 0;
	while (argv[ret])
		ret++;
	return (ret);
}

int			ft_check_time(time_t event)
{
	time_t	now;

	now = time(&now);
	if (now - event >= 0 && now - event <= 6 * 365 / 12 * 24 * 60 * 60)
		return (1);
	else
		return (0);
}

char		*ft_cut_name(char *dir)
{
	int cur;

	cur = ft_strlen(dir) - 1;
	if (dir[cur] == '/')
		dir[cur--] = 0;
	while (dir[cur] && dir[cur] != '/')
		cur--;
	if (cur < 0)
		cur = 0;
	return (dir + cur);
}
