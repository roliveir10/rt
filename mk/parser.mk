# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parser.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roliveir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/07 10:04:52 by roliveir          #+#    #+#              #
#    Updated: 2019/06/26 06:57:41 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSER_PATH = ./srcs/parser/

PARSER =	parser_main.c		\
			pars_file.c			\
			pars_camera.c		\
			pars_build_line.c	\
			print_errors.c		\
			lex_pile.c			\
			lex_get.c			\
			pars_token.c		\
			pars_material.c		\
			pars_type.c			\
			pars_lst.c			\
			pars_lst_form.c		\
			pars_field_camera.c	\
			ft_atod.c			\
			pars_field_light.c	\
			pars_field_form.c	\
			pars_vector.c		\
			pars_texture.c		\
			free_token.c		\
			free_move.c			\
			pars_check_form.c	\
			pars_check_light.c	\
			set_form.c			\
			set_light.c			\
			set_form_double.c	\
			set_form_text.c		\
			pars_init.c			\
			lex_add_char.c

PARSER_SRCS = $(addprefix $(PARSER_PATH),$(PARSER))
SRCS += $(PARSER_SRCS)
