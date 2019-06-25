/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_keyhandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 11:03:35 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 02:53:05 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"

int					rt_keypress(int keycode, void *param)
{
	static int		tkey[NBR_KEY] = {KESCAP, KLEFT, KRIGHT, KUP, KDOWN,
		KRXUP, KRXDOWN, KRYRIGHT, KRYLEFT, KRZRIGHT, KRZLEFT, KAA, KBLINN};
	static void		(*lst_function[NBR_KEY])(t_env *, int) = {
			rt_escap, rt_movecam_pos, rt_movecam_pos, rt_movecam_pos,
			rt_movecam_pos, rt_movecam_rot, rt_movecam_rot, rt_movecam_rot,
			rt_movecam_rot, rt_movecam_rot, rt_movecam_rot, rt_aa_blinn,
			rt_aa_blinn};
	int				i;

	i = -1;
	while (++i < NBR_KEY)
		if (tkey[i] == keycode)
			lst_function[i]((t_env*)param, keycode);
	return (0);
}

int					rt_mousepress(int keycode, int x, int y, void *param)
{
	static int		mkey[NBR_MKEY] = {MDOWN, MUP};
	static void		(*lst_function[NBR_MKEY])(t_env*, int) = {
		rt_mmovecam_pos, rt_mmovecam_pos};
	int				i;

	i = -1;
	(void)x;
	(void)y;
	while (++i < NBR_MKEY)
		if (mkey[i] == keycode)
			lst_function[i]((t_env*)param, keycode);
	return (0);
}

int					rt_keyrelease(int keycode, void *param)
{
	static int		tkey[NBR_KEY_REPEAT] = {KLEFT, KRIGHT, KUP, KDOWN,
		KRXUP, KRXDOWN, KRYRIGHT, KRYLEFT, KRZRIGHT, KRZLEFT, KBLINN};
	int				i;

	i = -1;
	while (++i < NBR_KEY_REPEAT)
		if (tkey[i] == keycode)
		{
			((t_env*)param)->key_repeat = 0;
			return (0);
		}
	return (0);
}
