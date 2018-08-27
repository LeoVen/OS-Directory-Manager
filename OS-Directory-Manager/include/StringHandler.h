/**
 * @file StringHandler.h
 *
 * @author Leonardo Vencovsky       (https://github.com/LeoVen)
 * @author Eduardo Vencovsky        (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza        (https://github.com/pinazza)
 * @author Erick Domingos Modenez
 *
 * @date 18/08/2018
 *
 * @brief Header file for @c DirectoryDynamicArray implementations
 *
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "Core.h"
#include "User.h"
#include "UserDynamicArray.h"
#include "Directory.h"
#include "DirectoryDynamicArray.h"

	Status shandler_getline(String *string);

	Status shandler_current_time(String **curr_time);

	Status shandler_current_date(String **curr_date);
	Status shandler_current_hour(String **curr_hour);

	bool shandler_login(DirectoryDynamicArray *dirs, UserDynamicArray *users, User **curr_user, Directory **curr_dir);
	Status shandler_make_prompt(User *curr_user, Directory *curr_dir, String *result);
	Status shandler_parse_input(String *input, String *cmd1, String *cmd2);


#ifdef __cplusplus
}
#endif