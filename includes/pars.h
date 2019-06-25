/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:15:46 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/24 14:15:23 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H
# define FALSE 0
# define NB_TYPES 4
# define TRUTH 1
# include "rt.h"
# define BUFF 2048

typedef struct		s_token
{
	struct s_token	*next;
	char			*word;
	int				type;
	int				pile;
}					t_token;

typedef struct		s_lstlum
{
	struct s_lstlum	*next;
	t_lum			lum;
}					t_lstlum;

typedef struct		s_lstform
{
	t_form				form;
	struct s_lstform	*next;
}					t_lstform;

/*
**	enum for types
**
**	START |	Starting point
**	NAMES |	Name of the object
**	TWPTS |	Separator name/argument
**	ARGMT |	Argument
**	WORDS |	Word in argument
**	ENDED |	End of argument
**	NOMBR |	Digit numbers
*/
# define NB_STATUS 8

typedef enum		e_status
{
	START = 0,
	NAMES,
	TWPTS,
	ARGMT,
	WORDS,
	ENDED,
	NOMBR,
	LSTOB,
	LSTCP,
	ERROR,
	PILDW
}					t_status;

/*
**	enum for char_types
**
**	DBQT |	Double quote, in order to store word
**	TWPT |	Separator Name, Argument
**	NBRS |	Digit kind
**	CBRO |	Curly bracket open
**	CBRC |	Curly bracket closure
**	BRAO |	Bracket open
**	BRAC |	Bracket closure
**	CHAR |	all other chars
*/

# define NB_TYPE 10

typedef enum		e_types
{
	DBQT = 0,
	TWPT,
	CARM,
	CBRO,
	CBRC,
	BRAO,
	BRAC,
	NBRS,
	SPAC,
	CHAR
}					t_types;

typedef struct		s_pile
{
	int				type;
	struct s_pile	*next;
}					t_pile;

typedef struct		s_stat
{
	char			cha;
	char			*load;
	t_pile			*pile;
	int				type;
	int				status;
	int				old_status;
	int				val;
}					t_stat;

double				ft_atod(char *str);
int					pars_build_line(t_token *tok, char *str, t_stat *st, int k);
int					pars_file(char *str, t_env *env);
int					get_type(char c);
int					get_next_state(int status, int type);
int					get_val(int status, int type);
void				lex_add_char(char buff[BUFF], char **load, char cha);
void				lex_add_token(char buff[BUFF], t_stat *stat, t_token *tok);
t_token				*lex_init_token(int type, char *str);
void				free_struct(t_token *token);
void				pile_up(t_stat *stat, int type);
int					pile_down(t_stat *stat, int type);
int					pile_last(t_stat *stat);
void				add_light(t_lstlum **lst, t_lum light);
void				add_form(t_lstform **lst, t_form form);
int					size_lst(t_lstlum *tmp);
int					size_lst_form(t_lstform *tmp);
t_lum				*lstlum_to_lum(t_lstlum *lstlum, int size);
t_form				*lstform_to_form(t_lstform *lstform, int size);

/*
**	Parsing tokens
*/

t_env				token_to_env(t_token **token, int *err);
int					pars_type(t_token **token, t_env *env);
int					pars_camera(t_token **token, t_env *env);
int					pars_scene(t_token **token, t_env *env);
int					pars_object(t_token **token, t_env *env);
int					pars_light(t_token **token, t_env *env);
void				free_token(t_token **token);
void				free_lstform(t_lstform **token);
void				free_lstlum(t_lstlum **token);
int					free_move(t_token **token);
int					free_double_move(t_token **token);

/*
**	Parsing fields
*/

void				pars_fill_cam(t_cam *cam);
int					pars_field_light(t_token **token, t_lum *light);
t_material			pars_material(t_token **token, t_env *env);
int					pars_field_form(t_token **token, t_form *form, t_env *env);
int					pars_field_camera(t_token **token, t_env *env);
int					pars_field_scene(t_token **token, t_env *env);
t_vector			pars_vector_color(t_token **token);
t_vector			pars_vector(t_token **token);
double				pars_double(t_token **token);
int					pars_name(t_token **token);

#endif
