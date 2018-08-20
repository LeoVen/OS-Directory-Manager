/**
 * @file Directory.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 18/08/2018
 *
 * @brief Source file for Directory
 *
 */

#include "Directory.h"

Status dir_make(Directory **dir, Directory *parent, User *usr, String *name)
{
	(*dir) = malloc(sizeof(Directory));

	if (!(*dir))
		return DS_ERR_ALLOC;

	Status st = ddar_init(&((*dir)->children));

	if (st != DS_OK)
		return st;

	st = shandler_current_time(&((*dir)->time));

	if (st != DS_OK)
		return st;

	(*dir)->parent = parent;

	(*dir)->owner = usr;

	(*dir)->name = name;

	return DS_OK;
}

Status dir_display(Directory *dir)
{
	if (dir == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n ---------- Directory ---------- \n");
	printf("\n Name      : %s", dir->name->buffer);
	printf("\n Parent    : %s", (dir->parent == NULL) ? " " : dir->parent->name->buffer);
	printf("\n Owner     : %s", dir->owner->name->buffer);
	printf("\n Time      : %s", dir->time->buffer);
	printf("\n ------------------------------- \n");

	return DS_OK;
}

Status dir_display_inline(Directory *dir)
{
	if (dir == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n ---------- Directory ---------- \n");
	printf("\n Name      : %s", dir->name->buffer);
	printf("\n Parent    : %s", (dir->parent == NULL) ? " " : dir->parent->name->buffer);
	printf("\n Owner     : %s", dir->owner->name->buffer);
	printf("\n Time      : %s", dir->time->buffer);
	printf("\n ------------------------------- \n");

	return DS_OK;
}

Status dir_delete(Directory **dir)
{
	if ((*dir) == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = ddar_delete(&((*dir)->children));

	if (st != DS_OK)
		return st;

	st += str_delete(&((*dir)->name));
	st += str_delete(&((*dir)->time));

	if (st != DS_OK)
		return st;

	free((*dir));

	*dir = NULL;

	return DS_OK;
}