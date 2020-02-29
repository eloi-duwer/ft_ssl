/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:16:21 by eduwer            #+#    #+#             */
/*   Updated: 2020/02/29 17:18:20 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void		process_stdin(t_ssl_args *args, bool print_stdin)
{
	char	*file;
	char	*ret;
	size_t	size;
	char	*format;

	args->print_stdin = false;
	if ((read_whole_file(0, (void **)&file, &size)) != 0)
	{
		write(2, "Error while reading from stdin\n", 30);
		return ;
	}
	ret = args->hash_func(file, size);
	if (print_stdin == false)
	{
		ft_asprintf(&format, "%%.%zus", size);
		ft_printf(format, file);
		free(format);
	}
	ft_printf("%s\n", ret);
	free(file);
	free(ret);
}

void		process_file(t_ssl_args *args, char *file_name)
{
	int		fd;
	char	*file;
	char	*ret;
	size_t	size;

	args->print_stdin = false;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error while opening the file\n", 29);
		args->return_status = 1;
		return ;
	}
	if ((read_whole_file(fd, (void **)&file, &size)) != 0)
	{
		write(2, "Error while reading file\n", 25);
		close(fd);
		return ;
	}
	close(fd);
	ret = args->hash_func(file, size);
	if (args->quiet == true)
		ft_printf("%s\n", ret);
	else if (args->reverse == true)
		ft_printf("%s %s\n", ret, file_name);
	else
		ft_printf("%s (%s) = %s\n", args->func_name, file_name, ret);
	free(ret);
	free(file);
}

static void	real_process_string(t_ssl_args *args, char *str)
{
	char *ret;

	ret = args->hash_func(str, ft_strlen(str));
	if (args->quiet == true)
		ft_printf("%s\n", ret);
	else if (args->reverse == true)
		ft_printf("%s \"%s\"\n", ret, str);
	else
		ft_printf("%s (\"%s\") = %s\n", args->func_name, str, ret);
	free(ret);
}

void		process_string(t_ssl_args *args, int ac, char **av)
{
	char	*err;
	size_t	len;

	args->print_stdin = false;
	if (av[args->av_i][args->av_j + 1] != '\0')
		real_process_string(args, &av[args->av_i][args->av_j + 1]);
	else if (args->av_i + 1 < (size_t)ac)
	{
		real_process_string(args, av[args->av_i + 1]);
		++args->av_i;
	}
	else
	{
		len = ft_asprintf(&err, "ft_ssl: option -s requires an argument\n");
		write(2, err, len);
		free(err);
		args->return_status = 1;
	}
	args->av_j = ft_strlen(av[args->av_i]);
}
