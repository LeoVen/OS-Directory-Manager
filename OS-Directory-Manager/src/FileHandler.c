/**
 * @file FileHandler.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
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

		fprintf(file, "%s,%s,%s,%zu,%c,%c\n", usr->name->buffer, usr->full_name->buffer,
			usr->password->buffer, usr->id, (usr->root) ? '1' : '0', (usr->locked) ? '1' : '0');
	}

	fclose(file);

	return DS_OK;
}