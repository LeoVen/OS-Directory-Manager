/**
* @file DirectoryDynamicArray.h
*
* @author Leonardo Vencovsky (https://github.com/LeoVen)
* @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
* @author Guilherme Pinazza  (https://github.com/pinazza)
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

	Status shandler_current_time(String **curr_time);

	Status shandler_current_date(String **curr_date);
	Status shandler_current_hour(String **curr_hour);

	bool shandler_login(UserDynamicArray *users);


#ifdef __cplusplus
}
#endif