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
        printf("Load: The values of row, col, and value are: %d %d %lf\n", row, col, value);
        set_tuples(tuple, row, col, value);
    }
    fclose(fpointer);
    return tuple;
}

//return value of element at the given row and column
double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    int i;
    sp_tuples_node* nodeptr = mat_t->tuples_head;
    for(i = 0; i < mat_t->nz; i++){ //Construct iterates through linked list until end (when nodeptr = NULL)
        if(row == nodeptr->row && col == nodeptr->col) //If an index exists within the list, that means a nonzero entity is present
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
                if(nodeptr == mat_t->tuples_head){
                    mat_t->tuples_head = nodeptr->next;
                    free(nodeptr);
                    mat_t->nz--;
                    return;
                }
                //Update next pointer of previous node
                prevptr->next = nodeptr->next; 
                free(nodeptr); //Free associated memory at node
                mat_t->nz--;
                return;
            }
            prevptr = nodeptr; //Set prevptr to current node
            nodeptr = nodeptr->next; //Set nodeptr to next node
        }
        return; //No associated nodes (linked list does not exist yet, and since value is zero we return)
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
            tempnode->next = nodeptr;
            mat_t->tuples_head = tempnode;
            mat_t->nz++; //Nonzero entry, increment nz
        return;
    }
    while(nodeptr != NULL){//This statement loops until no more nodes exist
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
/*
INPUT: matrix A and B both with size m by n.
INITIATE matrix C with the same size as A and B and nz = 0
FOR every non-zero entry in A                   (traverse the linked-list in matA)
    i = row of current entry in A; j = column of entry
    C_(i,j) = C_(i,j) + A_(i,j)
FOR every non-zero entry in B                   (do the same for matB)
    i = row of current entry in B; j = column of entry
    C_(i,j) = C_(i,j) + B_(i,j)
  
We are given matrices A and B (matA and matB, respectively), need to merge
them into the same matrix (matrix C). Follow the given algorithm:
*/
    //Check if matrices can be added. If not, return NULL.
    printf("--------------Adding Tuples....--------------------\n");
    if(matA->m != matB->m || matA->n != matB->n)
    return NULL;

    sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples)); //Initialize headpointer for matrix C
    
    //Initialize values of matrix C (row and col), set nz to 0
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    retmat->tuples_head = NULL;
    //Initialize temp pointers for usage
    sp_tuples_node* matAnode = matA->tuples_head;
    sp_tuples_node* matBnode = matB->tuples_head;
    int i;
    double value, checkA;
    //Throw matrix A into matrix C, use set_tuples and gv_tuples
    for(i = 0; i < matA->nz; i++){
        value = gv_tuples(matA, matAnode->row, matAnode->col);
        printf("A:The value at node %d is: %lf, with row %d and col %d\n", i, value, matAnode->row, matAnode->col);
        set_tuples(retmat, matAnode->row, matAnode->col, value);
        matAnode = matAnode->next;
    }
    for(i = 0; i < matB->nz;i++){
        value = gv_tuples(matB, matBnode->row, matBnode->col); //Takes value in matrix B at index, stores into "value"
        printf("B:The value at node %d is: %lf, with row %d and col %d\n", i, value, matBnode->row, matBnode->col);
        checkA = gv_tuples(retmat, matBnode->row, matBnode->col); //Takes value in matrix A at index, stores into "checkA"
        if(checkA != 0){ //If value in matrix A at index is nonzero, then add values and set tuple
            value = value + checkA;
            set_tuples(retmat, matBnode->row, matBnode->col, value);
        }
        if(checkA == 0) { //Else - value in matrix A at specified index is zero, 
            set_tuples(retmat, matBnode->row, matBnode->col, value);
        }
        matBnode = matBnode->next;
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
