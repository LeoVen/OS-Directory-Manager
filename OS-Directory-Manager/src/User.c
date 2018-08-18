/**
 * @file User.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 17/08/2018
 *
 * @brief Source file for User
 *
 */

#include "User.h"

Status usr_make(User **usr, String **name, String **full_name, String **password, size_t id)
{
	(*usr) = malloc(sizeof(User));

	if (!(*usr))
		return DS_ERR_ALLOC;

	(*usr)->name = (*name);
	(*usr)->full_name = (*full_name);
	(*usr)->password = (*password);

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
	printf("\n Is locked : %s", (usr->root) ? "yes" : "no");
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