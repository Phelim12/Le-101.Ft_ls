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
# define FT_MAX_WR(a,b)	a = FT_MAX(a,b)

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

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct group	t_group;
typedef struct passwd	t_passwd;

typedef struct	s_ls
{
	int			mode;
	char 		*path;
	char		*tmp;
	long int	time;
	char		type;
	char		*law;
	char		*user;
	char		*name;
	char		*group;
	char 		*error;
	char		*ptr_link;
	int			minor;
	int			major;
	int			rdev;
	int			size;
	int			nb_link;
	int			nb_file;
	int			nb_blocks;
	char 		special;
}				t_ls;

typedef struct	s_space
{
	int			user;
	int			size;
	int			link;
	int			minor;
	int			major;
	int			group;
	int			name;
}				t_space;

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

t_space	ft_fill_len_params(t_ls *file, t_option syn);

void	ft_error(char *str);
int		ft_count_file(char *str);
long int	ft_convert_base(long int nb, int len_base);

void	ft_sort_time(t_ls *file, int a, int b);
void	ft_sort_ascii(t_ls *file, int a, int b);

void	ft_ls(char *str, t_option syn);
void	ft_ls_R(t_ls *file, t_option syn, char *str, int a);
int		ft_max_lenint(t_ls *file, t_option syn, int choice);
int		ft_max_lenchar(t_ls *file, t_option syn, int choice);
void	ft_free_params(t_ls_r *params, char **name, char *str, int choice);

char	*ft_check_rwx(int law);
char	ft_check_type_char(char type);
char	*ft_find_permission(char *path, mode_t law_b10, char type);
t_ls	*ft_fill_all_files(char *str, t_option syn, int nb_file, int nb_blocks);
t_ls	ft_fill_one(char *path, t_dirent *ptr, t_stat statbuf, t_option syn);

t_option	ft_option_to_zero();
t_option	ft_check_params(char *str, int a);
void		ft_check_file(char **argv, t_option syn);
void	ft_fill_special(t_ls *file, char *path);

void	ft_print_file(t_ls *file, t_option syn, int a);
void	ft_print_stat(t_ls file, t_space space, t_option syn);
void	ft_print_file_rev(t_ls *file, t_option syn, int a);
void	ft_alignment(char *str, int before, int after, int pick);

#endif
