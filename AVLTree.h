int height(AVLTree t){
	if(t == NULL)
		return -1;

	return t -> height;
}

int max(int a,int b){
	return ((a > b)? a : b);
}

AVLTree singlerotatewithleft(AVLTree k2){
	AVLTree k1;
	k1 = k2 -> left;
	k2 -> left = k1 -> right;
	k1 -> right = k2;

	k2 -> height = max(height(k2 -> left),height(k2 -> right)) + 1;
	k1 -> height = max(height(k1 -> left),k2 -> height) + 1;

	return k1;
}

AVLTree singlerotatewithright(AVLTree k2){
	AVLTree k1;
	k1 = k2 -> right;
	k2 -> right = k1 -> left;
	k1 -> left = k2;

	k2 -> height = max(height(k2 -> left),height(k2 -> right)) + 1;
	k1 -> height = max(height(k1 -> left),k2 -> height) + 1;

	return k1;
}

AVLTree doublerotatewithleft(AVLTree k3){
	k3 -> left = singlerotatewithright(k3 -> left);

	return singlerotatewithleft(k3);
}

AVLTree doublerotatewithright(AVLTree k3){
	k3 -> right = singlerotatewithleft(k3 -> right);

	return singlerotatewithright(k3);
}


AVLTree insert(Record r,AVLTree t){
	if(t == NULL){
		t = (AVLTree)malloc(sizeof(AVLTreeNode));
		t -> r = r;
		t -> left = t -> right = NULL;
	}

	else if(r.rno < t -> r.rno){
		t -> left = insert(r,t -> left);
		if(height(t -> left) - height(t -> right) == 2)
			if(r.rno < t -> left -> r.rno){
				printf("\nSingle rotate performed!\n");
				t = singlerotatewithleft(t);
			}
			else{
				printf("\nDouble rotate performed!\n");
				t = doublerotatewithleft(t);
			}
	}

	else if(r.rno > t -> r.rno){
		t -> right = insert(r,t -> right);
		if(height(t -> right) - height(t -> left) == 2)
			if(r.rno > t -> right -> r.rno){
				printf("\nSingle rotate performed!\n");
				t = singlerotatewithright(t);
			}
			else{
				printf("\nDouble rotate performed!\n");
				t = doublerotatewithright(t);
			}
	}

	t -> height = max(height(t -> left),height(t -> right)) + 1;
	return t;
}

Record* search(AVLTree t,int rno){
	if(t == NULL){
		static Room r;
		CreateRoom(&r);
		printf("Not found!\n");
		return &r;
	}

	if(rno < t -> r.rno)
		return search(t -> left,rno);
	else if(rno > t -> r.rno)
		return search(t -> right,rno);
	else
		return &(t -> r);
}

AVLTree readFile(){
	FILE * f = fopen("Rooms.dat","rb");
	static AVLTree t = NULL;

	Room tmp;
	fread(&tmp,1,sizeof(Room),f);
	while(!feof(f)){
		t = insert(tmp,t);
		fread(&tmp,1,sizeof(Room),f);
	}
	fclose(f);

	return t;
}

void inorder(AVLTree t){
	if(t == NULL)
		return;
	inorder(t -> left);
	printf("%d\t",t -> r.rno);
	inorder(t -> right);
}

void writeFile(AVLTree t,FILE * f){
	if(t == NULL)
		return;
	writeFile(t -> left,f);
	fwrite(&(t -> r),1,sizeof(Room),f);
	writeFile(t -> right,f);
}
