#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>



/*
typedef struct sp_tuples_node
{
    double value;
    int row;
    int col;
    struct sp_tuples_node * next;

} sp_tuples_node;


typedef struct sp_tuples //list of coordinate format - each node is a tuple containing row col and value.
{
    int m; //# of rows
    int n; //# of cols
    int nz;//# of non-zero entries in matrix

    sp_tuples_node * tuples_head;
} sp_tuples;
*/


sp_tuples * load_tuples(char* input_file) //Opne file with name 'input_file', return a matrix (pointer to matrix?) of the list
{

    int row, col;
    double value;


    //1. Open File
    FILE* fpointer = fopen(input_file, "r");
    //2. Create sp_tuples with malloc
    sp_tuples* tuple = (sp_tuples*)malloc(sizeof(sp_tuples));
    //3. Read matrix dimension and initialize sp_tuples
    fscanf(fpointer,"%d %d", &(tuple->m), &(tuple->n));
    //4. Read through file line by line and use set_tuples() to build your list
    tuple->nz = 0;
    while(!feof(fpointer)){
        fscanf(fpointer,"%d %d %lf", &row, &col, &value);
        set_tuples(tuple, row, col, value);
    }
    fclose(fpointer);
    return tuple;
}

//return value of element at the given row and column
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node* nodeptr = mat_t->tuples_head;
    while(nodeptr != NULL){
        if(row == nodeptr->row && col == nodeptr->col)
        {
            return nodeptr->value;
        }
        nodeptr = nodeptr->next; //Iterate through list
    }
    return 0; //Otherwise, return 0 (if not in link, is not a nonzero entity).
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    /*
     1. What if value to insert is 0? Delete node - write helper function - FINISHED
     2. What if there is already a node with (row, col)? Replace existing value with new value - FINISHED
     3. What if head is NULL? Create new node and set it as head - FINISHED
     4. What if the correct position to insert is at the head? Have new node point to old head and update head
    */
   
    //mat_t holds # of rows, # of cols, and # of non-zero entries (nz), in addition to headpointer(tuples_head)
    sp_tuples_node* nodeptr = mat_t->tuples_head; //nodeptr of struct sp_tuples_node now points to headnode
    sp_tuples_node* prevptr = mat_t->tuples_head; //prevptr of struct sp_tuples_node points to the previous node (used as a temp)

    //1. What if value to insert is 0? Delete node - write helper function
    if(value == 0){ //If value is zero, we need to delete the associated node (if it exists)
        while(nodeptr != NULL){
            if(nodeptr->row == row && nodeptr->col == col){
                //Update next pointer of previous node
                prevptr->next = nodeptr->next; 
                free(nodeptr); //Free associated memory at node
                mat_t->nz--;
                return;
            }
            prevptr = nodeptr; //Set prevptr to current node
            nodeptr = nodeptr->next; //Set nodeptr to next node
        }
    }
    //3. What if head is NULL? Create new node and set it as head - FINISHED
    if(nodeptr == NULL){ //If nodeptr is NULL (i.e. no headnode exists), then create head
        sp_tuples_node* tempnode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create associated memory with head node
        tempnode->row = row; //Initialize values for headnode
        tempnode->col = col;
        tempnode->value = value;
        mat_t->tuples_head = tempnode; //Set tuples_head to tempnode
        mat_t->nz++;
        return;
    }
    //4. What if the correct position to insert is at the head? Have new node point to old head and update head
    if((nodeptr->row == row && nodeptr->col > col)||nodeptr->row > row){ //If index is less than index of the node currently looked at (nodeptr), place new node in b/w next node and prev node
            sp_tuples_node* tempnode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create associated memory with head node
            tempnode->row = row; //Initialize values for headnode
            tempnode->col = col;
            tempnode->value = value;
            //Set nextnode of previous node, and nextnode of current node
            tempnode->next = nodeptr->next;
            mat_t->tuples_head = tempnode;
            mat_t->nz++; //Nonzero entry, increment nz
        return;
    }
    while(nodeptr != NULL){//This statement 
        if(nodeptr->row == row && nodeptr->col ==col){ //If index exists, update value
            nodeptr->value = value; //Change value at node and return
            return;
        }
        //2. What if there is already a node with (row, col)? Replace existing value with new value 
        if((nodeptr->row == row && nodeptr->col > col)||nodeptr->row > row){ //If index is less than index of the node currently looked at (nodeptr), place new node in b/w next node and prev node
            sp_tuples_node* tempnode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create associated memory with head node
            tempnode->row = row; //Initialize values for headnode
            tempnode->col = col;
            tempnode->value = value;
            //Set nextnode of previous node, and nextnode of current node
            prevptr->next = tempnode;
            tempnode->next = nodeptr;
            mat_t->nz++; //Nonzero entry, increment nz
        return;
        }
        //If either of these aren't true, iterate to next node
        prevptr = nodeptr; //Set prevptr to current node
        nodeptr = nodeptr->next; //Set nodeptr to next node
    }
