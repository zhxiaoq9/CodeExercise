//目的:实现二叉查找树的基本操作
//说明:二叉查找树根节点的左子树的值均小于根节点,右子树的值均大于根节点，左右子树也分别为二叉查找树,二叉树中没有重复元素
//基本操作:前序遍历,中序遍历,后续遍历,层次遍历,查找指定节点,查找最大最小值,插入节点,查找节点,销毁二叉树,删除节点(暂未实现)
#include <iostream>
#include <queue>
using namespace std;

template <class T>
class Node{
public:
	T    key;     //键值
	Node *left;   //左孩子
	Node *right;  //右孩子
	//Node *parent;

	Node(T value, Node *l, Node *r) :key(value), left(l), right(r){}
};

template <class T>
class BSTree{
private:
	Node<T> *mRoot; //根节点

public:
	BSTree();
	~BSTree();

	void preOrder();  //前序遍历
	void inOrder();   //中序遍历
	void postOrder(); //后序遍历
	int  levelOrder();//层次遍历,返回二叉树深度

	Node<T>* search(T key) const; //递归查找
	Node<T>* iterativeSearch(T key) const; //非递归查找
	
	void insert(T key); //插入节点
	void remove(T key); //删除节点
	void destroy();//销毁二叉树
	
private:
	void preOrder(Node<T>* tree) const;
	void inOrder(Node<T>* tree) const;
	void postOrder(Node<T>* tree) const;
	int  levelOrder(Node<T>* tree) const;
	void printKey(const T &key) const;

	//因为销毁二叉树后需要将tree置为NULL,所以要使用引用传递
	//若不使用引用传递则传入的只是指针的地址副本.
	void destroy(Node<T>* &tree);
	void insert(Node<T>* &tree, Node<T>* target);
	Node<T>* search(Node<T>* tree, T key) const;
	Node<T>* iterativeSearch(Node<T>* tree, T key) const;
	
};

template <class T>
BSTree<T>::BSTree() :mRoot(NULL){};

template <class T>
BSTree<T>::~BSTree(){
	destroy();
}

//先删除叶节点并将其置为空,再删除父节点
//这样一直循环到根节点
template <class T>
void BSTree<T>::destroy(Node<T>* &tree){
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		destroy(tree->left);
	if (tree->right != NULL)
		destroy(tree->right);
	delete tree;
	tree = NULL;
}

template <class T>
void BSTree<T>::destroy(){
	destroy(mRoot);
}

template <class T>
void BSTree<T>::insert(Node<T>* &tree, Node<T>* target){
    //若已存在则直接返回
	if (tree != NULL){
		if (search(target->key) != NULL)
			return;
	}

	Node<T>* parent = NULL;
	Node<T>* pos = tree;
	//定位插入位置,注意对于不同类型的T,可能要重载<操作符
	while (pos != NULL){
		parent = pos;
		if (target->key < pos->key)
			pos = pos->left;
		else
			pos = pos->right;
	}
	if (parent == NULL){
		tree = target;
	}
	else if (target->key < parent->key){
		parent->left = target;
	}
	else{
		parent->right = target;
	}

}

template <class T>
void BSTree<T>::insert(T key){
	Node<T>* target = NULL;
	if ((target = new Node<T>(key, NULL, NULL)) == NULL)
		return;
	insert(mRoot, target);
}


template <class T>
Node<T>* BSTree<T>::search(Node<T>* tree, T key) const{
	if (tree == NULL || tree->key == key)
		return tree;
	if (key < tree->key)
		return search(tree->left, key);
	else
		return search(tree->right, key);
}

template <class T>
Node<T>* BSTree<T>::search(T key) const{
	return search(mRoot, key);
}

template <class T>
Node<T>* BSTree<T>::iterativeSearch(Node<T>* tree, T key) const{
	Node<T>* pos = tree;
	while (pos != NULL && key != pos->key){
		if (key < pos->key)
			pos = pos->left;
		else
			pos = pos->right;
	}
	return pos;
}

template <class T>
Node<T>* BSTree<T>::iterativeSearch(T key) const{
	return iterativeSearch(mRoot, key);
}


template <class T>
void BSTree<T>::printKey(const T &key) const{
	cout << key << " ";
}

template <class T>
void BSTree<T>::preOrder(Node<T>* tree) const{
	if (tree != NULL){
		printKey(tree->key);
		preOrder(tree->left);
		preOrder(tree->right);
	}
}
template <class T>
void BSTree<T>::preOrder(){
	preOrder(mRoot);
}

template <class T>
void BSTree<T>::inOrder(Node<T>* tree) const{
	if (tree != NULL){
		inOrder(tree->left);
		printKey(tree->key);
		inOrder(tree->right);
	}
}
template <class T>
void BSTree<T>::inOrder(){
	inOrder(mRoot);
}

template <class T>
void BSTree<T>::postOrder(Node<T>* tree) const{
	if (tree != NULL){
		postOrder(tree->left);
		postOrder(tree->right);
		printKey(tree->key);
	}
}
template <class T>
void BSTree<T>::postOrder(){
	postOrder(mRoot);
}

template <class T>
int BSTree<T>::levelOrder(Node<T>* tree) const{
	int depth = 0;  //保存树的深度
	int num = 0;    //保存当前层节点数目
	int next = 0;   //保存下一层节点数目,这个值的最大值可以表示二叉树宽度
	queue<Node<T>* > que;
	if (tree != NULL){
		que.push(tree);
		depth++;
		num++;
	}
		
	while (num--){
		Node<T>* q= que.front();
		que.pop();
		printKey(q->key);
		if (q->left != NULL){
			que.push(q->left);
			next++;
		}
			
		if (q->right != NULL){
			que.push(q->right);
			next++;
		}
		//当前层处理完且下一层仍然有节点
		if (num == 0 && next != 0){
			num = next;
			next = 0;
			depth++;
		}
	}
	return depth;
}

template <class T>
int BSTree<T>::levelOrder(){
	return levelOrder(mRoot);
}




int main()
{
	int i, ilen;
	int arr[] = { 16, 9, 18, 6, 12, 17, 25, 1, 10};
	ilen = (sizeof(arr)) / (sizeof(arr[0]));

	BSTree<int>* tree = new BSTree<int>();
	
	cout << "== 依次添加: ";
	
	for (i = 0; i<ilen; i++)
	{
		cout << arr[i] << " ";
		tree->insert(arr[i]);
	}

	cout << "\n== 前序遍历: ";
	tree->preOrder();

	cout << "\n== 中序遍历: ";
	tree->inOrder();

	cout << "\n== 后序遍历: ";
	tree->postOrder();

	cout << "\n== 层次遍历: ";
	int depth = tree->levelOrder();
	cout << " Tree depth: " << depth << endl;

	Node<int>* p = tree->iterativeSearch(1);
	if (p != NULL)
		cout << p->key << endl;
	p = tree->iterativeSearch(100);
	if (p == NULL)
		cout << "Can't find 100.\n";



	// 销毁二叉树
	tree->destroy();

	return 0;
}
