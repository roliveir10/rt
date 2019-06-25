/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:58:22 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/25 09:18:16 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft.h"
#include "pars.h"

void		del_pile(t_pile **pile)
{
	if (!(*pile))
		return ;
	del_pile(&(*pile)->next);
	free(*pile);
	*pile = NULL;
}

static int	free_stat(t_stat *stat, int ret)
{
	if (!stat || !stat->pile)
		return (ret);
	del_pile(&stat->pile);
	ft_strdel(&stat->load);
	return (ret);
}

static int	token_up(int fd, t_token *token, char **str)
{
	int		ret;
	char	*line;
	int		pos;
	t_stat	stat;
	int		k;

	k = 0;
	ft_bzero(&stat, sizeof(t_stat));
	stat.status = START;
	pos = -1;
	line = NULL;
	while ((ret = get_line(fd, &line, str)) > 0)
	{
		if (pars_build_line(token, line, &stat, ++k))
			return (free_stat(&stat, 1));
		ft_strdel(&line);
	}
	if (ret == -1)
	{
		ft_putstr_fd("rt: read error\n", 2);
		return (free_stat(&stat, 1));
	}
	return (free_stat(&stat, 0));
}

static int	quit_free(t_token **token, int ret, char **rest)
{
	ft_strdel(rest);
	free_token(token);
	return (ret);
}

int			pars_file(char *str, t_env *env)
{
	int		fd;
	t_token	*token;
	char	*rest;
	int		err;

	token = NULL;
	rest = NULL;
	if ((fd = open(str, O_RDONLY)) == -1)
	{
		ft_putstr_fd("rt: can not open: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("' for reading\n", 2);
		return (quit_free(&token, 1, &rest));
	}
	if (!(token = lex_init_token(0, NULL)))
		return (quit_free(&token, 1, &rest));
	rest = NULL;
	if (token_up(fd, token, &rest))
		return (quit_free(&token, 1, &rest));
	if (rest)
		free(rest);
	err = 0;
	*env = token_to_env(&token->next, &err);
	return (quit_free(&token, err, &rest));
}
