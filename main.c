#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char url[100];
    struct node* next;
};

struct node* back_top=NULL;
struct node* forward_top=NULL;
char current[100]="google.com";

void push_back(char url[]){
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    strcpy(newnode->url,url);
    newnode->next=back_top;
    back_top=newnode;
}

void push_forward(char url[]){
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    strcpy(newnode->url,url);
    newnode->next=forward_top;
    forward_top=newnode;
}

void clear_forward(){
    struct node* temp;
    while(forward_top!=NULL){
        temp=forward_top;
        forward_top=forward_top->next;
        free(temp);
    }
}

void visit(char url[]){
    push_back(current);
    strcpy(current,url);
    clear_forward();
    printf("\n VISITED : %s\n",current);
}

void back() {
    if (back_top == NULL) {
        printf("\nNo back history!\n");
        return;
    }
    push_forward(current);

    struct node* temp = back_top;
    strcpy(current, temp->url);
    back_top = back_top->next;
    free(temp);

    printf("\nMoved Back to: %s\n", current);
}

// Forward button function
void forward() {
    if (forward_top == NULL) {
        printf("\nNo forward history!\n");
        return;
    }
    push_back(current);

    struct node* temp = forward_top;
    strcpy(current, temp->url);
    forward_top = forward_top->next;
    free(temp);

    printf("\nMoved Forward to: %s\n", current);
}

// Print current browser status
void display() {
    printf("\n----------------------------------\n");
    printf("Current Page: %s\n", current);

    printf("Back Stack: ");
    struct node* temp = back_top;
    if (temp == NULL) {
        printf("Empty");
    }
    while (temp != NULL) {
        printf("%s -> ", temp->url);
        temp = temp->next;
    }

    printf("\nForward Stack: ");
    temp = forward_top;
    if (temp == NULL) {
        printf("Empty");
    }
    while (temp != NULL) {
        printf("%s -> ", temp->url);
        temp = temp->next;
    }
    printf("\n----------------------------------\n");
}

int main()
{
    int ch;
    char url[100];

    while (1) {
        display();
        printf("\n--- MENU ---\n");
        printf("1. Visit URL\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("Enter Website URL: ");
            scanf("%s", url);
            visit(url);
        }
        else if (ch == 2) {
            back();
        }
        else if (ch == 3) {
            forward();
        }
        else if (ch == 4) {
            printf("Exiting program...\n");
            break;
        }
        else {
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
