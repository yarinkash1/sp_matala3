#include "StrList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//define a struct named _node. it has a pointer to an array of chars(string) and a pointer to the next node.
typedef struct _node
{
    char *_word;
    struct _node *_next;
} Node;

//here we point to the head of the linked list. Also size_t determines how many elements we have in the linked list.
typedef struct _StrList
{
    Node* _head;
    size_t _size;
} _StrList;

//------------------------------------------------
// Node implementation - start
//------------------------------------------------

Node* Node_alloc(char* word,Node* next)
{
    Node* p= (Node*)malloc(sizeof(Node)); // the pointer will point to the newly allocated memory of the node.
    //we cast the pointer to a Node after we calculate the size in bytes we want to occupy on the heap.
    p->_word = (char*)malloc(strlen(word) * sizeof(char));
    strcpy(p->_word, word);
    p->_next= next; //same as this._next=next in java
    return p;
}

void Node_free(Node* node)
{
    //if the node is null we don't need to free space on the heap.
    //if it isn't we need to free the dynamic memory we allocated inside the Node struct(in our case the array of chars).
    //after we freed the _word array we need to free the node itself.

    if (node != NULL)
    {
        free(node->_word);
        free(node->_next);
    }
}
//------------------------------------------------
// Node implementation - end
//------------------------------------------------

//------------------------------------------------
// List implementation - start
//------------------------------------------------
StrList* StrList_alloc()
{
    StrList* p= (StrList*)malloc(sizeof(StrList)); // dynamic memory allocation to a new list.
    p->_head = NULL; // we create an empty list so there is no head to point to.
    p->_size = 0; // empty list size will be zero.
    return p;
}
//we go through each element in our linked list from the head to the next element until the very last.
//in each element we point to the next one and free the pointer of the previous node.
//in the end we free the list itself(the last node)
void StrList_free(StrList* StrList)
{
    if (StrList==NULL) return; // we don't need to free anything
    Node* p1= StrList->_head; // same as this.head=p1 in java
    Node* p2; // we define a new pointer p2
    while(p1) //while our head does not point to null
    {
        p2 = p1; // the new pointer p2 holds the pointer to p1
        p1 = p1->_next; // p1 pointer(the head of the list) now points to the next element.
        Node_free(p2); // we free the node that was the head of the list.
    }
    free(StrList);
}

//getter to the size of the list
size_t StrList_size(const StrList* StrList)
{
    return StrList->_size;// same as return this.size in java
}
//traverse the last until the last element and then insert the element we want in the last place(after creating a new one).
void StrList_insertLast(StrList* StrList,const char* data)
{
    if(StrList_size(StrList) == 0)
    {
        StrList->_head=Node_alloc(data,NULL);
        StrList->_size=1;
    }
    else
    {
        Node* current= StrList->_head;
        while(current->_next!=NULL)
        {
            current=current->_next;
        }
        current->_next= Node_alloc(data,NULL);
        ++(StrList->_size);
    }
}

void StrList_insertAt(StrList* StrList,const char* data,int index)
{
    //if the list is empty we just add the node in the function(no matter what is the index).
    if(StrList_size(StrList) == 0)
    {
        StrList->_head=Node_alloc(data,NULL);
        StrList->_size=1;
        return;
    }
    else
    {
        //if the size of the index is greater than or equal to the size of the list(we start from zero) we insert the wanted node in the last position.
        if(index>StrList->_size)
        {
            printf("cannot insert at an unavailable index!");
            return;
        }

        Node* new_node = Node_alloc(data,NULL);
        int sum=0;
        Node* current_node=StrList->_head;

        if(index==0)
        {

            // insert at the head of the list
            new_node->_next = StrList->_head;
            StrList->_head = new_node;
            ++(StrList->_size);
            return;
        }

        //end of while:
        //current_copy=current
        //current -> new node
        //new_node->current_copy.next
        while(sum<index-1)
        {
            current_node=current_node->_next;
            sum++;
        }
        new_node->_next=current_node->_next;
        current_node->_next=new_node;
        ++(StrList->_size);
    }
}

