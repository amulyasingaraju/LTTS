#include "library_header.h"

error_t searchSongs()
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
