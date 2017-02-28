/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:44:58 by frmarinh          #+#    #+#             */
/*   Updated: 2017/02/27 20:15:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	print_ascii(int size, void *ptr)
{
	int i;

	i = 0;
	while (i < size && i < 16)
	{
		if ((*(char*)ptr) > 33 && (*(char*)ptr) < 127)
			ft_putchar((*(char*)ptr));
		else
			ft_putchar('.');
		ptr++;
		i++;
	}
}

char	*get_and_print_first(char *tmp, void *ptr)
{
	tmp = ft_itoabase_uint((*(char*)ptr) >> 4, "0123456789ABCDEF");
	if (tmp != NULL)
	{
		ft_putchar(tmp[ft_strlen(tmp) - 1]);
		free(tmp);
	}
	else
		ft_putstr("0");
	return (tmp);
}

char	*get_and_print_second(char *tmp, void *ptr)
{
	tmp = ft_itoabase_uint((char)(*(char*)ptr) - \
		(((*(char*)ptr) >> 4) << 4), "0123456789ABCDEF");
	if (tmp != NULL)
	{
		ft_putchar(tmp[ft_strlen(tmp) - 1]);
		free(tmp);
	}
	else
		ft_putstr("0");
	return (tmp);
}

int		print_end_hexa(size_t count, void *ptr, int i)
{
	if (count > 0)
	{
		i = 0;
		while (i + count < 16)
		{
			ft_putstr("   ");
			i++;
		}
		ft_putstr(" | ");
		print_ascii(count, ptr - count);
		ft_putstr("\n");
	}
	return (i);
}

size_t	check_count(size_t count, void *ptr)
{
	if (count >= 16)
	{
		ft_putstr(" | ");
		print_ascii(16, ptr - 16);
		ft_putstr("\n");
		count = 0;
	}
	return (count);
}

static void		*ft_mmap(int fd, size_t size)
{
	return (mmap(0, size, PROT_READ, \
		MAP_SHARED, fd, 0));
}

static	int		read_byte(int toRead);

static void		print_usage(void)
{
	ft_putstr("Usage : ./ft_otool <object file> (print the text section)\n");
}

static void		read_data(t_file	*file)
{
	char	*buffer;
	char	*tmp;
	int		i;
	int		count;

	i = 0;
	count = 0;
	tmp = NULL;
	buffer = ft_mmap(file->fd, file->stat_data->st_size);
	while (i < file->stat_data->st_size)
	{
		get_and_print_first(tmp, buffer);
		get_and_print_second(tmp, buffer);
		ft_putstr(" ");
		count++;
		count = check_count(count, buffer);
		buffer++;
		i++;
		
	}
	i = print_end_hexa(count, buffer, i);
}

t_file			*get_file_structure(char *name)
{
	struct s_file	*file;

	if (!(file = (struct s_file*)malloc(sizeof(struct s_file))))
		return (NULL);
	file->file_name = name;
	if ((file->fd = open(file->file_name, O_RDONLY)) == -1)
		return (NULL);
	if (!(file->stat_data = (struct stat*)malloc(sizeof(struct stat))))
		return (NULL);
	return (file);
}

static void		get_content(char *name)
{
	struct s_file	*file;

	if (!(file  = get_file_structure(name)))
	{
		print_usage();
		return ;
	}
	if (stat(file->file_name, file->stat_data) < 0)
	{
		print_usage();
		return ;
	}
	read_data(file);
}

int				main(int argc, char **argv)
{
	if (argc == 2)
		get_content(argv[1]);
	else
		print_usage();
	return (0);
}
