//(1) 实现二叉树中序遍历的递归算法。
//(2) 实现二叉树中序遍历的非递归算法。

#include<iostream>
using namespace std;


//要完成中序遍历
//1.先要完成树的建立（数的初始化，数的插入，数的遍历）
//2.为了完成树的中序遍历，确定树的结构以及节点的组成
//要完成递归以及非递归就要找到相似的结构



//方法一、普通的二叉树结构（左右节点）的遍历
// 普通的二叉树有两种
// 1.有父以及儿子的执政
// 2.只有父亲或者儿子的指针
//方法二、线索二叉树的结构（包含遍历前、后的节点指针以及字子节点）



//中序遍历
//一、普通的二叉树结构

//普通二叉树的节点的定义
//双向的节点
struct Pt_node;
typedef struct Pt_node Ptnode;
typedef struct Pt_node Pt_node;


struct Pt_node{
	char elm;          //节点元素
	Ptnode* son_left;    //左子树
	Ptnode* son_right;   //右子树
	Ptnode* father;      //父
	bool  is_search;
};


Pt_node* NULL_NODE; //定义的一个空节点
void Init_nullnode();

//创建一个新的普通的节点
Pt_node* Create_Pnode();
//struct  Ptree_stack;
//typedef struct Ptree_stack Ptree_stack;

//需要用到栈
class  Ptree_stack {
public:
	int stack_length;  //栈的长度
	Pt_node** mem_begin;//存储已经遍历的点的开始
	Pt_node** mem_end; //存储已经遍历的点的结尾


	void stack_push(Pt_node* p); //入栈
	Pt_node* stack_pop();//出栈
	void Init_stack(); //初始化堆栈
	void Show_top();//显示栈顶的元素
	void Print_stack();//打印栈元素

	//void reset();//重置元素栈元素;

};

//需要用到队列
class Ptree_queue {

public:
	int queue_length;//队列的长度
	Pt_node** start;//队列的头
	Pt_node** end;//队列的尾
	Pt_node** begin_inital; //队列的头固定
	int queue_length_inital; //队列的最初长度
	void Init_queue();//初始化队列
	void queue_in(Pt_node* new_node);//入队
	Pt_node* queue_out();//出队

	void Print_queue();//打印队列列表
	void Reset();//将队列重置

};
//树的定义

class P_tree {
public:
	Pt_node* root;	//树的根节点
	int num;		//目前的节点数
	Ptree_queue create_queue;// 创建时所用的队列
	Ptree_stack search_stack;//遍历所用的堆栈


	P_tree();//初始化
	void Root_Init();//根节点初始化
	void Greate_Ptree(int node_num);//创建一个确定的节点
	void Insert_Node(Ptnode* new_node);//插入一个节点

	void Sreach_Z();//中序遍历  不需要进行迭代


	void Sreach_Z_digui(int &count_num, Pt_node*  &p);//中序遍历 递归


	void Print_tree();//将树打印出来


	void Search_left(Pt_node* &p, int& count_num);//历遍左子树
	void Search_right(Pt_node* &p, int& count_num);//历遍右子树


	void Reset_flag();//将树元素重置   将标志为重写
};



/***********************************通用函数****************************************/
//创建一个新的节点
Pt_node* Create_Pnode() {
	Pt_node* p = (Pt_node*)malloc(sizeof(Pt_node));
	p->elm = '\0';
	p->father=NULL_NODE;
	p->son_left=NULL_NODE;
	p->son_right=NULL_NODE;
	p->is_search = false;
	return p;
}

//空节点的定义
void Init_nullnode() {
	NULL_NODE = (Pt_node*)malloc(sizeof(Pt_node));
	NULL_NODE->elm = '\0';
}

/********************************************树函数的定义****************************************/
//树类的初始化定义 
P_tree::P_tree(){
	this->num = 0;
	Init_nullnode();
	this->Root_Init();
	(this->create_queue).Init_queue();
	(this->search_stack).Init_stack();
 }


//根的初始化
void P_tree::Root_Init() {
	Pt_node* p = Create_Pnode();
	this->root = p;
}


