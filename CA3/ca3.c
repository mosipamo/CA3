#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "myhead.h"
#include "defines.h"
int main()
{
    printf("  <<  Welcome to UTI TOTI  >>  \n");
    /*signup_node*/
    struct signup_node *head = (struct signup_node *)malloc(sizeof(struct signup_node));
    head->link = NULL;
    if (head == NULL)
    {
        printf("memory allocation failed");
        exit(0);
    }
    struct signup_node *tail = head;
    struct signup_node *currUsuer = NULL;

    int state = 1;   /*there are two states*/
    int cntpost = 0; // post id

    /*post_node*/
    struct posts *headpost = (struct posts *)malloc(sizeof(struct posts));
    headpost->link = NULL;
    if (headpost == NULL)
    {
        printf("memory allocation failed");
        exit(0);
    }
    struct posts *tail_post = headpost;
    struct posts *temppost;

    /*some variables*/
    char command[50];
    char password[20];
    char name[20];
    int postIDtemp;

    /*FIle*/
    FILE *users_file = fopen("users.txt", "w");
    fclose(users_file);
    FILE *posts_file = fopen("posts.txt", "w");

    while (state)
    {
        if (currUsuer == NULL)
        {
            printf("S) << signup >>\n");
            printf("P) << list show >>\n");
            printf("L) << login >>\n");
            printf("Q) << exit >>\n");
            printf("Enter code : ");
            scanf("%s", command);
            if (command[0] == 'S' || command[0] == 's')
            {
                users_file = fopen("users.txt", "a");
                //printf("\nenter username : ");
                scanf("%s", &name);
                //printf("Enter password : ");
                scanf("%s", &password);
                tail = add_at_end(tail, password, name);
                fwrite(name, 1, strlen(name), users_file);
                fwrite("\t", 1, strlen("\t"), users_file);
                fwrite(password, 1, strlen(password), users_file);
                fwrite("\n", 1, strlen("\n"), users_file);
                fclose(users_file);
            }
            else if (command[0] == 'Q' || command[0] == 'q')
            {
                state = 0;
                printf("BYE BYE");
                break;
            }
            else if (command[0] == 'P' || command[0] == 'p')
            {
                print_list_signup(head);
            }
            else if (command[0] == 'L' || command[0] == 'l')
            {
                //printf("\nenter username : ");
                scanf("%s", &name);
                //printf("Enter password : ");
                scanf("%s", &password);
                //printf("\n");
                currUsuer = login(head, name, password);
            }
            else
            {
                printf("Wrong choice!\n");
                continue;
            }
        }
        else if (currUsuer != NULL)
        {
            printf("choose between : post, like, delete, postlist, info, user_info, logout -> \n");
            char command1[50];
            char tmp;
            scanf("%s", command1);
            if (!strcmp(command1, "post"))
            {
                char text[100];
                scanf("%c", &tmp);
                scanf("%[^\n]", text);
                tail_post = post(tail_post, text, currUsuer, cntpost);
                cntpost++;
                postsFile(posts_file, headpost, head);
            }
            else if (!strcmp(command1, "postlist"))
            {
                print_list_post(headpost);
            }
            else if (!strcmp(command1, "like"))
            {
                //printf("enter postID , username\n");
                scanf("%d %s", &postIDtemp, name);
                like(headpost, postIDtemp, name);
                postsFile(posts_file, headpost, head);
            }
            else if (!strcmp(command1, "delete"))
            {
                //printf("enter postID : ");
                scanf("%d", &postIDtemp);
                del(postIDtemp, &headpost, currUsuer, name, &tail_post);
                postsFile(posts_file, headpost, head);
            }
            else if (!strcmp(command1, "logout"))
            {
                currUsuer = logout();
            }
            else if (!strcmp(command1, "info"))
            {
                info(currUsuer, headpost);
            }
            else if (!strcmp(command1, "user_info"))
            {
                char name1[20];
                //printf("username is : ");
                scanf("%s", name1);
                user_info(headpost, name1);
            }
            else
            {
                printf("Wrong choice!\n");
                continue;
            }
        }
    }
}