char* StrList_firstData(const StrList* StrList)
{
    if(StrList->_head!=NULL)
    {
        //return the first word
        return StrList->_head->_word;
    }
    return NULL;
}
void StrList_print(const StrList* StrList)
{
    Node* current = StrList->_head;

    //print each word in a different line
    while (current != NULL)
    {
        printf("%s ", current->_word);
        current = current->_next;
    }
}

void StrList_printAt(const StrList* Strlist,int index)
{
    //empty list:
    if(StrList_size(Strlist) == 0)
    {
        printf("");
    }
        //we print each string in all the nodes the list has.
    else
    {
        int i = 0;
        Node* current=Strlist->_head;
        for (i=0; i <index && current!=NULL; i++)
        {

            current=current->_next;
        }
        printf("%s\n", current->_word);
    }
}
int StrList_printLen(const StrList* Strlist)
{
    if(StrList_size(Strlist) == 0)
    {
        return 0;
    }


    Node* current=Strlist->_head;
    int counter=0;
    while(current!=NULL)
    {
        //counting the chars in each string and summing in each loop the total amount.
        counter = counter + (int)strlen(current->_word);
        current=current->_next;
    }
    return counter;
}
int StrList_count(StrList* StrList, const char* data)
{
    if(StrList_size(StrList) == 0)
    {
        return 0;
    }
    Node* current=StrList->_head;
    int counter=0;
    while (current!=NULL)
    {
        //if the result is zero it means the strings are identical.
        int result=strcmp(current->_word, data);
        if(result==0)
        {
            counter++;
        }
        current=current->_next;
    }
    return counter;
}
void StrList_remove(StrList* StrList, const char* data)
{
    // if the list is empty we don't need to do anything.
    if (StrList_size(StrList) > 0)
    {
        // Iterate until StrList_head() is not NULL
        while (StrList->_head != NULL)
        {
            // if the result is zero it means the strings are identical.
            int result = strncmp(StrList->_head, data, strlen(data));
            if (result == 0)
            {
                // Remove the head node if the strings match
                Node* temp = StrList->_head;
                StrList->_head = temp->_next;
                free(temp);
            }
            else
            {
                // Break the loop if the strings don't match
                break;
            }
        }

        // If there are more nodes in the list, iterate through them and remove if necessary
        Node* current = StrList->_head;
        Node* prev = NULL;
        while (current != NULL)
        {
            int result = strncmp(current->_word, data, strlen(data));
            if (result == 0)
            {
                // Remove the current node
                Node* temp = current;
                if (prev != NULL)
                {
                    prev->_next = current->_next;
                }
                else
                {
                    StrList->_head = current->_next;
                }
                current = current->_next;
                free(temp);
            }
            else
            {
                // Move to the next node
                prev = current;
                current = current->_next;
            }
        }
    } else
    {
        printf("can't delete from empty list!");
    }
}





void StrList_removeAt(StrList* StrList, int index)
{
    if((int)StrList_size(StrList) > 0)
    {
        Node* temp_node=StrList->_head;
        Node* prev=StrList->_head;
        int counter=0;
        if (index >= 0 && index < (int)StrList_size(StrList))
        {
            if(StrList->_head->_next==NULL||index==0)//the list is of size 1 or we want to remove the head
            {

                StrList->_head=temp_node->_next;
                Node_free(temp_node);
                --(StrList->_size);
            }
            else
            {
                while((temp_node!=NULL&&counter<index))
                {
                    prev = temp_node;
                    temp_node = temp_node->_next;
                    counter++;
                }
                prev->_next = temp_node->_next;
                free(temp_node); // Free memory
                --(StrList->_size);
            }
        }
        else
        {
            printf("index out of bounds!\n");
        }
    }

}


