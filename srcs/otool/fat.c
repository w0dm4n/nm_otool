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

void	text_section_fat(t_file *file, struct section_64 *section, void *ptr)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	ft_putstr(file->file_name);
	ft_putstr(":\n");
	ft_putstr("Contents of (__TEXT,__text) section\n");
	print_text_section(section->size, get_text_section(section->offset, ptr), \
		section->addr, file);
}

void	print_fat_mach_header(t_file *file)
{
	void					*ptr;
	struct fat_arch			*arch;
	struct mach_header_64	*header;

	file->is_fat = TRUE;
	ptr = get_ptr(file);
	arch = ptr + sizeof(struct fat_header) + sizeof(struct fat_arch);
	header = ptr + swap_int32(arch->offset);
	ft_putstr("Mach header\n      ");
	ft_putstr("magic cputype cpusubtype  caps    filetype");
	ft_putstr(" ncmds sizeofcmds      flags\n");
	ft_putstr(" 0xfeedfacf ");
	ft_putnbr(header->cputype);
	ft_putstr("          3  0x80          ");
	ft_putnbr(header->filetype);
	ft_putstr("     ");
	ft_putnbr(header->ncmds);
	ft_putstr("       ");
	ft_putnbr(header->sizeofcmds);
	ft_putstr(" 0x");
	print_addr(header->flags, file);
}

void	read_fat_x64(t_file *file, struct mach_header_64 *header, void *ptr)
{
	int							i;
	struct load_command			*cmd;
	struct segment_command_64	*segment;
	struct symtab_command		*symtab;
	struct section_64			*section;

	file->is_x64 = TRUE;
	file->filetype = header->filetype;
	ptr = (void*)header + sizeof(struct mach_header_64);
	i = 0;
	segment = NULL;
	symtab = NULL;
	while (i < (int)header->ncmds)
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64*)ptr;
			section = ptr + sizeof(struct segment_command_64);
			if (ft_strcmp(section->segname, "__TEXT") == 0)
				text_section_fat(file, section, header);
		}
		ptr += cmd->cmdsize;
		i++;
	}
}