//创建树
//输入参数需要的点数
void P_tree::Greate_Ptree(int node_num){
	this->num = node_num;

	//创建树
	//先对需要插入树的元素进行定义
	char* tree_elm;
	tree_elm = (char*)malloc(sizeof(char) * node_num);

	char* elm_p = tree_elm;

	for (int i = 0; i < node_num; i++) {
		if (i >= 0 && i <= 27) {
			*elm_p = 'a' + i;
			elm_p++;
		}
		else if (i >= 28 && i <= 54) {
			*elm_p ='A'+(i-28);
			elm_p++;
		}	
		else {
			cout << "长度已经超过定义的能够辨别的字符种类，需要重新定义字符" << endl;
		}
	}

	//创建树
	Pt_node* p = this->root;
	elm_p = tree_elm;
	//cout << p->elm << endl;
	cout << "正在创建树......" << endl;
	cout << endl;

	int ci = 0;
	while (ci < node_num) {
		//第一次初始化
		//初始化成功
		cout << ci << endl;
		if (!ci) {
			p->elm = *(elm_p); elm_p++;
			this->create_queue.queue_in(p);
			ci++;
			continue;
		}

		cout << (p->son_left == NULL_NODE);
		cout << (p->son_right == NULL_NODE) << endl;
		//检测尾节点是否为插满，满了后出队
		if ((p->son_left != NULL_NODE) && (p->son_right != NULL_NODE)) {
			p = this->create_queue.queue_out();
			cout << p->elm << endl;
			cout << "出队" << endl;
		}
		//没有满则确定其子树加在哪
		else {
			p = *this->create_queue.start;
			cout << (p)->elm << endl;
			if (p->son_left == NULL_NODE) {
				p->son_left = Create_Pnode();
				p->son_left->elm = *(elm_p);
				cout << "左节点建立" << endl;
				cout << p->son_left->elm << endl;
				this->create_queue.queue_in(p->son_left);
				ci++;
				elm_p++;
			}
			else {
				p->son_right = Create_Pnode();
				p->son_right->elm = *(elm_p);
				cout << "右节点建立" << endl;
				cout << p->son_right->elm << endl;
				this->create_queue.queue_in(p->son_right);
				ci++;
				elm_p++;
			}
		}
	}
	//cout << this->create_queue.queue_length << endl;
	//cout << (*(this->create_queue.start))->son_left->elm << endl;
	
	cout << "创建成功........" << endl;
	cout << endl;
}


void P_tree::Insert_Node(Ptnode* new_node) {
	cout << endl;
	cout << "插入数据中......" << endl;

	Pt_node* p = *this->create_queue.start;
	Pt_node* p1;
	if (p->son_left!=NULL_NODE && p->son_right!=NULL_NODE) {
		p1=this->create_queue.queue_out();
		p1->son_left = new_node;
		this->create_queue.queue_in(new_node);
		this->num++;
		this->create_queue.queue_length++;
	}
	else {
		if (p->son_left==NULL_NODE) {
			p->son_left = new_node;
			this->create_queue.queue_in(new_node);
			this->num++;
			this->create_queue.queue_length++;
		}
		else {
			p->son_right = new_node;
			this->create_queue.queue_in(new_node);
			p1 = this->create_queue.queue_out();
			this->num++;
			this->create_queue.queue_length++;
		}
	}
	cout << "插入完成" << endl;
}



//void Cp_pos();//计算插入值所在位置	
//void Sreach_Z();//中序遍历
//void Print_tree();//将树打印出来

//中序遍历     非递归
void P_tree::Sreach_Z(){


	int search_num = 0;//中序遍历的节点数
	Pt_node* p = this->root;

	this->search_stack.stack_push(p);
	this->search_stack.Show_top();

	while (search_num < this->num) {
		if (p->son_left != NULL_NODE && !p->son_left->is_search) {
			this->search_stack.stack_push(p->son_left);
			p = p->son_left;
			this->search_stack.Show_top();
		}
		else {
			cout << "最左节点找到" << endl;
			p = this->search_stack.stack_pop();
			cout << p->elm << endl;
			p->is_search = true;
			search_num++;
			cout << search_num << endl;
			if (p->son_right != NULL_NODE) {
				cout << "左子树不为空，已其为根节点继续遍历" << endl;
				this->search_stack.stack_push(p->son_right);
				p = p->son_right;
				this->search_stack.Show_top();
			}
		}
	}
}

//中序遍历递归
//需要遍历左子树
//需要遍历右子树

//遍历左子树
//递归
void P_tree::Search_left(Pt_node* &p,int &count_num){
	if (p->son_left != NULL_NODE && !p->son_left->is_search) {
		this->search_stack.stack_push(p->son_left);
		p = p->son_left;
	}
	else {
		p = this->search_stack.stack_pop();
		cout << p->elm << endl;
		p->is_search = true;
		count_num++;
		cout << count_num << endl;
	}
}

void P_tree::Search_right(Pt_node*  &p, int &count_num) {
	if (p->son_right != NULL_NODE) {
		this->search_stack.stack_push(p->son_right);
		p = p->son_right;
	}
}



void P_tree::Sreach_Z_digui(int &count_num,Pt_node* &p) {
	if (count_num >= this->num) {return;}    //迭代结束的标志
	if (!count_num) {
		this->search_stack.stack_push(p);
		cout << count_num << endl;
		this->Sreach_Z_digui(count_num, p);
	}

	//遍历左子树
	this->Search_left(p, count_num);

	//遍历右子树
	this->Search_right(p,count_num);

	//再次执行迭代
	this->Sreach_Z_digui(count_num, p);
}



