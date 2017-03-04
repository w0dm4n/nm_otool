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

void	print_addr(int val, int filetype)
{
	char	*tmp;
	size_t	i;

	filetype = 0;
	i = 8;
	tmp = ft_itoabase_uint(val, "0123456789abcdef");
	if (tmp != NULL && ft_strlen(tmp) > 0)
	{
		ft_putstr("00000001");
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
		ft_putstr("00000001");
		ft_putstr("00000000");
	}
}

void	print_customs(void)
{
	while (g_customs)
	{
		if (g_customs->content)
		{
			if (g_customs->addr)
				print_addr(g_customs->addr, -1);
			else
				ft_putstr("\t\t");
			if (g_customs->type == 1)
				ft_putstr(" U ");
			else if (g_customs->type == 14)
				ft_putstr(" t ");
			else if (g_customs->type == 15)
				ft_putstr(" T ");
			ft_putstr(g_customs->content);
			ft_putstr("\n");
		}
		g_customs = g_customs->next;
	}
}

void	read_symtab_x64(void *map, struct symtab_command *symtab)
{
	struct nlist_64			*n_list;
	int						i;

	n_list = (struct nlist_64*)(map + symtab->symoff);
	i = 0;
	while (i < (int)symtab->nsyms)
	{
		add_custom_x64(get_custom_nlist(), n_list, (map + symtab->stroff + n_list->n_un.n_strx));
		n_list++;
		i++;
	}
	range_customs_by_ascii();
	print_customs();
}

void	read_x64(struct mach_header_64 *header, t_file *file)
{
	int							i;
	struct load_command			*cmd;
	void						*ptr;
	struct segment_command_64	*segment;
	struct section_64			*section;
	struct symtab_command		*symtab;

	ptr = get_ptr(file) + sizeof(struct mach_header_64);
	i = 0;
	segment = NULL;
	section = NULL;
	symtab = NULL;
	while (i < (int)header->ncmds)
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SYMTAB)
			read_symtab_x64(get_ptr(file), (struct symtab_command*)ptr);
		ptr += cmd->cmdsize;
		i++;
	}
}
