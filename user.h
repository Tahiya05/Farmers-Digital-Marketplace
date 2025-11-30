#ifndef USER_H
#define USER_H

typedef struct {
    char username[50];
    char phonenum[50];
    char password[20];
    int type;
    char status[20];
} user;

#endif
