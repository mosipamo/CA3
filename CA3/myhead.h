struct signup_node;
struct posts;
struct signup_node *add_at_end(struct signup_node *ptr, char password[20], char name[20]);
struct signup_node* login(struct signup_node *head, char name[15], char password[20]);
void print_list_signup(struct signup_node *head);
struct signup_node* logout();
void like(struct posts *headpost,int postID, char name[20]);
void del(int postID,struct posts** headpost,struct signup_node *currentuser, char name[20], struct posts **tailpost);
struct posts * post(struct posts *ptrpost, char text[100],struct signup_node *curruser,int postid);
void print_list_post(struct posts *headpost);
void user_info(struct posts* headpost, char name1[20]);
void info(struct signup_node *currUSER, struct posts* headpost);
void postsFile(FILE *posts_file,struct posts *head_post, struct signup_node *head);