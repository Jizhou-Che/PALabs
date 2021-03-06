#include <stdio.h>
#include <stdlib.h>

struct binary_search_int_tree{
	int value;
	struct binary_search_int_tree * left;
	struct binary_search_int_tree * right;
};

struct singly_linked_tree_list{
	struct binary_search_int_tree * node;
	struct singly_linked_tree_list * next;
};

struct tree_queue{
	struct singly_linked_tree_list * queue_list_head;
	struct singly_linked_tree_list * queue_list_tail;
};

int list_append(struct singly_linked_tree_list ** head_ref, struct singly_linked_tree_list ** tail_ref, struct binary_search_int_tree * node_to_append){
	struct singly_linked_tree_list * new_node = malloc(sizeof(struct singly_linked_tree_list));
	if(new_node == NULL){
		return 0;
	}else{
		new_node->node = node_to_append;
		new_node->next = NULL;
		if(*tail_ref == NULL){
			*head_ref = new_node;
			*tail_ref = new_node;
		}else{
			(*tail_ref)->next = new_node;
			*tail_ref = new_node;
		}
		return 1;
	}
}

int list_pop(struct singly_linked_tree_list ** head_ref, struct singly_linked_tree_list ** tail_ref){
	if(*head_ref == NULL){
		return 0;
	}else{
		struct singly_linked_tree_list * temp = *head_ref;
		*head_ref = (*head_ref)->next;
		free(temp);
		if(*head_ref == NULL){
			*tail_ref = NULL;
		}
		return 1;
	}
}

void queue_create(struct tree_queue * queue_ref){
	queue_ref->queue_list_head = NULL;
	queue_ref->queue_list_tail = NULL;
	return;
}

int enqueue(struct tree_queue * queue_ref, struct binary_search_int_tree * node_to_enqueue){
	return list_append(&(queue_ref->queue_list_head), &(queue_ref->queue_list_tail), node_to_enqueue);
}

int dequeue(struct tree_queue * queue_ref){
	return list_pop(&(queue_ref->queue_list_head), &(queue_ref->queue_list_tail));
}

int binary_search_tree_insert(struct binary_search_int_tree ** tree_ref, int new_value){
	if(*tree_ref == NULL){
		struct binary_search_int_tree * new_node = malloc(sizeof(struct binary_search_int_tree));
		if(new_node == NULL){
			return 0;
		}
		new_node->value = new_value;
		new_node->left = NULL;
		new_node->right = NULL;
		*tree_ref = new_node;
	}else{
		if(new_value <= (*tree_ref)->value){
			if(!binary_search_tree_insert(&((*tree_ref)->left), new_value)){
				return 0;
			}
		}else{
			if(!binary_search_tree_insert(&((*tree_ref)->right), new_value)){
				return 0;
			}
		}
	}
	return 1;
}

