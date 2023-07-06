#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "data.h"
/*
struct website_login{
    char *website;
    char *username;
    char *password;
};

struct User{
    char *username;
    char *password;
    struct website_login *list;
};

typedef struct node{
    struct User *entry;
    struct node *next;
}Node;
*/
Node masterlist;
Node *last;
Node *first;

void createmaster(struct User *new){
    if(!last){
        *masterlist.entry = *new;
        *last = masterlist;
        *first = masterlist;
    }
    else{
        Node newuser;
        *newuser.entry = *new;
        *(*last).next = newuser;
        *last = newuser;
    }
}

int masterexists(char *user, char *pass){
    Node *curr = first;
    while(curr){
        /* (*(*curr).entry).username == *user && (*(*curr).entry).password == *pass */
        if(curr->entry->username == user && curr->entry->password == pass){
            return 1;
        }
        curr = curr->next;
    }    
    return 0;
}

int existinguser(char *user){
    Node *curr = first;
    while(curr){
        if((*(*curr).entry).username == user){
            return 1;
        }
        curr = curr->next;
    } 
    return 0;
}

// check how to use ferror to use findmaster for createmaster
Node *findmaster(char *user, char *pass){
    Node *curr = first;
    while(curr){
        if((*(*curr).entry).username == user && (*(*curr).entry).password == pass){
            return curr;
        }
        curr = curr->next;
    }
    fprintf(stderr, "Failed to find the thing");
    exit(1);
}

void removemaster(Node *delete){
    Node *curr = first;
    Node *prev = first;
    int found;
    found = -1;
    while(curr){
        if((*(*curr).entry).username == (*(*delete).entry).username){
            found = 0;
            if(prev == first){
                first = first->next;
                if(last == prev){
                    last == prev->next;
                }
            }
            else{
                prev->next = curr->next;
            }
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if(found == -1){
        fprintf(stderr, "Failed to find the thing");
        exit(1);
    }
}

void editmaster(Node *edit, char *user, char *pass){
    edit->entry->password = pass;
    edit->entry->username = user;
}

void addwebinfo(Node *master, char *web, char *user, char *pass){
    struct website_login new;
    new.password = pass;
    new.username = user;
    new.website = web;
    if(strlen(master->entry->list[0].website) == 1){
        master->entry->list[0].website = web;
        master->entry->list[0].username = user;
        master->entry->list[0].password = pass;
    }
    else{
        struct website_login *newlist = malloc(sizeof(master->entry->list) + sizeof(struct website_login));
        for(int i=0; i<(sizeof(master->entry->list)/sizeof(struct website_login)); i++){
            newlist[i] = master->entry->list[i];
        }
        newlist[sizeof(master->entry->list)/sizeof(struct website_login)] = new;
        free(master->entry->list);
        master->entry->list = newlist;
    }
}

void editwebinfo(Node *master, char *web, char *user, char *pass){
    struct website_login new;
    new.password = pass;
    new.username = user;
    new.website = web;
    if(strlen(master->entry->list[0].website) == 1){
        fprintf(stderr, "Web info does not exist");
        exit(1);
    }
    for(int i=0; i<(sizeof(master->entry->list)/sizeof(struct website_login)); i++){
        if(master->entry->list[i].website == web){
            master->entry->list[i].password = pass;
            master->entry->list[i].username = user;
            break;
        }
    }
}

void removewebinfo(Node *master, char *web){
    if(strlen(master->entry->list[0].website) == 1){
        fprintf(stderr, "Web info does not exist");
        exit(1);
    }
    
    struct website_login *newlist = malloc(sizeof(master->entry->list) - sizeof(struct website_login));
    for(int i=0; i<(sizeof(master->entry->list)/sizeof(struct website_login)); i++){
        if(master->entry->list[i].website != web){
            newlist[i] = master->entry->list[i];
        }
    }
    free(master->entry->list);
    master->entry->list = newlist;

}

char *randompword(int length){
    char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char pword[length];
    for(int i=0;i<length;i++){
        pword[i] = alphabet[(rand() % 52) + 1];
    }
    char *p = pword;
    return p;
}