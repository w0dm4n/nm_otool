/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_x64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:53:00 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:12:33 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	print_by_type(int type, int is_x64)
{
	if (is_x64)
	{
		ft_putstr("0000000");
		if (type == 1)
			ft_putstr("0");
		else if (type == 2)
			ft_putstr("1");
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

void	print_text_section(int size, char *ptr, uint64_t addr, t_file *file)
{
	int		i;
	int		count;
	char	*tmp;
	char	*str;

	tmp = NULL;
	i = -1;
	count = 0;
	str = (char*)ptr;
	while (++i < size)
	{
		if (count == 0)
		{
			print_addr((int)addr + i, file);
			ft_putstr("\t");
		}
		count++;
		get_and_print_first(tmp, str[i]);
		get_and_print_second(tmp, str[i]);
		if (count == 16)
		{
			ft_putstr("\n");
			count = 0;
		}
	}
}

void	text_section_x64(t_file *file, struct section_64 *section)
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
}

void	read_x64(struct mach_header_64 *header, t_file *file)
{
	int							i;
	struct load_command			*cmd;
	void						*ptr;
	struct segment_command_64	*segment;
	struct section_64			*section;

	ptr = get_ptr(file) + sizeof(struct mach_header_64);
	i = 0;
	segment = NULL;
	section = NULL;
	while (i < (int)header->ncmds)
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64*)ptr;
			section = ptr + sizeof(struct segment_command_64);
			if (ft_strcmp(section->segname, "__TEXT") == 0)
				text_section_x64(file, section);
		}
		ptr += cmd->cmdsize;
		i++;
	}
}
