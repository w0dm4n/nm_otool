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
	int			is_x64;
	int			is_fat;
	char		*flags;
}						t_file;

typedef struct			s_custom_nlist
{
	char					*content;
	uint32_t				type;
	uint64_t				addr;
	struct s_custom_nlist	*next;
	struct s_custom_nlist	*prev;
	uint8_t					sect;
	char					symbol;
}						t_custom_nlist;

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
void					print_addr(int val, t_file *file);

t_custom_nlist			*get_custom_nlist(void);

void					add_custom_x64(t_custom_nlist *customs, \
	struct nlist_64 *nlist, char *c, char symbol);
void					add_custom_x32(t_custom_nlist *customs, \
	struct nlist *nlist, char *c, char symbol);

void					range_customs_by_ascii(void);
void					print_customs(t_file *file);
void					print_space(int space);
int						authorized_type(int type);
void					print_glob_by_type(int type);
int						should_swap_bytes(uint32_t magic);
int						is_fat(uint32_t magic);
int						is_magic_64(uint32_t magic);
int						is_magic_32(uint32_t magic);
void					read_universal(void *map, \
	struct symtab_command *symtab, t_file *file, void *header);
int						is_universal(t_file *file);
void					do_fat(struct s_file *file);
void					read_fat_x64(t_file *file, \
	struct mach_header_64 *header, void *ptr);
char					get_symbol_x64(struct nlist_64 symbol, \
	void *buf, t_file *file);
char					get_symbol_x32(struct nlist symbol, \
	void *buf, t_file *file);
void					print_symbol(t_custom_nlist *current, t_file *file);
void					text_section_x64(t_file *file, \
	struct section_64 *section);
char					*get_flags(char **argv);
int						has_flags(char f, char *flags);
void					print_customs(t_file *file);
void					print_extern(t_file *file);
int						count_file(char **argv);
void					print_help(void);
void					print_mach_header(t_file *file);

struct s_custom_nlist	*g_customs;

# define FIND_OBJ_X64 st_find_char_obj(segment, symbol.n_sect - n - 1)
# define FIND_ALL_X64 st_find_char(segment, symbol.n_sect - n - 1)

# define FIND_OBJ_X32 st_find_char_x32_obj(segment, symbol.n_sect - n - 1)
# define FIND_ALL_X32 st_find_char_x32(segment, symbol.n_sect - n - 1)

# define NM_FLAGS "urhj"
# define OTOOL_FLAGS "ahm"

#endif
