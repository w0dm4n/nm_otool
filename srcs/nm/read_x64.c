/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_x64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:53:00 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:15:55 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*get_ptr(t_file *file)
{
	return (ft_mmap(file->fd, file->stat_data->st_size));
}

void	print_by_type(int type, int is_x64)
{
	if (is_x64)
	{
		ft_putstr("0000000");
		if (type == 1)
			ft_putstr("0");
		else if (type == 2)
			ft_putstr("1");
		else
			ft_putstr("0");
	}
}

void	print_addr(int val, t_file *file)
{
	char	*tmp;
	size_t	i;

	i = 8;
	tmp = ft_itoabase_uint(val, "0123456789abcdef");
	if (tmp != NULL && ft_strlen(tmp) > 0)
	{
		print_by_type(file->filetype, file->is_x64);
		while (i > ft_strlen(tmp))
		{
			ft_putchar('0');
			i--;
		}
		ft_putstr(tmp);
		free(tmp);
	}
	else
	{
		print_by_type(file->filetype, file->is_x64);
		ft_putstr("00000000");
	}
}

void	read_symtab_x64(void *map, struct symtab_command *symtab, t_file *file)
{
	struct nlist_64			*n_list;
	int						i;

	n_list = (struct nlist_64*)(map + symtab->symoff);
	i = 0;
	while (i < (int)symtab->nsyms)
	{
		add_custom_x64(get_custom_nlist(),\
			n_list, (map + symtab->stroff + n_list->n_un.n_strx),\
			get_symbol_x64(*n_list, map, file));
		n_list++;
		i++;
	}
	range_customs_by_ascii();
	if (has_flags('u', file->flags))
		print_extern(file);
	else
		print_customs(file);
}

void	read_x64(struct mach_header_64 *header, t_file *file)
{
	int							i;
	struct load_command			*cmd;
	void						*ptr;
	struct segment_command_64	*segment;
	struct symtab_command		*symtab;

	ptr = get_ptr(file) + sizeof(struct mach_header_64);
	i = 0;
	segment = NULL;
	symtab = NULL;
	while (i < (int)header->ncmds)
	{
		segment = (struct segment_command_64*)ptr;
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SYMTAB)
			read_symtab_x64(get_ptr(file), (struct symtab_command*)ptr, file);
		ptr += cmd->cmdsize;
		i++;
	}
}
