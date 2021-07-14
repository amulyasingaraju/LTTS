/**
 * @file library_header.h
 * @author Singaraju Amulya (amulyanets@gmail.com)
 * @brief Songbook Management System
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define MAX_YR  9999  ///<Maximum year
#define MIN_YR  1900  ///<Minimum year
#define MAX_SIZE_USER_NAME 30 ///<Maximum Username Size
#define MAX_SIZE_PASSWORD  20 ///<Minimum Username Size
#define FILE_NAME  "SongBook.bin"


/// Defined For Songs
#define MAX_SONG_NAME   50 //Maximum song name
#define MAX_COMPOSER_NAME 50 //Maximum composer name
#define MAX_GENRE_NAME 50 //Maximum genre name
#define FILE_HEADER_SIZE  sizeof(sFileHeader)


#ifndef _LIBRARY_HEADER_
#define _LIBRARY_HEADER_

#ifdef _WIN32               ///Defining CLS for linux and Windows
    #define CLS "cls"
#elif __linux__
    #define CLS "clear"
#endif


/**
 * @brief For error Handling
 * 
 */
typedef enum error_t
{
    FILE_NOT_FOUND=-1,
	FAILURE=0,
    SUCCESS=1,
    NOT_FOUND=2
	
}error_t;

/**
 * @brief Structure for Date
 * 
 */
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

/**
 * @brief Username and Password for file
 * 
 */
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;


/**
 * @brief Structure for song information
 * 
 */
typedef struct
{
    unsigned int songs_id; // declaring integer datatype
    char songName[MAX_SONG_NAME];// declaring character datatype
    char composerName[MAX_COMPOSER_NAME];// declaring character datatype
    char genreName[MAX_GENRE_NAME];// declaring character datatype
    Date songPracDate;// declaring integer datatype
} s_SongsInfo;


/**
 * @brief  function creates the file if not exist and copies the default password (“abcde”) in file header structure.
 * 
 * @return error_t 
 */
error_t initialise();


/**
 * @brief This function verifies that a file has been created or not. If the file exists, the function return SUCCESS otherwise returns FILE_NOT_FOUND.
 * 
 * @param path 
 * @return error_t 
 */
error_t isFileExists(const char *path);


/**
 * @brief It prints the message on the top of the console and prints the welcome message.
 * 
 * @param message 
 * @return error_t 
 */

error_t welcomeMessage();


/**
 * @brief It validates the user name and check any invalid character is present or not
 * 
 * @param name 
 * @return error_t 
 */
error_t isNameValid(const char *name);


/**
 * @brief It take Date and check whether it is a valid date or not 
 * 
 * @param validDate 
 * @return error_t 
 */
error_t isValidDate(Date *validDate);


/**
 * @brief Displays the Main Menu for opearations
 * 
 * @param FILE_NAME 
 * @return error_t 
 */
error_t menu(const char *FILE_NAME);

/**
 * @brief Function to add song ID,name,composer name, genre and date of last practice
 * 
 * @param FILE_NAME 
 * @return error_t 
 */
error_t addSongInDataBase(const char *FILE_NAME);

/**
 * @brief Searches for the song 
 * 
 * @param FILE_NAME 
 * @return error_t 
 */
error_t searchSongs(const char *FILE_NAME);

/**
 * @brief Displays all songs details
 * 
 * @param FILE_NAME 
 * @return error_t 
 */
error_t viewSongs(const char *FILE_NAME);

/**
 * @brief It deletes song by taking its ID
 * 
 * @param FILE_NAME 
 * @return error_t 
 */
error_t deleteSongs(const char *FILE_NAME);

/**
 * @brief To update the username and password
 * 
 * @param FILE_NAME 
 * @return error_t 
 */
error_t updateCredential(const char *FILE_NAME);

/**
 * @brief User logs in to system by entering the username and password
 * 
 * @param FILE_NAME 
 * @param username 
 * @param password 
 * @return error_t 
 */
error_t login();

/**
 * @Checking for valid date
 * 
 * @param d 
 * @return Date 
 */
int isValidDate(Date *validDate);

/**
 * @brief Chech for leap year 
 * 
 * @param year 
 * @return int 
 */
int IsLeapYear(int year);
#endif
