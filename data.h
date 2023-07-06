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

extern Node masterlist;
extern Node *last;
extern Node *first;

void createmaster(struct User *);
Node *findmaster(char *user, char *pass);
void removemaster(Node *);
void addwebinfo(Node *master, char *web, char *user, char *pass);
void editwebinfo(Node *master, char *web, char *user, char *pass);
void removewebinfo(Node *master, char *web);
char *randompword(int length);
void editmaster(Node *edit, char *user, char *pass);
int masterexists(char *user, char *pass);
int existinguser(char *user);