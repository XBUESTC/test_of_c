#include<iostream>
#include<iostream>
#define MAX_NUM  50  //ͼ���Ķ�����
#define INF     -1  //���弫��ֵ
#include<vector>

using namespace std;

//���Ķ���
struct Arcnode;
typedef struct Arcnode Arcnode;
struct Arcnode {
	int h_num;//��β�ڵ�
	Arcnode* next_arc;//ָ����һ����
	int w;//���ϵ�Ȩ��
};

//�ڵ㶨��
struct Vnode;
typedef struct Vnode Vnode;
struct Vnode {
	int num;//�ڵ����
	int arc_num;//����������Ŀ;
	Arcnode* first_arc; //��һ����
};
typedef Vnode Vnode_list[MAX_NUM];



//����һ��ͼ�ṹ��
struct Gram;
typedef struct Gram Gram;
struct Gram {
	int point_num;//ͼ��ĵ���
	int arc_num;//ͼ��Ļ���
	Vnode_list node_list; //�洢���Լ���صĻ�
	int gram_type; //0 ����ͼ 1����ͼ
};

Arcnode arc_null; //�սڵ�


//������С�������Ľڵ�
struct Tnode;
typedef struct Tnode Tnode;
typedef Tnode* Troot;
struct Tnode {
	int elm;  //Ԫ��
	int w;//Ȩ��
	Tnode* left;//��ڵ�
	Tnode* right;//�ҽڵ�
};

Tnode T_null;

//��ʼ��ͼ
void Init_gram(Gram &gram) {
	gram.point_num = 0;
	gram.arc_num = 0;
}

//����ͼ
// //����������󡢲������͡�ͼ
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

//��ӡ����洢��ͼ
void Print_gram(Gram gram){
	cout << "��ӡͼ" << endl;
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
	cout << "��ӡ���" << endl;
}


//�ж��Ƿ��ڴ洢�ռ���
bool If_in(vector<int> &num_mem, int num) {
	for (int i = 0; i < num_mem.size(); i++) {
		if (num_mem.at(i) == num) {
			num_mem.at(i) = -1;
			return false; //����
		}
	}
	return true;  //��
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
	cout << "����" << endl;
	return &arc_null;
};


//�������
//������
//�������ͼ,��ʼλ��
void Depth_Search(Gram gram,int start_num) {
	vector<int> se_num_mem; //û�б�����������
	vector<int> sed_num_mem; //�Ѿ�������������

	cout << endl;
	cout << "������ȱ���" << endl;

	for (int i = 0; i < gram.point_num; i++) {
		se_num_mem.push_back(i);
	}
	sed_num_mem.push_back(start_num);
	If_in(se_num_mem, start_num);

	Arcnode* p = gram.node_list[start_num].first_arc;

	int pos = 0;
	while (se_num_mem.size() != sed_num_mem.size()) {
		//�ж��Ƿ��ڿռ���
		//�鿴��ǰ�Ķ���������ĵ��Ƿ�ȫ���������û��ȫ����������ѡȡһ����ǰ�ĵ�

		for (int i = 0; i < gram.node_list[p->h_num].arc_num; i++) {
			//������ִ�����û�б�������Ϊ�����Ķ���ͬʱ���뵽�洢�ռ�
			if (!If_in(se_num_mem, p->h_num)) {
				sed_num_mem.push_back(p->h_num);
				cout << endl;
				cout << "��" << endl;
				cout << p->h_num << endl;
				p = Get_arc(gram.node_list[p->h_num].first_arc, gram.node_list[p->h_num].arc_num,se_num_mem);
				cout << p->h_num << endl;
				break;
			}
			else {
				p = p->next_arc;
				cout << endl;
				cout << "��һ��" << endl;
				cout << p->h_num << endl;
			}
		}
		cout << "��ͷ" << endl;


		if (p->h_num == -1) {
			p = gram.node_list[sed_num_mem.at(pos)].first_arc;
			pos++;
		}
		if (pos >= sed_num_mem.size()) {
			break;
		}
	}
	//��ӡ�������
	cout << endl;
	for (int i = 0; i < sed_num_mem.size(); i++) {
		cout << sed_num_mem.at(i);
	}
	cout << endl;
	cout << "��������" << endl;
}

//�������
void Width_Search(Gram gram,int start_num) {

	cout << endl;
	cout << "������ȱ���" << endl;

	vector<int> sed_mem;  //�������ĵ�洢
	vector<int> se_mem;  //δ�����ĵ�Ĵ洢

	//��ʼ��
	for (int i = 0; i < gram.point_num; i++) {
		se_mem.push_back(i);
	}
	//ȷ�����
	sed_mem.push_back(start_num);
	If_in(se_mem, start_num);
	Arcnode* p = gram.node_list[start_num].first_arc;
	int pos = 0;


	//��ʼ����
	while (se_mem.size() != sed_mem.size()) {
		cout << pos << endl;
		cout << gram.node_list[sed_mem.at(pos)].arc_num << endl;
		for (int i = 0;i< gram.node_list[sed_mem.at(pos)].arc_num; i++) {
			//��������
			if (!If_in(se_mem, p->h_num)) {
				//�����ѱ����ռ�
				cout << "��";
				cout << p->h_num << endl;
				sed_mem.push_back(p->h_num);
			}
			cout << "��һ��:";
			p = p->next_arc;
			cout << p->h_num << endl;
		}
		pos++;
		p = gram.node_list[sed_mem.at(pos)].first_arc;
	}

	cout << endl;
	cout << "��ӡ���" << endl;
	//��ӡ�������
	for (int i = 0; i < sed_mem.size(); i++) {
		cout << sed_mem.at(i);
	}
	cout << endl;
	cout << "��������" << endl;
}


//����һ���յ����ڵ�
//Ȩ��Ϊ-1
//Ԫ��Ϊ-1
void Init_Tnull() {
	T_null.elm = -1;
	T_null.w = -1;
}

//����һ���½ڵ�
Tnode* Generate_Tnode() {
	Tnode* p = (Tnode*)malloc(sizeof(Tnode));
	p->left = &T_null;
	p->right = &T_null;
	return p;
}

//�жϵ��Ƿ��Ѿ�����
//�����Ѿ������ռ��Լ���Ҫ�����ĵ�
bool Not_in(vector<int> mem, int num) {
	for (int i = 0; i < mem.size(); i++) {
		if (mem.at(i) == num) {
			return false;  //�Ѿ�����
		}
	}
	return true; //��δ����
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

	//���²���ɹ�
	Gram gram;
	Init_gram(gram);
	int gram_type = 1;//����ͼ
	

	//����ͼ
	Generate_gram(mat, gram_type, gram);
	//��ӡͼ
	Print_gram(gram);


	//����ͼ����ȱ���
	Depth_Search(gram,5);

	//ͼ��Ĺ�ȱ���
	Width_Search(gram,5);

}

void main() {
	test0();
}

