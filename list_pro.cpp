/*
题目
1.顺序表的初始化、建立、插入、查找、删除
2.单链表的初始化，建立，插入，删除
3.加分题：采用循环链表实现约瑟夫问题
*/


/*
1.顺序表的初始化、建立、查找、删除 *******************************************************************
*/
#include<iostream>
#include<iostream>
#include<stdio.h>

#define MAX_LENGTH 100

using namespace std;

/*
1.顺序表
*/
//定义状态
typedef int Status;
#define ERROR 0
#define TURE 1
#define OVERFLOWER -1;


//定义顺序表类
class sunList;
typedef class sunList sunList;



//使用类进行定义一个顺序表
//在定义一个变量后自动进行初始化
class sunList {
private:
	int length;     //顺序表长度
	int* head;		//顺序表的长度

public:
	//初始化
	//不带参数的初始化
	sunList() {
		length = 0;
		head = (int*)malloc((MAX_LENGTH) * sizeof(int));

	}

	//带参的初始化
	//输入数组大于定义最大长度 则 截断
	//sunList(int* int_list,int length_num) {
	//	sunList();
	//	int* start = head;
	//	while (length_num) {
	//		if (length > MAX_LENGTH) { return;}
	//		*start = *int_list;
	//		start++;
	//		int_list++;
	//		length++;
	//	}
	//}

	//使用[]对元素进行访问
	//超出目前的长度返回ERROR
	int* operator[](int num) {
		int* end = head;
		if (num<0 || num>length) {
			cout << "错误" << endl;
			return ERROR;
		}
		return end + num - 1;
	}


	//元素插入
	//第一个参数数字，第二个参数位置
	//超出目前的长度，返回0
	Status Insert_num(int num, int pos) {
		if (pos >= length || pos < -1) return ERROR;  //超出目前的长度
		else {
			int* end = head + length;
			for (int i = length; i > pos - 1; i--) { *end = *(end - 1); end--; }
			length++;
			*end = num;
		}
	}
	//元素插入（在末尾插入）
	Status Insert_num(int num) {
		int* end = head;
		end = head + num - 1;
		*end = num;
		length++;
		return TURE;
	}

	//元素的查找
	//输入一个数字参数
	//返回找到的第一个位置
	//否则返回-1
	int Find_Elm(int num) {
		int* end = head;
		int i = 0;
		while (i < length) {
			if (num == *end) {
				return i + 1;
			}
			end++;
			i++;
		}
		return OVERFLOWER;
	}

	//元素的打印
	void Print_Elm() {
		int* end = head;
		int i = length;
		while (i > 0) {
			cout << *end;
			cout << " ";
			i--;
			end++;
		}
		cout << endl;
	}

	//元素的删除
	//删除指定位置的数
	Status Del_Elm(int pos) {

		if (pos >= length || pos < 0) { return ERROR; }
		int* end = head;
		end += pos;
		end--;
		for (int i = length - pos; i >0; i--) {
			*end = *(end + 1);
			end++;
		}

		//free(end);
		//realloc(head, sizeof(MAX_LENGTH * sizeof(int)));
		*end = NULL;
		return TURE;
	};

};


/*
2.单链表的初始化,建立，插入，删除 ********************************************************************************************
*/


class Link_list;
typedef class Link_list Link_list;
struct Node;
typedef struct Node Node;
typedef Node* head;

//定义链表的节点
struct Node {
	int elm;
	Node* next;
};

//定义链表类
//包含头
//链表最大长度
//基本的函数
//链表的初始化:带参的初始化(功能覆盖链表的创建),不带参的初始化
//链表的插入

class Link_list {
private:

	//链表的元素
	Node* list_head;    //表头
	int length=0;        //链表的长度

public:


	//初始化：分为带参数的初始化以及不带参数的初始化
	//无参数初始化                                      //没有问题
	Link_list() {
		list_head = (Node*)malloc(sizeof(Node));
		//cout << sizeof(list_head) << endl;
		/*list_head = NULL;*/
		//cout << sizeof(list_head) << endl;
	}

	//带参数的初始化
	//输入一个int的指针                                  //没有问题
	Link_list(int elm_list[],int length_list) {
	/*	if (length_list > sizeof(elm_list) / sizeof(int) || length_list < 0) { return;}*/
		list_head = (Node*)malloc(sizeof(Node));
		Node* p;
		Node* start = list_head;
		//cout << length_list << endl;
		for (int i = 0; i < length_list;i++) {
			p = (Node*)malloc(sizeof(Node));
			p->elm = elm_list[i];
			//cout << elm_list[i]<<endl;
			start->next = p;
			start = p;
			length++;
		}
	}

