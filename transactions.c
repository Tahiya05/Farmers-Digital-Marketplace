void feedback(int consumerID){
    char cmnt[200];
    int rating;

    printf("Rate your experience (1-5): ");
    if(scanf("%d",&rating)!=1 || rating<1 || rating>5){
        clearInputBuffer();
        printf("Invalid rating! Please enter a number between 1 and 5.\n");
        return;
    }

    clearInputBuffer();

    printf("Write Your Feedback: ");
    getchar();
    fgets(cmnt,sizeof(cmnt),stdin);
    cmnt[strcspn(cmnt,"\n")]='\0';

    FILE *fp = fopen("feedback.txt","a");

    if(!fp){
        printf("Error!\n");
        return;
    }

    else
    fprintf(fp,"%d|%d|%s\n", consumerID, rating, cmnt);
    fclose(fp);

    printf("\nThank You For Your Feedback!\n");
}
