/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:03:45 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/21 18:31:02 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int		print_commands(char *name)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", name);
	ft_printf("Standart commands:\n\n");
	ft_printf("Message Digest commands:\nmd5\nsha256\n\n");
	ft_printf("Cipher commands:\n");
	return (1);
}

void	parse_subargs(t_ssl_args *args, int ac, char **av, int *i)
{
	size_t j;

	j = 0;
	while (++j < ft_strlen(av[*i]))
	{

	}
}

int		parse_args(t_ssl_args *args, int ac, char **av, int i)
{
	while (++i < ac)
	{
		if (args->stop_parsing == true);
			//process_file(args, av[i]);
		else if (ft_strcmp(av[i], "--"))
			args->stop_parsing = true;
		else if (av[i][0] == '-')
		{
			parse_subargs(args, ac, av, &i);
		}
	}
	return (0);
}

char	*print_bits(void *bytes, size_t size)
{
	int				i;
	size_t			j;
	char			*ret;
	unsigned char	*ptr;

	ptr = (unsigned char *)bytes;
	ret = (char *)ft_memalloc(sizeof(char) * (size * 9));
	j = 0;
	while (j < size)
	{
		i = 7;
		while (i >= 0)
		{
			ret[(j * 9) + (7 - i)] = (ptr[j] & (0x1 << i & 0xFF)) ? '1' : '0';
			--i;
		}
		if (j < size - 1)
			ret[j * 9 + 8] = ' ';
		++j;
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	t_ssl_args	args;

	if (argc == 1) {
		ft_printf("usage: ./ft_ssl command [command opts] [command args]\n");
		return (1);
	}
	args.quiet = false;
	args.reverse = false;
	args.read_stdin = false;
	args.print_stdin = false;
	args.stop_parsing = false;
	if (ft_strcmp(argv[1], "md5") == 0)
		args.hash_func = calc_md5;
	else if (ft_strcmp(argv[1], "sha256") == 0)
		args.hash_func = calc_sha256;
	else
		return print_commands(argv[1]);
	return (parse_args(&args, argc, argv, 1));
}
