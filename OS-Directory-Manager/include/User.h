/**
 * @file User.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 17/08/2018
 *
 * @brief User header file
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Core.h"
#include "SString.h"

	typedef struct User
	{
		struct String *name;
		struct String *full_name;
		struct String *password;
		size_t id;
		bool root;
		bool locked;
	} User;

	Status usr_make(User **usr, String *name, String *full_name, String *password, size_t id);

	Status usr_display(User *usr);
	Status usr_display_inline(User *usr);

	Status usr_delete(User **usr);

#ifdef __cplusplus
}
#endif