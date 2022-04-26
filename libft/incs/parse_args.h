/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:35:34 by besellem          #+#    #+#             */
/*   Updated: 2022/03/15 23:05:13 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ARGS_H
# define PARSE_ARGS_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>

/* options masks */
# define OPT_A       0x1
# define OPT_B       0x2
# define OPT_C       0x4
# define OPT_D       0x8
# define OPT_E       0x10
# define OPT_F       0x20
# define OPT_G       0x40
# define OPT_H       0x80
# define OPT_I       0x100
# define OPT_J       0x200
# define OPT_K       0x400
# define OPT_L       0x800
# define OPT_M       0x1000
# define OPT_N       0x2000
# define OPT_O       0x4000
# define OPT_P       0x8000
# define OPT_Q       0x10000
# define OPT_R       0x20000
# define OPT_S       0x40000
# define OPT_T       0x80000
# define OPT_U       0x100000
# define OPT_V       0x200000
# define OPT_W       0x400000
# define OPT_X       0x800000
# define OPT_Y       0x1000000
# define OPT_Z       0x2000000
# define OPT_A_MIN   0x4000000
# define OPT_B_MIN   0x8000000
# define OPT_C_MIN   0x10000000
# define OPT_D_MIN   0x20000000
# define OPT_E_MIN   0x40000000
# define OPT_F_MIN   0x80000000
# define OPT_G_MIN   0x100000000
# define OPT_H_MIN   0x200000000
# define OPT_I_MIN   0x400000000
# define OPT_J_MIN   0x800000000
# define OPT_K_MIN   0x1000000000
# define OPT_L_MIN   0x2000000000
# define OPT_M_MIN   0x4000000000
# define OPT_N_MIN   0x8000000000
# define OPT_O_MIN   0x10000000000
# define OPT_P_MIN   0x20000000000
# define OPT_Q_MIN   0x40000000000
# define OPT_R_MIN   0x80000000000
# define OPT_S_MIN   0x100000000000
# define OPT_T_MIN   0x200000000000
# define OPT_U_MIN   0x400000000000
# define OPT_V_MIN   0x800000000000
# define OPT_W_MIN   0x1000000000000
# define OPT_X_MIN   0x2000000000000
# define OPT_Y_MIN   0x4000000000000
# define OPT_Z_MIN   0x8000000000000
# define OPT_0       0x10000000000000
# define OPT_1       0x20000000000000
# define OPT_2       0x40000000000000
# define OPT_3       0x80000000000000
# define OPT_4       0x100000000000000
# define OPT_5       0x200000000000000
# define OPT_6       0x400000000000000
# define OPT_7       0x800000000000000
# define OPT_8       0x1000000000000000
# define OPT_9       0x2000000000000000
# define OPT_ILLEGAL 0x4000000000000000

/*
** end_pos: position of the last option in argv
** opts:    options masks
*/
typedef struct s_parsing_opts
{
	int			end_pos;
	uint64_t	opts;
}	t_parsing_opts;

/* find character corresponding to this `mask' */
char			find_option_symbol(uint64_t);

/* find mask for the corresponding `character' */
uint64_t		find_option_mask(char);

/* check if an option is set */
bool			option_set(uint64_t, uint64_t);

/*
** parse_args() parses the arguments passed to the program and returns the
** options found. It also fills the `va_list' array with the options requiring.
**
** argc:              number of arguments passed to the program
** argv:              array of arguments passed to the program
** return_on_illegal: if true, return directly if an illegal option is found,
**                    holding the mask of the illegal option.
**                    In that case, `t_parsing_opts::opts' contains the illegal
**                    option's mask and OPT_ILLEGAL is set.
**                    If false, OPT_ILLEGAL would be set with no effect.
** options_haystack:  characters representing the options to search for.
**                    You may also add `:' after a symbol to indicate that the
**                    option requires an argument right after.
**                    It will then be stored in the `va_list' array if found.
**
** Examples:
** parse_args(argc, argv, false, "abc")
**  -> will search for the options 'a', 'b' and 'c'
**
** parse_args(argc, argv, false, "a:bc", &keep_a)
**  -> will search for the options 'a', 'b' and 'c' and store the argument of
**     'a' in `keep_a'
**
**
** Notes:
** `argv' and `options_haystack' are required to be valid strings.
** If not, the function will crash on purpose.
*/
t_parsing_opts	parse_args(
	int argc,
	char **argv,
	bool return_on_illegal,
	const char *options_haystack,
	...);

#endif /* !defined(PARSE_ARGS_H) */