//NodeIf it gets past all these statements, indicates new node needs to be created at end of list
    sp_tuples_node* tempnode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create memory for new node
    tempnode->row = row; //Initialize values for headnode
    tempnode->col = col;
    tempnode->value = value;
    tempnode->next = NULL;
    prevptr->next = tempnode; //Set prevnode's next to tempnode (newnode)
    mat_t->nz++;
    /* INITIALIZE THESE VARS AFTER WE FINISH WRITING OTHER THINGS
    node1 - first node encountered
    node2 - node after first node
    currentnode - node you're trying to insert
    newptr - a temp pointer (this actually gets initialized within the function, so don't have to initialze. However, notes are stored here regradless).
    */    
    //First, check if the node index is the same
    /*
    if((node1->row * mat_t->n + node1->col) < (currentnode->row * mat_t->n + currentnode->col)){
        node1->value = currentnode->value; //Set new value
        break; //Break loop, node placement completed
    }
    if((node1->row * mat_t->n + node1->col) < (currentnode->row * mat_t->n + currentnode->col)){ //If index of the next node is less than the index of the current node
     //AND if the index of the current node is less than the index of the next node + 1
     if((node2->row * mat_t->n + node2->col) > (currentnode->row * mat_t->n + currentnode->col)){
         //Place new node in between node 1 and node 2
         sp_tuples_node* newptr;
         //Set next pointers correctly
         newptr = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Allocate memory for new node, return pointer into newptr
         newptr->next = node1->next; //Set new node's next to node2 
         node1->next = newptr; //Set first node's next to new node
         //Now initialize values into new node
         newptr->row = row;
         newptr->col = col;
         mat_t->nz++; //Increment nz
         break; //Break loop
     }
    
    }*/
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* fpointer = fopen(file_name, "w");//Open file to write
    sp_tuples_node* nodeptr = mat_t->tuples_head;//initialize node ptr for iteration
    fprintf(fpointer, "%d %d\n", mat_t->m, mat_t->n);//write the dimensions
    while(nodeptr != NULL){ //While not at end of list
        fprintf(fpointer,"%d %d %lf\n", nodeptr->row, nodeptr->col, nodeptr->value); //Write row, column, and value to file
        nodeptr = nodeptr->next; //Set next node. If no more nodes, finished writing.
    }
    fclose(fpointer);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    int i;
    double value, check;
    sp_tuples_node* matCptr; //Points to current node being looked at
    sp_tuples_node* matAptr = matA->tuples_head; //Points to head of matA
    sp_tuples_node* matBptr = matB->tuples_head; //Points to head of matB
    sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples)); //Create headnode of matrix C
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    matCptr = (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //Created new node, currentptr points to it
    retmat->tuples_head = matCptr; //Set headpointer for retmat
    for(i = 0; i < matA->nz; i++){
        value = gv_tuples(matA, matAptr->row, matAptr->col); //Return value stored at row, col of A
        matCptr->row = matAptr->row; //Initialize node
        matCptr->col = matAptr->col;
        matCptr->value = value;
        retmat->nz++;
        matCptr->next = (sp_tuples_node *)malloc(sizeof(sp_tuples_node)); //Allocate new memory for next node
        matCptr = matCptr->next; //Change matCptr to next node
        matAptr = matAptr->next; //Change matAptr to next node
    }
    free(matCptr);
    matCptr = retmat->tuples_head; //Reset matCptr to beginning of list
    for(i=0;i < matB->nz; i++){
        value = gv_tuples(matB, matBptr->row, matBptr->col); //Return value stored at row, col of matB
        check = gv_tuples(matA, matBptr->row, matBptr->col);
        if(check != 0){
            value = value + check;
            set_tuples(retmat, matBptr->row, matBptr->col, value);
        }
        else{
            set_tuples(retmat, matBptr->row, matBptr->col, value);
        }



    }    
	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    sp_tuples* retmat = NULL;
    return retmat;

}


	
void destroy_tuples(sp_tuples * mat_t){
	int length = mat_t->nz; //# of nodes plus headnode
    int i;
    sp_tuples_node* prevptr = mat_t->tuples_head;
    sp_tuples_node* nextptr = mat_t->tuples_head;
    for(i = 0; i < length; i++){
        nextptr = prevptr->next;
        free(prevptr);
        prevptr = nextptr;
    }
    free(mat_t);
    return;
}
