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

int f_load_dir(DirectoryDynamicArray *dir_list, UserDynamicArray *usr_list)
{
	FILE *file;

	String *text;

	Status st = str_init(&text);

	if (st != DS_OK)
		return st;

	fopen_s(&file, DIR_FILE_NAME, "r");

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
	{
		str_delete(&text);
		return DS_OK;
	}
	
	// Making directories from data
	// Owner and parent are later linked by searching by name in array
	String *name, *time, *owner_s, *parent_s;

	Directory *directory;
	size_t usr_index, dir_index;

	while (text->len > 1)
	{
		st += str_init(&name);
		st += str_init(&time);
		st += str_init(&owner_s);  // Search only -> delete
		st += str_init(&parent_s); // Search only -> delete

		// dir_name
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

		// dir_time
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(time, c);

			if (st != DS_OK)
				return st;
		}

		// owner_name
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(owner_s, c);

			if (st != DS_OK)
				return st;
		}

		// parent_name
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == '\n')
				break;

			st = str_push_char_back(parent_s, c);

			if (st != DS_OK)
				return st;
		}

		// Find owner
		st = udar_find(usr_list, owner_s, &usr_index);

		if (st != DS_OK)
			return st;

		// Find parent
		st = ddar_find(dir_list, parent_s, &dir_index);

		if (st != DS_OK)
			return st;

		// make directory
		st = dir_make(&directory, dir_list->buffer[dir_index], usr_list->buffer[usr_index], name);

		if (st != DS_OK)
			return st;

		// change time
		str_delete(&(directory->time));

		directory->time = time;

		// Add to global list
		st = ddar_insert_back(dir_list, directory);

		if (st != DS_OK)
			return st;

		// Add to parent's list
		st = ddar_insert_back(dir_list->buffer[dir_index]->children, directory);

		if (st != DS_OK)
			return st;

		name = NULL;
		time = NULL;
		str_delete(&owner_s);
		str_delete(&parent_s);
	}

	str_delete(&text);

	return DS_OK;
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

		// Without root being added to the file there shouldn't be a problem when
		// the parent directory is NULL but the ternary operator is kept just for safety
		if (!str_eqstr(dir->name, "/"))
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
	{
		str_delete(&text);
		return DS_OK;
	}

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

		// Add to global list
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