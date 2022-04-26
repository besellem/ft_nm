/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_templates.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:48:02 by besellem          #+#    #+#             */
/*   Updated: 2022/04/26 21:38:04 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_TEMPLATES_H
# define LIST_TEMPLATES_H

/*
** THIS ABI DOES PRETTY MUCH THE EQUIVALENT OF C++'S LIST TEMPLATES IN C
*/

#include "ft_stdlib.h"


/*
** creates a new type of linked list.
** in order to use the lst_* macro like functions, you may want to use your own
** list type, and then use the lst_* functions on it. Or you can just create a
** new type of list with the following macro.
** note that if you use your own list type, the structure must be defined as the
** following format :
*/
#define CREATE_LST_TYPE(__name, __type)                                        \
	typedef struct __s##__name  __name;                                        \
	struct __s##__name {                                                       \
		__type				content;                                           \
		struct __s##__name	*next;                                             \
	};


/*
** add a new element at the beginning of a list
**   @param __head: a pointer on the head of the list (list **)
**   @param __val: the value to add
**   @return: nothing
*/
#define lst_push_front(__head, __val) {                                        \
	if (1) {                                                              \
		typeof(**__head) *__x = ft_calloc(1, sizeof(typeof(**__head)));        \
		if (!__x)                                                              \
			die();                                                             \
		__x->content = (__val);                                                \
		__x->next = *__head;                                                   \
		*__head = __x;                                                         \
	}																		   \
}


/*
** add a new element at the end of a list
**   @param __head: a pointer on the head of the list (list **)
**   @param __val: the value to add
**   @return: nothing
*/
#define lst_push_back(__head, __val) {                                         \
		typeof(**__head) *__x = ft_calloc(1, sizeof(typeof(**__head)));        \
		if (!__x)                                                              \
			die();                                                             \
		__x->content = (__val);                                                \
		if (!*__head)                                                          \
			*__head = __x;                                                     \
		else {                                                                 \
			typeof(**__head) *__tmp = *__head;                                 \
			while (__tmp->next)                                                \
				__tmp = __tmp->next;                                           \
			__tmp->next = __x;                                                 \
		}                                                                      \
}


/*
** add a new element in a sorted list
**   @param __head: a pointer on the head of the list (list **)
**   @param __val: the value to add
**   @param __cmp: the function to use to compare two nodes
**   @return: nothing
*/
#define lst_push_sorted(__head, __val, __cmp) {                                \
	if (1) {                                                   \
		typeof(**__head) *__lst = *__head;                                     \
		typeof(**__head) *__next;                                              \
		typeof(**__head) *__prev = NULL;                                       \
		while (__lst && (*__cmp)(__lst->content, __val) <= 0) {                \
			__prev = __lst;                                                    \
			__lst = __lst->next;                                               \
		}                                                                      \
		if (!__lst) {                                                          \
			lst_push_back(__head, __val);                                      \
		} else if (!__prev) {                                                  \
			lst_push_front(__head, __val);                                     \
		} else {                                                               \
			__next = __prev->next;                                             \
			__prev->next = ft_calloc(1, sizeof(typeof(**__head)));             \
			if (!__prev->next)                                                 \
				die();                                                         \
			__prev->next->content = __val;                                     \
			__prev->next->next = __next;                                       \
		}                                                                      \
	}                                                                          \
}


/*
** delete a list and all its nodes
**   @param __head: a pointer on the head of the list (list **)
**   @param __del: a pointer on a function that will delete the content of a node.
**                 if you don't want to delete the content, you can pass
**                 LST_CLEAR_IGN. It will only free the node and not its content.
**   @return: nothing
*/
#define lst_clear(__head, __del) {                                             \
	typeof(**__head) *__tmp;                                                   \
	while (*__head) {                                                          \
		if ((*__del))                                                          \
			(*__del)((*__head)->content);                                      \
		__tmp = (*__head)->next;                                               \
		free(*__head);                                                         \
		*__head = __tmp;                                                       \
	}                                                                          \
	free(*__head);                                                             \
	*__head = NULL;                                                            \
}


/*
** get size of the list
**   @param __lst: the list itself (list *)
**   @return: the size of the list
*/
#define lst_size(__lst) ({                                                     \
	typeof(*__lst) *__tmp = __lst;                                             \
	size_t __i = 0;                                                            \
	while (__tmp) {                                                            \
		++__i;                                                                 \
		__tmp = __tmp->next;                                                   \
	}                                                                          \
	__i;                                                                       \
})


/*
** ignore functions pointer for lists
*/
#define LST_CMP_IGN    ((int (*)())0)
#define LST_CLEAR_IGN  ((void (*)())0)


/*
** exit the program on allocation error
** you can replace it with your own function: you just have to define it before
** including this header.
*/
#ifndef die
# define die() exit(1)
#endif


#endif
