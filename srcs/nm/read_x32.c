/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_x32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:01:39 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:16:33 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	read_symtab_x32(void *map, struct symtab_command *symtab, t_file *file)
{
	struct nlist			*n_list;
	int						i;

	n_list = (struct nlist*)(map + symtab->symoff);
	i = 0;
	while (i < (int)symtab->nsyms)
	{
		add_custom_x32(get_custom_nlist(), \
			n_list, (map + symtab->stroff + n_list->n_un.n_strx));
		n_list++;
		i++;
	}
	range_customs_by_ascii();
	print_customs(file);
}

void	read_x32(struct mach_header *header, t_file *file)
{
	int							i;
	struct load_command			*cmd;
	void						*ptr;
	struct segment_command		*segment;
	struct symtab_command		*symtab;

	ptr = get_ptr(file) + sizeof(struct mach_header);
	i = 0;
	segment = NULL;
	symtab = NULL;
	while (i < (int)header->ncmds)
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SYMTAB)
			read_symtab_x32(get_ptr(file), (struct symtab_command*)ptr, file);
		ptr += cmd->cmdsize;
		i++;
	}
}
