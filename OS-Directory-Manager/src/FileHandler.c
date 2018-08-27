/**
 * @file FileHandler.c
 *
 * @author Leonardo Vencovsky       (https://github.com/LeoVen)
 * @author Eduardo Vencovsky        (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza        (https://github.com/pinazza)
 * @author Erick Domingos Modenez
 *
 * @date 22/08/2018
 *
 * @brief Handling Save/Load functions
 *
 */

#include "FileHandler.h"

int f_load_dir(DirectoryDynamicArray *array)
{

	return 0;
}

/**
 * The CSV is saved as:
 *
 * dir_name, dir_time, owner_name, parent_name (0 if NULL)
 *
 */
int f_save_dir(DirectoryDynamicArray *array)
{
	FILE *file;
	fopen_s(&file, DIR_FILE_NAME, "w");

	if (!file)
		return DS_ERR_NULL_POINTER;

	Directory *dir;

	size_t i;
	for (i = 0; i < array->size; i++)
	{
		dir = array->buffer[i];

		fprintf(file, "%s,%s,%s,%s\n", dir->name->buffer, dir->time->buffer,
			dir->owner->name->buffer, (dir->parent) ? dir->parent->name->buffer : "0");
	}

	fclose(file);

	return DS_OK;
}

int f_load_usr(UserDynamicArray *array)
{
	FILE *file;

	String *text;

	Status st = str_init(&text);

	if (st != DS_OK)
		return st;

	fopen_s(&file, USR_FILE_NAME, "r");

	if (!file)
		return DS_ERR_NULL_POINTER;

	char c;


	while (1)
	{
		c = fgetc(file);

		if (c == EOF)
			break;
		
		st = str_push_char_back(text, c);

		if (st != DS_OK)
			return st;
	}

	fclose(file);

	if (text->len == 0)
		return DS_OK;

	// Making users from data

	User *user;
	String *name, *full_name, *password, *id_s;
	size_t id;
	bool root, locked;

	while (text->len > 1)
	{
		st += str_init(&name);
		st += str_init(&full_name);
		st += str_init(&password);
		st += str_init(&id_s);

		if (st != DS_OK)
			return st;

		// name
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(name, c);

			if (st != DS_OK)
				return st;
		}

		// full_name
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(full_name, c);

			if (st != DS_OK)
				return st;
		}

		// password
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(password, c);

			if (st != DS_OK)
				return st;
		}

		// user id
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(id_s, c);

			if (st != DS_OK)
				return st;
		}

		// is root
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			// should be only one character -- 0 or 1
			if (c == '1')
				root = true;
			else
				root = false;
		}

		// is locked
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == '\n')
				break;

			// should be only one character -- 0 or 1
			if (c == '1')
				locked = true;
			else
				locked = false;
		}

		id = (size_t)atoi(id_s->buffer);

		// make user and insert into the array
		st = usr_make(&user, name, full_name, password, id);
		
		if (st != DS_OK)
			return st;

		user->locked = locked;
		user->root = root;

		st = udar_insert_back(array, user);

		if (st != DS_OK)
			return st;

		// Reset
		user = NULL;
		name = NULL;
		full_name = NULL;
		password = NULL;
		str_delete(&id_s);
	}

	str_delete(&name);
	str_delete(&full_name);
	str_delete(&password);

	str_delete(&text);

	return 0;
}

/**
 * The CSV is saved as:
 *
 * usr_name, usr_fullname, usr_password, usr_id, is_root (0:false, 1:true), is_locked (0:false, 1:true)
 *
 */
int f_save_usr(UserDynamicArray *array)
{
	FILE *file;
	fopen_s(&file, USR_FILE_NAME, "w");

	if (!file)
		return DS_ERR_NULL_POINTER;

	User *usr;

	size_t i;
	for (i = 0; i < array->size; i++)
	{
		usr = array->buffer[i];

		if (!str_eqstr(usr->name, "root"))
			fprintf(file, "%s,%s,%s,%zu,%c,%c\n", usr->name->buffer, usr->full_name->buffer,
				usr->password->buffer, usr->id, (usr->root) ? '1' : '0', (usr->locked) ? '1' : '0');
	}

	fclose(file);

	return DS_OK;
}