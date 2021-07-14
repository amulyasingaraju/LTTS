#include "library_header.h"

error_t addSongInDataBase()
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
