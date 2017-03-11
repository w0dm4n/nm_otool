/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:44:58 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:10:28 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void			get_and_print_first(char *tmp, char ptr)
{
	tmp = ft_itoabase_uint((ptr) >> 4, "0123456789abcdef");
	if (tmp != NULL)
	{
		ft_putchar(tmp[ft_strlen(tmp) - 1]);
		free(tmp);
	}
	else
		ft_putstr("0");
}

void			get_and_print_second(char *tmp, char ptr)
{
	tmp = ft_itoabase_uint(ptr - \
		((ptr >> 4) << 4), "0123456789abcdef");
	if (tmp != NULL)
	{
		ft_putchar(tmp[ft_strlen(tmp) - 1]);
		free(tmp);
	}
	else
		ft_putstr("0");
	ft_putstr(" ");
}

t_file			*get_file_struct(char *name, char *flags)
{
	struct s_file	*file;

	if (!(file = (struct s_file*)malloc(sizeof(struct s_file))))
		return (NULL);
	file->file_name = name;
	if ((file->fd = open(file->file_name, O_RDONLY)) == -1)
		return (NULL);
	if (!(file->stat_data = (struct stat*)malloc(sizeof(struct stat))))
		return (NULL);
	file->is_x64 = FALSE;
	file->flags = flags;
	return (file);
}

static void		get_content(char *name, char *flags)
{
	struct s_file			*file;

	if (!(file = get_file_struct(name, flags)))
	{
		print_usage();
		return ;
	}
	if (!check_file(file))
		return ;
	if (has_flags('m', flags))
	{
		print_mach_header(file);
		return ;
	}
	if (is_universal(file))
		do_fat(file);
	else
		(is_x64(file)) ? do_64(file) : do_32(file);
}

int				main(int argc, char **argv)
{
	int i;

	i = 1;
	if (has_flags('h', get_flags(argv)))
	{
		print_help();
		return (0);
	}
	if (argc >= 2)
	{
		while (argv[i])
		{
			if (argv[i][0] != '-')
			{
				get_content(argv[i], get_flags(argv));
				ft_putstr("\n");
			}
			i++;
		}
	}
	else
		print_usage();
	return (0);
}
