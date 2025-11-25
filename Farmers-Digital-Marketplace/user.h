#ifndef USER_H
#define USER_H

typedef struct {
    int id;
    char name[50];
    char email[50];
    char password[20];
    int type;
    int status;
} user;

#endif
