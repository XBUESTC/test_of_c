/*
��Ŀ
1.˳���ĳ�ʼ�������������롢���ҡ�ɾ��
2.������ĳ�ʼ�������������룬ɾ��
3.�ӷ��⣺����ѭ������ʵ��Լɪ������
*/


/*
1.˳���ĳ�ʼ�������������ҡ�ɾ�� *******************************************************************
*/
#include<iostream>
#include<iostream>
#include<stdio.h>

#define MAX_LENGTH 100

using namespace std;

/*
1.˳���
*/
//����״̬
typedef int Status;
#define ERROR 0
#define TURE 1
#define OVERFLOWER -1;


//����˳�����
class sunList;
typedef class sunList sunList;



//ʹ������ж���һ��˳���
//�ڶ���һ���������Զ����г�ʼ��
class sunList {
private:
	int length;     //˳�����
	int* head;		//˳���ĳ���

public:
	//��ʼ��
	//���������ĳ�ʼ��
	sunList() {
		length = 0;
		head = (int*)malloc((MAX_LENGTH) * sizeof(int));

	}

	//���εĳ�ʼ��
	//����������ڶ�����󳤶� �� �ض�
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

	//ʹ��[]��Ԫ�ؽ��з���
	//����Ŀǰ�ĳ��ȷ���ERROR
	int* operator[](int num) {
		int* end = head;
		if (num<0 || num>length) {
			cout << "����" << endl;
			return ERROR;
		}
		return end + num - 1;
	}


	//Ԫ�ز���
	//��һ���������֣��ڶ�������λ��
	//����Ŀǰ�ĳ��ȣ�����0
	Status Insert_num(int num, int pos) {
		if (pos >= length || pos < -1) return ERROR;  //����Ŀǰ�ĳ���
		else {
			int* end = head + length;
			for (int i = length; i > pos - 1; i--) { *end = *(end - 1); end--; }
			length++;
			*end = num;
		}
	}
	//Ԫ�ز��루��ĩβ���룩
	Status Insert_num(int num) {
		int* end = head;
		end = head + num - 1;
		*end = num;
		length++;
		return TURE;
	}

	//Ԫ�صĲ���
	//����һ�����ֲ���
	//�����ҵ��ĵ�һ��λ��
	//���򷵻�-1
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

	//Ԫ�صĴ�ӡ
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

	//Ԫ�ص�ɾ��
	//ɾ��ָ��λ�õ���
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
2.������ĳ�ʼ��,���������룬ɾ�� ********************************************************************************************
*/


class Link_list;
typedef class Link_list Link_list;
struct Node;
typedef struct Node Node;
typedef Node* head;

//��������Ľڵ�
struct Node {
	int elm;
	Node* next;
};

//����������
//����ͷ
//������󳤶�
//�����ĺ���
//����ĳ�ʼ��:���εĳ�ʼ��(���ܸ�������Ĵ���),�����εĳ�ʼ��
//����Ĳ���

class Link_list {
private:

	//�����Ԫ��
	Node* list_head;    //��ͷ
	int length=0;        //����ĳ���

public:


	//��ʼ������Ϊ�������ĳ�ʼ���Լ����������ĳ�ʼ��
	//�޲�����ʼ��                                      //û������
	Link_list() {
		list_head = (Node*)malloc(sizeof(Node));
		//cout << sizeof(list_head) << endl;
		/*list_head = NULL;*/
		//cout << sizeof(list_head) << endl;
	}

	//�������ĳ�ʼ��
	//����һ��int��ָ��                                  //û������
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

	//����Ĳ���                                                //û������
	//˫����,��һ��������Ҫ����������ڶ���������λ��
	Status Insert_elm(int num, int pos) {
		Node* start = list_head;
		start = start->next;;
		if (pos<0 || pos>length) { return ERROR;}  //λ��С��0 ����Ŀǰ��������
		for (int i = 0; i < pos-1; i++) {
			start = start->next;
		}
		//����
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->elm = num;
		new_node->next = start->next;
		start->next = new_node;
		length++;
		return TURE;
	}

	//����Ĳ���
	//�������������������������           //û������
	Status Insert_elm(int elm) {
		Node* start = list_head;
		Node* new_node = (Node*)malloc(sizeof(Node));
		for (int i = 0; i < length; i++) {start = start->next;}
		new_node->elm = elm;
		start->next = new_node;
		length++;
		return TURE;
	}

	//����Ĳ���                             //û������
	//�������һ������
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


	//����Ĵ�ӡ                  //û������
	void Print_list() {
		Node* start = list_head;
		start = start->next;
		cout << "����Ԫ��Ϊ:";
		for (int i = 0; i < length;i++) {
			cout << start->elm;
			cout << "  ";
			start = start->next;
		}
		cout << endl;
	}

