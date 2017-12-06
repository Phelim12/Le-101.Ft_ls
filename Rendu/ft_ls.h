/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/04 14:58:58 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/04 14:58:58 by clcreuso    ###    #+. /#+    ###.fr     */
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
# include <time.h>
# include "libft/libft.h"
# include <sys/xattr.h>

# include <stdio.h>

# define TRUE 1
# define FALSE 0

typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct group t_group;
typedef struct passwd t_passwd;

typedef struct	s_ls
{
	char		type;
	char		*law;
	char		*user;
	char		*name;
	char		*group;
	long int	time;
	int			rdev;
	int			nb_byte;
	int			nb_link;
	int			nb_file;
	int			len_user;
	int			len_size;
	int			len_link;
	int			len_minor;
	int			len_major;
	int			nb_blocks;
	int			len_group;
}				t_ls;

typedef struct  s_option
{
	char	l;
	char	u_r;
	char	l_r;
	char	a;
	char	t;
	char 	error;
}				t_option;


typedef struct	s_ls_r
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *tmp4;
	DIR	 *repo;
}				t_ls_r;

void	ft_ls(char *str, t_option syn);

char	*ft_check_rwx(int law);
char	ft_check_type_char(char type);
char	*ft_find_permission(char *str, mode_t law_b10, char type);
t_ls	ft_fill_one_file(t_dirent *ptr_file, t_stat statbuf, char *str, t_option syn);
t_ls	*ft_fill_all_files(char *str, t_option syn);

int		ft_count_file(char *str);
long int	ft_convert_base(long int nb, int len_base);
void	ft_print_stat(t_ls file, t_ls space, t_option syn);

#endif