int binary_search_tree_delete(struct binary_search_int_tree ** tree_ref, int value_to_delete){
	if(*tree_ref == NULL){
		return 0;
	}else if((*tree_ref)->value == value_to_delete){
		if((*tree_ref)->left == NULL && (*tree_ref)->right == NULL){
			free(*tree_ref);
			*tree_ref = NULL;
		}else if((*tree_ref)->left == NULL){
			struct binary_search_int_tree * temp = *tree_ref;
			*tree_ref = (*tree_ref)->right;
			free(temp);
		}else if((*tree_ref)->right == NULL){
			struct binary_search_int_tree * temp = *tree_ref;
			*tree_ref = (*tree_ref)->left;
			free(temp);
		}else{
			struct binary_search_int_tree * current_node = (*tree_ref)->right;
			if(current_node->left == NULL){
				(*tree_ref)->value = current_node->value;
				(*tree_ref)->right = current_node->right;
				free(current_node);
			}else{
				while(current_node->left->left != NULL){
					current_node = current_node->left;
				}
				(*tree_ref)->value = current_node->left->value;
				struct binary_search_int_tree * temp = current_node->left;
				current_node->left = current_node->left->right;
				free(temp);
			}
		}
		return 1;
	}else{
		if((*tree_ref)->left != NULL){
			if((*tree_ref)->left->value == value_to_delete){
				if((*tree_ref)->left->left == NULL && (*tree_ref)->left->right == NULL){
					free((*tree_ref)->left);
					(*tree_ref)->left = NULL;
				}else if((*tree_ref)->left->left == NULL){
					struct binary_search_int_tree * temp = (*tree_ref)->left;
					(*tree_ref)->left = (*tree_ref)->left->right;
					free(temp);
				}else if((*tree_ref)->left->right == NULL){
					struct binary_search_int_tree * temp = (*tree_ref)->left;
					(*tree_ref)->left = (*tree_ref)->left->left;
					free(temp);
				}else{
					struct binary_search_int_tree * current_node = (*tree_ref)->left->right;
					if(current_node->left == NULL){
						(*tree_ref)->left->value = current_node->value;
						(*tree_ref)->left->right = current_node->right;
						free(current_node);
					}else{
						while(current_node->left->left != NULL){
							current_node = current_node->left;
						}
						(*tree_ref)->left->value = current_node->left->value;
						struct binary_search_int_tree * temp = current_node->left;
						current_node->left = current_node->left->right;
						free(temp);
					}
				}
				return 1;
			}
			if(binary_search_tree_delete(&((*tree_ref)->left), value_to_delete)){
				return 1;
			}
		}
		if((*tree_ref)->right != NULL){
			if((*tree_ref)->right->value == value_to_delete){
				if((*tree_ref)->right->left == NULL && (*tree_ref)->right->right == NULL){
					free((*tree_ref)->right);
					(*tree_ref)->right = NULL;
				}else if((*tree_ref)->right->left == NULL){
					struct binary_search_int_tree * temp = (*tree_ref)->right;
					(*tree_ref)->right = (*tree_ref)->right->right;
					free(temp);
				}else if((*tree_ref)->right->right == NULL){
					struct binary_search_int_tree * temp = (*tree_ref)->right;
					(*tree_ref)->right = (*tree_ref)->right->left;
					free(temp);
				}else{
					struct binary_search_int_tree * current_node = (*tree_ref)->right->right;
					if(current_node->left == NULL){
						(*tree_ref)->right->value = current_node->value;
						(*tree_ref)->right->right = current_node->right;
						free(current_node);
					}else{
						while(current_node->left->left != NULL){
							current_node = current_node->left;
						}
						(*tree_ref)->right->value = current_node->left->value;
						struct binary_search_int_tree * temp = current_node->left;
						current_node->left = current_node->left->right;
						free(temp);
					}
				}
				return 1;
			}
			if(binary_search_tree_delete(&((*tree_ref)->right), value_to_delete)){
				return 1;
			}
		}
		return 0;
	}
}

int binary_search_tree_search(struct binary_search_int_tree * tree_ref, int value_to_search){
	if(tree_ref == NULL){
		return 0;
	}else{
		if(tree_ref->value == value_to_search){
			return 1;
		}else if(value_to_search < tree_ref->value){
			int step = binary_search_tree_search(tree_ref->left, value_to_search);
			if(step == 0){
				return 0;
			}else{
				return step + 1;
			}
		}else{
			int step = binary_search_tree_search(tree_ref->right, value_to_search);
			if(step == 0){
				return 0;
			}else{
				return step + 1;
			}
		}
	}
}

void binary_tree_clear(struct binary_search_int_tree ** tree_ref){
	if(*tree_ref != NULL){
		if((*tree_ref)->left != NULL){
			binary_tree_clear(&((*tree_ref)->left));
		}
		if((*tree_ref)->right != NULL){
			binary_tree_clear(&((*tree_ref)->right));
		}
		free(*tree_ref);
		*tree_ref = NULL;
	}
	return;
}

void binary_tree_print_depth_first_in_order(struct binary_search_int_tree * tree_ref){
	if(tree_ref != NULL){
		if(tree_ref->left != NULL){
			binary_tree_print_depth_first_in_order(tree_ref->left);
		}
		printf("%d ", tree_ref->value);
		if(tree_ref->right != NULL){
			binary_tree_print_depth_first_in_order(tree_ref->right);
		}
	}
	return;
}

