//目的:深度优先遍历(DFS)与广度优先遍历(BFS)
//DFS:从图的某一顶点A起,访问它的第一个邻接顶点B，然后访问B的第一个邻接顶点C，若C没有邻接顶点则返回B访问B的其它邻接顶点。若B的邻接顶点全部访问完，就访问A的其它邻接顶点。DFS的非递归形式可以使用栈来实现
//BFS:从图的某一顶点A起，先得到A的所有邻接顶点B/C/D，访问完B/C/D后访问B/C/D的邻接顶点，直到所有邻接顶点被访问,可以将已访问过的顶点放到队列中，每次拿出队首顶点时将其邻接顶点放入队尾，直到队列为空为止

#include <iostream>
#include <vector>
using namespace std;

#define MAX 100

class MatrixUDG{
private:
	char mVex[MAX];         //顶点
	int  mVexNum;           //顶点数目
	int  mEdgeNum;          //边数
	int  mMatrix[MAX][MAX]; //邻接矩阵
	MatrixUDG();            //暂时不允许无参数的构造函数
public:
	MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);
	void DFS();             //深度优先遍历
	void BFS();             //广度优先遍历
	void printAdjMatrix();  //打印邻接矩阵

private:
	void DFS(int index, int visited[]);
	int firstVertex(int v);
	int nextVertex(int v, int w);
};

MatrixUDG::MatrixUDG(char vexs[], int vlen, char edges[][2], int elen){
	mVexNum = vlen;
	mEdgeNum = elen;
	//初始化顶点
	for (int i = 0; i < mVexNum; i++){
		mVex[i] = vexs[i];
	}
	//初始化邻接矩阵
	for (int i = 0; i < mEdgeNum; i++){
		int start;
		int end;
		//寻找边的起点字符在邻接矩阵中的位置
		for (int j = 0; j < mVexNum; j++){
			if (mVex[j] == edges[i][0]){
				start = j;
				break;
			}
		}
		//寻找边的终点字符在邻接矩阵中的位置
		for (int j = 0; j < mVexNum; j++){
			if (mVex[j] == edges[i][1]){
				end = j;
				break;
			}
		}
		//这里针对无向图,所以除了从start->end外还需要end->start
		mMatrix[start][end] = 1;
		mMatrix[end][start] = 1;	
	}

}

int MatrixUDG::firstVertex(int v){
	if (v < 0 || v > mVexNum - 1)
		return -1;
	for (int i = 0; i < mVexNum; i++){
		if (mMatrix[v][i] == 1)
			return i;
	}
	return -1;
}
//返回顶点v邻接表中在顶点w之后的第一个顶点
int MatrixUDG::nextVertex(int v, int w){
	if (v < 0 || v > mVexNum - 1 || w <0 || w > mVexNum - 1)
		return -1;
	for (int i = w + 1; i < mVexNum; i++){
		if (mMatrix[v][i] == 1)
			return i;
	}
	return -1;
}

//深度优先搜索
void MatrixUDG::DFS(){
	//设置访问标记并初始化
	int visited[MAX];
	for (int i = 0; i < mVexNum; i++){
		visited[i] = 0;
	}
	cout << "Start DFS: ";
	//遍历访问
	for (int i = 0; i < mVexNum; i++){
		//如果当前节点没有访问,则递归访问当前节点
		if (!visited[i]){
			DFS(i, visited);
		}
	}
	cout << endl;
	return;
}

void MatrixUDG::DFS(int index, int visited[]){
	//设置当前顶点为已访问
	visited[index] = 1;
	cout << mVex[index] << " ";
	//遍历当前顶点的邻接顶点,若没有访问,则递归访问其邻接节点
	for (int w = firstVertex(index); w >= 0; w = nextVertex(index, w)){
		if (!visited[w])
			DFS(w, visited);
	}
	return;
}

//广度优先搜索
void MatrixUDG::BFS(){
	//这里采用一个数组与两个整形变量代替队列的功能
	int queue[MAX];
	int head = 0;
	int rear = 0;
	int visited[MAX];
	for (int i = 0; i < mVexNum; i++){
		visited[i] = 0;
	}
	cout << "Start BFS: ";
	for (int i = 0; i < mVexNum; i++){
		//若当顶点未被访问,则入队列(只有已访问的节点才能入队列)
		if (!visited[i]){
			visited[i] = 1; //标记已访问
			cout << mVex[i] << " ";
			queue[rear++] = i; //入队列
		}
		//若队列不为空,则访问队列头顶点的邻接顶点
		while (head != rear) {
			int j = queue[head++]; //出队列
			//遍历当前顶点的所有邻接顶点
			for (int w = firstVertex(j); w >= 0; w = nextVertex(j, w)){
				//如果邻接顶点已被访问则直接寻找下一个邻接顶点,如果没有被访问则
				//标记为已访问并入队列
				if (!visited[w]){
					visited[w] = 1;
					cout << mVex[w] << " ";
					queue[rear++] = w;
				}
			}
		}
	}
	cout << endl;
}


void MatrixUDG::printAdjMatrix(){
	cout << " ";
	for (int i = 0; i < mVexNum; i++){
		cout <<" " << mVex[i];
	}
	cout << endl;


	for (int i = 0; i < mVexNum; i++){
		cout << mVex[i];
		for (int j = 0; j < mVexNum; j++){
			if (mMatrix[i][j] != 1){
				cout << " " << 0;
			}
			else{
				cout << " " << mMatrix[i][j];
			}							
		}
		cout << endl;
	}

}

int main(){

	//顶点
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	//边
	char edges[][2] = {
		{ 'A', 'C' },
		{ 'A', 'D' },
		{ 'A', 'F' },
		{ 'B', 'C' },
		{ 'C', 'D' },
		{ 'E', 'G' },
		{ 'F', 'G' } };
	//顶点数目
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	//边数
	int elen = sizeof(edges) / sizeof(edges[0]);

	MatrixUDG *pG = new MatrixUDG(vexs, vlen, edges, elen);

	pG->printAdjMatrix();
	pG->DFS();
	pG->BFS();
	return 0;
}






