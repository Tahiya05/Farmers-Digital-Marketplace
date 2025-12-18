#ifndef USER_H
#define USER_H

typedef struct {
    int id;
    char username[50];
    char phonenum[50];
    char password[20];
    int type;
} user;

void farmerMenu();
void farmerRegister();
int farmerLogin();
void consumerMenu();

#endif
