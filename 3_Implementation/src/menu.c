#include "library_header.h"

error_t menu() //main menu being displayed to the user
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
