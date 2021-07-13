#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "SongBook.bin"
// Macro related to the songs info
#define MAX_SONG_NAME   50
#define MAX_COMPOSER_NAME 50
#define MAX_GENRE_NAME 50
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//structure to store date
typedef struct
{
    int yyyy;// variable to store year
    int mm;// variable to store month
    int dd;// variable to store day
} Date;
typedef struct//to call the program
{
    char username[MAX_SIZE_USER_NAME];//username
    char password[MAX_SIZE_PASSWORD];//password
} sFileHeader;
typedef struct// to call the program
{
    unsigned int songs_id; // declaring integer datatype
    char songName[MAX_SONG_NAME];// declaring character datatype
    char composerName[MAX_COMPOSER_NAME];// declaring character datatype
    char genreName[MAX_GENRE_NAME];// declaring character datatype
    Date songPracDate;// declaring integer datatype
} s_SongsInfo;
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate space needed to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
void headMessage(const char *message)
{
    system("cls");
    printf("\n\t\t\tSong Book Project in C");
    printMessageCenter(message); //Print message
}
void welcomeMessage()
{
    headMessage("\nAmulya's SongBook");
    printf("\n\n\n\t\t\t WELCOME TO YOUR SONGBOOK");
    printf("\n\n\n\t\t\t Enter any key to continue.....");//Print message
    getch();
}
int isNameValid(const char *name) //Check whether name entered is valid (alphabets only)
{
    int validName = 1; 
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
// Add songs to database
void addSongInDataBase()
{
    int days;
    s_SongsInfo addSongInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    //Prints details about data being collected from the user
    headMessage("ADD NEW SONGS");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tSONG ID = ");
    fflush(stdin);
    scanf("%u",&addSongInfoInDataBase.songs_id);
    do
    {
        printf("\n\t\t\tSong Name  = ");
        fflush(stdin);
        fgets(addSongInfoInDataBase.songName,MAX_SONG_NAME,stdin);
        status = isNameValid(addSongInfoInDataBase.songName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tComposer Name  = ");
        fflush(stdin);
        fgets(addSongInfoInDataBase.composerName,MAX_COMPOSER_NAME,stdin);
        status = isNameValid(addSongInfoInDataBase.composerName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tGenre Name  = ");
        fflush(stdin);
        fgets(addSongInfoInDataBase.genreName,MAX_GENRE_NAME,stdin);
        status = isNameValid(addSongInfoInDataBase.genreName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date last practiced in format (day/month/year): ");
        scanf("%d/%d/%d",&addSongInfoInDataBase.songPracDate.dd,&addSongInfoInDataBase.songPracDate.mm,&addSongInfoInDataBase.songPracDate.yyyy);
        //check date validity
        status = isValidDate(&addSongInfoInDataBase.songPracDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    fwrite(&addSongInfoInDataBase,sizeof(addSongInfoInDataBase), 1, fp);
    fclose(fp);
}
// function to search for songs
void searchSongs()
{
    int found = 0;
    char songName[MAX_SONG_NAME] = {0};
    s_SongsInfo addSongInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH SONGS");
    //put the control on songs detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Song Name to search:");
    fflush(stdin);
    fgets(songName,MAX_SONG_NAME,stdin);
    while (fread (&addSongInfoInDataBase, sizeof(addSongInfoInDataBase), 1, fp))
    {
        if(!strcmp(addSongInfoInDataBase.songName, songName))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tSong id = %u\n",addSongInfoInDataBase.songs_id);
        printf("\t\t\tSong name = %s",addSongInfoInDataBase.songName);
        printf("\t\t\tSong composerName = %s",addSongInfoInDataBase.composerName);
        printf("\t\t\tSong Genre = %s",addSongInfoInDataBase.genreName);
        printf("\t\t\tSong last practiced date(day/month/year) =  (%d/%d/%d)",addSongInfoInDataBase.songPracDate.dd,
               addSongInfoInDataBase.songPracDate.mm, addSongInfoInDataBase.songPracDate.yyyy);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getchar();
}
// view songs function
void viewSongs()
{
    int found = 0;
    char songName[MAX_SONG_NAME] = {0};
    s_SongsInfo addSongInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countSong = 1;
    headMessage("VIEW SONGS DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&addSongInfoInDataBase, sizeof(addSongInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\tSong Count = %d\n\n",countSong); //prints song data that was collected from user
        printf("\t\t\tSong id = %u",addSongInfoInDataBase.songs_id);
        printf("\n\t\t\tSong name = %s",addSongInfoInDataBase.songName);
        printf("\t\t\tSong composerName = %s",addSongInfoInDataBase.composerName);
        printf("\t\t\tSong Genre = %s",addSongInfoInDataBase.genreName);
        printf("\t\t\tSong last practiced date(day/month/year) =  (%d/%d/%d)\n\n",addSongInfoInDataBase.songPracDate.dd,
               addSongInfoInDataBase.songPracDate.mm, addSongInfoInDataBase.songPracDate.yyyy);
        found = 1;
        ++countSong;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// delete function
void deleteSongs()
{
    int found = 0;
    int songDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char songName[MAX_SONG_NAME] = {0};
    s_SongsInfo addSongInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("Delete Songs Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter Song ID to be deleted:");
    scanf("%d",&songDelete);
    while (fread (&addSongInfoInDataBase, sizeof(addSongInfoInDataBase), 1, fp))
    {
        if(addSongInfoInDataBase.songs_id != songDelete)
        {
            fwrite(&addSongInfoInDataBase,sizeof(addSongInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
void updateCredential(void) //function to change the credentials of the user 
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credentials");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}
void menu() //main menu being displayed to the user
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Songs");
        printf("\n\t\t\t2.Search Songs");
        printf("\n\t\t\t3.View Songs");
        printf("\n\t\t\t4.Delete Song");
        printf("\n\t\t\t5.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            addSongInDataBase();
            break;
        case 2:
            searchSongs();
            break;
        case 3:
            viewSongs();
            break;
        case 4:
            deleteSongs();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT! Please Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
//login password
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("\nLogin");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="abcdef\n"; //default username
    const char defaultPassword[] ="abcdef\n"; //default password
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}