	//�����ɾ��                    //û������
	void Delete_elm(int pos) {
		Node* start = list_head;
		if (pos<-1 || pos>length) { cout << "λ�ô���" << endl; return; }
		
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
		cout << "ɾ���ɹ�" << endl;
		length--;
		return;
	}

	//�� ���� ����Ԫ��                    //û������
	int operator[] (int num) {
		Node* start = list_head;
		if (num > length || num < 0) { return OVERFLOW;}

		for (int i = 0; i < num;i++) {
			start = start->next;
		}
		return start->elm;
	}



};

//3.Լɪ������
//����ѭ������ʵ��Լɪ������
/*
Լɪ�����⣺n����Χ��һȦ����ʼ��Ŵ�1~n���У�
��Լ�����Ϊx���˿�ʼ������������m���˳�Ȧ��
�����ִ�1��ʼ������������m�����������˳�Ȧ��
�Դ����ƣ����Ȧ��ֻʣ��һ���ˣ�
����˾���Ӯ�ң����Ӯ�ҵı�š�
*/

class xunlist;
typedef xunlist xunlist;
struct xun_Node;
typedef xun_Node xun_Node;
typedef xun_Node* head_xun;


//�˵����Զ���
struct xun_Node {
	int num;            //�˵ı��
	int state;          //�˵�״̬ 0:����,1�ڳ�
	xun_Node* next;         //ָ����һ��
};


//������Ķ���
class xunlist {

public:
	int length = 0; //���г���
	xun_Node* head;//����ͷ

	int left; //ʣ�µ���  ��Ϊ��Ϸ�����ı�־

	int game_num = 1;
	xun_Node* current; //��ǰ���е�����
	//�޲γ�ʼ��
	//�ڵ�����,����ָ���Լ�
	xunlist(){
		head = (xun_Node*)malloc(sizeof(xun_Node));
		head->next = head;
		head->state = 1;
	}

	//�вγ�ʼ��
	//�б��Լ���Ҫ�ĳ���
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

	//������ڽ�����Ϸ����
	void Print_gaming() {
		cout << "��ǰʣ�����:" << endl;
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

	//��Ϸ��ʼ
	//���� ��Ҫ������

	void Game_start(int num) {

		if (length == 0) {return;}  //û�г�ʼ��
		
		//��ʼ
		//�˳����� ʣ��һ��
		left = length;          //��ʼ������
		current = head;			//��ʼλ��
		cout << "��Ϸ��ʼ" << endl;
		/*Print_gaming();*/
		cout << endl;

		int i = 0;
		while (left > 1) {

			cout << endl;
			cout << "��" << game_num - 1 << "��" << endl;
			cout << "current=" << current->num << endl;
			while (1) {
				while (current->state == 0) { current = current->next; }  //��û����̭��
				i++;                  //�ҵ���;

				if (i>=num) {break;} //������Ŀ�����˳�;

				current=current->next;//����һ����ʼ������;
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
		cout << "��ʤ��: ��� " << start->num <<"��" << endl;;
	}

	//��ʼʱ ��Ҽ���
	
	void Insert_num(int num){
		if (game_num != 1) { return; } //��Ϸδ��ʼ
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
���Ժ��� ****************************************************************************************************
*/

//���Ա�Ĳ���

void test0() {
	sunList list;
	int i = 10;
	while (i>0) {
		list.Insert_num(i);
		i--;
	}
	list.Print_Elm();

	cout << "[]����" << endl;
	cout << *list[5] << endl;
	cout << "����" << endl;
	list.Insert_num(0, 1);
	list.Print_Elm();
	cout << "����" << endl;
	cout<<list.Find_Elm(5)<<endl;
	cout << "ɾ��" << endl;
	list.Del_Elm(3);
	list.Print_Elm();

}

//����Ĳ���
void test1() {
	Link_list list;

	cout << "�޲γ�ʼ�����ֵ" << endl;
	for (int i = 0; i < 5; i++) {
		list.Insert_elm(i);
	}
	list.Print_list();

	int num[]={0,1,2,3,4,5};
	cout << "�������ĳ�ʼ��" << endl;
	Link_list  list1(num,sizeof(num)/sizeof(int));
	list1.Print_list();
 	
	cout << "Ԫ�ص�ɾ��" << endl;
	list.Delete_elm(5);
	list.Print_list();
	list1.Print_list();
	list1.Insert_elm(5, 4);
	list1.Print_list();

	cout << list[1] << endl;
}

//Լɪ���������
////��Ʋ��Ժ����㷨����
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
//		cout << "��" << game_num << "��" << endl;
//		while (true) {
//			//�˳���ѭ�������� ��������num ��
//			if (current->state == 0) { current = current->next; continue; } //����̭�������Զ�����
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











