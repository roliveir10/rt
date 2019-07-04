# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rt.mk                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roliveir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/07 10:06:25 by roliveir          #+#    #+#              #
#    Updated: 2019/07/02 15:46:43 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RT_PATH = ./srcs/rt/

RT = rt_main.c					\
	 rt_vector_calc.c			\
	 rt_4th_deg.c				\
	 rt_print.c					\
	 rt_basics_shapes.c			\
	 rt_medium_shapes.c			\
	 rt_basics_normal.c			\
	 rt_medium_normal.c			\
	 rt_keyhandler.c			\
	 rt_inter_manager.c			\
	 rt_light_manager.c			\
	 rt_light_type.c			\
	 rt_light_utils.c			\
	 rt_color_manager.c			\
	 rt_rotation.c				\
	 rt_material.c				\
	 rt_material_matrix.c		\
	 rt_camera.c				\
	 rt_anti_aliasing.c			\
	 rt_keyfunction.c			\
	 rt_reflection.c

RT_SRCS = $(addprefix $(RT_PATH),$(RT))
SRCS += $(RT_SRCS)
