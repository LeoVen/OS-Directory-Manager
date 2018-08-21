/**
 * @file DirectoryDynamicArray.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 18/08/2018
 *
 * @brief Source file for DirectoryDynamicArray
 *
 */

#include "DirectoryDynamicArray.h"

// +-------------------------------------------------------------------------------------------------+
// |                                          Initializers                                           |
// +-------------------------------------------------------------------------------------------------+

Status ddar_init(DirectoryDynamicArray **ddar)
{
	(*ddar) = malloc(sizeof(DirectoryDynamicArray));

	if (!(*ddar))
		return DS_ERR_ALLOC;

	(*ddar)->buffer = calloc(_DYNAMIC_ARRAY_INIT_SIZE, sizeof(DIRECTORY_T));

	if (!((*ddar)->buffer))
		return DS_ERR_ALLOC;

	(*ddar)->capacity = _DYNAMIC_ARRAY_INIT_SIZE;
	(*ddar)->growth_rate = _DYNAMIC_ARRAY_GROW_RATE;

	(*ddar)->size = 0;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Insertion                                            |
// +-------------------------------------------------------------------------------------------------+

Status ddar_insert_front(DirectoryDynamicArray *ddar, DIRECTORY_T value)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	if (ddar_is_full(ddar))
	{
		Status st = ddar_realloc(ddar);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = ddar->size; i > 0; i--)
	{
		ddar->buffer[i] = ddar->buffer[i - 1];
	}

	ddar->buffer[0] = value;

	(ddar->size)++;

	return DS_OK;
}

Status ddar_insert_at(DirectoryDynamicArray *ddar, DIRECTORY_T value, size_t index)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	if (index > ddar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = ddar_insert_front(ddar, value);

		if (st != DS_OK)
			return st;
	}
	else if (index == ddar->size)
	{
		st = ddar_insert_back(ddar, value);

		if (st != DS_OK)
			return st;
	}
	else
	{
		if (ddar_is_full(ddar))
		{
			st = ddar_realloc(ddar);

			if (st != DS_OK)
				return st;
		}

		size_t i;
		for (i = ddar->size; i > index; i--)
		{
			ddar->buffer[i] = ddar->buffer[i - 1];
		}

		ddar->buffer[index] = value;

		(ddar->size)++;
	}

	return DS_OK;
}

Status ddar_insert_back(DirectoryDynamicArray *ddar, DIRECTORY_T value)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	if (ddar_is_full(ddar))
	{
		Status st = ddar_realloc(ddar);

		if (st != DS_OK)
			return st;
	}

	ddar->buffer[ddar->size] = value;

	(ddar->size)++;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

Status ddar_remove_front(DirectoryDynamicArray *ddar, DIRECTORY_T *result)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	if (ddar_is_empty(ddar))
		return DS_ERR_INVALID_OPERATION;

	*result = ddar->buffer[0];

	size_t i;
	for (i = 0; i < ddar->size; i++)
	{
		ddar->buffer[i] = ddar->buffer[i + 1];
	}

	(ddar->size)--;

	return DS_OK;
}

Status ddar_remove_at(DirectoryDynamicArray *ddar, size_t index, DIRECTORY_T *result)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	if (ddar_is_empty(ddar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= ddar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = ddar_remove_front(ddar, result);

		if (st != DS_OK)
			return st;
	}
	else if (index == ddar->size - 1)
	{
		st = ddar_remove_back(ddar, result);

		if (st != DS_OK)
			return st;
	}
	else
	{
		*result = ddar->buffer[index];

		size_t i;
		for (i = index; i < ddar->size; i++)
		{
			ddar->buffer[i] = ddar->buffer[i + 1];
		}

		(ddar->size)--;
	}

	return DS_OK;
}

Status ddar_remove_back(DirectoryDynamicArray *ddar, DIRECTORY_T *result)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	if (ddar_is_empty(ddar))
		return DS_ERR_INVALID_OPERATION;

	*result = ddar->buffer[ddar->size - 1];

	(ddar->size)--;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Display                                             |
// +-------------------------------------------------------------------------------------------------+

