/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/16 13:09:02 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

# define COLOR_RED 		"\x1b[31m"
# define COLOR_GREEN 	"\x1b[32m"
# define COLOR_YELLOW 	"\x1b[33m"
# define COLOR_BLUE 	"\x1b[34m"
# define COLOR_RESET	"\x1b[0m"

/* ------------------------------  STRUCTURE  ------------------------------- */

	/*Structure des listes chainées.*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ------------------------------  PROTOTYPE  ------------------------------- */

	/* ------ ft_atoi_itoa.c ------- */

		/*Convertie une chaine de caratère en nombre entier.*/
int		ft_atoi(const char *str);

		/*Convertie un nombre entier en chaine de caratère (malloc).*/
char	*ft_itoa(int n);

	/* -------- ft_calloc.c -------- */

		/*Remplie une chaine de caractère avec n 0.*/
void	ft_bzero(void *s, size_t n);

		/*Genere une chaine de caractère (malloc) de n caractère init à 0*/
void	*ft_calloc(size_t count, size_t size);

	/* ----- ft_get_next_line.c ---- */

		/*Lis un fichier et retroune une ligne (malloc) à chaque appel.
		Il est possible d'appeler plusieurs fichier à la fois.*/	
char	*get_next_line(int fd);

	/* -------- ft_is_alpha.c ------ */

		/*Check si le char est une lettre majuscule.*/
int		ft_isupper(int c);

		/*Check si le char est une lettre minuscule.*/
int		ft_islower(int c);

		/*Check si le char est alphabetique.*/
int		ft_isalpha(int c);

	/* -------- ft_is_other.c ------ */

		/*Check si le char est un chiffre.*/
int		ft_isdigit(int c);

		/*Check si le char est un chiffre ou une lettre.*/
int		ft_isalnum(int c);

		/*Check si le char est un ascii.*/
int		ft_isascii(int c);

		/*Check si le char est imprimable.*/
int		ft_isprint(int c);

	/* ------- ft_lst_apply.c ------ */

		/*Inverse l'odre de l'ensemble de la liste.*/
void	ft_lstrev(t_list **lst);

		/*Itère sur une liste et applique une fonction à chaque élément.*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

		/*Renvoie le dernier élément de la liste.*/
t_list	*ft_lstlast(t_list *lst);

		/*Compte le nombre d’éléments de la liste.*/
int		ft_lstsize(t_list *lst);

		/*Itère sur une liste et applique la fonction a chaque élément en créant
		une nouvelle liste résultant des applications. La fonction ’del’ est là
		pour détruire cette nouvelle liste si nécessaire.*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

	/* ------- ft_lst_clear.c ------ */
		/*Libère la mémoire de content*/
void	del(void *content);
		/*Libère la mémoire de l’élément passé en argument avec la fonction
		'del' sans touché à next*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));

		/*Libère la mémoire de l’élément passé en argument et de tous les
		éléments qui suivent, à l’aide de ’del’.*/
void	ft_lstclear(t_list **lst, void (*del)(void*));

	/* -------- ft_lst_new.c ------- */

		/*Ajoute l’élément ’new’ au début de la liste.*/
void	ft_lstadd_front(t_list **lst, t_list *new);

		/*Ajoute l’élément ’new’ a la fin de la liste.*/
void	ft_lstadd_back(t_list **lst, t_list *new);

		/*Alloue (malloc) et renvoie un nouvel élément en liant le ’content’ et
		en initialisant ’next’ à NULL.*/
t_list	*ft_lstnew(void *content);

	/* -------- ft_mem_all.c ------- */

		/*Retrouve la première occurance de c (int) dans s (void) en s'arrétant
		à n bytes de s*/
void	*ft_memchr(const void *s, int c, size_t n);

		/*Compare la chaine s1(void) et s2(void) en bytes converties en unsigned
		char. Renvois un nombre postif, nul ou negatif selon si s1 est superieur,
		egal ou inferieur à s2.*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

		/*Copie c len fois dans b et retourne le debut de cette chaine.*/
void	*ft_memset(void *b, int c, size_t len);

		/*Copie n bytes de la chaine src dans la chaine dst. Si elles se superposent
		la retour est indéfinis dans ce cas utiliser ft_memmove.*/
void	*ft_memcpy(void *dst, const void *src, size_t n);

		/*Copie n bytes de la chaine src dans la chaine dst en parvenant a gérer
		lorsques les chaines se superposent.*/