	//链表的插入                                                //没有问题
	//双参数,第一个参数是要插入的数，第二个参数是位置
	Status Insert_elm(int num, int pos) {
		Node* start = list_head;
		start = start->next;;
		if (pos<0 || pos>length) { return ERROR;}  //位置小于0 大于目前的链表长度
		for (int i = 0; i < pos-1; i++) {
			start = start->next;
		}
		//插入
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->elm = num;
		new_node->next = start->next;
		start->next = new_node;
		length++;
		return TURE;
	}

	//链表的插入
	//单参数，插入的树，从最后插入           //没有问题
	Status Insert_elm(int elm) {
		Node* start = list_head;
		Node* new_node = (Node*)malloc(sizeof(Node));
		for (int i = 0; i < length; i++) {start = start->next;}
		new_node->elm = elm;
		start->next = new_node;
		length++;
		return TURE;
	}

	//链表的插入                             //没有问题
	//插入的是一个数组
	Status Insert_elm(int* elm) {
		Node* start = list_head;
		Node* new_node;
		for (int i = 0; i < length; i++) { start = start->next;}
		while (*elm) {
			new_node = (Node*)malloc(sizeof(Node));
			new_node->elm = *elm;
			start->next = new_node;
			elm++;
			length++;
			}
		return TURE;
	}


	//链表的打印                  //没有问题
	void Print_list() {
		Node* start = list_head;
		start = start->next;
		cout << "链表元素为:";
		for (int i = 0; i < length;i++) {
			cout << start->elm;
			cout << "  ";
			start = start->next;
		}
		cout << endl;
	}

	//链表的删除                    //没有问题
	void Delete_elm(int pos) {
		Node* start = list_head;
		if (pos<-1 || pos>length) { cout << "位置错误" << endl; return; }
		
		for (int i = 0; i < pos - 1; i++) {
			start = start->next;
		}

		if (pos == length) {
			start->next = NULL;
			free(start->next);
		}
		else {
			Node* p = start->next;
			start->next = start->next->next;
			free(p);
		}
		cout << "删除成功" << endl;
		length--;
		return;
	}

	//用 【】 访问元素                    //没有问题
	int operator[] (int num) {
		Node* start = list_head;
		if (num > length || num < 0) { return OVERFLOW;}

		for (int i = 0; i < num;i++) {
			start = start->next;
		}
		return start->elm;
	}



};

//3.约瑟夫问题
//采用循环链表实现约瑟夫问题
/*
约瑟夫问题：n个人围成一圈，初始编号从1~n排列，
从约定编号为x的人开始报数，数到第m个人出圈，
接着又从1开始报数，报到第m个数的人又退出圈，
以此类推，最后圈内只剩下一个人，
这个人就是赢家，求出赢家的编号。
*/

class xunlist;
typedef xunlist xunlist;
struct xun_Node;
typedef xun_Node xun_Node;
typedef xun_Node* head_xun;


//人的属性定义
struct xun_Node {
	int num;            //人的编号
	int state;          //人的状态 0:出局,1在场
	xun_Node* next;         //指向下一个
};


//队列类的定义
class xunlist {

public:
	int length = 0; //队列长度
	xun_Node* head;//队列头

	int left; //剩下的人  作为游戏结束的标志

	int game_num = 1;
	xun_Node* current; //当前进行到的人
	//无参初始化
	//节点生成,并且指向自己
	xunlist(){
		head = (xun_Node*)malloc(sizeof(xun_Node));
		head->next = head;
		head->state = 1;
	}

	//有参初始化
	//列表以及需要的长度
	xunlist(int* elm_list,int elm_length) {
		xunlist();
		xun_Node* start = head;
		xun_Node* new_node;

		for (int i = 0; i < elm_length; i++) {
			new_node = (xun_Node*)malloc(sizeof(xun_Node));
			new_node->num = elm_list[i];
			new_node->state = 1;

			start->next = new_node;
			new_node->next = head;
	
			start = new_node;
			length++;
		}
	}

	//输出还在进行游戏的人
	void Print_gaming() {
		cout << "当前剩余玩家:" << endl;
		xun_Node* start = head;
		for (int i = 0; i < length; i++) {
			if (!start->state) { start=start->next;continue; }
			else {
				cout << start->num;
				cout << " ";
				start = start->next;
			}
		}
		game_num++;
		cout << endl;
	}

	//游戏开始
	//参数 需要报的数

