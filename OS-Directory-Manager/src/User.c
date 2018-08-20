/**
 * @file User.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 17/08/2018
 *
 * @brief Source file for User
 *
 */

#include "User.h"
#include "StringHandler.h"

Status usr_make(User **usr, String *name, String *full_name, String *password, size_t id)
{
	(*usr) = malloc(sizeof(User));

	if (!(*usr))
		return DS_ERR_ALLOC;

	(*usr)->name = name;
	(*usr)->full_name = full_name;
	(*usr)->password = password;

	(*usr)->id = id;

	(*usr)->locked = false;
	(*usr)->root = false;

	return DS_OK;
}

Status usr_display(User *usr)
{
	if (usr == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n ---------- User ---------- \n");
	printf("\n Name      : %s", usr->name->buffer);
	printf("\n Full Name : %s", usr->full_name->buffer);
	printf("\n Password  : %s", usr->password->buffer);
	printf("\n Is root   : %s", (usr->root) ? "yes" : "no");
	printf("\n Is locked : %s", (usr->locked) ? "yes" : "no");
	printf("\n -------------------------- \n");

	return DS_OK;
}

Status usr_display_inline(User *usr)
{
	if (usr == NULL)
		return DS_ERR_NULL_POINTER;

	printf("%-10s\t%-20s\t%-20s\t%s\t%s\n", usr->name->buffer, usr->full_name->buffer,
		usr->password->buffer, (usr->root) ? "yes" : "no", (usr->locked) ? "yes" : "no");

	return DS_OK;
}

// Exclusive use
Status usr_display_noroot(User *usr)
{
	if (usr == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n ---------- User ---------- \n");
	printf("\n Name      : %s", usr->name->buffer);
	printf("\n Full Name : %s", usr->full_name->buffer);
	printf("\n Is root   : %s", (usr->root) ? "yes" : "no");
	printf("\n Is locked : %s", (usr->locked) ? "yes" : "no");
	printf("\n -------------------------- \n");

	return DS_OK;
}

Status usr_delete(User **usr)
{
	if ((*usr) == NULL)
		return DS_ERR_NULL_POINTER;

	str_delete(&((*usr)->name));
	str_delete(&((*usr)->full_name));
	str_delete(&((*usr)->password));
	
	free(*usr);

	*usr = NULL;

	return DS_OK;
}

Status usr_input(User **result, String *user_name, size_t *global_id)
{
	String *name, *full_name, *password;

	Status st = 0;

	// These strings are freed from memory later when the user list is deleted
	st += str_init(&name);
	st += str_init(&full_name);
	st += str_init(&password);

	if (st != DS_OK)
		return st;

	printf("Full name : ");
	st += shandler_getline(full_name);
	printf("Password  : ");
	st += shandler_getline(password);
	st += str_append(name, user_name); // Cheap copy  ;P

	st = usr_make(result, name, full_name, password, *global_id);

	if (st != DS_OK)
		return st;

	(*global_id)++;

	return DS_OK;
}