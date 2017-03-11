/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:44:58 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:13:48 by frmarinh         ###   ########.fr       */
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
	file->is_fat = FALSE;
	file->flags = flags;
	return (file);
}

static void		get_content(char *name, char *flags)
{
	struct s_file			*file;

	if (has_flags('h', flags))
		print_help();
	if (!(file = get_file_struct(name, flags)))
	{
		print_usage();
		return ;
	}
	if (!check_file(file))
		return ;
	if (is_universal(file))
		do_fat(file);
	else
		(is_x64(file)) ? do_64(file) : do_32(file);
}

int				main(int argc, char **argv)
{
	int		i;
	char	*flags;

	i = 1;
	flags = get_flags(argv);
	if (argc >= 2)
	{
		if (count_file(argv) > 1)
			ft_putstr("\n");
		while (argv[i])
		{
			if (argv[i][0] != '-' || argv[i][1] == 'h')
			{
				if (count_file(argv) >= 2)
				{
					ft_putstr(argv[i]);
					ft_putstr(":\n");
				}
				get_content(argv[i], flags);
				if ((i + 1) < argc && count_file(argv) > 1)
					ft_putstr("\n");
			}
			i++;
		}
	}
	else
		print_usage();
	return (0);
}