void	*ft_memmove(void *dst, const void *src, size_t len);

	/* ------- ft_print_fd.c ------- */

		/*Écrit le caractère c sur le descripteur de fichier donné.*/
void	ft_putchar_fd(char c, int fd);

		/*Écrit le nombre n sur le descripteur de fichier donné.*/
void	ft_putnbr_fd(int n, int fd);

		/*Écrit la chaîne de caractères s sur le descripteur de fichier.*/
void	ft_putstr_fd(char *s, int fd);

		/*Écrit la chaîne s en ajoutant \n sur le descripteur de fichier.*/
void	ft_putendl_fd(char *s, int fd);

	/* ----- ft_print_number.c ----- */

		/*Imprime le nombre n sur le terminal*/
void	ft_print_nbr(long int n, size_t *i);

		/*Imprime le nombre n de type unsigned sur le terminal*/
void	ft_print_nbr_uns(size_t n, size_t *i);

		/*Imprime le nombre n de type unsigned selon une base sur le terminal*/
void	ft_print_nbr_base_uns(size_t n, char *base, size_t size, size_t *i);

	/* ------ ft_print_other.c ----- */

		/*Imprime le charatère c sur le terminal*/
size_t	ft_put_char(char c);

		/*Imprime la chaine de charatère s sur le terminal*/
size_t	ft_put_str(char *s);

		/*Imprime l'adresse d'un pointeur sur le terminal*/
size_t	ft_put_ptr(size_t n);

void	ft_putstr_color(char *color, char *s, int fd);

	/* -------- ft_printf.c -------- */

		/*Imprime une chaine de caractères sur le terminal en ajoutant differentes
		variables passées en paramètre*/
int		ft_printf(const char *str, ...);

	/* --------- ft_split.c -------- */

void	ft_free_split(char **str);

		/*Separe s par c en comptabiliasant le nombre de mots.*/
int		ft_divide(char const *s, char c);

		/*Retourne un tableau de chaînes de caractères (malloc) en séparant la
		chaine s a chaque caractère c*/
char	**ft_split(char const *s, char c);

	/* -------- ft_str_add.c ------- */

		/*Copie n char de src a la fin de dst et ajoute \0 à la fin.*/
char	*ft_strncat(char *dst, const char *src, size_t n);

		/*Copie n char de src a la fin de dst et ajoute \0 à la fin tout prenant en
		compte la taille de dst pour eviter depasser la place disponible.*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

		/*Concatene s2 après s1 et retourne une nouvelle chaîne (malloc).*/
char	*ft_strjoin(char const *s1, char const *s2);

	/* ------- ft_str_apply.c ------ */

		/*Applique la fonction ’f’ à chaque caractère de la chaîne.*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

		/*Applique la fonction ’f’ à chaque caractère de la chaîne et retourne une
		copie de cette nouvelle chaine (malloc).*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

	/* -------- ft_str_copy.c ------ */

		/*Copie jusqu'à dstsize - 1 la chaine src dans dst et finis par \0.*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

		/*Copie la chaine s1 (malloc).*/
char	*ft_strdup(const char *s1);

		/*Retourne une copie de la chaîne s1 (malloc) sans les caractères set au
		début et à la fin de la chaîne.*/
char	*ft_strtrim(char const *s1, char const *set);

		/*Retourne une chaîne (malloc) issue de la chaîne s qui commence à l’index
		start et a pour taille maximale len.*/
char	*ft_substr(char const *s, unsigned int start, size_t len);

	/* -------- ft_str_find.c ------ */

		/*Retrouve la première occurance de needle dans la chaine haystack en limitant
		la recherche a len char.*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

		/*Retrouve la première occurance du char c dans la chaine s*/
char	*ft_strchr(const char *str, int c);

		/*Retrouve la dernière occurance du char c dans la chaine s*/
char	*ft_strrchr(const char *str, int c);

		/*Compare la chaine s1 et s2 en limitant à n char. Renvois un nombre postif,
		nul ou negatif selon si s1 est superieur, egal ou inferieur à s2.*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

		/*Determine la taile de la chaine s.*/
size_t	ft_strlen(const char *str);

	/* --------- ft_to_all.c ------- */

		/*Convertis une lettre majuscule en lettre minuscule.*/
int		ft_tolower(int c);

		/*Convertis une lettre minuscule en lettre majuscule.*/
int		ft_toupper(int c);

#endif
