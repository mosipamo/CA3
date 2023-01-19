#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
struct signup_node  
{
    char name[20];
    char password[20];
    struct signup_node *link;
};
struct posts
{
    char content[100];
    struct signup_node *owner; // char owner;
    int likes;
    int postID;
    struct posts *link;
};
struct signup_node *add_at_end(struct signup_node *ptr, char password[20], char name[20]) /*add users to the end of the linked list*/
{
    struct signup_node *temp;
    temp = (struct signup_node *)malloc(sizeof(struct signup_node));
    strcpy(temp->password, password);
    strcpy(temp->name, name);
    temp->link = NULL;

    ptr->link = temp;
    return temp;
}
struct signup_node *login(struct signup_node *head, char name[15], char password[20])
{
    struct signup_node *currentUser = NULL;
    if (head == NULL)
    {
        printf("linked list is empty");
    }
    struct signup_node *ptr = NULL;
    ptr = head->link;

    int foundUser = 0;
    while (ptr != NULL)
    {
        if (!strcmp(ptr->password, password) && !strcmp(ptr->name, name)) /*if the enterd username and password equals the signuped users -> you can login*/
        {
            foundUser = 1;
            currentUser = ptr;
            //printf("%s %s\n", currentUser->name, currentUser->password);
            printf("You are logged on successfully\n");
            break;
        }
        ptr = ptr->link;
    }
    if (!foundUser)
    {
        printf("wrong username/password\n");
        return ptr;
    }
    return currentUser;
}
void print_list_signup(struct signup_node *head)     /*list of users*/
{
    if (head == NULL)
    {
        printf("linked list is empty\n");
    }
    struct signup_node *ptr = NULL;
    ptr = head->link;
    while (ptr != NULL)  /*traverse the signup list to print list of users*/
    {
        printf("password is :%s   name is : %s\n", ptr->password, ptr->name);
        ptr = ptr->link;
    }
}
struct signup_node *logout()
{
    struct signup_node *currentUser = NULL;
    return currentUser;
}
void like(struct posts *headpost, int postID, char name[20]) 
{
    if (headpost == NULL)
    {
        printf("linked list is empty\n");
    }
    struct posts *ptr = NULL;
    ptr = headpost->link;
    while (ptr != NULL)     /*traverse the posts_lists to find the user to like it*/
    {
        if ((ptr->postID == postID))    /*if the choosen postid is found , then add one number of likes*/
        {
            ptr->likes++;
            printf("%d\n", ptr->likes);
        }
        ptr = ptr->link;    /*if the postid is not found, go through the postlist to find it*/
    }
}
void del(int postID, struct posts **headpost, struct signup_node *currentuser, char name[20], struct posts **tailpost)
{
    struct posts *temp = *headpost, *prev;
    // If head node itself holds the postid to be deleted
    if (temp != NULL && temp->postID == postID)
    {
        *headpost = temp->link; // Changed head
        free(temp);             // free old head
    }
    // Search for the postid to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->postID != postID)
    {
        prev = temp;
        temp = temp->link;
    }

    // If key was not present in linked list
    if (temp == NULL)
    {
        return;
    }

    if (temp->owner != currentuser)
    {
        printf("You can't delete this post!!\n");
        return;
    }

    // Unlink the node from linked list
    if (temp->link == NULL)
    {
        *tailpost = prev;
    }
    prev->link = temp->link;

    free(temp);
}
struct posts *post(struct posts *ptrpost, char text[100], struct signup_node *curruser, int postid)
{
    struct posts *postnode;
    postnode = (struct posts *)malloc(sizeof(struct posts));
    postnode->owner = curruser; /*equal the currentuser to the owner of the post*/
    strcpy(postnode->content, text);    /*equal the values*/
    postid++;
    postnode->link = NULL;
    postnode->postID = postid;
    postnode->likes = 0;
    ptrpost->link = postnode;

    return postnode;
}
void print_list_post(struct posts *headpost) /*print all posts*/
{
    if (headpost == NULL)
    {
        printf("linked list is empty\n");
    }
    struct posts *ptr = NULL;
    ptr = headpost->link;
    while (ptr != NULL)
    {
        printf("%s  postID is : %d  owner : %s\n", ptr->content, ptr->postID, ptr->owner);
        ptr = ptr->link;
    }
}
void user_info(struct posts *headpost, char name1[20])
{
    struct posts *ptr = NULL;
    ptr = headpost->link;
    while (ptr != NULL)
    {
        if (!strcmp(ptr->owner->name, name1))   /*if the username equals to the owner of posts, print the posts, num of likes and postid of posts*/
        {
            printf("\nusername is : %s   content : %s   postID : %d   likes : %d\n", name1, ptr->content, ptr->postID, ptr->likes);
        }
        ptr = ptr->link;    /*go through the postlist to find the owner*/
    }
}
void info(struct signup_node *currUSER, struct posts *headpost)
{
    struct posts *ptr = NULL;
    ptr = headpost->link;
    printf("username : %s   password : %s\n", currUSER->name, currUSER->password); /*curruser is the person who is loged in now*/
    while (ptr != NULL)
    {
        if (ptr->owner == currUSER)   /*if curruser equals to the owner if the posts, print the posts, num of likes and postid of posts*/
        {
            printf("\ncontent : %s   postID : %d   likes : %d\n", ptr->content, ptr->postID, ptr->likes);
        }
        ptr = ptr->link;     /*go through the postlist to find the owner*/
    }
}
void postsFile(FILE *posts_file, struct posts *head_post, struct signup_node *head)  /*save posts int the textfile*/
{
    posts_file = fopen("posts.txt", "w");
    struct signup_node *ptr = NULL;
    ptr = head->link;
    struct posts *ptrpost = NULL;
    ptrpost = head_post->link;
    while (ptr != NULL)
    {
        ptrpost = head_post->link;
        while (ptrpost != NULL)
        {
            if (!strcmp(ptrpost->owner->name, ptr->name))
            {
                fwrite(ptrpost->content, 1, strlen(ptrpost->content), posts_file);
                fwrite("\t", 1, strlen("\t"), posts_file);

                fwrite(ptrpost->owner->name, 1, strlen(ptrpost->owner->name), posts_file);
                fwrite("\t", 1, strlen("\t"), posts_file);

                char likes[10]; /*itoa = function which converts given integer into a string using a given base*/
                itoa(ptrpost->likes, likes, 10);      /*int value, char *, int base*/

                fwrite(likes, 1, strlen(likes), posts_file);
                fwrite("\n", 1, strlen("\n"), posts_file);
            }
            ptrpost = ptrpost->link;
        }
        ptr = ptr->link;
    }
    fclose(posts_file);
}