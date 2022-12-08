#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s {
    NODE right;
    NODE left;
    int key;
    void *data;
    int height;
} NODE_t[1];

typedef struct {
    NODE root;
} AVL_t[1], *AVL;

AVL avl_init() {
    AVL t = (AVL) malloc(sizeof(AVL_t));
    t->root = NULL;
    return t;
}

NODE init_node(int key, void *data) {
    NODE node = (NODE) malloc(sizeof(NODE_t));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data = data;
    node->height = NULL;
    return node;
}


void tree_print(NODE node, int l) {
    int i;
    if (node != NULL) {
        tree_print(node->right, l + 1);
        for (i = 0; i < l; ++i) {
            printf("        ");
        }
        printf("%d\n", node->key);
        tree_print(node->left, l + 1);
    }
}

int max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

int get_height(NODE node) {
    if (node == NULL || node->height == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

NODE left_rotation(NODE parent, int decrease) {

    //DONE: Decided the structure
    NODE child = parent->right;
    parent->height = parent->height - decrease;
    NODE t2 = child->left;

    //DONE: Rotation
    child->left = parent;
    parent->right = t2;
    parent = child;
    parent->height = (max(get_height(parent->left), get_height(parent->right)) + 1);


    return parent;
}

NODE right_rotation(NODE parent, int decrease) {

    //DONE: Decided the structure
    NODE child = parent->left;
    parent->height = parent->height - decrease;
    NODE t2 = child->right;

    //DONE: Rotation
    child->right = parent;
    parent->left = t2;
    parent = child;
    parent->height = (max(get_height(parent->left), get_height(parent->right)) + 1);

    return parent;
}

NODE avl_search_rec(NODE node, int key) {
    if (node == NULL) {
        printf("Key: %d does not exist in the tree \n", key);
    } else {
        if (key < node->key) {
            node->left = avl_search_rec(node->left, key);
        } else if (key > node->key) {
            node->right = avl_search_rec(node->right, key);
        } else {
            printf("Key: %d found and height is %d !!!! Also you can see part of the tree below after key: %d \n\n",
                   key, node->height, key);
            tree_print(node, 0);

        }
    }
    return node;
}

void avl_search(AVL t, int key) {
    if (t == NULL) {
        printf("ERROR. Uninitialized tree\n");
    } else {
        if (t->root == NULL) {
            printf("There is no element in the tree \n");
        } else {
            t->root = avl_search_rec(t->root, key);
        }
    }
}

NODE avl_insert_rec(NODE node, int key, void *data) {
    if (node == NULL) {
        node = init_node(key, data);
    } else {
        if (key < node->key) {
            node->left = avl_insert_rec(node->left, key, data);
        } else if (key > node->key) {
            node->right = avl_insert_rec(node->right, key, data);
        } else {
            printf("Duplicate key: %d. Ignoring...\n\n\n", key);
        }
    }

    //DONE: Update the height of current node;
    //DONE: node->height = max(node->left->height,node->right->height) + 1;
    node->height = (max(get_height(node->left), get_height(node->right)) + 1);

    //DONE: Compute Balance Factor
    //DONE: bf = node->left->height - node->right->height
    int bf = get_height(node->left) - get_height(node->right); //Balance Factor


    if (bf < -1) {
        if (get_height(node->right->left) < get_height(node->right->right)) {
            //PROBLEM:Right Right Problem

            //DONE: left Rotate
            node = left_rotation(node, 2);

        } else {
            //PROBLEM:Right Left Problem

            //TODO: Right Rotate
            node->right = right_rotation(node->right, 1);

            //TODO: Left Rotate
            node = left_rotation(node, 2);
        }
    } else if (bf > 1) {
        if (get_height(node->left->right) < get_height(node->left->left)) {
            //PROBLEM:Left Left Problem

            //TODO: Right Rotate
            node = right_rotation(node, 2);
        } else {
            //PROBLEM:Left Right Problem

            //TODO: Left Rotate
            node->left = left_rotation(node->left, 1);

            //TODO: Right Rotate
            node = right_rotation(node, 2);
        }
    }
    return node;
}

void avl_insert(AVL t, int key, void *data) {
    if (t == NULL) {
        printf("ERROR. Uninitialized tree\n");
    } else {
        if (t->root == NULL) {
            t->root = init_node(key, data);
        } else {
            t->root = avl_insert_rec(t->root, key, data);
        }
    }
}

NODE avl_delete_rec(NODE node, int key) {
    if (node == NULL) {
        printf("The does not exist in the tree!!");
    } else {
        if (key < node->key) {
            node->left = avl_delete_rec(node->left, key);
        } else if (key > node->key) {
            node->right = avl_delete_rec(node->right, key);
        } else {
            printf("You found the key\n\n\n", key);

            // Check the node if it is leaf or not.if it is delete it
            if (node->left == NULL && node->right == NULL) {
                free(node);
                node = NULL;
            }

            // If Parent
            // has one child
            // has two children
/*            if (node->left != NULL || node->right != NULL) {
                //has left child
                if (node->left != NULL && node->right == NULL) {
                    //find max in left subtree

                }
                //has right child
                if (node->left == NULL && node->right != NULL) {
                    //find min in right subtree
                }
                //has Two children
            }*/


        }
    }
    return node;
}


void avl_delete(AVL t, int key) {
    if (t == NULL) {
        printf("ERROR. Uninitialized tree\n");
    } else {
        if (t->root == NULL) {
            printf("Tree is empty!!");
        } else {
            t->root = avl_delete_rec(t->root, key);
        }
    }
}


/*Insert All numbers into the Tree from the array*/
void insertTest(AVL t, int *numbers, int n) {
    for (int i = 0; i < n; i++) {
        printf("Num %d added\n", *(numbers + (i * 2)));
        avl_insert(t, *(numbers + (i * 2)), NULL);
    }
}


int main() {

    AVL t1 = avl_init();

/*
    avl_insert(t1, 100, NULL);
    avl_insert(t1, 90, NULL);
    avl_insert(t1, 110, NULL);
    avl_insert(t1, 80, NULL);
    avl_insert(t1, 85, NULL);
*/

    avl_insert(t1, 100, NULL);
    avl_insert(t1, 150, NULL);
    avl_insert(t1, 90, NULL);
    avl_insert(t1, 70, NULL);
    avl_insert(t1, 80, NULL);
    avl_insert(t1, 50, NULL);
    avl_insert(t1, 34, NULL);
    avl_insert(t1, 12, NULL);
    avl_insert(t1, 200, NULL);
    avl_insert(t1, 124, NULL);
    avl_insert(t1, 8, NULL);
    avl_insert(t1, 7, NULL);
    avl_insert(t1, 4, NULL);
    avl_insert(t1, 58, NULL);
    avl_insert(t1, 121, NULL);
    avl_insert(t1, 122, NULL);
    avl_insert(t1, 123, NULL);
    avl_insert(t1, 125, NULL);
    avl_insert(t1, 126, NULL);
    avl_insert(t1, 127, NULL);
    avl_insert(t1, 362, NULL);
    avl_insert(t1, 397, NULL);
    avl_insert(t1, 455, NULL);
    avl_insert(t1, 500, NULL);
    avl_insert(t1, 600, NULL);
    avl_insert(t1, 316, NULL);
    avl_insert(t1, 390, NULL);
    avl_insert(t1, 387, NULL);
    avl_insert(t1, 310, NULL);
    avl_insert(t1, 300, NULL);





/*    //TODO: Left Left Problem Insert Test numbers
    int* numbersLL[7] = { 100,150,90,70,80,50,60};
    insertTest(t1,&numbersLL,7);*/

/*    //TODO: Left Right Problem Insert Test numbers
    int* numbersLR[7] = { 50,75,40,130,45,60,30};
    insertTest(t1,&numbersLR,7);*/



    tree_print(t1->root, 0);
    avl_search(t1, 90);

    avl_delete(t1, 90);

    tree_print(t1->root, 0);

    //Searching Test
    //avl_search(t1,150);

    return 0;
}
