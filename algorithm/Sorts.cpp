//目的:实现基本的排序算法,包括冒泡排序,选择排序,插入排序,归并排序,桶排序,基数排序；快速排序与堆排序单独在其它文件中实现

#include <iostream>
#include <vector>
using namespace std;

//冒泡排序:设置标志位,当检测到没有数据交换时证明已经排序完毕
//冒泡排序是稳定的算法
void bubbleSort(vector<int> &vec){
	int len = vec.size();
	if (len < 2)
		return;
	bool flag = false;
	for (int i = len - 1; i > 0; i--){
		flag = false; //默认没有交换
		for (int j = 0; j < i; j++){
			if (vec[j] > vec[j + 1]){
				swap(vec[j], vec[j + 1]);
				flag = true; 
			}							
		}
		//本趟排序没有发生交换则退出
		if (flag == false)
			break;
	}
}

//选择排序:一次次选择最小的元素
void selectSort(vector<int> &vec){
	int len = vec.size();
	if (len < 2)
		return;
	for (int i = 0; i < len - 1; i++){
		int min = i;
		//选择未排序元素中最小元素的索引
		for (int j = i + 1; j < len; j++){
			//注意这里比较的是vec[min]不是vec[i]
			if (vec[j] < vec[min])
				min = j;
		}
		swap(vec[i], vec[min]);
	}
}

//插入排序:从待排序的部分取出第一个元素插入已经排序好的元素中
//选择排序是稳定排序
void insertSort(vector<int> &vec){
	int len = vec.size();
	if (len < 2)
		return;
	//注意这里从第二个元素开始,因为刚开始的第一个元素我们把它看作已排序好的
	for (int i = 1; i < len; i++){
		//依次和已排好的数据比较,找到合适的位置
		int j;
		for (j = i - 1; j >= 0; j--){
			if (vec[i] > vec[j])
				break;
		}
		//如果j = i -1则要插入的元素比已排好序的元素都要大,则直接处理下一个元素
		//否则就先将后面的元素向后移动一个位置再将此元素插入
		if (j < i - 1){
			//暂存要插入的数据
			int insert_num = vec[i]; 
			//数据后移动
			for (int k = i - 1; k > j; k--){
				vec[k + 1] = vec[k];
			}
			//插入
			vec[j + 1] = insert_num;
		}
	}
}

//希尔排序:基本思想是将数组按照步长进行分组,组内进行插入排序
//逐渐缩小分组直到步长为1为止
void shellSort(vector<int> &vec){
	int len = vec.size();
	if (len < 2)
		return;
	//gap为步长,也是分组组数,gap减小到1时结束
	for (int gap = len / 2; gap > 0; gap /= 2){
		//总共gap组,每组组内进行插入排序
		for (int i = 0; i < gap; i++){
			//开始插入排序
			for (int j = i + gap; j < len; j += gap){
				//如果待排序的元素小于签名的元素则,找到合适的插入位置
				if (vec[j] < vec[j - gap]){
					int tmp = vec[j]; //保存当前元素
					int k = j - gap;  //k指向已排好元素的最后一个元素
					//若已排好元素大于待排元素则将其向后移动,并将k指向再前一个元素
					while (k >= 0 && vec[k] > tmp){
						vec[k + gap] = vec[k];
						k -= gap;
					}
					//最后k指向了第一个小于等于待排序元素的位置,所以要再加上步长值
					vec[k + gap] = tmp;
				}
			}
		}
	}

}

//合并:归并排序中的合并过程
void merge(vector<int> &vec, int start, int end){
	//保存归并排序后的数据
	vector<int> merge_tmp(vec);
	//从mid开始分为两个数组区间
	int mid = start + (end - start + 1) / 2;
	int i = start;
	int j = mid + 1;
	
	//将两个数组归并
	int index = 0;
	while (i <= mid && j <= end){
		if (vec[i] < vec[j])
			merge_tmp[index++] = vec[i++];
		else
			merge_tmp[index++] = vec[j++];
	}
	//将未归并的数据合并到临时空间内
	while (i <= mid)
		merge_tmp[index++] = vec[i++];
	while (j <= end)
		merge_tmp[index++] = vec[j++];
	//将临时空间中的数据再恢复到原来的空间
	for (int i = 0; i < index; i++)
		vec[start + i] = merge_tmp[i];
}
//归并排序
void mergeSort(vector<int> &vec, int start, int end){
	//递归终止条件1,如果只有一个元素则返回
	if (end - start == 0){
		return;
	}
	//递归终止条件2,如果有两个元素,则比较后返回
	if (end - start == 1){
		if (vec[start] > vec[end]){
			swap(vec[start], vec[end]);
		}
		//无论是否交换都要返回
		return;
	}
	//如果超过2个元素,则递归
	int mid = start + (end - start + 1) / 2;
	mergeSort(vec, start, mid);
	mergeSort(vec, mid + 1, end);
	
	//递归完毕后进行数组合并
	merge(vec, start, end);
}

//桶排序:思想是将数组位置看作一个个的桶,其中装着元素的个数,如a[3] = 5就表示数组中值为3的元素有5个
//桶排序适合元素最大值与最小值范围差别不大的数组排序,并且数组中不能有负值,如果有负值则需要找到最小
//的负值并将其整体加上一个偏移量变为正值(下面的程序并没有对有负数的情况做处理)
void bucketSort(vector<int> &vec){
	int len = vec.size();
	if (len < 2)
		return;
	//找到数组最大值,并检查是否有负数
	int max = vec[0];
	for (int i = 0; i < len; i++){
		if (vec[i] < 0)
			return;
		if (vec[i] > max)
			max = vec[i];
	}
	//注意要把bucket中的值初始化为0,且元素个数要加1,因为数组索引是从0算起的
	vector<int> bucket(max + 1, 0);
	for (int i = 0; i < len; i++){
		bucket[vec[i]]++;
	}
	//原数组排序,注意max+1
	for (int i = 0, j = 0; i < max + 1; i++){
		while ((bucket[i]--) > 0)
			vec[j++] = i;
	}
}
//基数排序


int main(){
	vector<int> vec = { 3, 1, 4, 28, 9, 6, 7, 3, 23, 5 };

	//bubbleSort(vec);
	//selectSort(vec);
	//insertSort(vec);
	//bucketSort(vec);
	//mergeSort(vec, 0, vec.size() - 1);
	shellSort(vec);
	for (int i = 0; i < vec.size(); i++){
		cout << vec[i] << " ";
	}

	return 0;
}
