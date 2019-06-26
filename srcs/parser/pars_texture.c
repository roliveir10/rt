/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 06:43:44 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 07:14:35 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"
#include "libft.h"

int			pars_texture(t_token **token)
{
	char		*name;
	static char	*lst[NBR_TEXT] = {"\"nothing\""};
	int			k;

	if (!(name = ft_strdup((*token)->word)))
		return (0);
	k = -1;
	while (++k < NBR_TEXT)
		if (!ft_strcmp(name, lst[k]))
		{
			free_move(token);
			ft_strdel(&name);
			return (k);
		}
	free_move(token);
	print_na_recon(name, "texture");
	ft_strdel(&name);
	return (0);
}
