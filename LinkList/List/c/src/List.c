/*************************************************************************
	> File Name: ./src/List.c
	> Author: yang 
	> Mail: yangperasd@163.com 
	> Created Time: 2015年09月10日 星期四 19时10分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "List.h"

/* list_init */
void list_init(List * list,void (*destroy)(void *data))
{/*{{{*/
    /* Initialize the list. */
    list->size=0;
    list->destroy=destroy;
    list->head=list->tail=NULL;

    return;
}/*}}}*/

/* list_destroy */
void list_destory(List *list)
{/*{{{*/
    /* Remove each element. */
    void* data;
    while(list_size(list))
    {
        if(list_rem_next(list,NULL,&data)==0&&list->destroy!=NULL)
            list->destroy(data);
    }

    return;
}/*}}}*/

int list_ins_next(List *list, ListElmt *element, const void *data)
{/*{{{*/
    ListElmt *new_element=(ListElmt*)calloc(1,sizeof(ListElmt));
    if(!new_element) return -1;

    new_element->data=(void*)data;
    if(new_element==NULL)
    {
        if(list_size(list)==0)
            list->tail=new_element;
        new_element->next=list->head;
        list->head=new_element;
    }
    else
    {
        if(element->next!=NULL)
            list->tail=new_element;
        new_element->next=element->next;
        element->next=new_element;
    }
    ++list->size;
    return 0;
}/*}}}*/

/* list_rem_next */
int list_rem_next(List *list, ListElmt *element, void **data)
{/*{{{*/
    ListElmt *old_element;
    if(list_size(list)==0)
        return -1;
    
    if(element==NULL)
    {
        old_element=list->head;
        *data=list->head->data;
        list->head=list->head->next;

        if(list_size(list)==1)
            list->tail=NULL;
    }
    else 
    {
        if(element->next==NULL)
            return -1;

        old_element=element->next;
        *data=old_element->data;
        element->next=old_element->next;

        if(list_size(list)==1)
            list->tail=element;
    }

    free(old_element);
    --list->size;
    return 0;
}/*}}}*/


