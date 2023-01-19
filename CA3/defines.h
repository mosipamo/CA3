struct signup_node
{
    char name[20];
    char password[20];
    struct signup_node *link;
};
struct posts
{
    char content[100];
    struct signup_node * owner;
    int likes;
    int postID;
    struct posts* link;
};