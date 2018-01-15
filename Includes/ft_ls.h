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

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
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
	int		nb_blocks;
	int		error;
	char	*name;
	char	*path;
	char	type;
	int		time;
	int		nb;
}				t_ls;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   main.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				main(int argc, char const *argv[]);
void			ft_ls_dir(t_ls *file, char *option);
void			ft_ls(char *dir, char *option, int release);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 argv_ls.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_ls			*ft_find_argv(char **argv, char *option);
int				ft_print_reg_argv(t_ls *file, char *option, char *space, int cur);
void			ft_fill_argv(t_ls *file, char *str, int *ptr2);
void			ft_ls_argv(char **argv, char *option, int cur1, int cur2);
char			*ft_find_space_argv(t_ls *file, char *space, int cur);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 check_ls.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char			*ft_check_rwx(int law);
char			ft_check_acl(char *path);
int				ft_check_time(time_t event);
char			ft_check_type_char(char type);
char			*ft_check_permission(char *path, mode_t law_b10, char type);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 print_ls.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			ft_print_error(char *name);
void			ft_print_error_argv(char **argv);
void			ft_print_ls(t_ls *file, char *option);
void			ft_print_line_start(t_ls file, char *space);
void			ft_print_line_end(t_ls file, t_stat stat, char *space);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  sort_ls.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			ft_sort_rev(t_ls *file, int a);
void			ft_sort_time_argc(char ***av);
void			ft_sort_time(t_ls *file, int a, int b);
void			ft_sort_ascii(t_ls *file, int a, int b);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 stock_ls.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char			*ft_find_time(time_t time);
t_ls			*ft_find_files(char *str, char *option);
char			*ft_find_space(t_ls *file, char *space, int cur);
char			*ft_find_option(char ***argv, char *ret, int y, int x);
void			ft_fill_file(t_ls *file, t_dirent *ptr1, char *str, int *ptr2);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools_ls.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char			*ft_cut_name(char *dir);
int				ft_count_file(char *str);
void			ft_free_files(t_ls *file);
void			ft_safe_space(t_stat stat, char **space);

#endif
