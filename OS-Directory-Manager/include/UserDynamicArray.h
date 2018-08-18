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

	Status dar_init(UserDynamicArray **dar);

	Status dar_get(UserDynamicArray *dar, size_t index, USER_T *result);

	Status dar_insert_front(UserDynamicArray *dar, USER_T value);
	Status dar_insert_at(UserDynamicArray *dar, USER_T value, size_t index);
	Status dar_insert_back(UserDynamicArray *dar, USER_T value);

	Status dar_remove_front(UserDynamicArray *dar, USER_T *result);
	Status dar_remove_at(UserDynamicArray *dar, size_t index, USER_T *result);
	Status dar_remove_back(UserDynamicArray *dar, USER_T *result);

	Status dar_display(UserDynamicArray *darr);
	Status dar_display_raw(UserDynamicArray *darr);

	Status dar_delete(UserDynamicArray **darr);

	size_t dar_cap(UserDynamicArray *dar);
	size_t dar_size(UserDynamicArray *dar);

	bool dar_is_empty(UserDynamicArray *dar);
	bool dar_is_full(UserDynamicArray *dar);

	bool dar_exists(UserDynamicArray *dar, USER_T value);

	Status dar_realloc(UserDynamicArray *dar);

#ifdef __cplusplus
}
#endif