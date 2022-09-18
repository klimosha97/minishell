/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:51:18 by                   #+#    #+#             */
/*   Updated: 2022/01/04 17:22:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

# define SPACES 14

# define WORD 2
# define QUOTES 3
# define DOUBLE_QUOTES 4

# define REDIR_OUT 5
# define REDIR_IN 6
# define REDIR_APPEND 7
# define REDIR_DISAPPEND 8
# define HEREDOC 9

# define PIPE 10
# define SIMICOLON 11
# define UMPERS 16

# define AND 12
# define OR 13
# define GROUP_OK 15

typedef struct s_list
{
	int				type;
	char			*key;
	void			*value;
	int				start;
	int				last;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_cmdinfo
{
	int					type;
	char				**prog_args;
	int					size_args;
	char				*file_in;
	int					fd_in;
	char				*file_out;
	int					fd_out;
	char				*delim;
	int					size_pipes;
	int					chmod;
	struct s_cmdinfo	*next;
	struct s_cmdinfo	*prev;
}				t_cmdinfo;

int			ft_isalpha(int ch);
int			ft_isdigit(int num);
int			ft_is_and(const char *str);
int			ft_is_or(const char *str);
int			ft_word(int a);
int			ft_isalnum(int a);
int			ft_isascii(int a);
int			ft_isprint(int a);
int			ft_isnotspec(int a);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *memptr, int val, size_t num);
void		ft_bzero(void *str, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t num);
void		*ft_memmove(void *dest, const void *src, size_t count);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int character);
int			ft_tolower(int c);
char		*ft_strchr(const char *string, int symbol);
char		*ft_strrchr(const char *string, int symbol);
int			ft_strncmp(const char *string1, const char *string2, size_t num);
int			ft_strncmpp(const char *string1, const char *string2, size_t num);
void		*ft_memchr(const void *memptr, int val, size_t num);
int			ft_memcmp(const void *memptr1, const void *memptr2, size_t num);
char		*ft_strnstr(const char *string1, const char *string2, size_t len);
long long	ft_atoi(const char *string);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *str);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strtrim(const char *s1, const char *set);
char		**ft_split(const char *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(int type);
t_list		*get_head(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstfirst(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst);
void		ft_lstdelone_cmd(t_cmdinfo *lst);
int			ft_abs(int n);
int			ft_max(int a, int b);
t_cmdinfo	*ft_lstnew_cmd(void);
void		ft_lstadd_back_cmd(t_cmdinfo **cmd, t_cmdinfo *new);
t_cmdinfo	*ft_lstlast_cmd(t_cmdinfo *lst);
char		*ft_charjoin(char *s1, char s2);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_clean_all(char *s1, char *s2);

#endif