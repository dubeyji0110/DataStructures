#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct node{
int info;
struct node *next;
}nodetype;

nodetype* push(nodetype *tp,int nm);
nodetype* pop(nodetype*tp);
void display(nodetype *tp);

int main()
{
nodetype *top=NULL;
int num,opt;
char choice = 'Y';
do{
printf("enter opt\n");
scanf("%d",&opt);
if(opt==1){
scanf("%d",&num);
top=push(top,num);
}
else if(opt==2){
if(top!=NULL){
top=pop(top);
 }
else {
printf("stack is empty\n");
 }
}
else if(opt==3){
if(top!=NULL){
display(top);
}
else
printf("stack is empty\n");
}
else{
 printf("invalid opt\n");
}
printf("to continue  Y/N\n");
//scanf("%c",&choice);
choice = getch();
}while(choice=='Y');
    return 0;
}

nodetype* push(nodetype *tp,int nm){
nodetype *p;
p=(nodetype*)malloc(sizeof(nodetype)) ;
if(p==NULL)
printf("not space\n");
else{
p->info=nm;
p->next=tp;
tp=p;
}
return (tp);
  }

nodetype* pop(nodetype*tp){
nodetype *temp;
temp=tp;
printf("element popped %d",tp->info);
tp=tp->next;
free(temp);
return tp;
}

void display(nodetype *tp){
if(tp==NULL)
printf("stack empty\n");
else{
while(tp!=NULL){
printf("%d",tp->info);
tp=tp->next;
}
}
}