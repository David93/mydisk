#include <stdio.h>
#include<stdlib.h>
#include<ucontext.h>

//File node
struct f_Node {
	char name[30];
	char *data;
	struct f_Node* next;
};
void addFile(char *name,char *x, struct f_Node** list){
	struct f_Node* temp=(struct c_Node*)malloc(sizeof(struct f_Node));
	temp->data=x;		
	if(*list==NULL)
	{	*list=temp; (*list)->next=NULL;return;}
	temp->next=*list;
	*list=temp;
}
void remFile(char *name,struct c_Node** list){
	struct c_Node* ptr=*list;
	struct c_Node* prev;
	if(ptr!=NULL && ptr->data==id){
		*list=ptr->next;
		free(ptr);
		return;
	}
	while(ptr!=NULL && ptr->data!=id )
	{
		prev=ptr;
		ptr=ptr->next;
	}
	if(ptr==NULL) return;
	prev->next=ptr->next;
	free(ptr);
}