void binary_tree_print_depth_first_pre_order(struct binary_search_int_tree * tree_ref){
	if(tree_ref != NULL){
		printf("%d ", tree_ref->value);
		if(tree_ref->left != NULL){
			binary_tree_print_depth_first_pre_order(tree_ref->left);
		}
		if(tree_ref->right != NULL){
			binary_tree_print_depth_first_pre_order(tree_ref->right);
		}
	}
	return;
}

void binary_tree_print_depth_first_post_order(struct binary_search_int_tree * tree_ref){
	if(tree_ref != NULL){
		if(tree_ref->left != NULL){
			binary_tree_print_depth_first_post_order(tree_ref->left);
		}
		if(tree_ref->right != NULL){
			binary_tree_print_depth_first_post_order(tree_ref->right);
		}
		printf("%d ", tree_ref->value);
	}
	return;
}

void binary_tree_print_breadth_first(struct tree_queue * queue_ref){
	if(queue_ref->queue_list_head != NULL){
		printf("%d ", queue_ref->queue_list_head->node->value);
		if(queue_ref->queue_list_head->node->left != NULL){
			enqueue(queue_ref, queue_ref->queue_list_head->node->left);
		}
		if(queue_ref->queue_list_head->node->right != NULL){
			enqueue(queue_ref, queue_ref->queue_list_head->node->right);
		}
		dequeue(queue_ref);
		binary_tree_print_breadth_first(queue_ref);
	}
	return;
}

int main(){
	struct binary_search_int_tree * tree = NULL;

	printf("1: Insert\n");
	printf("2: Delete\n");
	printf("3: Search\n");
	printf("4: Clear the tree\n");
	printf("5: See the tree\n");
	printf("6: See all options\n");
	printf("0: Quit\n");

	while(1){
		printf("> ");
		int option;
		scanf("%d", &option);
		if(option == 1){
			int value_to_insert;
			printf("The integer to insert?: ");
			scanf("%d", &value_to_insert);
			int step = binary_search_tree_search(tree, value_to_insert);
			if(step != 0){
				printf("%d already in the tree.\n", value_to_insert);
				continue;
			}
			if(binary_search_tree_insert(&tree, value_to_insert)){
				printf("%d inserted.\n", value_to_insert);
			}else{
				printf("Memory allocation failed while inserting node.\n");
				binary_tree_clear(&tree);
				return 0;
			}
		}else if(option == 2){
			int value_to_delete;
			printf("The integer to delete?: ");
			scanf("%d", &value_to_delete);
			if(binary_search_tree_delete(&tree, value_to_delete)){
				printf("%d deleted.\n", value_to_delete);
			}else{
				printf("%d is not in the tree.\n", value_to_delete);
			}
		}else if(option == 3){
			int value_to_search;
			printf("The integer to search?: ");
			scanf("%d", &value_to_search);
			int step = binary_search_tree_search(tree, value_to_search);
			if(step != 0){
				printf("Traversed %d nodes to find value %d.\n", step, value_to_search);
			}else{
				printf("%d is not in the tree.\n", value_to_search);
			}
		}else if(option == 4){
			binary_tree_clear(&tree);
			printf("Tree cleared.\n");
		}else if(option == 5){
			printf("Depth first, in-order:\n");
			binary_tree_print_depth_first_in_order(tree);
			printf("\n");
			printf("Depth first, pre-order:\n");
			binary_tree_print_depth_first_pre_order(tree);
			printf("\n");
			printf("Depth first, post-order:\n");
			binary_tree_print_depth_first_post_order(tree);
			printf("\n");
			printf("Breadth first:\n");
			if(tree != NULL){
				struct tree_queue breadth_first_queue;
				queue_create(&breadth_first_queue);
				enqueue(&breadth_first_queue, tree);
				binary_tree_print_breadth_first(&breadth_first_queue);
			}
			printf("\n");
		}else if(option == 6){
			printf("1: Insert\n");
			printf("2: Delete\n");
			printf("3: Search\n");
			printf("4: Clear the tree\n");
			printf("5: See the tree\n");
			printf("6: See all options\n");
			printf("0: Quit\n");
		}else if(option == 0){
			binary_tree_clear(&tree);
			return 0;
		}else{
			printf("Invalid option.\n");
		}
	}
}
