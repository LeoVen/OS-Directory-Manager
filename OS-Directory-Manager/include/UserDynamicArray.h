/**
* @file UserDynamicArray.h
*
* @author Leonardo Vencovsky (https://github.com/LeoVen)
* @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
* @author Guilherme Pinazza  (https://github.com/pinazza)
*
* @date 17/08/2018
*
* @brief Header file for @c UserDynamicArray implementations
*
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "Core.h"
#include "User.h"

#ifndef _USER_TYPE
#define USER_T User*
#endif

#ifndef _DYNAMIC_ARRAY_SPEC
#define _DYNAMIC_ARRAY_SPEC

#define _DYNAMIC_ARRAY_INIT_SIZE 8
#define _DYNAMIC_ARRAY_GROW_RATE 2

#endif

	typedef struct UserDynamicArray
	{
		USER_T *buffer;
		size_t size;
		size_t capacity;
		size_t growth_rate;
	} UserDynamicArray;

	Status udar_init(UserDynamicArray **udar);

	Status udar_insert_front(UserDynamicArray *udar, USER_T value);
	Status udar_insert_at(UserDynamicArray *udar, USER_T value, size_t index);
	Status udar_insert_back(UserDynamicArray *udar, USER_T value);

	Status udar_remove_front(UserDynamicArray *udar, USER_T *result);
	Status udar_remove_at(UserDynamicArray *udar, size_t index, USER_T *result);
	Status udar_remove_back(UserDynamicArray *udar, USER_T *result);

	Status udar_display_inline(UserDynamicArray *udar);
	Status udar_display(UserDynamicArray *darr);

	Status udar_delete(UserDynamicArray **darr);

	size_t udar_cap(UserDynamicArray *udar);
	size_t udar_size(UserDynamicArray *udar);

	bool udar_is_empty(UserDynamicArray *udar);
	bool udar_is_full(UserDynamicArray *udar);

	bool udar_exists(UserDynamicArray *udar, USER_T value);
	bool udar_find(UserDynamicArray *udar, String *name, size_t *result);

	Status udar_realloc(UserDynamicArray *udar);

#ifdef __cplusplus
}
#endif