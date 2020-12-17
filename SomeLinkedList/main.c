#include <stdio.h>
#include <stdlib.h>

// linked list node
// a -> b -> c ... -> d -> NULL
struct node {
	int this_;
	struct node *next;
};

struct node new_list(int x);
void print_list(struct node current);
void append_to_list(struct node *current, int i, int x);
int pop_list(struct node *current, int i);

int main(int argc, char **argv) {
	struct node A = new_list(2);
	print_list(A);
	append_to_list(&A, 0, 3);
	print_list(A);
	append_to_list(&A, 1, 5);
	print_list(A);
	append_to_list(&A, 1, 7);
	print_list(A);
	
	printf("%d\n", pop_list(&A, 1));
	print_list(A);
	printf("%d\n", pop_list(&A, 2));
	print_list(A);
	printf("%d\n", pop_list(&A, 1));
	print_list(A);
	// can't pop last value left
	printf("%d\n", A.this_);
	
	return 0;
}

// creates and returns a new head, O(1)
struct node new_list(int x) {
	struct node head;
	head.this_ = x; head.next = NULL;
	return head;
}

// prints the list when passed head O(n)
void print_list(struct node current){
	printf("[");
	while (current.next) {
		printf("%d, ", current.this_);
		current = *current.next;
	}
	printf("%d]\n", current.this_);
}

// Adds a value to some place in the list, O(n)
void append_to_list(struct node *current, int i, int x){
	struct node *after = NULL;
	while ((current -> next) && (i != 0)) {
		current = current -> next;
		i--;
	}
	
	if (current -> next){
		after = current -> next;
	}
	current -> next = malloc(sizeof(struct node));
	current = current -> next;
	
	current -> this_ = x;
	if (after) {
		current -> next = after;
	}
}

// Removes a value from some place in the list, O(n)
int pop_list(struct node *current, int i){
	int value = 0;
	struct node *after = NULL;
	
	while (((current -> next) -> next) && (i != 1)) {
		current = current -> next;
		i--;
	}
	if ((current -> next) -> next) {
		after = ((current -> next) -> next);
	}
	value = (current -> next) -> this_;
	
	free(current -> next);
	if (after) {
		current -> next = after;
	} else {
		current -> next = NULL;
	}
	
	
	
	return value;
}
