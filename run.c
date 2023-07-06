#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "data.h"

void printintro(){
    printf("====================================\n");
    printf("  Login information storing system\n");
    printf("====================================\n");
    printf("Press m then e/r/a to edit/remove/add a master user\n");
    printf("Press w then e/r/a to edit/remove/add website login info\n");
    printf("Press q to exit.\n");
}

struct User *assign(char *user, char *pass){
    struct User new;
    struct User *newp;
    *(new.username) = *user;
    *(new.password) = *pass;
    return newp;
}

char *askinput(char *query, int querylen){
    char *input;
    int len;
    if(querylen == 0){
        len = strlen(query);
    }
    else{
        len = querylen;
    }
    printf("%s\n", query);
    fgets(input, len, stdin);
    fflush(stdin);
    return input;
}

Node *login(char *user, char *pass){
    int done = 0;
    while(done != 1){
        if(masterexists(user, pass) == 1){
            done = 1;
            break;
        }
        user = askinput("Enter a username : ", 0);
        pass = askinput("Enter a password : ", 0);

    }
    return findmaster(user, pass);
}

void run(){
    int end = -1;
    while(end == -1){
        char f_input;
        char s_input;
        printintro();
        f_input = askinput("Enter mode (m/w): ", 1)[0];
        s_input = askinput("Enter mode (e/r/a): ", 1)[0];
        switch(f_input){
            case 'm' :
                switch(s_input){
                    case 'e':
                        /*char *user;
                        user = askinput("Enter a username : ", 0);
                        char *pass = askinput("Enter a password : ", 0);
                        */
                        editmaster(login(askinput("Enter a username : ", 0), askinput("Enter a password : ", 0))\
                        , askinput("Enter a new username : ", 0), askinput("Enter a new password : ", 0));
                        break;
                    case 'r':
                        removemaster(login(askinput("Enter a username : ", 0), askinput("Enter a password : ", 0)));
                        break;
                    case 'a':
                    /*
                        struct User *new;
                        *(new->username) = askinput("Enter a new username : ", 0);
                        *(new->password) = askinput("Enter a new password : ", 0);
                        createmaster(new);*/
                        createmaster(assign(askinput("Enter a new username : ", 0), askinput("Enter a new password : ", 0)));
                        break;
                    default:
                        printf("Incorrect input.\n");
                        break;
                }
                break;
            case 'w':
                switch(s_input){
                    case 'e':
                        editwebinfo(login(askinput("Enter a username : ", 0), askinput("Enter a password : ", 0)), \
                        askinput("Enter a website : ", 0), askinput("Enter a new username : ", 0), askinput("Enter a new password : ", 0));
                        break;
                    case 'r':
                        removewebinfo(login(askinput("Enter a username : ", 0), askinput("Enter a password : ", 0)), \
                        askinput("Enter a website : ", 0));
                        break;
                    case 'a':
                        addwebinfo(login(askinput("Enter a username : ", 0), askinput("Enter a password : ", 0)), \
                        askinput("Enter a website : ", 0), askinput("Enter a new username : ", 0), askinput("Enter a new password : ", 0));
                        break;
                    default:
                        printf("Incorrect input.\n");
                        break;
                }
                break;
            case 'q':
                end == 0;
                break;
            default:
                printf("Incorrect input.\n");
                break;
        }
    }
}

int main(){
    run();
    return 0;
}