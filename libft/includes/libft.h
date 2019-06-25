/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:28:12 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/24 14:25:37 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# include <string.h>
# include <wchar.h>

# define BUFF_SIZE 512

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

double				ft_clamp(double value, double lo, double hi);
void				ft_fmat(double (*mat)[3][3][3], t_vector rotation,
		double way);
t_vector			ft_vrotate(t_vector v, double mat[3][3]);
double				ft_2nd_degree(double a, double b, double c);
t_vector			ft_normalize(t_vector v);
double				ft_dot(t_vector va, t_vector vb);
t_vector			ft_get_vector(t_vector pos_a, t_vector pos_b);
double				ft_vdist(t_vector pos_a, t_vector pos_b);
t_vector			ft_vdiv(t_vector v, double f);
t_vector			ft_vvmul(t_vector va, t_vector vb);
t_vector			ft_vsub(t_vector pos_a, t_vector pos_b);
t_vector			ft_vadd(t_vector pos_a, t_vector pos_b);
t_vector			ft_vmul(t_vector v, double f);
int					ft_abs(int x);
void				ft_swap_int(int *a, int *b);
void				ft_swap(char **a, char **b);
void				ft_sort_tab(char ***tab);
void				ft_tab_reverse(char ***tab);
int					ft_count_n(int nbr);
int					ft_is_prime(int nb);
int					ft_find_next_prime(int nb);
int					ft_atoi_base(char *str, char *base);
void				ft_putnbr_base(int nbr, char *base);
void				ft_print_words_tables(char **tab);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *hay, const char *n, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_atoi_p(const char *str, int *i);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isquote(char c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
char				*ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinf(char *s1, char *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
int					ft_putchar(wchar_t c);
int					ft_putcharz(int c);
int					ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putendlnb(int nbr);
void				ft_putchar_fd(wchar_t c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_del_words_tables(char ***tab);
int					get_next_line(const int fd, char **line);
int					get_line(const int fd, char **line, char **isread);
void				ft_print_digit_tables(short **mat, int x, int y);
void				ft_print_digit(int *tab, int size);
size_t				ft_strclen(const char *s, char c);
int					ft_tablen(char **tab);
int					ft_isalnum_tab(char *str);
char				*ft_tabstr(char ***str, char c);
char				*ft_getenv(char **env, char *name);
int					ft_intdel(int **tab);
int					ft_mgerror(int ex_code, int fd, char *mg);
char				*ft_delc(char **str);
long				ft_diff_abs(int a, int b);
#endif
