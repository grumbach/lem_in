/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:32:54 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/21 03:59:44 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_viewer.h"

void	reset_controls(t_param *param)
{
	param->scaling = 1;
	param->padding.x = 0;
	param->padding.y = 0;
}

/*
** 53 is ESC
** 49 is space bar (used to reset params)
** 69 is + amd 78 is -
*/

int		hook(int k, t_ants *ants)
{
	hook_move(k, ants);
	if (k == 49 )
	{
		mlx_clear_window(ants->mlx->mlx, ants->mlx->win);
		reset_controls(&ants->param);
	}
	else if (k == 53)
		exit(1);
	else if (k == 69 || (k == 78 && ants->param.scaling > 0.05))
		ants->param.scaling *= (k == 69 ? 1.25 : 0.8);
	return (0);
}

int		hook_move(int k, t_ants *ants)
{
	if (k == K_A || k == K_LEFT)
		--ants->param.padding.x;
	else if (k == K_D || k == K_RIGHT)
		++ants->param.padding.x;
	else if (k == K_S || k == K_DOWN)
		++ants->param.padding.y;
	else if (k == K_W || k == K_UP)
		--ants->param.padding.y;
	return (0);
}