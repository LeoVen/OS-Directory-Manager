/**
 * @file UserDynamicArray.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 20/03/2018
 *
 * @brief Header file for @c UserDynamicArray implementations in C
 *
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "Core.h"
#include "User.h"

#ifndef _DYNAMIC_ARRAY_SPEC
#define _DYNAMIC_ARRAY_SPEC

#define _DYNAMIC_ARRAY_INIT_SIZE 8
#define _DYNAMIC_ARRAY_GROW_RATE 2

#endif

	typedef struct UserDynamicArray
	{
		int *buffer;
		size_t size;
		size_t capacity;
		size_t growth_rate;
	} UserDynamicArray;

	Status dar_init(UserDynamicArray **dar);

	Status dar_get(UserDynamicArray *dar, size_t index, int *result);

	Status dar_insert_front(UserDynamicArray *dar, int value);
	Status dar_insert_at(UserDynamicArray *dar, int value, size_t index);
	Status dar_insert_back(UserDynamicArray *dar, int value);

	Status dar_remove_front(UserDynamicArray *dar);
	Status dar_remove_at(UserDynamicArray *dar, size_t index);
	Status dar_remove_back(UserDynamicArray *dar);

	Status dar_display(UserDynamicArray *darr);
	Status dar_display_raw(UserDynamicArray *darr);

	Status dar_delete(UserDynamicArray **darr);
	Status dar_erase(UserDynamicArray **dar);

	size_t dar_cap(UserDynamicArray *dar);
	size_t dar_size(UserDynamicArray *dar);

	bool dar_is_empty(UserDynamicArray *dar);
	bool dar_is_full(UserDynamicArray *dar);

	Status dar_find_max(UserDynamicArray *dar, int *result);
	Status dar_find_min(UserDynamicArray *dar, int *result);
	Status dar_find_max_pos(UserDynamicArray *dar, size_t *result);
	Status dar_find_min_pos(UserDynamicArray *dar, size_t *result);

	Status dar_frequency(UserDynamicArray *dar, int value, size_t *frequency);

	Status dar_contains(UserDynamicArray *dar, int value, bool *result);
	bool dar_exists(UserDynamicArray *dar, int value);

	Status dar_find_occurrance_first(UserDynamicArray *dar, int value, size_t *position);
	Status dar_find_occurrance_last(UserDynamicArray *dar, int value, size_t *position);

	Status dar_grow(UserDynamicArray *dar, size_t size);
	Status dar_realloc(UserDynamicArray *dar);

#ifdef __cplusplus
}
#endif