//目的:实现堆排序
//堆的特点:节点值总是不大于或不小于其父节点的值;堆是一颗完全二叉树;堆只对父子节点做了约束,左右子节点没有必然大小关系;
//          给定节点i(下标从0开始),则其左节点为2i+1,右节点为2i+2,父节点为(i-1)/2;
//堆的建立:堆的每个子树也是堆,建堆的核心就是让每个子树都成为堆. 以建立最小堆为例，将堆的某一个节点与其左右子节点比较，并将3个节点中
//          最小的值调整为根节点，调节完后递归保证调整后的根节点所有的子树都是最小堆。然后遍历树中的每一层节点即可


#include <iostream>
#include <vector>
using namespace std;

void printVec(const vector<int> &vec){
	for (int j = 0; j < vec.size(); j++){
		cout << vec[j] << " ";
	}
	cout << endl;
}

//vec:保存堆的数组
//len:堆的元素个数
//index:要调整的节点索引
void adjustHeap(vector<int> &vec, int len, int index){

	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int min_index = index;

	//如果左子节点存在并且其值小于跟节点,则标记左子节点为最小
	if (left < len && vec[left] < vec[min_index]){
		min_index = left;
	}
	//如果右子节点存在并且其值小于之前标记的最小值,则标记右子节点为最小
	if (right < len && vec[right] < vec[min_index]){
		min_index = right;
	}
	//当根节点不是最小值时,将最小值与根节点交换并再次调用自身保证调整后的根节点的所有子树都是堆
	if (min_index != index){
		swap(vec[min_index], vec[index]);
		adjustHeap(vec, len, min_index);
	}
	return;
}


void createHeap(vector<int> &vec, int len){
	//从倒数第二层开始调整
	for (int i = len / 2 - 1; i >= 0; i--){
		adjustHeap(vec, len, i);
	}
}

void heapSort(vector<int> &vec){
	int len = vec.size();
	if (len <= 1)
		return;
	//建立堆
	createHeap(vec, len);
	for (int i = len - 1; i > 0; i--){
		//将堆顶最小值交换到数组最后面
		swap(vec[0], vec[i]);
		printVec(vec);
		//堆元素数目减1.由于交换元素后整个树的根的左右子树仍然为合法的堆,所以不用再对整个树建堆,
		//只要调整整颗树的根元素对应的树为合法堆即可.
		len--;
		adjustHeap(vec, len, 0);
	}
	return;
}



int main(){

	//vector<int> vec = { 3, 4, 5, 1, 7, 2, 0, 8 };
	vector<int> vec = { 23, 6, 5, 82, 7, 45, 0, 26, 45, 68, 123, 5 };
	heapSort(vec);

	return 0;
}






