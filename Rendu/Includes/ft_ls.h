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
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include "../Libft/Includes/libft.h"

# define TRUE 1
# define FALSE 0
# define COL "C"
# define LINE "glno"
# define LARGE "glno"
# define NOLARGE "1"
# define S_IXUGO (S_IXUSR | S_IXGRP | S_IXOTH)

typedef struct winsize	t_winsize;
typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct group	t_group;
typedef struct passwd	t_passwd;

typedef struct	s_ls
{
	int			nb;
	int			error;
	int			nb_blocks;
	char		type;
	char		exec;
	char		*name;
	char		*path;
	intmax_t	time;
	intmax_t	size;
}				t_ls;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 main_ls.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				main(int argc, char const *argv[]);
void			ft_ls_dir(t_ls *file, char *option);
void			ft_ls_argv(t_ls *file, char *option, int cur1, int argc);
void			ft_ls(char *dir, char *option, int release);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              find_option_ls.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			ft_modify_option_end(char **option, char c);
void			ft_modify_option_next(char **option, char c);
void			ft_modify_option(char **option, char **ptr, char c);
char			*ft_find_option(char ***argv, char *option, int y, int x);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               find_files_ls.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			ft_fill_file(t_ls *file, char *str, char *option, int *ptr);
void			ft_fill_file_argv(t_ls *file, char *str, char *option);
t_ls			*ft_find_files_argv(char **argv, char *option);
t_ls			*ft_find_files(char *str, char *option);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              print_files_ls.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			ft_print_files(t_ls *file, char *option);
int				ft_print_reg_argv(t_ls *file, char *opt, int cur);
void			ft_print_uid_gid(t_stat stat, char *option, char *space);
void			ft_print_line_start(t_ls file, char *space, char *option);
void			ft_print_line_end(t_ls file, t_stat stat, char *sp, char *opt);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              find_params_ls.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

intmax_t		ft_find_good_time(char *option, t_stat stat);
char			*ft_find_time(time_t time, char *option);
char			*ft_find_space_argv(t_ls *file, char *opt);
char			*ft_find_space(t_ls *file, char *space, char *option, int cur);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               find_law_ls.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char			*ft_check_rwx(int law);
char			ft_check_type_char(char type);
void			ft_modify_law(char **ret, char *path, char c);
char			*ft_find_law(char *path, mode_t law_b10, char type);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               sort_files_ls.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			ft_sort_rev(t_ls *file, int a);
void			ft_sort_ascii(t_ls *file, int a, int b);
void			ft_sort_time(t_ls *file, int a, int b);
void			ft_sort_size(t_ls *file, int a, int b);
void			ft_sort_files(t_ls *file, char *option);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              print_error_ls.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char			*ft_print_error_usage(char c);
void			ft_print_error(char *name);
int				ft_print_empty_argv(char **argv);
char			**ft_print_error_argv(char **argv, int ac, int cur1, int cur2);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_a_ls.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				ft_nb_col(void);
char			*ft_cut_name(char *dir);
void			ft_free_files(t_ls *file);
int				ft_count_argv(char **argv);
int				ft_check_time(time_t event);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_b_ls.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				ft_count_file(char *str);
int				ft_check_type(mode_t st_mode, int lst);
void			ft_safe_space(t_stat stat, char **space, char *option);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              column_bonus_ls.c                             ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				ft_space_name(t_ls *file);
int				ft_words_line(int nb_file, int max_name);
void			ft_print_one_line(t_ls *file, char *option, int space);
void			ft_print_column(t_ls *file, char *option, int cur);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              multi_bonus_ls.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char			*ft_check_color(t_ls file);
char			ft_check_char_file(t_ls file, char *option);
void			ft_print_bonus_d(t_ls *file, char *name, char *opt, char *sp);
void			ft_print_color_ls(t_ls file, char *opt, int space, int enter);

#endif
