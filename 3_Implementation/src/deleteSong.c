#include "library_header.h"

error_t deleteSongs()
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
