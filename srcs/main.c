/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:03:45 by eduwer            #+#    #+#             */
/*   Updated: 2020/03/03 20:04:11 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static int	print_commands(char *name)
{
	ft_fdprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", name);
	ft_fdprintf(2, "Standart commands:\n\n");
	ft_fdprintf(2, "Message Digest commands:\nmd5\nsha256\nsha512\n\n");
	ft_fdprintf(2, "Cipher commands:\n");
	return (1);
}

static int	print_usage(void)
{
	ft_fdprintf(2, "Usage: ./ft_ssl command [-pqr] [-s string] \
[files ...]\n");
	return (1);
}

static int	parse_subargs(t_ssl_args *args, int ac, char **av)
{
	args->av_j = 0;
	while (++args->av_j < ft_strlen(av[args->av_i]))
	{
		if (av[args->av_i][args->av_j] == 'q')
			args->quiet = true;
		else if (av[args->av_i][args->av_j] == 'r')
			args->reverse = true;
		else if (av[args->av_i][args->av_j] == 'p')
			process_stdin(args, false);
		else if (av[args->av_i][args->av_j] == 's')
			process_string(args, ac, av);
		else
		{
			ft_fdprintf(2, "Illegal option -- %c\n", \
				av[args->av_i][args->av_j]);
			return (print_usage());
		}
	}
	return (0);
}

static int	parse_args(t_ssl_args *args, int ac, char **av)
{
	while (++args->av_i < (size_t)ac)
	{
		if (args->stop_parsing == true)
			process_file(args, av[args->av_i]);
		else if (ft_strcmp(av[args->av_i], "--") == 0)
			args->stop_parsing = true;
		else if (av[args->av_i][0] == '-')
		{
			if (parse_subargs(args, ac, av) != 0)
				return (1);
		}
		else
		{
			args->stop_parsing = true;
			process_file(args, av[args->av_i]);
		}
	}
	if (args->print_stdin == true)
		process_stdin(args, true);
	return (args->return_status);
}

int			main(int argc, char **argv)
{
	t_ssl_args	args;

	if (argc == 1)
		return (print_usage());
	args.av_i = 1;
	args.av_j = 0;
	args.quiet = false;
	args.reverse = false;
	args.return_status = 0;
	args.read_stdin = false;
	args.print_stdin = true;
	args.stop_parsing = false;
	if (ft_strcmp(argv[1], "md5") == 0)
		args.hash_func = calc_md5;
	else if (ft_strcmp(argv[1], "sha256") == 0)
		args.hash_func = calc_sha256;
	else if (ft_strcmp(argv[1], "sha512") == 0)
		args.hash_func = calc_sha512;
	else
		return (print_commands(argv[1]));
	args.func_name = argv[1];
	ft_strtoupper(args.func_name);
	return (parse_args(&args, argc, argv));
}
