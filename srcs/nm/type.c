/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:03:43 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/10 19:03:44 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void		print_glob(int type)
{
	if (type == 6)
		ft_putstr(" S ");
	else
		ft_putstr(" D ");
}

static char						st_set_upper(char c, struct nlist_64 symbol)
{
	if ((symbol.n_type & N_EXT) && c != ' ')
		return (ft_toupper(c));
	return (c);
}

static char						st_find_char(struct segment_command_64 *segment,
		unsigned int index)
{
	struct section_64			*sect;

	sect = (struct section_64 *)((char *)segment
			+ sizeof(struct segment_command_64));
	sect += index;
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__bss"))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__data"))
		return ('d');
	if (!ft_strcmp(segment->segname, "__TEXT")
			&& !ft_strcmp(sect->sectname, "__text"))
		return ('t');
	return ('s');
}

static char						st_find_char_obj(struct segment_command_64 *segment,
		unsigned int index)
{
	struct section_64			*sect;

	sect = (struct section_64 *)((char *)segment
			+ sizeof(struct segment_command_64));
	sect += index;
	if (!ft_strcmp(segment->segname, "__DATA")
			|| !ft_strcmp(sect->sectname, "__bss"))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			|| !ft_strcmp(sect->sectname, "__data"))
		return ('d');
	if (!ft_strcmp(segment->segname, "__TEXT")
			|| !ft_strcmp(sect->sectname, "__text"))
		return ('t');
	return ('s');
}

char						st_find(struct nlist_64 symbol, void *buf, int obj)
{
	struct load_command			*cmd;
	struct mach_header_64		*header;
	struct segment_command_64	*segment;
	unsigned int				i;
	unsigned int				n;

	header = (struct mach_header_64 *)buf;
	i = 0;
	n = 0;
	cmd = (struct load_command *)(((char *)buf)
			+ sizeof(struct mach_header_64));
	while (i < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if ((n + segment->nsects) >= symbol.n_sect)
				return ((obj == 1) ? st_find_char_obj(segment, symbol.n_sect - n - 1) : st_find_char(segment, symbol.n_sect - n - 1));
			n += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}

char							get_symbol_x64(struct nlist_64 symbol, void *buf, t_file *file)
{
	if ((symbol.n_type & N_TYPE) == N_SECT)
		return (st_set_upper(st_find(symbol, buf, \
			(file->filetype != 1) ? 0 : 1), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF)
	{
		if (symbol.n_value == 0)
			return (st_set_upper('u', symbol));
		else
			return (st_set_upper('c', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper('i', symbol));
	return ('X');
}

/* FOR 32 BITS 
*
*
*
*/

static char						st_set_upper_x32(char c, struct nlist symbol)
{
	if ((symbol.n_type & N_EXT) && c != ' ')
		return (ft_toupper(c));
	return (c);
}

static char						st_find_char_x32(struct segment_command *segment,
		unsigned int index)
{
	struct section			*sect;

	sect = (struct section *)((char *)segment
			+ sizeof(struct segment_command));
	sect += index;
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__bss"))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__data"))
		return ('d');
	if (!ft_strcmp(segment->segname, "__TEXT")
			&& !ft_strcmp(sect->sectname, "__text"))
		return ('t');
	return ('s');
}

static char						st_find_char_x32_obj(struct segment_command *segment,
		unsigned int index)
{
	struct section			*sect;

	sect = (struct section *)((char *)segment
			+ sizeof(struct segment_command));
	sect += index;
	if (!ft_strcmp(segment->segname, "__DATA")
			|| !ft_strcmp(sect->sectname, "__bss"))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			|| !ft_strcmp(sect->sectname, "__data"))
		return ('d');
	if (!ft_strcmp(segment->segname, "__TEXT")
			|| !ft_strcmp(sect->sectname, "__text"))
		return ('t');
	return ('s');
}

char						st_find_x32(struct nlist symbol, void *buf, int obj)
{
	struct load_command			*cmd;
	struct mach_header		*header;
	struct segment_command	*segment;
	unsigned int				i;
	unsigned int				n;

	header = (struct mach_header *)buf;
	i = 0;
	n = 0;
	cmd = (struct load_command *)(((char *)buf)
			+ sizeof(struct mach_header));
	while (i < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command *)cmd;
			if ((n + segment->nsects) >= symbol.n_sect)
				return ((obj) ? st_find_char_x32_obj(segment, symbol.n_sect - n - 1) : st_find_char_x32(segment, symbol.n_sect - n - 1));
			n += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}

char							get_symbol_x32(struct nlist symbol, void *buf, t_file *file)
{
	if ((symbol.n_type & N_TYPE) == N_SECT)
		return (st_set_upper_x32(st_find_x32(symbol, buf, \
			(file->filetype != 1) ? 0 : 1), symbol));
	if ((symbol.n_type & N_TYPE) == N_UNDF)
	{
		if (symbol.n_value == 0)
			return (st_set_upper_x32('u', symbol));
		else
			return (st_set_upper_x32('c', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper_x32('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper_x32('i', symbol));
	return ('X');
}



void	print_symbol(t_custom_nlist *current, t_file *file)
{
	if ((int)current->sect == 8 && current->type == 15)
		print_glob(file->filetype);
	else if (((int)current->sect == 12 && current->type == 14) ||
		((int)current->sect == 14 && current->type == 30))
		ft_putstr(" d ");
	else if (((int)current->sect == 13 && current->type == 14) ||
		(((int)current->sect == 15 && current->type == 14)))
		ft_putstr(" b ");
	else if (((int)current->sect == 5 && current->type == 14) ||
		((int)current->sect == 16 && current->type == 30) ||
		((int)current->sect == 4 && current->type == 14) || 
		((int)current->sect == 6 && current->type == 30) ||
		((int)current->sect == 12 && current->type == 30))
		ft_putstr(" s ");
	else if (current->type == 1)
		ft_putstr(" U ");
	else if (current->type == 14 || \
		((int)current->sect == 1 && current->type == 30))
		ft_putstr(" t ");
	else if ((int)current->sect == 1 && current->type == 15)
		ft_putstr(" T ");
	else if ((int)current->sect == 12 && current->type == 15)
		ft_putstr(" D ");
}
