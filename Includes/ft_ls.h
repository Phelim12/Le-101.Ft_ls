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

# define FT_MAX(a, b) ((a) > (b) ? (a) : (b))
# define FT_MAX_A(a,b) a = FT_MAX(a,b)

# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/stat.h> 
# include <dirent.h>
# include <unistd.h>
# include <time.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/xattr.h>
# include <sys/acl.h>

# include <stdio.h>

# define TRUE 1
# define FALSE 0

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct group	t_group;
typedef struct passwd	t_passwd;

typedef struct	s_ls
{
	int 	nb_blocks;
	int 	error;
	char	*name;
	char	*path;
	char	type;
	int		time;
	int		nb;
}				t_ls;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               ft_printf.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		ft_sort_ascii(t_ls *file, int a, int b);
void		ft_sort_time(t_ls *file, int a, int b);
void		ft_ls(char *dir, char *option);

int			ft_count_file(char *str);
char		*ft_find_option(char *str);
t_ls		*ft_find_files(char *str, char *option);
void		ft_ls_argv(const char **argv, char *option);
void		ft_ls_dir(t_ls *file, char *option);

char		*ft_check_rwx(int law);
char		ft_check_type_char(char type);
char		*ft_find_permission(char *path, mode_t law_b10, char type);
void		ft_print_ls(t_ls *file, char *option);

char		*ft_find_space(t_ls *file, char *space, int cur);
void		ft_free_files(t_ls *file);
#endif
