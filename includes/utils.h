/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:04:00 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 21:52:34 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

/*					SPLIT_CHARSET.C					*/
char				**ft_split_charset(char **split, char *str, char *charset);

/*					UTILS.C					*/
int					ft_strcmp(const char *s1, const char *s2);
void				try_free(char *s);
t_p_node			*skip_faulty_nodes(t_p_node *curr);
bool				is_minishell(char *path);

/*					UTILS_CHAR_CHECK.C					*/
bool				is_space(char c);
bool				is_special(char c);
int					is_quote(char c);
int					is_metachar(char c);
int					is_charset(char c, char *charset);

/*					UTILS_HELPER.C					*/
int					is_valid_var_char(char c);
void				print_tab(char **tabb);
bool				is_only_digits(char *str);

/*					UTILS_NUMBER.C					*/
unsigned long long	ft_atoull(const char *str);

/*					QUOTES_COUNT.C					*/
void				count_quoted_word(char *str, char quote, int *count,
						int *i);
int					length_word_quotes(char *str, char quote);

/*					STRING_QUOTES.C					*/
size_t				strlcpy_quotes(char *dest, char *src, size_t size);
void				cpy_quotes(size_t *i, size_t *j, char *dest, char *src);
char				*add_char_to_string(char *s1, char c);

/*					REMAKE_ENVP.C		*/
char				*ft_strjoin_and_replace(char *ori, char *append);
void				remake_envp(t_data *data);

/*					PRINT_STRUCTURE.C		*/
void				print_array(char **arr);
void				print_parser(t_data *data);

#endif