	void Game_start(int num) {

		if (length == 0) {return;}  //没有初始化
		
		//开始
		//退出条件 剩余一人
		left = length;          //初始化人数
		current = head;			//开始位置
		cout << "游戏开始" << endl;
		/*Print_gaming();*/
		cout << endl;

		int i = 0;
		while (left > 1) {

			cout << endl;
			cout << "第" << game_num - 1 << "局" << endl;
			cout << "current=" << current->num << endl;
			while (1) {
				while (current->state == 0) { current = current->next; }  //找没被淘汰的
				i++;                  //找到了;

				if (i>=num) {break;} //到达数目可以退出;

				current=current->next;//从下一个开始继续找;
			}
			cout << "current=" << current->num << endl;
			current->state= 0;


			left--;
			i = 0;
			print_p();
			game_num++;
		}


		xun_Node* start=head;
		for (; start->state != 1; start = start->next)

		cout << "game over" << endl;
		cout << "获胜者: 玩家 " << start->num <<"号" << endl;;
	}

	//开始时 玩家加入
	
	void Insert_num(int num){
		if (game_num != 1) { return; } //游戏未开始
		xun_Node* start = head;

		if (length != 0) {
			for (int i = 1; i < length; i++) {
				start = start->next;
			}
			xun_Node* new_mem = (xun_Node*)malloc(sizeof(xun_Node));
			new_mem->num = num;
			new_mem->state = 1;
			start->next = new_mem;
			new_mem->next = head;
		}
		else {
			start->num = num;
		}
		length++;
	}

	void print_p() {
		xun_Node* start = head;
		for (int i = 0; i < length; i++) {
			cout<<start->num<<" " << start->state << endl;
			start = start->next;
		}
	}

};

/*
测试函数 ****************************************************************************************************
*/

//线性表的测试

void test0() {
	sunList list;
	int i = 10;
	while (i>0) {
		list.Insert_num(i);
		i--;
	}
	list.Print_Elm();

	cout << "[]访问" << endl;
	cout << *list[5] << endl;
	cout << "插入" << endl;
	list.Insert_num(0, 1);
	list.Print_Elm();
	cout << "查找" << endl;
	cout<<list.Find_Elm(5)<<endl;
	cout << "删除" << endl;
	list.Del_Elm(3);
	list.Print_Elm();

}

//链表的测试
void test1() {
	Link_list list;

	cout << "无参初始化后插值" << endl;
	for (int i = 0; i < 5; i++) {
		list.Insert_elm(i);
	}
	list.Print_list();

	int num[]={0,1,2,3,4,5};
	cout << "带参数的初始化" << endl;
	Link_list  list1(num,sizeof(num)/sizeof(int));
	list1.Print_list();
 	
	cout << "元素的删除" << endl;
	list.Delete_elm(5);
	list.Print_list();
	list1.Print_list();
	list1.Insert_elm(5, 4);
	list1.Print_list();

	cout << list[1] << endl;
}

//约瑟夫问题测试
////设计测试核心算法案例
//struct test_sim;
//typedef test_sim test_sim;
//
//struct test_sim {
//	int num;
//	int state;
//	test_sim* next;
//};
//
//void print_list(test_sim* sim) {
//	for (int i = 0; i < 10; i++) {
//		if (sim->state == 0) {continue;}
//		cout << sim->num;
//		cout << " ";
//	}
//	cout << endl;
//}
//
//
//
//void test03() {
//	test_sim  sim[10];
//	for (int i = 0; i < 10; i++) {
//		sim[i].state = 1;
//		sim[i].num = i;
//	}
//	for (int i = 0; i < 9; i++) {
//		sim[i].next = &sim[i + 1];
//	}
//	sim[9].next = &sim[0];
//
//	int num = 2;
//	int left = sizeof(sim) / sizeof(test_sim);
//	test_sim* current = sim;
//	int game_num = 1;
//	int i = 0;
//
//	while (left > 1) {
//		cout << endl;
//		cout << "第" << game_num << "局" << endl;
//		while (true) {
//			//退出该循环的条件 数数到达num 个
//			if (current->state == 0) { current = current->next; continue; } //到淘汰的人则自动跳过
//			else {
//				if (i != num - 1) { i++; current = current->next; }
//				else {
//					current->state = 0;
//					current = current->next;
//					left--; break;
//				}
//			}
//		}
//		i = 0;
//		print_list(sim);
//		game_num++;
//	}
//
//}


void test02() {
	xunlist list;
	//i
	for (int i = 0; i < 10; i++) {
		list.Insert_num(i);
	}

	////list.Print_gaming();
	list.Game_start(3);
	//list.print_p();
	// 	int game_num = 1;
	/*xun_Node* start = list.head;*/


	//for (int i = 0; i < 20; i++) {
	//	cout << start->num << endl;
	//	start = start->next;
	//}

	return;
}


void main() {
	test0();
	/*test1();*/


	/*test02();*/
	system("pause");
}











