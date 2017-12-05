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

# include <stdio.h>

# define TRUE 1
# define FALSE 0

typedef struct	s_ls
{
	int			nb_blocks;
	int			nb_file;
	char		*name;
	long int	time;
	char		type;
	char		*law;
	char		*group;
	char		*user;
	int			nb_byte;
	int			nb_link;
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
t_ls	*ft_fill_all_files(char *str, t_option syn);
char	*ft_find_permission(mode_t law_b10, char type);
t_ls	ft_fill_one_file(struct dirent *ptr_file, struct stat statbuf, t_option syn);

int		ft_count_file(char *str);
int		ft_convert_base(int nb, int len_base);
void	ft_print_stat(t_ls file, t_option syn, int len_link, int len_byte);

#endif
