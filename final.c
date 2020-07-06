/*
 * Chung-Ang UNIV. school of CSE
 * Lecture: Data Structure 2020-1
 * Author: 20162191 SangJin Lee (CSE undergraduate student)
 * Textbook: Fundamentals of Data Structures in C 2nd edit.
 * project: Finalterm (ASSI-VII)
 * binary search tree and min heap
 */
 
 /****************************** fix here ******************************/
 #define MaxRow 5
 
 //key of binary search tree can NOT be overlapped
 int bst[MaxRow][2] = {
 {3,17},
 {1,18},
 {5,20},
 {4,20},
 {2,15};
 }
 
 //key of binary search tree can NOT be overlapped
 int mh[MaxRow][2] = {
 {2,20},
 {1,15},
 {5,20},
 {1,19},
 {7,17};
 }
 /**********************************************************************/
 
 #include <stdio.h>
 
 typedef struct node *treePointer;
 typedef struct {
         int key;
         int value;
         treePointer leftChild, rightChild;
 } NODE;
 
 int main(){
 
 
 
 return 0;
 }
  
 init_tree(NODE *tree_node){
         for(;;){
                 tree_node = ()malloc(sizeof(NODE));
         }
 }

