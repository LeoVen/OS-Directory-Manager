/**
* @file UserDynamicArray.c
*
* @author Leonardo Vencovsky (https://github.com/LeoVen)
* @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
* @author Guilherme Pinazza  (https://github.com/pinazza)
*
* @date 17/08/2018
*
* @brief Source file for UserDynamicArray
*
*/

#include "UserDynamicArray.h"

// +-------------------------------------------------------------------------------------------------+
// |                                          Initializers                                           |
// +-------------------------------------------------------------------------------------------------+

Status udar_init(UserDynamicArray **udar)
{
	(*udar) = malloc(sizeof(UserDynamicArray));

	if (!(*udar))
		return DS_ERR_ALLOC;

	(*udar)->buffer = calloc(_DYNAMIC_ARRAY_INIT_SIZE, sizeof(USER_T));

	if (!((*udar)->buffer))
		return DS_ERR_ALLOC;

	(*udar)->capacity = _DYNAMIC_ARRAY_INIT_SIZE;
	(*udar)->growth_rate = _DYNAMIC_ARRAY_GROW_RATE;

	(*udar)->size = 0;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Insertion                                            |
// +-------------------------------------------------------------------------------------------------+

Status udar_insert_front(UserDynamicArray *udar, USER_T value)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (udar_is_full(udar))
	{
		Status st = udar_realloc(udar);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = udar->size; i > 0; i--)
	{
		udar->buffer[i] = udar->buffer[i - 1];
	}

	udar->buffer[0] = value;

	(udar->size)++;

	return DS_OK;
}

Status udar_insert_at(UserDynamicArray *udar, USER_T value, size_t index)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (index > udar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = udar_insert_front(udar, value);

		if (st != DS_OK)
			return st;
	}
	else if (index == udar->size)
	{
		st = udar_insert_back(udar, value);

		if (st != DS_OK)
			return st;
	}
	else
	{
		if (udar_is_full(udar))
		{
			st = udar_realloc(udar);

			if (st != DS_OK)
				return st;
		}

		size_t i;
		for (i = udar->size; i > index; i--)
		{
			udar->buffer[i] = udar->buffer[i - 1];
		}

		udar->buffer[index] = value;

		(udar->size)++;
	}

	return DS_OK;
}

Status udar_insert_back(UserDynamicArray *udar, USER_T value)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (udar_is_full(udar))
	{
		Status st = udar_realloc(udar);

		if (st != DS_OK)
			return st;
	}

	udar->buffer[udar->size] = value;

	(udar->size)++;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

Status udar_remove_front(UserDynamicArray *udar, USER_T *result)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (udar_is_empty(udar))
		return DS_ERR_INVALID_OPERATION;

	*result = udar->buffer[0];

	size_t i;
	for (i = 0; i < udar->size; i++)
	{
		udar->buffer[i] = udar->buffer[i + 1];
	}

	(udar->size)--;

	return DS_OK;
}

Status udar_remove_at(UserDynamicArray *udar, size_t index, USER_T *result)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (udar_is_empty(udar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= udar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = udar_remove_front(udar, result);

		if (st != DS_OK)
			return st;
	}
	else if (index == udar->size - 1)
	{
		st = udar_remove_back(udar, result);

		if (st != DS_OK)
			return st;
	}
	else
	{
		*result = udar->buffer[index];

		size_t i;
		for (i = index; i < udar->size; i++)
		{
			udar->buffer[i] = udar->buffer[i + 1];
		}

		(udar->size)--;
	}

	return DS_OK;
}

Status udar_remove_back(UserDynamicArray *udar, USER_T *result)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (udar_is_empty(udar))
		return DS_ERR_INVALID_OPERATION;

	*result = udar->buffer[udar->size - 1];

	(udar->size)--;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Display                                             |
// +-------------------------------------------------------------------------------------------------+

Status udar_display(UserDynamicArray *udar)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (udar->size == 0)
	{

		printf("\n[ Empty ]\n");

		return DS_OK;
	}

	size_t i;
	for (i = 0; i < udar->size; i++)
	{

		usr_display(udar->buffer[i]);
	}


	return DS_OK;
}

Status udar_display_inline(UserDynamicArray *udar)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	if (udar->size == 0)
	{

		printf("\n[ Empty ]\n");

		return DS_OK;
	}

	size_t i;
	for (i = 0; i < udar->size; i++)
	{

		usr_display_inline(udar->buffer[i]);
	}


	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Resets                                              |
// +-------------------------------------------------------------------------------------------------+

Status udar_delete(UserDynamicArray **udar)
{
	if (*udar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	size_t i;
	for (i = 0; i < (*udar)->size; i++)
	{
		st = usr_delete(&((*udar)->buffer[i]));

		if (st != DS_OK)
			return st;
	}

	free((*udar)->buffer);
	free((*udar));

	(*udar) = NULL;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

size_t udar_cap(UserDynamicArray *udar)
{
	return udar->capacity;
}

size_t udar_size(UserDynamicArray *udar)
{
	return udar->size;
}

bool udar_is_empty(UserDynamicArray *udar)
{
	return udar->size == 0;
}

bool udar_is_full(UserDynamicArray *udar)
{
	return udar->size == udar->capacity;
}

bool udar_exists(UserDynamicArray *udar, USER_T value)
{
	if (udar == NULL)
		return false;

	if (udar_is_empty(udar))
		return false;

	size_t i;
	for (i = 0; i < udar->size; i++)
	{
		if (str_equals(value->name, udar->buffer[i]->name))
			return true;
	}

	return false;
}

Status udar_find(UserDynamicArray *udar, String *name, size_t *result)
{
	if (udar == NULL || name == NULL)
		return DS_ERR_NULL_POINTER;

	*result = 0;

	bool found = false;

	size_t i;
	for (i = 0; i < udar->size; i++)
	{
		if (str_equals(udar->buffer[i]->name, name))
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

Status udar_realloc(UserDynamicArray *udar)
{
	if (udar == NULL)
		return DS_ERR_NULL_POINTER;

	udar->capacity *= udar->growth_rate;

	USER_T *new_buffer = realloc(udar->buffer, sizeof(USER_T) * udar->capacity);

	if (!new_buffer)
	{
		udar->capacity /= udar->growth_rate;

		return DS_ERR_ALLOC;
	}

	udar->buffer = new_buffer;

	return DS_OK;
}
