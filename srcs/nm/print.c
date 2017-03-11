/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 08:50:11 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/11 08:50:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_custom_nlist		*get_last_customs(void)
{
	while (g_customs->next)
		g_customs = g_customs->next;
	return (g_customs);
}

void				print_data(t_custom_nlist *g_customs, t_file *file)
{
	if (!has_flags('j', file->flags))
	{
		if (g_customs->addr || \
			(g_customs->type == 14 || g_customs->type == 15))
			print_addr(g_customs->addr, file);
		else
			(file->is_x64) ? print_space(16) : print_space(8);
		if (g_customs->symbol > 0)
		{
			ft_putstr(" ");
			ft_putchar(g_customs->symbol);
			ft_putstr(" ");
		}
		else
			print_symbol(g_customs, file);
	}
	ft_putstr(g_customs->content);
	ft_putstr("\n");
}

void				print_customs(t_file *file)
{
	if (!has_flags('r', file->flags))
	{
		while (g_customs)
		{
			if (g_customs->content)
				print_data(g_customs, file);
			g_customs = g_customs->next;
		}
	}
	else
	{
		g_customs = get_last_customs();
		while (g_customs)
		{
			print_data(g_customs, file);
			g_customs = g_customs->prev;
		}
	}
}

void				print_help(void)
{
	ft_putstr("USAGE: ./ft_nm [options] <input files> ");
	ft_putstr("Dump only symbols from this segment ");
	ft_putstr("and section name, Mach-O only\n\n");
	ft_putstr("OPTIONS:\n\n");
	ft_putstr("  -r        - Sort in reverse order\n");
	ft_putstr("  -u        - Show only undefined symbols\n");
	ft_putstr("  -h        - Show help on ft_nm\n");
	ft_putstr("  -j        - Show all without n_value and symbols\n");
	exit(0);
}

void				print_extern(t_file *file)
{
	if (!has_flags('r', file->flags))
	{
		while (g_customs)
		{
			if (g_customs->content && g_customs->symbol == 'U')
			{
				ft_putstr(g_customs->content);
				ft_putstr("\n");
			}
			g_customs = g_customs->next;
		}
	}
	else
	{
		g_customs = get_last_customs();
		while (g_customs)
		{
			if (g_customs->content && g_customs->symbol == 'U')
			{
				ft_putstr(g_customs->content);
				ft_putstr("\n");
			}
			g_customs = g_customs->prev;
		}
	}
}
