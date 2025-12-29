    #include <stdio.h>// lujain alawneh 1230127 sec 4
#include <stdlib.h>
#include <string.h>
typedef struct node {
    int taskId;
    char  name [20];
    char  date [20] ;
    double  duration ;
    struct node *next;
}node;
typedef node* stack;

void displayMainMenu( ) ;
void  loadTasks( FILE *input  , node*l );
node  * creatList (   );
node* creatNode (  node*l   );
int isEmpty ( node *l);
int isLast ( node *p ,node *l);
int  addTask(node*l) ;
void deleteTask(node*l,int key);
void  searchForTaskById(node*l ) ;
void searchForTaskByName(node*l );
void printList(node*l);
void PerformTask( node*l, stack performed);
void UndoLastPerformedTask(stack undone ,stack performed ,node*l);
void GenerateSummaryReport(node*l ,stack performed,stack undone );
void Push( int taskId ,  char  name [20],char  date [20] ,  double  duration,stack performed );
void Pop( stack performed ) ;
void printPerformed ( stack performed );

int main(void) {
    FILE *input = fopen("tasks.txt", "r");
    if (input == NULL) {
        printf("Error opening file\n");
        return 1 ;
    }
    int choice ,s;
    node *l =creatList ( );
    stack performed =creatList ( );
    stack undone = creatList ( );

    do {
        displayMainMenu( );

        scanf("%d",&choice);
        switch(choice) {

            case 1:
                loadTasks(  input  ,  l );

                break;
            case 2:
                 s =  addTask( l);
                break;
            case 3:
                printf("enter the task ID\n");
            int key;
            scanf("%d",&key);
             deleteTask( l,key );
                break;

            case 4:
                printf("if you  want to search by id press0 if by name press 1");
            int x ;
            scanf("%d",&x);
            if (x ==1) {
                searchForTaskByName( l ) ;
            }
            if (x==0) {
                searchForTaskById( l ) ;
            }
            else {
                printf("please enter 0 or 1 \n");
                break ;
            }
                break;
            case 5:
                printList( l);
                break;
            case 6:
                 PerformTask(  l, performed);
                break;
            case 7:
             UndoLastPerformedTask( undone, performed,l);
                break;
            case 8:
                printPerformed ( performed );
                break;
            case 9:
                GenerateSummaryReport( l , performed , undone );
            break ;
            case 10:
                printf("Thank you for using My ask Management System .GoodBye.\n");
                break;
            default :
                printf("\nNo such operation! Please try again.\n");
            break;

        }
    }while(choice != 10 );
    fclose(input);

    return 0;
}
void displayMainMenu( ) {
    printf("\n");
    printf("\nWelcome to  the Task Management System\n");
    printf("please select an operation.....\n");
    printf("1-Load Tasks File:\n");
    printf("2-Add a New Task :\n");
    printf("3-Delete a Task:\n");
    printf("4-Search for a Task:\n");
    printf("5-View Unperformed Tasks\n");
    printf("6-Perform a Task\n");
    printf("7-Undo Last Performed Task\n");
    printf("8-View Performed Tasks\n");
    printf("9-Generate Summary Report\n");
    printf("10-Exit\n");
    printf("please enter your choice \n") ;
    printf("\n");
}
void loadTasks(  FILE *input ,node*l ) {
    char array[100];
    char temp  [20];
while ( fgets(array,sizeof(array),input) != NULL) {
  node*p = creatNode ( l );
char *token  = strtok(array,"#");
    p->taskId = atoi(token);
        strcpy (temp,strtok(NULL,"#")) ;
        strcpy (p->name,temp ) ;
        strcpy (temp ,strtok(NULL,"#")) ;
        strcpy (p->date,temp  ) ;
    p->duration = atof(strtok(NULL,"#"));  // in order to store  the double value since token is a pointer
}
    printf("\ndata loaded successfully !\n");
}
  node  * creatList (  ) {
    node *l=  (  node*) malloc (sizeof( node) ) ;
    if  (l == NULL){
        printf("out of memory ") ;
    }
    l-> next = NULL ;
    return l ;
}