int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
    int str1_length = (int)StrList_size(StrList1);
    int str2_length = (int)StrList_size(StrList2);
    //if their size is not equal they cannot be the same string list.
    if(str1_length!=str2_length)
    {
        return 0;
    }
    Node* current1=StrList1->_head;
    Node* current2=StrList2->_head;

    int i = 0;
    for(i = 0; i <str1_length; i++) //we checked the lists are the same size(we will take WLOG we will take str1_length)
    {
        int result=strcmp(current1->_word,current2->_word);
        if(result!=0) // if one of the strings in our for is not equal then the lists aren't identical.
        {
            return 0;
        }
        current1=current1->_next;
        current2=current2->_next;
    }
    return 1;

}
StrList* StrList_clone(const StrList* StrList)
{
    int str_length = (int)StrList_size(StrList);

    _StrList* clone;
    clone=StrList_alloc();

    Node* current_node=StrList->_head;

    int i = 0;
    for(i = 0; i < str_length; i++)
    {
        // Get the length of the current string
        int word_length = (int)strlen(current_node->_word);

        // Allocate memory for a new string
        char* new_word = (char*)malloc((word_length + 1) * sizeof(char));

        // Copy the contents of the current string to the new string
        strncpy(new_word, current_node->_word, word_length);
        new_word[word_length] = '\0'; // Add \0 ath the end of the string we copied.

        // Add the new string to the new list
        StrList_insertLast(clone, new_word);

        // Move to the next node in the original list
        current_node = current_node->_next;
    }
    return clone;
}
void StrList_reverse( StrList* StrList)
{
    //initialize three pointers to traverse the list and reverse it.
    Node* prev=NULL;
    Node* current=StrList->_head;
    Node* next=NULL;

    while(current!=NULL)
    {
        // Store next
        next=current->_next;
        // Reverse current node's pointer
        current->_next=prev;
        // Move pointers one position ahead.
        prev=current;
        current=next;
    }
    StrList->_head=prev; // in the end we want to point to the end of the list instead of the start.
}
void StrList_sort( StrList* StrList)
{
    size_t listSize = (int)StrList_size(StrList);

    if(listSize>1) // if the list is empty or has one element we don't need to sort it
    {
        Node* current =StrList->_head;
        Node* next;
        char* temp;

        int i = 0;
        int j = 0;
        for (i = 0; i < listSize; ++i)
        {
            next=current->_next;

            // the inner loop traverses from the 'i'-th element to the 'listSize-i-2'-th element
            for (j = 0; j < listSize-i-1; ++j)
            {

                //The strcmp function returns an integer that indicates the relationship between two strings. Specifically:

                //1) If the strings are equal, strcmp returns 0.
                //2) If the first string is lexicographically less than the second string, strcmp returns a negative value.
                //3) If the first string is lexicographically greater than the second string, strcmp returns a positive value.

                //if the third case happens, meaning strcmp returns something greater than zero than we need to swap between to adjacent words in the list.
                if (strcmp(current->_word, next->_word) > 0)
                {
                    // Swap the words
                    temp = current->_word;
                    current->_word = next->_word;
                    next->_word = temp;
                }

                // Move to the next node
                current = next;
                next = next->_next;
            }

            // Reset the pointers for the next pass
            current = StrList->_head;
            next = current->_next;
        }
    }

}
int StrList_isSorted(StrList* StrList)
{
    _StrList* clone_list = StrList_clone(StrList);//copy the original list to a new list
    StrList_sort(clone_list);//sort the copy list we got
    int result=StrList_isEqual(StrList,clone_list); //check if the sorted array is the same as the original list we got
    if (result == 1)//if we got 1, then our original list was sorted
    {
        free(clone_list);
        return 1;
    }
    else
    {
        free(clone_list);
        return 0;
    }
}
//------------------------------------------------
// List implementation - end
//------------------------------------------------