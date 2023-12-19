#include<iostream>
#include<iostream>
#define MAX_NUM  50  //图最大的顶点数
#define INF     -1  //定义极大值
#include<vector>

using namespace std;

//弧的定义
struct Arcnode;
typedef struct Arcnode Arcnode;
struct Arcnode {
	int h_num;//弧尾节点
	Arcnode* next_arc;//指向下一个弧
	int w;//弧上的权重
};

//节点定义
struct Vnode;
typedef struct Vnode Vnode;
struct Vnode {
	int num;//节点序号
	int arc_num;//关联弧的数目;
	Arcnode* first_arc; //第一条弧
};
typedef Vnode Vnode_list[MAX_NUM];



//定义一个图结构体
struct Gram;
typedef struct Gram Gram;
struct Gram {
	int point_num;//图里的点数
	int arc_num;//图里的弧数
	Vnode_list node_list; //存储点以及相关的弧
	int gram_type; //0 有向图 1无向图
};

Arcnode arc_null; //空节点


//定义最小生成树的节点
struct Tnode;
typedef struct Tnode Tnode;
typedef Tnode* Troot;
struct Tnode {
	int elm;  //元素
	int w;//权重
	Tnode* left;//左节点
	Tnode* right;//右节点
};

Tnode T_null;

//初始化图
void Init_gram(Gram &gram) {
	gram.point_num = 0;
	gram.arc_num = 0;
}

//输入图
// //输入参数矩阵、参数类型、图
void Generate_gram(vector<vector<int>> mat,int gramtype,Gram& gram){
	int sum_arc = 0;
	for (int i = 0; i < mat.size(); i++) {
		gram.node_list[i].num = i;
		gram.node_list[i].first_arc = (Arcnode*)malloc(sizeof(Arcnode));
		gram.node_list[i].arc_num=0;
		Arcnode* p = gram.node_list[i].first_arc;
		for(int j = 0; j < mat.size();j++){
			if (i == j) {continue;}
			if ((mat.at(i)).at(j) != -1){
				p->next_arc=(Arcnode*)malloc(sizeof(Arcnode));
				p->h_num = j;
				p->w = (mat.at(i)).at(j);
				gram.node_list[i].arc_num++;
				p = p->next_arc;
			}
		}
		sum_arc += gram.node_list[i].arc_num;
	}
	cout << sum_arc << endl;
	gram.point_num = mat.size();
	gram.gram_type = gramtype;
	if (!gram.gram_type) {
		gram.arc_num = sum_arc / 2;
	}
	else {
		gram.arc_num = sum_arc;
	}
}

//打印链表存储的图
void Print_gram(Gram gram){
	cout << "打印图" << endl;
	for (int i = 0; i < gram.point_num; i++){
		Arcnode* p = gram.node_list[i].first_arc;
		cout << i << ":" << endl;
		for (int j = 0; j < gram.node_list[i].arc_num;j++) {
			cout << p->h_num;
			cout << " ";
			cout << p->w;
			cout << " ; ";
			p = p->next_arc;
		}
		cout << endl;
	}
	cout << "打印完成" << endl;
}


//判断是否在存储空间中
bool If_in(vector<int> &num_mem, int num) {
	for (int i = 0; i < num_mem.size(); i++) {
		if (num_mem.at(i) == num) {
			num_mem.at(i) = -1;
			return false; //不在
		}
	}
	return true;  //在
}

Arcnode* Get_arc(Arcnode* p,int len,vector<int> mem){
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < mem.size(); j++) {
			if (p->h_num == mem.at(j)) {
				cout << p->h_num << endl;
				return p;
			}
		}
		p = p->next_arc;
	}
	cout << "给空" << endl;
	return &arc_null;
};


