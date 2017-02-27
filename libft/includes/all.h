/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 01:18:49 by frmarinh          #+#    #+#             */
/*   Updated: 2016/01/21 01:18:55 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H
# include "libft.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdio.h>
# define MAX_FILES_PER_FOLDER 81920
# define PERMISSIONS_BUFFER 12
# define ALL_DIR_AND_FILES 81920
# define ALL_RECURSIVE_POSSIBILITY 81920
# define DEFAULT_BUFFER 1024
# define DEFAULT_COLOR "\e[0m"
# define DEF "\e[0m"
# define COLOR_WHITE "\e[1;37m"
# define COLOR_BLUE "\e[0;34m"
# define COLOR_PURPLE "\e[0;35m"
# define COLOR_YELLOW "\e[1;33m"
# define COLOR_GREEN "\e[0;32m"
# define COLOR_CYAN "\e[4;36m"
# define COLOR_RED "\e[0;31m"
# define COLOR_LIGHT_RED "\e[1;31m"
# define COLOR_LIGHT_RED_2 "\e[0;31m"

void			print_error(char *name);
char			*add_flags(char *current_flags, char *flag_toadd);
void			get_current_dir(char *flags, char *folder);
void			print_error_usage(char invalid_flag);
void			print_dir(char *all_flags);
void			print_file_or_dir(char *flags, char **av, int *pos);
char			**get_specified_dir(char *dir, char *all_flags);
char			**range_byascii(char **files);
struct stat		*get_file_stat(char *name, struct stat *file_stat, char *f);
char			*get_permissions(struct stat *file_stat);
char			*get_user(struct stat *file_stat);
char			*get_group(struct stat *file_stat);
char			*get_last_modification_time(struct stat *file_stat);
size_t			get_total_blocks(char **files, struct stat *file_stat, char *f);
void			print_line(struct stat *file_stat, char *flag, char **f, int i);
int				*initialise_array(int *array);
int				check_l_or_1(char *flags);
char			**range_byfilenfolder(char **file_n_folder, int folder);
char			**set_dir_on_array(char **tmp, char **old, int index);
int				get_file_nbr(char **file_n_folder);
void			print_asked_dir_with_flags(char **files, char *flags, char *f);
void			just_print_files(char **files, char *flags, char *folder);
char			**reverse_array(char **files);
char			**read_without_hidden_files(char **files, DIR *current_dir);
char			**read_with_hidden_files(char **files, DIR *current_dir);
void			free_files(char **files);
char			**modify_if_flags(char *flags, char **files, char *folder);
void			print_file_with_flags(char **files, char *flags);
void			print_recursive(char **files, char *flags, char *folder, int i);
void			print_current_dir_with_flags(char **files, char *flags);
char			**range_by_t_flags(char **files, char *folder);
int				*reverse_int_array(int *array);
char			*add_p(char *permissions, char to_add);
char			*get_state(char *p, struct stat *file_stat);
void			print_with_nl(char *to_print, char *flags);
void			print_arg(int *i, char *f, char **fd);
void			print_arg_2(int *i, char *f, char **fd, char **all_files);
int				print_name_by_permissions(char *permissions, char *file_name);
char			*get_file_extension(char *file);
int				print_name_by_extension(char *file_name);
#endif
