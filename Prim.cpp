//Prim �㷨
#include<iostream>
#include<vector>
using namespace std;



////������
//struct Tnode;
//typedef struct Tnode Tnode;
//struct Tnode {
//	int elm;//���
//	int w;//Ȩ��
//	Tnode* left;
//	Tnode* right;
//};
//
struct Arc;
typedef struct Arc Arc;

struct Arc {
	int head;
	int end;
};

//Tnode Null_node;
//
////��ʼ���սڵ�
////����Ȩ���Լ�Ԫ�ؾ�Ϊ-1�Ľڵ�Ϊ�սڵ�
//void Init_Null_node() {
//	Null_node.elm = -1;
//	Null_node.w = -1;
//}
//
//
////���ɿսڵ�
//Tnode* Generate_node() {
//	Tnode* p = (Tnode*)malloc(sizeof(Tnode));
//	p->left = &Null_node;
//	p->right = &Null_node;
//	return p;
//}


//ȷ��û������ĵ�
bool Finished(vector<int> mem) {

	for (int i = 0; i < mem.size(); i++) {
		if (mem.at(i) == -1) {
			return false;
		}
	}
	return true;

}
void Prin_vec(vector<int> mem) {
	for (int i = 0; i < mem.size(); i++) {
		cout << mem.at(i);
		cout << " ";
	}


	cout << endl;
}
bool In_mem(int x, int y, vector<Arc*> arc_mem) {
	for (int i = 0; i < arc_mem.size(); i++) {
		if ((x == arc_mem[i]->head && y == arc_mem[i]->end)|| (y == arc_mem[i]->head && x == arc_mem[i]->end)) {
			return true;
		}
	}
	return false;
}

int Find_min(vector<vector<int>> mat, int start_num,vector<Arc*> arc_mem,vector<int> num_mem) {
	int pos = -1;
	int w = 1000;
	for (int i = 0; i < mat.size(); i++) {
		if (mat.at(start_num).at(i) < w && mat.at(start_num).at(i) > -1 && !In_mem(start_num,i,arc_mem) && num_mem[i]==-1) {
			pos = i;
			w = mat.at(start_num).at(i);
		}
	}


	return pos;
}

//�ҵ����е���ѵľ���,��ʼλ���Լ���ֵ
int* Find_best(vector<vector<int>> mat, vector<int> num_mem,vector<Arc*> arc_mem) {
	int pos = 0;
	int w = 100000;
	int* mem = (int*)malloc(sizeof(int) * 3); //��һ����Ϊ��ʼλ�ã��ڶ���ֵΪ�յ㣬������ֵΪȨ��

	cout << "Ѱ�ҹ�������С��" << endl;
	for (int i = 0; i < num_mem.size(); i++) {
		if (num_mem.at(i) == -1) {
			cout << "����" << endl;
			continue;
		}
		else{
			pos = Find_min(mat,i,arc_mem,num_mem);
			cout << pos << endl;
			if (pos == -1) { continue;};
			if (mat.at(i).at(pos) < w) {
				w = mat.at(i).at(pos);
				cout << i<<" ";
				cout << pos<<endl;
				mem[1] = pos;
				mem[0] = i;
			}

		}
	}
	mem[2] = w;
	cout << "����" << endl;
	return mem;
}

//�㷨ʵ��
//������� ����+��ʼλ��
void Prim(vector<vector<int>> mat, int start_num) {

	vector<int> se_mem;
	vector<Arc*> arc_mem;

	int* data;
	//��ʼ���ڵ�
	//ȫ���ڵ㵽sed_mem�ľ������� -1
	for (int i = 0; i < mat.size(); i++) {
		se_mem.push_back(-1);
	}
	se_mem.at(start_num) = 0;

	cout << "��ʼ" << endl;
	while (!Finished(se_mem)) {
		data = Find_best(mat, se_mem, arc_mem);
		cout << data[0] << " " << data[1] << " " << data[2] << endl;
		se_mem.at(data[1]) = data[2];
		Prin_vec(se_mem);
		Arc* new_arc = (Arc*)malloc(sizeof(Arc));
		new_arc->head = data[0];
		new_arc->end = data[1];
		arc_mem.push_back(new_arc);
	}


	for (int i = 0; i < arc_mem.size(); i++) {
		cout << arc_mem[i]->head;
		cout << "->";
		cout << arc_mem[i]->end;
		cout << endl;
	}
}


//���Ժ���
void test0() {

	//��ʼ������
	vector<vector<int>> mat;
	int a[6][6] = {
		{-1,6,1,5,-1,-1},
		{6,-1,5,-1,3,-1},
		{1,5,-1,5,6,4},
		{5,-1,5,-1,-1,2},
		{-1,3,6,-1,-1,6},
		{-1,-1,4,2,6,-1},
	};
	for (int i = 0; i < 6; i++) {
		mat.push_back(*(vector<int>*)malloc(sizeof(vector<int>)));
		for (int j = 0; j < 6; j++) {
			mat.at(i).push_back(a[i][j]);
		}
	}

	Prim(mat, 5);

}


//������
void main() {

	test0();




}