//打印树
//先序遍历
void P_tree::Print_tree(){
	cout << "打印树" << endl;
	Pt_node** p = this->create_queue.begin_inital;
	int i = 0;
	int f = 1;//第几层
	Pt_node* pos=(*(this->create_queue.begin_inital))->son_right;

	while (1) {
		if (!i) {
			cout << "第" << f << "层" << endl;
			cout << (*p)->elm << endl;
			p++;
			f++;
		}

		cout << "第" << f << "层" << endl;
		while (*p != pos) {
			if (i >= this->num - 1) {break;}
			cout << (*p)->elm;
			cout << " ";
			p++;
			i++;
		}
		if (i >= this->num - 1) { break;}
		cout<< (*p)->elm;
		p++;
		i++;

		cout << endl;
		pos = (*(p-1))->son_right;
		f++;
	}
	cout << endl;
}


void P_tree::Reset_flag() {
	Pt_node** p = this->create_queue.begin_inital;
	for (int i = 0;i < this->num;i++) {
		(*p)->is_search = false;
		p++;
	}
}


/***********************************************堆栈函数定义********************************/
//初始化堆栈
void Ptree_stack::Init_stack() {

	//最多存储100个点
	Pt_node** p = (Pt_node**)malloc(sizeof(Pt_node*)*100);
	this->mem_begin = p;
	this->mem_end = p;
	this->stack_length = 0;
}

//void stack_push(Pt_node* p); //入栈
//Pt_node stack_pop();//出栈
//void Init_stack(); //初始化堆栈

//入栈
void Ptree_stack::stack_push(Pt_node* p) {
	if (stack_length >= 100) { cout << "堆栈溢出" << endl; return;}
	this->mem_end++;
	*this->mem_end = p;
	this->stack_length++;
}

//出栈
Ptnode* Ptree_stack::stack_pop() {
	Pt_node* p=*(this->mem_end);
	*this->mem_end=NULL_NODE;
	*this->mem_end--;
	this->stack_length--;
	return p;
}

//打印栈的元素
void Ptree_stack::Print_stack() {

	cout << endl;
	cout << "正在打印栈中的元素......" << endl;
	
	Pt_node* p = *this->mem_begin;
	p++;
	for (int i = 0; i < this->stack_length; i++) {
		cout << p->elm;
		cout << " ";
		p++;
	}
	cout << "打印结束" << endl;
}


//显示栈顶的元素
void Ptree_stack::Show_top() {
	cout << endl;
	cout << "栈顶的元素为" << (*this->mem_end)->elm<<endl;
	cout << endl;
}


/*
************************队列函数的定义*********/

//void Init_queue();//初始化队列
//void queue_in(Pt_node* new_node);//入队
//Pt_node* queue_out();//出队
//
//void Print_queue();//打印队列列表



//队列的初始化
void Ptree_queue::Init_queue() {
	//最多容纳100个点
	Pt_node** p = (Pt_node**)malloc(sizeof(Pt_node*)*100);
	this->start=p;
	this->end=p;
	this->begin_inital=p;
	this->queue_length = 0;
}

//入队
void Ptree_queue::queue_in(Pt_node* new_node){
	*(this->end)=new_node;
	this->end++;
	this->queue_length++;
}

//出队
Pt_node* Ptree_queue::queue_out() {
	this->start++;
	this->queue_length++;
	return *(this->start);
}


//打印队列
void Ptree_queue::Print_queue() {
	Pt_node* p = *(this->start);
	cout << endl;
	cout << "正在打印队列" << endl;
	for (;p != *(this->end); p++) {
		cout << p->elm;
		cout << " ";
	}
	cout << "打印完成" << endl;
}

//重置队列头指针
void Ptree_queue::Reset() {
	this->start = this->begin_inital + 1;
}



//差一个测试函数
void test0() {

	//P_tree();//初始化
	//void Root_Init();//根节点初始化
	//void Greate_Ptree(int node_num);//创建一个确定的节点
	//void Insert_Node(Ptnode * new_node);//插入一个节点
	//void Sreach_Z();//中序遍历
	//void Print_tree();//将树打印出来



	P_tree tree; //创建树
	tree.Greate_Ptree(10);//创建完成
	tree.Print_tree();//打印完成


	Pt_node* p = Create_Pnode();
	p->elm = 'a' + 10;

	cout << endl;
	tree.Insert_Node(p);

	cout << endl;
	cout << "检测新插入数据是否正常"<<endl;
	cout << (*(tree.create_queue.end-1))->elm << endl;

	cout << endl;
	tree.Print_tree();//打印完成

	
	tree.Reset_flag();
	cout << "中序遍历" << endl;
	tree.Sreach_Z();//中序遍历     成功
	
    //将堆栈初始化
	//中序遍历递归
	//tree.Reset_flag();
	//int num_count = 0;
	//Pt_node* p1 = tree.root;
	//tree.Sreach_Z_digui(num_count, p1);

}

void main(){
	test0();
}













