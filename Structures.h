
typedef struct{
	int m,d,y;
} Date;


typedef struct{
	int rno;
	Date Check_In , Check_Out;
	unsigned isOccupied : 1;
	unsigned int cust_id;
} Room;


typedef struct{
	unsigned int id;
	unsigned int visit_no;
	char name[30];
	char ph[11];
	Room r;
} Customer;

typedef Room Record;


typedef struct avlnode{
	Record r;
	struct avlnode * left , * right;
	short int height;
}AVLTreeNode;

typedef AVLTreeNode * AVLTree;

