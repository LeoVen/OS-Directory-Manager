/**
 * @file UserDynamicArray.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 20/03/2018
 *
 * @brief Source file for @c UserDynamicArray implementations in C
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

	(*dar)->buffer = calloc(_DYNAMIC_ARRAY_INIT_SIZE, sizeof(int));

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

Status dar_insert_front(UserDynamicArray *dar, int value)
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

Status dar_insert_at(UserDynamicArray *dar, int value, size_t index)
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

Status dar_insert_back(UserDynamicArray *dar, int value)
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

Status dar_update(UserDynamicArray *dar, int value, size_t index)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	dar->buffer[index] = value;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

//Status dar_remove(UserDynamicArray *dar, size_t from, size_t to)

Status dar_remove_front(UserDynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		dar->buffer[i] = dar->buffer[i + 1];
	}

	(dar->size)--;

	return DS_OK;
}

Status dar_remove_at(UserDynamicArray *dar, size_t index)
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
		st = dar_remove_front(dar);

		if (st != DS_OK)
			return st;
	}
	else if (index == dar->size - 1)
	{
		st = dar_remove_back(dar);

		if (st != DS_OK)
			return st;
	}
	else
	{
		size_t i;
		for (i = index; i < dar->size; i++)
		{
			dar->buffer[i] = dar->buffer[i + 1];
		}

		(dar->size)--;
	}

	return DS_OK;
}

Status dar_remove_back(UserDynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

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

		printf("\n[ Empty ] \n");

		return DS_OK;
	}

	printf("\nDynamicArray\n[ ");

	size_t i;
	for (i = 0; i < dar->size - 1; i++)
	{

		printf("%d, ", dar->buffer[i]);
	}

	printf("%d", dar->buffer[dar->size - 1]);

	printf(" ]\n");

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

	free((*dar)->buffer);
	free((*dar));

	(*dar) = NULL;

	return DS_OK;
}

Status dar_erase(UserDynamicArray **dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = dar_delete(dar);

	if (st != DS_OK)
		return st;

	st = dar_init(dar);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

Status dar_get(UserDynamicArray *dar, size_t index, int *result)
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

Status dar_find_max(UserDynamicArray *dar, int *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] > *result)
			*result = dar->buffer[i];
	}

	return DS_OK;
}

Status dar_find_min(UserDynamicArray *dar, int *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] < *result)
			*result = dar->buffer[i];
	}

	return DS_OK;
}

Status dar_find_max_pos(UserDynamicArray *dar, size_t *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] > dar->buffer[(*result)])
			*result = i;
	}

	return DS_OK;
}

Status dar_find_min_pos(UserDynamicArray *dar, size_t *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] < dar->buffer[(*result)])
			*result = i;
	}

	return DS_OK;
}

Status dar_frequency(UserDynamicArray *dar, int value, size_t *frequency)
{
	*frequency = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
			(*frequency)++;
	}

	return DS_OK;
}

Status dar_contains(UserDynamicArray *dar, int value, bool *result)
{
	*result = false;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
		{
			*result = true;

			return DS_OK;
		}
	}

	return DS_OK;
}

bool dar_exists(UserDynamicArray *dar, int value)
{
	if (dar == NULL)
		return false;

	if (dar_is_empty(dar))
		return false;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
			return true;
	}

	return false;
}

Status dar_find_occurrance_first(UserDynamicArray *dar, int value, size_t *position)
{
	*position = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
		{
			*position = i;

			return DS_OK;
		}
	}

	return DS_ERR_NOT_FOUND;
}

Status dar_find_occurrance_last(UserDynamicArray *dar, int value, size_t *position)
{
	*position = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	bool found = false;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
		{
			*position = i;

			found = true;
		}
	}

	if (found)
		return DS_OK;

	return DS_ERR_NOT_FOUND;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Buffer                                               |
// +-------------------------------------------------------------------------------------------------+

Status dar_grow(UserDynamicArray *dar, size_t size)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar->capacity >= size)
		return DS_OK;

	size_t temp_cap = dar->capacity;

	while (dar->capacity < size)
	{
		dar->capacity *= dar->growth_rate;
	}

	int *new_buffer = realloc(dar->buffer, sizeof(int) * dar->capacity);

	if (!new_buffer)
	{
		dar->capacity = temp_cap;

		return DS_OK;
	}

	dar->buffer = new_buffer;

	return DS_OK;
}

Status dar_realloc(UserDynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	dar->capacity *= dar->growth_rate;

	int *new_buffer = realloc(dar->buffer, sizeof(int) * dar->capacity);

	if (!new_buffer)
	{
		dar->capacity /= dar->growth_rate;

		return DS_ERR_ALLOC;
	}

	dar->buffer = new_buffer;

	return DS_OK;
}
