/**
 * @file FileHandler.h
 *
 * @author Leonardo Vencovsky       (https://github.com/LeoVen)
 * @author Eduardo Vencovsky        (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza        (https://github.com/pinazza)
 * @author Erick Domingos Modenez
 *
 * @date 22/08/2018
 *
 * @brief Handling Save/Load header
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "DirectoryDynamicArray.h"
#include "UserDynamicArray.h"

#define DIR_FILE_NAME "directory.txt"
#define USR_FILE_NAME "user.txt"

	int f_load_dir(DirectoryDynamicArray *array);
	int f_save_dir(DirectoryDynamicArray *array);

	int f_load_usr(UserDynamicArray *array);
	int f_save_usr(UserDynamicArray *array);

#ifdef __cplusplus
}
#endif