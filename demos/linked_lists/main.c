//
// Linked List Example
// Dr Anton Gerdelan <gerdela@scss.tcd.ie>
// Trinity College Dublin, Ireland
// First v. 25 July 2016
//
// to compile with gcc: gcc -o lldemo main.c
// to compile with visual studio: can compile as C++. comment out #include <stdbool.h>

#include <stdio.h> // standard I/O functions
#include <assert.h> // force crash on major errors
#include <string.h> // strings and data copies
#include <stdbool.h> // for bool in C99 (not needed in C++)
#include <stdlib.h> // memory allocation

typedef struct Node Node; // forward declare type and alias `struct Node` with `Node`
struct Node{
	char data[256];
	Node* next; // note: we refer to our own type here
};

// C and C++ do not retain memory allocated to a pointer given as a function argument
// to get around this we can add another pointer level (another *) and dereference back to a single level with *list
// in C++ you can use Node*& notation instead
bool add_node(Node** list, const char* data){
	assert(data); // crash deliberately if data is invalid
	Node* new_node = (Node*)malloc(sizeof(Node));
	if(!new_node){
		// fprintf to stderr is guaranteed to print in correct order. also prints this file's name and line number.
		fprintf(stderr, "ERROR: out of memory. %s:%i\n", __FILE__, __LINE__);
		return false;
	}
	// if this is the first node in the list, what value will ->next receive?
	new_node->next = *list;
	strcpy(new_node->data, data);
	*list = new_node;
	return true;
}

// no need for Node** here because we don't allocate memory to the list inside the function
void print_all_nodes(Node* list){
	printf("entire list data contents:\n");
	Node* ptr = list;
	while(ptr != NULL){
		printf("%s\n", ptr->data);
		ptr = ptr->next;
	}
}

int main(){
	Node* linked_list = NULL;
	if(!add_node(&linked_list, "Anton Gerdelan")){
		return 1;
	}
	if(!add_node(&linked_list, "Keith Hardwick, PhD")){
		return 1;
	}
	print_all_nodes(linked_list);
	return 0;
}
