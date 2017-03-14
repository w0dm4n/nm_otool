/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:57:33 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/10 17:57:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		is_universal(t_file *file)
{
	struct mach_header	*mach_header;

	if (!(mach_header = (struct mach_header*)ft_mmap(file->fd, \
		sizeof(struct mach_header))))
		return (-1);
	return (is_fat(mach_header->magic));
}

void	read_universal(void *map, struct symtab_command *symtab, \
	t_file *file, void *header)
{
	struct nlist_64			*n_list;
	int						i;

	n_list = (struct nlist_64*)\
	(map + (symtab->symoff - (sizeof(struct nlist_64) * 2)));
	i = 0;
	while (i < (int)symtab->nsyms)
	{
		add_custom_x64(get_custom_nlist(),\
			n_list, (header + symtab->stroff + n_list->n_un.n_strx), 0);
		n_list++;
		i++;
	}
	range_customs_by_ascii();
	print_customs(file);
}

void	read_universal_x32(struct symtab_command *symtab, \
	t_file *file, void *header)
{
	struct nlist			*n_list;
	int						i;

	n_list = (struct nlist*)\
	(header + ((swap_int32(symtab->symoff) - (sizeof(struct nlist) * 2))));
	i = 0;
	while (i < (int)swap_int32(symtab->nsyms))
	{
		add_custom_x32(get_custom_nlist(),\
			n_list, (header + swap_int32(symtab->stroff) \
				+ swap_int32(n_list->n_un.n_strx)), -1);
		n_list++;
		i++;
	}
	range_customs_by_ascii();
	print_customs(file);
}

void	read_fat_x64(t_file *file, struct mach_header_64 *header, void *ptr)
{
	int							i;
	struct load_command			*cmd;
	struct segment_command_64	*segment;
	struct symtab_command		*symtab;

	file->is_x64 = TRUE;
	file->filetype = header->filetype;
	ptr = (void*)header + sizeof(struct mach_header_64);
	i = 0;
	segment = NULL;
	symtab = NULL;
	while (i < (int)header->ncmds)
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SYMTAB)
			read_universal((void*)header + sizeof(struct mach_header_64), \
				(struct symtab_command*)cmd, file, (void*)header);
		ptr += cmd->cmdsize;
		i++;
	}
}

void	read_fat_x32(t_file *file, struct mach_header *header, void *ptr)
{
	int							i;
	struct load_command			*cmd;
	struct segment_command_64	*segment;
	struct symtab_command		*symtab;

	file->is_x64 = FALSE;
	file->filetype = swap_int32(header->filetype);
	ptr = (void*)header + sizeof(struct mach_header);
	i = 0;
	segment = NULL;
	symtab = NULL;
	while (i < (int)swap_int32(header->ncmds))
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == swap_int32(LC_SYMTAB))
			read_universal_x32((struct symtab_command*)cmd, file, \
				(void*)header);
		ptr += swap_int32(cmd->cmdsize);
		i++;
	}
}
