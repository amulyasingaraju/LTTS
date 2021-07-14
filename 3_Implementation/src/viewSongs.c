#include "library_header.h"

error_t viewSongs()
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
