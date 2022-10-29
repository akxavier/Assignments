#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/slab.h>

struct node {
	int key;
	struct node *l;
	struct node *r;
};

typedef struct node *node;

struct tree {
	node root;
};

node Create_Node(int k) {
	node x = (node) kmalloc (sizeof(struct node), GFP_DMA);
	x -> key = k;
	x -> l = NULL;
	x -> r = NULL;
	return x;
}

void Insert(struct tree *T, int k) {
	node x = Create_Node(k);

	node y, z;

	y = NULL;
	z = T -> root;

	while(z != NULL) {
		y = z;

		if(x -> key < z -> key)
			z = z -> l;
		else 
			z = z -> r;
	}

	if(y == NULL)
		T -> root = x;
	else if(x -> key < y -> key)
		y -> l = x;
	else
		y -> r = x;
}

void Inorder(node x) {
	if(x != NULL) {
		Inorder(x -> l);
		printk(KERN_INFO "%d", x -> key);
		Inorder(x -> r);
	}
}

int simple_init(void) {
	struct tree *T = (struct tree*) kmalloc (sizeof(struct tree), GFP_DMA);
	T -> root = NULL;

	Insert(T, 11);
	Insert(T, 6);
	Insert(T, 8);
	Insert(T, 19);
	Insert(T, 4);
	Insert(T, 10);
	Insert(T, 5);
	Insert(T, 17);
	Insert(T, 43);
	Insert(T, 49);
	Insert(T, 31);

	Inorder(T -> root);
	return 0;
}

void simple_exit(void) {
	printk(KERN_INFO "Removing Kernel Module");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_AUTHOR("Aadharsh K Xavier");
MODULE_DESCRIPTION("Assg2");
MODULE_LICENSE("MIT");
