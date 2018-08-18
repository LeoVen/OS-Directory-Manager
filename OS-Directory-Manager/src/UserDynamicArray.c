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

Status dar_init(UserDynamicArray **dar)
{
	(*dar) = malloc(sizeof(UserDynamicArray));

	if (!(*dar))
		return DS_ERR_ALLOC;

	(*dar)->buffer = calloc(_DYNAMIC_ARRAY_INIT_SIZE, sizeof(USER_T));

	if (!((*dar)->buffer))
		return DS_ERR_ALLOC;

	(*dar)->capacity = _DYNAMIC_ARRAY_INIT_SIZE;
	(*dar)->growth_rate = _DYNAMIC_ARRAY_GROW_RATE;

	(*dar)->size = 0;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Insertion                                            |
// +-------------------------------------------------------------------------------------------------+

Status dar_insert_front(UserDynamicArray *dar, USER_T value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_full(dar))
	{
		Status st = dar_realloc(dar);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = dar->size; i > 0; i--)
	{
		dar->buffer[i] = dar->buffer[i - 1];
	}

	dar->buffer[0] = value;

	(dar->size)++;

	return DS_OK;
}

Status dar_insert_at(UserDynamicArray *dar, USER_T value, size_t index)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (index > dar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = dar_insert_front(dar, value);

		if (st != DS_OK)
			return st;
	}
	else if (index == dar->size)
	{
		st = dar_insert_back(dar, value);

		if (st != DS_OK)
			return st;
	}
	else
	{
		if (dar_is_full(dar))
		{
			st = dar_realloc(dar);

			if (st != DS_OK)
				return st;
		}

		size_t i;
		for (i = dar->size; i > index; i--)
		{
			dar->buffer[i] = dar->buffer[i - 1];
		}

		dar->buffer[index] = value;

		(dar->size)++;
	}

	return DS_OK;
}

Status dar_insert_back(UserDynamicArray *dar, USER_T value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_full(dar))
	{
		Status st = dar_realloc(dar);

		if (st != DS_OK)
			return st;
	}

	dar->buffer[dar->size] = value;

	(dar->size)++;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

Status dar_remove_front(UserDynamicArray *dar, USER_T *result)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		dar->buffer[i] = dar->buffer[i + 1];
	}

	(dar->size)--;

	return DS_OK;
}

Status dar_remove_at(UserDynamicArray *dar, size_t index, USER_T *result)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = dar_remove_front(dar, result);

		if (st != DS_OK)
			return st;
	}
	else if (index == dar->size - 1)
	{
		st = dar_remove_back(dar, result);

		if (st != DS_OK)
			return st;
	}
	else
	{
		*result = dar->buffer[index];

		size_t i;
		for (i = index; i < dar->size; i++)
		{
			dar->buffer[i] = dar->buffer[i + 1];
		}

		(dar->size)--;
	}

	return DS_OK;
}

Status dar_remove_back(UserDynamicArray *dar, USER_T *result)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[dar->size - 1];

	(dar->size)--;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Display                                             |
// +-------------------------------------------------------------------------------------------------+

Status dar_display(UserDynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar->size == 0)
	{

		printf("\n[ Empty ]\n");

		return DS_OK;
	}

	size_t i;
	for (i = 0; i < dar->size; i++)
	{

		usr_display(dar->buffer[i]);
	}


	return DS_OK;
}

Status dar_display_raw(UserDynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n");

	if (dar_is_empty(dar))
		return DS_OK;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{

		printf("%d ", dar->buffer[i]);
	}

	printf("\n");

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Resets                                              |
// +-------------------------------------------------------------------------------------------------+

Status dar_delete(UserDynamicArray **dar)
{
	if (*dar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	size_t i;
	for (i = 0; i < (*dar)->size; i++)
	{
		st = usr_delete(&((*dar)->buffer[i]));

		if (st != DS_OK)
			return st;
	}

	free((*dar)->buffer);
	free((*dar));

	(*dar) = NULL;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

Status dar_get(UserDynamicArray *dar, size_t index, USER_T *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	*result = dar->buffer[index];

	return DS_OK;
}

size_t dar_cap(UserDynamicArray *dar)
{
	return dar->capacity;
}

size_t dar_size(UserDynamicArray *dar)
{
	return dar->size;
}

bool dar_is_empty(UserDynamicArray *dar)
{
	return dar->size == 0;
}

bool dar_is_full(UserDynamicArray *dar)
{
	return dar->size == dar->capacity;
}

bool dar_exists(UserDynamicArray *dar, USER_T value)
{
	if (dar == NULL)
		return false;

	if (dar_is_empty(dar))
		return false;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (str_equals(value->name, dar->buffer[i]->name))
			return true;
	}

	return false;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Buffer                                               |
// +-------------------------------------------------------------------------------------------------+

Status dar_realloc(UserDynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	dar->capacity *= dar->growth_rate;

	USER_T *new_buffer = realloc(dar->buffer, sizeof(USER_T) * dar->capacity);

	if (!new_buffer)
	{
		dar->capacity /= dar->growth_rate;

		return DS_ERR_ALLOC;
	}

	dar->buffer = new_buffer;

	return DS_OK;
}