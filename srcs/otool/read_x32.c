/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_x32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:01:39 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:13:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	text_section_x32(t_file *file, struct section *section)
{
	void	*ptr;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!(ptr = ft_mmap(file->fd, file->stat_data->st_size)))
		return ;
	ft_putstr(file->file_name);
	ft_putstr("\n");
	ft_putstr("Contents of (__TEXT,__text) section\n");
	print_text_section(section->size, get_text_section(section->offset, ptr), \
		section->addr, file);
	ft_putstr("\n");
}

void	read_x32(struct mach_header *header, t_file *file)
{
	int							i;
	struct load_command			*cmd;
	void						*ptr;
	struct segment_command		*segment;
	struct section				*section;

	ptr = get_ptr(file) + sizeof(struct mach_header);
	i = 0;
	segment = NULL;
	section = NULL;
	while (i < (int)header->ncmds)
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command*)ptr;
			section = ptr + sizeof(struct segment_command);
			if (ft_strcmp(section->segname, "__TEXT") == 0)
				text_section_x32(file, section);
		}
		ptr += cmd->cmdsize;
		i++;
	}
}
