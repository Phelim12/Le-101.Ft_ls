/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/30 15:07:40 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/11/30 15:07:40 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H


# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/stat.h> 
# include <dirent.h>
# include <unistd.h>
# include "libft/libft.h"

# include <stdio.h>

# define TRUE 1
# define FALSE 0

typedef struct	s_ls
{
	int		nb_file;
	char	*name;
	int		time;
	char	type;
	char	*law;
	char	*group;
	char	*user;
	int		nb_byte;
	int		nb_link;
}				t_ls;

void	ft_ls(char *str);

char	*ft_check_rwx(int law);
char	ft_check_type_char(char type);
t_ls	*ft_fill_all_files(char *str);
char	*ft_find_permission(mode_t law_b10, char type);
t_ls	ft_fill_one_file(struct dirent *ptr_file, struct stat statbuf, int a);

int		ft_count_file(char *str);
int		ft_convert_base(int nb, int len_base);

#endif
