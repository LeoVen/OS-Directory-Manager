/**
 * @file Core.h
 *
 * @author Leonardo Vencovsky       (https://github.com/LeoVen)
 * @author Eduardo Vencovsky        (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza        (https://github.com/pinazza)
 * @author Erick Domingos Modenez
 *
 * @date 17/08/2018
 *
 * @brief Main header file
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <Windows.h>

#define MACHINE_NAME "ubuntu"

#define CLEAR_SCREEN system("cls")
//#define CLEAR_SCREEN system("clear")

	/**
	 * @brief Status code returned by functions
	 *
	 * These status codes are returned by almost all functions in the project.
	 * They are used to prevent unwanted results when a function fails and can
	 * also be used by the user to control his/her own program flow.
	 *
	 */
	typedef enum Status {
		DS_OK                        =  0, /**< Returned by a function when all operations were successful */
		DS_ERR_INVALID_POSITION      =  1, /**< When an invalid position is passed as argument */
		DS_ERR_INVALID_OPERATION     =  2, /**< When an invalid operation is made (e.g. remove element of an empty list ) */
		DS_ERR_INVALID_SIZE          =  3, /**< When an invalid size is given */
		DS_ERR_NOT_FOUND             =  4, /**< When a search fails to find a value */
		DS_ERR_ALLOC                 =  5, /**< When a function fails to allocate memory  */
		DS_ERR_UNEXPECTED_RESULT     =  6, /**< When an unexpected result happens. Contact developers. */
		DS_ERR_ITER                  =  7, /**< When an iteration reaches an unexpected value */
		DS_ERR_NULL_POINTER          =  8, /**< When a @c NULL parameter is passed to a function */
		DS_ERR_FULL                  =  9, /**< When a structure reaches its maximum capacity */
		DS_ERR_INVALID_ARGUMENT      = 10  /**< When an argument passed is invalid for that operation */
	} Status;
	
	char * status_repr(Status status);

	void print_status_repr(Status status);

	// Tests.c
	int SINGLE_TESTS(void);
	int USER_ARRAY_TESTS(void);
	int DIRECTORY_ARRAY_TESTS(void);

	// Others.c
	void final_shutdown(void);
	void help(void);
	void copyright(void);

#ifdef __cplusplus
}
#endif