node* creatNode(node*l) {
    node*p = ( node * )malloc(sizeof(node));
    if  (p == NULL) {
        printf("out of memory ") ;
    }
    node*temp = l->next  ;
    if (l->next ==NULL) {
        l->next =p;
        p->next =NULL;
        return p;
    }
    while (temp -> next !=NULL) {
        temp = temp->next ;
    }

     temp->next =p;
    p->next =NULL;
    return p;

}


int isEmpty ( node *l){
    return l->next == NULL;

}
int isLast ( node *p ,node *l) {
    return p->next == NULL;
}
int addTask(node*l) {
    node*temp = l->next;
    printf("Enter the Task ID: \n");
    int  x;
    scanf("%d",&x);
       while (temp!=NULL) {
if (temp->taskId==x) {
    printf("Task already exists\n");
   return 0;
}
    temp=  temp ->next ;
       }
 node*p = creatNode(l);
    p->taskId = x;
    printf("Enter the Task name: \n");
    gets(p->name );
    gets(p->name );
    printf("Enter the Task Date: \n");
    gets(p->date );

    printf("Enter the Task Duration: \n");
    scanf("%lf",&p->duration);
    printf("A new task added successfully !");
    return 1;
}
void deleteTask(node*l ,int key ) {
    node*p = l->next;
    node* n = l ;
    while (p!=NULL && p->taskId!=key){
        n=p;
        p = p->next ;
    }
    if (p->taskId!=key) {
        printf("task  with this ID doesn't exist\n");
    }
    else {
        n->next = p->next;
        free(p);
    }

}
void searchForTaskById(node*l ) {
    printf("enter the task ID\n");
    int key;
    scanf("%d",&key);
    node*p = l->next;
    while (p!=NULL && p->taskId!=key) {
        p = p->next ;
    }
    if (p->taskId!=key) {
        printf("task  with this ID doesn't exist\n");
    }
    else {
        printf("Task ID: %d ",p->taskId);
        printf("Task Name: %s ",p->name);
        printf("Task Date: %s ",p->date);
        printf("Task Duration: %lf ",p->duration);
        printf("\n");
    }

}
void searchForTaskByName(node*l ) {
    printf("\n enter the task name\n");
    char arrayName[20];
    scanf("%s",&arrayName);
    node*p = l->next;
    while (p!=NULL && strcmp(p->name,arrayName)!=0) { //strcmp returns  0  if strings are  equals
        p = p->next ;
    }
    if ( strcmp(p->name,arrayName)) {
        printf("task  with this ID doesn't exist\n");
    }
    else {
        printf("\nTask ID: %d ",p->taskId);
        printf("Task Name: %s ",p->name);
        printf("Task Date: %s ",p->date);
        printf("Task Duration: %lf ",p->duration);
        printf("\n");
    }
}
void printList(node*l) {
    struct node *p =l->next ;
    if (isEmpty ( l)){
        printf("List is Empty ");
    }
    while (p!= NULL){
        printf("Task ID: %d ",p->taskId);
        printf("Task Name: %s ",p->name);
        printf("Task Date: %s ",p->date);
        printf("Task Duration: %lf ",p->duration);
        printf("\n");
        p =p->next ;
    }

}
void PerformTask( node*l,stack performed) {
    printf("\nplease enter the ID  of the  task you  want to  perform\n");
    int key;
    scanf("%d",&key);
    node*p = l->next;
    while (p!=NULL && p->taskId!=key) {
        p = p->next ;
    }
    if (p->taskId!=key) {
        printf("task  with this ID doesn't exist\n");
    }
    else {
         Push( p->taskId ,p->name,p->date,p->duration,performed );
        printf("task performed successfully !");
        deleteTask( l ,  key );
    }

}
void UndoLastPerformedTask(stack undone ,stack performed ,node*l) {

    if (isEmpty(performed)) {
        printf(" there is no performed tasks to undo");
    }
    else {
        node*q =creatNode ( l );
        node* p = performed ->next ;
        Push( p-> taskId,p->name , p->date , p-> duration, undone ) ;
        q->taskId = p->taskId;
        strcpy(q->name ,p->name);
        strcpy(q->date ,p->date);
        q->duration = p->duration;
     Pop(  performed );
    }
}
void GenerateSummaryReport(node*l,stack performed ,stack undone ) {
    FILE *summary = fopen("summary.txt","w");
    if (isEmpty(performed)) {
        fprintf(summary,"no  performed  tasks ");
      return;
    }
    stack tempstack =creatList (   );
    while (!isEmpty(performed)) {
        node* p =performed->next ;
        Push( p->taskId,p-> name,p-> date,p->duration, tempstack  );
        Pop( performed ) ;
    }
    fprintf(summary,"performed\n");
    while (!isEmpty(tempstack)) {
        node* p = tempstack->next ;
        Push( p->taskId,p-> name,p-> date,p->duration, performed   );
        fprintf( summary,"\nTask ID: %d ",p->taskId);
        fprintf( summary," Task Name: %s ",p->name);
        fprintf( summary," Task Date: %s ",p->date);
        fprintf( summary," Task Duration: %lf ",p->duration);
        Pop( tempstack  ) ;
    }
    //printing undone tasks

    if ( isEmpty(undone)) {
        fprintf(summary,"no  undone tasks ");
        return;
    }
    while (!isEmpty(undone)) {
        node* p =undone->next ;
        Push( p->taskId,p-> name,p-> date,p->duration, tempstack  );
        Pop( undone ) ;
    }
    fprintf(summary,"\n\nundone\n");
    while (!isEmpty(tempstack)) {
        node* p = tempstack->next ;
        Push( p->taskId,p-> name,p-> date,p->duration, undone  );
        fprintf( summary,"\nTask ID: %d ",p->taskId);
        fprintf( summary," Task Name: %s ",p->name);
        fprintf( summary," Task Date: %s ",p->date);
        fprintf( summary," Task Duration: %lf ",p->duration);
        Pop( tempstack  ) ;
    }
    //print n the  unperformed
    fprintf(summary,"\n\n unperformed\n");
    struct node *p =l->next ;
    if (isEmpty ( l)){
        printf("List is Empty ");
    }
    while (p!= NULL){
        fprintf( summary,"\nTask ID: %d ",p->taskId);
        fprintf( summary," Task Name: %s ",p->name);
        fprintf( summary," Task Date: %s ",p->date);
        fprintf( summary," Task Duration: %lf ",p->duration);
        p =p->next ;
    }
fclose(summary);
    }
