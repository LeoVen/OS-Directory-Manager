/**
 * @file DirectoryDynamicArray.h
 *
 * @author Leonardo Vencovsky       (https://github.com/LeoVen)
 * @author Eduardo Vencovsky        (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza        (https://github.com/pinazza)
 * @author Erick Domingos Modenez
 *
 * @date 18/08/2018
 *
 * @brief Header file for @c DirectoryDynamicArray implementations
 *
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "Core.h"
#include "Directory.h"

	
#ifndef _DIRECTORY_TYPE
#define DIRECTORY_T Directory*
#endif

#ifndef _DYNAMIC_ARRAY_SPEC
#define _DYNAMIC_ARRAY_SPEC

#define _DYNAMIC_ARRAY_INIT_SIZE 8
#define _DYNAMIC_ARRAY_GROW_RATE 2

#endif

	typedef struct DirectoryDynamicArray
	{
		DIRECTORY_T *buffer;
		size_t size;
		size_t capacity;
		size_t growth_rate;
	} DirectoryDynamicArray;

	Status ddar_init(DirectoryDynamicArray **ddar);

	Status ddar_insert_front(DirectoryDynamicArray *ddar, DIRECTORY_T value);
	Status ddar_insert_at(DirectoryDynamicArray *ddar, DIRECTORY_T value, size_t index);
	Status ddar_insert_back(DirectoryDynamicArray *ddar, DIRECTORY_T value);

	Status ddar_remove_front(DirectoryDynamicArray *ddar, DIRECTORY_T *result);
	Status ddar_remove_at(DirectoryDynamicArray *ddar, size_t index, DIRECTORY_T *result);
	Status ddar_remove_back(DirectoryDynamicArray *ddar, DIRECTORY_T *result);

	Status ddar_display(DirectoryDynamicArray *ddar);
	Status ddar_display_inline(DirectoryDynamicArray *ddar);

	Status ddar_delete(DirectoryDynamicArray **ddar);
	Status ddar_delete_shallow(DirectoryDynamicArray **ddar);

	size_t ddar_cap(DirectoryDynamicArray *ddar);
	size_t ddar_size(DirectoryDynamicArray *ddar);

	bool ddar_is_empty(DirectoryDynamicArray *ddar);
	bool ddar_is_full(DirectoryDynamicArray *ddar);

	bool ddar_exists(DirectoryDynamicArray *ddar, DIRECTORY_T value);
	bool ddar_contains(DirectoryDynamicArray *ddar, String *name);
	Status ddar_find(DirectoryDynamicArray *ddar, String *name, size_t *result);

	Status ddar_realloc(DirectoryDynamicArray *ddar);

	Status dir_input(DirectoryDynamicArray *global_list, Directory **result, Directory *parent, String *name, User *owner);

#ifdef __cplusplus
}
#endif