//深度优先
//遍历弧
//输入参数图,起始位置
void Depth_Search(Gram gram,int start_num) {
	vector<int> se_num_mem; //没有遍历过的数字
	vector<int> sed_num_mem; //已经遍历过的数字

	cout << endl;
	cout << "深度优先遍历" << endl;

	for (int i = 0; i < gram.point_num; i++) {
		se_num_mem.push_back(i);
	}
	sed_num_mem.push_back(start_num);
	If_in(se_num_mem, start_num);

	Arcnode* p = gram.node_list[start_num].first_arc;

	int pos = 0;
	while (se_num_mem.size() != sed_num_mem.size()) {
		//判断是否在空间中
		//查看当前的顶点相关连的点是否全遍历完如果没有全部遍历完则选取一个最前的点

		for (int i = 0; i < gram.node_list[p->h_num].arc_num; i++) {
			//如果发现存在仍没有遍历的作为遍历的对象同时放入到存储空间
			if (!If_in(se_num_mem, p->h_num)) {
				sed_num_mem.push_back(p->h_num);
				cout << endl;
				cout << "入" << endl;
				cout << p->h_num << endl;
				p = Get_arc(gram.node_list[p->h_num].first_arc, gram.node_list[p->h_num].arc_num,se_num_mem);
				cout << p->h_num << endl;
				break;
			}
			else {
				p = p->next_arc;
				cout << endl;
				cout << "下一个" << endl;
				cout << p->h_num << endl;
			}
		}
		cout << "回头" << endl;


		if (p->h_num == -1) {
			p = gram.node_list[sed_num_mem.at(pos)].first_arc;
			pos++;
		}
		if (pos >= sed_num_mem.size()) {
			break;
		}
	}
	//打印遍历结果
	cout << endl;
	for (int i = 0; i < sed_num_mem.size(); i++) {
		cout << sed_num_mem.at(i);
	}
	cout << endl;
	cout << "遍历结束" << endl;
}

//广度优先
void Width_Search(Gram gram,int start_num) {

	cout << endl;
	cout << "广度优先遍历" << endl;

	vector<int> sed_mem;  //遍历过的点存储
	vector<int> se_mem;  //未遍历的点的存储

	//初始化
	for (int i = 0; i < gram.point_num; i++) {
		se_mem.push_back(i);
	}
	//确定起点
	sed_mem.push_back(start_num);
	If_in(se_mem, start_num);
	Arcnode* p = gram.node_list[start_num].first_arc;
	int pos = 0;


	//开始遍历
	while (se_mem.size() != sed_mem.size()) {
		cout << pos << endl;
		cout << gram.node_list[sed_mem.at(pos)].arc_num << endl;
		for (int i = 0;i< gram.node_list[sed_mem.at(pos)].arc_num; i++) {
			//在里面则
			if (!If_in(se_mem, p->h_num)) {
				//归入已遍历空间
				cout << "入";
				cout << p->h_num << endl;
				sed_mem.push_back(p->h_num);
			}
			cout << "下一个:";
			p = p->next_arc;
			cout << p->h_num << endl;
		}
		pos++;
		p = gram.node_list[sed_mem.at(pos)].first_arc;
	}

	cout << endl;
	cout << "打印结果" << endl;
	//打印遍历结果
	for (int i = 0; i < sed_mem.size(); i++) {
		cout << sed_mem.at(i);
	}
	cout << endl;
	cout << "遍历结束" << endl;
}


//定义一个空的树节点
//权重为-1
//元素为-1
void Init_Tnull() {
	T_null.elm = -1;
	T_null.w = -1;
}

//生成一个新节点
Tnode* Generate_Tnode() {
	Tnode* p = (Tnode*)malloc(sizeof(Tnode));
	p->left = &T_null;
	p->right = &T_null;
	return p;
}

//判断点是否已经遍历
//输入已经遍历空间以及想要遍历的点
bool Not_in(vector<int> mem, int num) {
	for (int i = 0; i < mem.size(); i++) {
		if (mem.at(i) == num) {
			return false;  //已经遍历
		}
	}
	return true; //还未遍历
}


void Init_null() {
	arc_null.w = -1;
	arc_null.h_num = -1;
}

void test0() {

	Init_null();
	cout << arc_null.w << endl;
	cout << arc_null.h_num << endl;


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

	//以下步骤成功
	Gram gram;
	Init_gram(gram);
	int gram_type = 1;//无向图
	

	//生成图
	Generate_gram(mat, gram_type, gram);
	//打印图
	Print_gram(gram);


	//进行图的深度遍历
	Depth_Search(gram,5);

	//图像的广度遍历
	Width_Search(gram,5);

}

void main() {
	test0();
}