void Push( int taskId,char name [20],char  date [20] ,double duration,stack performed ) {
    stack l=  (stack) malloc (sizeof( node) ) ;
    if  (l == NULL){
        printf("out of memory\n") ;
        return ;
    }
    l->taskId = taskId;
    strcpy(l->name,name);
    strcpy(l->date,date);
    l->duration =duration;
    l->next = performed->next ;
    performed->next = l ;
}
void Pop( stack performed ) {
    if (performed == NULL) {
        printf(" list is  not exist ");
        return;
    }

    if (isEmpty( performed )) {
        printf(" stack  is  empty ");
        return;
    }
        node * p = performed->next ;
    node* temp  = p  ;
        performed->next  =  p->next ;
        free(temp);
}


void printPerformed ( stack performed ) {

    if (isEmpty(performed)) {
        printf("stack is empty\n");
        return;
    }
    stack tempstack =creatList (   );
    while (!isEmpty(performed)) {
        node* p =performed->next ;
        Push( p->taskId,p-> name,p-> date,p->duration, tempstack  );
        Pop( performed ) ;
    }

    while (!isEmpty(tempstack)) {
        node* p = tempstack->next ;
        Push( p->taskId,p-> name,p-> date,p->duration, performed   );
        printf( "\nTask ID: %d ",p->taskId);
        printf( "\nTask Name: %s ",p->name);
        printf( "\nTask Date: %s ",p->date);
        printf( "\nTask Duration: %lf ",p->duration);
        Pop( tempstack  ) ;
    }
}