Status ddar_display(DirectoryDynamicArray *ddar)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	size_t i;
	for (i = 0; i < ddar->size; i++)
	{

		dir_display(ddar->buffer[i]);
	}

	return DS_OK;
}

Status ddar_display_inline(DirectoryDynamicArray *ddar)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	printf("%-20s\t%-20s\t%-20s\t%-20s\n", "Name", "Parent", "Owner", "Time");

	size_t i;
	for (i = 0; i < ddar->size; i++)
	{

		dir_display_inline(ddar->buffer[i]);
	}

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Resets                                              |
// +-------------------------------------------------------------------------------------------------+

Status ddar_delete(DirectoryDynamicArray **ddar)
{
	if (*ddar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	size_t i;
	for (i = 0; i < (*ddar)->size; i++)
	{
		st = dir_delete(&((*ddar)->buffer[i]));

		if (st != DS_OK)
			return st;
	}

	free((*ddar)->buffer);
	free((*ddar));

	(*ddar) = NULL;

	return DS_OK;
}

Status ddar_delete_shallow(DirectoryDynamicArray **ddar)
{
	if (*ddar == NULL)
		return DS_ERR_NULL_POINTER;

	free((*ddar)->buffer);
	free((*ddar));

	(*ddar) = NULL;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

size_t ddar_cap(DirectoryDynamicArray *ddar)
{
	return ddar->capacity;
}

size_t ddar_size(DirectoryDynamicArray *ddar)
{
	return ddar->size;
}

bool ddar_is_empty(DirectoryDynamicArray *ddar)
{
	return ddar->size == 0;
}

bool ddar_is_full(DirectoryDynamicArray *ddar)
{
	return ddar->size == ddar->capacity;
}

bool ddar_exists(DirectoryDynamicArray *ddar, DIRECTORY_T value)
{
	if (ddar == NULL)
		return false;

	if (ddar_is_empty(ddar))
		return false;

	size_t i;
	for (i = 0; i < ddar->size; i++)
	{
		if (str_equals(value->name, ddar->buffer[i]->name))
			return true;
	}

	return false;
}

// Exclusive use
bool ddar_contains(DirectoryDynamicArray *ddar, String *name)
{
	if (ddar == NULL)
		return false;

	if (ddar_is_empty(ddar))
		return false;

	size_t i;
	for (i = 0; i < ddar->size; i++)
	{
		if (str_equals(name, ddar->buffer[i]->name))
			return true;
	}

	return false;
}

Status ddar_find(DirectoryDynamicArray *ddar, String *name, size_t *result)
{
	if (ddar == NULL || name == NULL)
		return DS_ERR_NULL_POINTER;

	*result = 0;

	bool found = false;

	size_t i;
	for (i = 0; i < ddar->size; i++)
	{
		if (str_equals(ddar->buffer[i]->name, name))
		{
			*result = i;

			found = true;

			break;
		}
	}

	if (found)
		return DS_OK;

	return DS_ERR_NOT_FOUND;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Buffer                                               |
// +-------------------------------------------------------------------------------------------------+

Status ddar_realloc(DirectoryDynamicArray *ddar)
{
	if (ddar == NULL)
		return DS_ERR_NULL_POINTER;

	ddar->capacity *= ddar->growth_rate;

	DIRECTORY_T *new_buffer = realloc(ddar->buffer, sizeof(DIRECTORY_T) * ddar->capacity);

	if (!new_buffer)
	{
		ddar->capacity /= ddar->growth_rate;

		return DS_ERR_ALLOC;
	}

	ddar->buffer = new_buffer;

	return DS_OK;
}


// Exclusive use
Status dir_input(DirectoryDynamicArray *global_list, Directory **result, Directory *parent, String *name, User *owner)
{
	String *dir_name;

	Status st = str_init(&dir_name);

	if (st != DS_OK)
		return st;

	st = str_append(dir_name, name);

	if (st != DS_OK)
		return st;

	st = dir_make(result, parent, owner, dir_name);

	if (st != DS_OK)
		return st;

	st += ddar_insert_back(parent->children, (*result));
	st += ddar_insert_back(global_list, (*result));

	if (st != DS_OK)
		return st;

	return DS_OK;
}