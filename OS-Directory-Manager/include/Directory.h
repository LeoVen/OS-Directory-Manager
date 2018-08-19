/**
 * @file Directory.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 17/08/2018
 *
 * @brief Directory header file
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "User.h"
#include "SString.h"

	typedef struct Directory
	{
		struct String *name;
		struct String *time;
		struct User *owner;
		struct Directory *parent;
		struct DirectoryDynamicArray *children;
	} Directory;

	Status dir_make(Directory **dir, Directory *parent, User *usr, String *name);

	Status dir_display(Directory *dir);
	Status dir_display_inline(Directory *dir);

	Status dir_delete(Directory **dir);



#ifdef __cplusplus
}
#endif