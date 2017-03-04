/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:40:17 by frmarinh          #+#    #+#             */
/*   Updated: 2017/02/28 16:41:24 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/swap.h>
# include <mach/machine.h>
# include "../libft/includes/libft.h"

typedef struct			s_file
{
	char		*file_name;
	int			fd;
	struct stat	*stat_data;
	int			filetype;
}						t_file;

int						check_file(struct s_file *file);
void					print_usage(void);
void					print_not_object(void);
void					do_64(struct s_file *file);
void					do_32(struct s_file *file);
void					*get_ptr(t_file *file);
void					*get_text_section(int index, char *ptr);
uint32_t				swap_int32(uint32_t x);
void					*ft_mmap(int fd, size_t size);

void					*ft_mmap(int fd, size_t size);
int						is_x64(t_file *file);
struct mach_header_64	*get_x64(t_file *file);
struct mach_header		*get_x32(t_file *file);
void					check_swap_x64(struct mach_header_64 *header);
void					check_swap_x32(struct mach_header *header);
void					read_x64(struct mach_header_64 *header, t_file *file);
void					read_x32(struct mach_header *header, t_file *file);
void					get_and_print_first(char *tmp, char ptr);
void					get_and_print_second(char *tmp, char ptr);

void					print_text_section(int size, char *ptr, uint64_t addr, \
	struct s_file *file);

void					*get_text_section(int index, char *ptr);
void					*get_ptr(t_file *file);

#endif
