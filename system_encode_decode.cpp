#include<iostream>
#define MAX_CODE_NUM 100//����ܹ�ʶ���ַ���
using namespace std;


//�洢�ַ���Ԫ
struct  system_elm {          //ϵͳ�ܹ�ʶ����ַ�
	char elm;					//�ַ�
	int w;						//Ȩ��
	char* code;                 //����
	int code_length;            //���볤�� 
};
typedef struct system_elm   system_elm;

//���ڵ�
struct hf_node;
typedef struct hf_node hf_node;
struct hf_node {             //������������Ľڵ�
	char elm;                   //�ַ�     ��ʼ��Ϊ" "
	int w;                      //��ʼ��Ϊ0
	char code;                //����
	hf_node* right;           //������
	hf_node* left;          //������
};
typedef  hf_node* hf_root;


//ϵͳ����
class System {
public:
	system_elm* can_code_char;       //�������ϵͳ�ܹ�ʶ����ַ����ڳ�ʼ��ʱȷ����С
	hf_root  root;             //��Ź��������ĸ�
	bool if_hf_created;        //��������������־
	bool if_input;             //�Ƿ�����
	int char_size;               //ʶ���������
	char* input_char;           //ϵͳ����
	char* output;               //ϵͳ���

	int code_type;               //��������ַ���������          0��ʾ������Ҫ����  1��ʾ�ַ���Ҫ����

	bool if_get_code;            //�Ƿ��Ѿ���ɱ����ʼ��
	int input_size;
	int output_size;

	System();

	void System_Init(char* p); //��ʼ���ַ���,��ɨ�赽�����ݷŵ�SYS_ELM��     
	void System_Init(system_elm* init_input);        //��ʼ��,��ɨ�赽�����ݷŵ�SYS_ELM��,��Ҫ�Լ������ַ���


	//void Creat_hftree();    //����������������root����
	//void Search_hftree();  //���������������õ�����
	//void Print_hftree();  //��ӡ��������.


	void System_input(char* want_code,int want_code_num);//ϵͳ����
	void System_output();//ϵͳ���      ����0������  ����1������

	void Clear(); //�ع��ʼ״̬
	void Print_elm(); //��ʾ�ܱ���/�����ַ�


	hf_node* Generate_newnode(); //���ڵ���г�ʼ��    //�涨�ַ�Ϊ'/0'��Ϊ��
	void get_hftree(hf_node* &new_root,int &elm_num);  //������
	void Print_tree();                                //��ӡ��
	void Init_root();                                 //��ʼ����
	void Get_code();                               //�������õ�����
	void Print_code();                              //��ӡ����


	//����������ԭ�����
	//���ĺ��
	void Get_hftree_new(hf_node* new_root);        //������
	void Get_code_new();                     //�õ�����
	void Print_newtree();                   //��ӡ��
	void Print_input();									

	//������ϵͳ��ʶ���Լ�����
	void Check_type();

};

//������������
//char Find_min(int* int_list, int list_size, int& num);
system_elm NULL_elm;
hf_node* NULL_node;

//��ʼ�����������Ľڵ�
//�����ַ���
//�����ַ�����ͷ���Լ���С�����峤�Ⱥܴ�
char* Get_code(char* p, int size);


//��ʵ������ĳ�ʼ��
System::System() {
	this->if_hf_created = false;
	this->if_input = false;
	this->if_get_code = false;
}

//�����洢�Ľڵ�
void System::Print_elm() {
	cout << "���ڴ�ӡԪ��" << endl;
	system_elm* p = this->can_code_char;
	for (int i = 0; i < this->char_size; i++) {
		cout << (this->can_code_char+i)->elm<<' ';
		cout << (this->can_code_char +i)->w<<" ";
		if (this->if_get_code){
			char* p1 = (this->can_code_char+i)->code;
			int p2 = (this->can_code_char + i)->code_length;
			for(int i=0;i<p2;i++){
				cout << *(p1+i);
			}
			cout << ' ';
		}
		cout << endl;
	}
	cout << "��ӡ���" << endl;
	cout << endl;
}

//�����ʼ��

//��һ�ִ��λ�ó�ʼ���ı���
void System::System_Init(char* p) {
	cout << "���ڳ�ʼ��" << endl;
	char get_char[100];	//�洢�ַ���
	int get_count[100];		//��¼�ַ������ָ���
	int get_size = 0;												//��¼�ַ�Ŀǰ���ֵ�����
	while (*p) {
		if (!get_size) {*get_char = *p; *get_count = 1;get_size++; p++;} //��ûʵ�������Զ��õ�һ���ַ�����ʵ����
		else {
			for (int i = 0;i<get_size;i++) {
				if (*p == *(get_char + i)) {
					(*(get_count + i))++;
					break;
				}
			}
			if(*p != *(get_char + get_size-1)) {
				*(get_char + get_size) = *p;
				*(get_count + get_size) = 1;
				get_size++;
			}
			p++;
		}
	}
	//cout << "ʶ�����" << endl;
	this->char_size = get_size;     //��ʶ���ַ������͸����洢
	//���õ������ݱ��浽ϵͳ��
	//�����ִ�����С�����������
	//save_size �洢λ��
	int save_size = 0;
	int sort_num[100];
	this->can_code_char = (system_elm*)malloc(sizeof(system_elm) * get_size);
	*sort_num = -1;
	while (save_size!=get_size){
		//����Сֵ
		int num = 1000;
		for (int i = 0; i < get_size; i++) {
			//����ʶ�� 
			if (*(get_count + i) < num && *(sort_num+save_size) < *(get_count + i) && !save_size){
				num = *(get_count+i);
			}
			else if(*(get_count + i) < num && *(sort_num + save_size-1) < *(get_count + i) && save_size){
				num = *(get_count + i);
			}
		}
			*(sort_num + save_size) = num;
			save_size++;
	}

	for (int i = 0; i < get_size; i++){
		(this->can_code_char+i)->w = *(get_count+(*(sort_num+i)-1));
		(this->can_code_char+i)->elm = *(get_char+(*(sort_num+i)-1));
	}
	this->if_input = true;
	cout << "��ʼ�����" << endl;
	cout << endl;
}

////������
//void System::Creat_hftree() {
//
//	if (!this->if_input) { cout << "��δ�������ݽ���ϵͳ�ĳ�ʼ��" << endl; return; }
//	//��д�Զ�ʶ��İɣ���С��������
//
//	int tree_node_num = 0;
//	(this->root) = (hf_node*)malloc(sizeof(hf_node));
//	hf_node* p = root;
//	int k = this->char_size - 1;
//
//	while (k!=-1) {
//		hf_node* new_node = (hf_node*)malloc(sizeof(hf_node));
//		new_node->elm = (this->can_code_char+ k)->elm;
//		new_node->w = (this->can_code_char + k)->w;
//		new_node->code='1';
//		p->left = new_node;
//		p->right = (hf_node*)malloc(sizeof(hf_node));
//		p->right->w = 0;
//		p = p->right;
//		k--;
//	}
//}
//
//void System::Print_hftree() {
//	hf_node* p = this->root;
//	int count = this->char_size;
//	while (count) {
//		cout << p->left->elm<<' ';
//		cout << p->left->w<<" ";
//		cout << p->left->code<<" ";
//		cout << endl;
//		p = p->right;
//		cout << p->w << " " << endl;
//		count--;
//	}
//	
//}




////���������������õ�����
//void System::Search_hftree(){
//	char code_count[100];
//	int j = 0;
//	int length = 0;
//	char* p1 = code_count;
//		for (int i = 0; i < this->char_size;i++){
//				if (i == 0) {
//					*p1 = '1';
//					p1++;
//					length++;
//					(this->can_code_char+i)->code = (char*)malloc(sizeof(char) * length);
//					(this->can_code_char + i)->code_length = length;
//					for (int k = 0; k < length; k++) {
//						*(((this->can_code_char+i)->code)+k)= *(code_count + k);
//					}
//					
//				}
//				else if(i <= this->char_size-2){
//					*p1 = '0';
//					p1++;
//					*p1 = '1';
//					*p1++;
//					length += 2;
//					(this->can_code_char + i)->code = (char*)malloc(sizeof(char) * length);
//					(this->can_code_char + i)->code_length = length;
//					for (int k = 0; k < length; k++) {
//						*((this->can_code_char + i)->code + k) = *(code_count + k);
//					}
//				}
//				else {
//					(this->can_code_char + i)->code = (char*)malloc(sizeof(char) * length);
//					(this->can_code_char + i)->code_length = length;
//					for (int k = 0; k < length; k++) { 
//						if (k = length - 1) {
//							*((this->can_code_char + i)->code + k) ='1';
//						}
//						else { *((this->can_code_char + i)->code + k) = *(code_count + k); } 
//					}
//				}
//				
//			}
//	this->if_get_code =true;
//};


//�����ɷ���

//���ɿսڵ�
//������Ԫ��ֵΪ\0��ֵΪ�սڵ�
hf_node* System::Generate_newnode() {
	hf_node* p = (hf_node*)malloc(sizeof(hf_node));
	p->elm = '\0';
	p->code = '0';
	return p;
}
//��ʼ�����ڵ�
void System::Init_root() {
	this->root = Generate_newnode();
}


//������
//������������ڵ㣬�Լ���Ӧ�½ڵ�洢λ��
void System::get_hftree(hf_node* &new_root,int &elm_num) {
	cout << "����������......" << endl;
	while (1) {
		new_root->left = Generate_newnode();
		new_root->right = Generate_newnode();
		if (elm_num == 1) {
			new_root->left->elm = (this->can_code_char + elm_num)->elm;
			new_root->left->w = (this->can_code_char + elm_num)->w;
			new_root->right->elm = (this->can_code_char + elm_num-1)->elm;
			new_root->right->w = (this->can_code_char + elm_num-1)->w;
			break;
		}
		new_root->left->elm = (this->can_code_char + elm_num)->elm;
		new_root->left->w = (this->can_code_char + elm_num)->w;
		new_root = new_root->right;
		elm_num--;
	}
	this->if_hf_created = true;
	cout << "���Ѿ�����" << endl;
	cout << endl;
}


//��ӡ��
void System::Print_tree() {
	hf_node* p = this->root;
	while (!(p->elm)) {
		cout << "���ڵ�ֵ" << p->elm;
		cout << "��ڵ���" << p->left->elm << endl;;
		cout << "�¸��ڵ�Ϊԭ���ڵ������" << endl;
		p = p->right;
	}
	cout << "���Ľڵ�" << p->elm << endl;;
	cout << "����" << endl;
}


//void System_input(char* want_code);
//ϵͳ����
//�����ַ���ָ��       ��Ҫ������ַ�������
void System::System_input(char* want_code,int want_code_length) {
	this->input_char = (char*)malloc(sizeof(char) * MAX_CODE_NUM);
	char* p1 = this->input_char;
	int num = 0;
	while (*want_code) {
		if (want_code_length < num || num >= MAX_CODE_NUM) {
			break;
		}
		*p1 = *want_code;
		num++;
		p1++;
		want_code++;	
	}
	this->if_hf_created = true;
	this->input_size = want_code_length;
	this->Check_type();
}



void System::Get_code() {
	if (!this->if_hf_created){cout << "��δ����" << endl; return;}
	cout << "���ڱ������õ�����" << endl;
	//������
	hf_node* p = this->root;
	int num = 0;
	while (!p->elm) {
		p = p->right;
		num++;
	}
	cout <<num<<endl;
	cout << this->char_size << endl;

	for (int i = this->char_size - 1;i>0; i--) {
		(this->can_code_char + i)->code = (char*)malloc(sizeof(char) * num);
		char* p = (this->can_code_char + i)->code;
		int code_l = 0;
		for (int j = 0; j < this->char_size-i-1;j++) {
			*p = '0';
			*p++;
			code_l++;
		}
		*p = '1';
		code_l++;
		(this->can_code_char + i)->code_length = code_l;
	}
	this->can_code_char->code = (char*)malloc(sizeof(char) * num);
	char* p1= this->can_code_char->code;
	char* p2= (this->can_code_char+1)->code;
	for (int i = 0; i < num-1; i++) {
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '0';
	if_get_code = true;

	cout << "�Ѿ��õ�������Զ�������б���" << endl;
}

void System::System_output() {
	if (!(*this->input_char)) { cout << "δ����" << endl; return; }
	if (!this->if_get_code) { cout << "δ�������õ�����" << endl; return; }

	if (!this->code_type) {
		cout << "���ڶ�������б���....." << endl;
		this->output = (char*)malloc(sizeof(char) * MAX_CODE_NUM * 10);
		char* p = this->input_char;
		char* p1 = this->output;
		int num = 0;

		for (int i = 0; i < this->input_size; i++) {
			for (int j = 0; j < this->char_size; j++) {
				if (*(p + i) == (this->can_code_char + j)->elm) {
					for (int k = 0; k < (this->can_code_char + j)->code_length; k++) {
						*p1 = *((this->can_code_char + j)->code + k);
						p1++;
						num++;
					}
					break;
				}
			}
		}

		cout << "����������Զ���ӡ���" << endl;
		cout << endl;
		cout << "��������" << endl;
		p1 = this->output;

		for (int i = 0; i < num; i++) {
			cout << *(p1 + i);
		}
		cout << endl;
		this->output_size = num;
	}
	else
	{
		cout << "���ڽ��н���" << endl;
		//���ڽ��벻��Ҫ�ÿո���зָ�
		char* p = this->input_char;
		this->output = (char*)malloc(sizeof(char) * MAX_CODE_NUM);
		char* p1 = this->output;
		int size=0;
		int num=0;
		for (int i = 0; i < this->input_size; i++) {
			if (*(p+i) == '1') {
				num++;
			}
			else {
				size ++;
				switch (num) {
				case 0:*p1 = 'f'; p1++; num = 0; continue;
				case 1:*p1 = 'e'; p1++; num = 0; continue;
				case 2:*p1 = 'd'; p1++; num = 0; continue;
				case 3:*p1 = 'c'; p1++; num = 0; continue;
				case 4:*p1 = 'a'; p1++; num = 0; continue;
				case 5:*p1 = 'b'; p1++; num = 0; continue;
				}
			}
		}

		cout << "����������Զ���ӡ���" << endl;
		cout << "��������" << endl;
		p1 = this->output;

		for (int i = 0; i < size; i++) {
			cout << *(p1 + i);
		}
		cout << endl;
		cout << endl;

		this->output_size = size;
	};
}
//ϵͳ����
void System::Clear() {
	free(this->input_char);
	free(this->output);
	free(this->can_code_char);
	free(this->root);
	this->if_input = false;
	this->if_hf_created = false;
	this->if_get_code = false;
}


//��ӡ����
void System::Print_code() {
	cout << endl;
	cout << "���ڴ�ӡ����" << endl;

	for (int i = 0; i < this->char_size; i++) {
		char* p = (this->can_code_char + i)->code;
		cout << "Ԫ��Ϊ:" << (this->can_code_char + i)->elm;
		cout << "     ";
		cout << "����Ϊ�� ";
		int j = (this->can_code_char + i)->code_length;
		for (int k = 0; k < j; k++) {
			cout << *(p + k);
		}
		cout << endl;
	}
	cout << "��ӡ���" << endl;
	cout << endl;
}

//�µ����Ĵ���

void System::Get_hftree_new(hf_node* new_root) {
	cout << "���ڴ�����....." << endl;
	int sum_w = 0;
	for (int i = 0; i < this->char_size; i++) {
		sum_w += (this->can_code_char + i)->w;
	}
	new_root->w = sum_w;

	//�Ҵ���С
	//�Ҵ�Ϊ 1 СΪ0
	for (int i = this->char_size - 1; i > 1; i--) {
		new_root->left = Generate_newnode();
		new_root->right = Generate_newnode();
		sum_w -= (this->can_code_char + i)->w;
		if (sum_w >= (this->can_code_char + i)->w) {
			new_root->right->w = sum_w;
			new_root->left->w = (this->can_code_char + i)->w;
			new_root->left->elm = (this->can_code_char + i)->elm;
			new_root->left->code = '0';
			new_root->right->code = '1';
			new_root = new_root->right;
		}
		else {
			new_root->left->w = sum_w;
			new_root->right->w = (this->can_code_char + i)->w;
			new_root->right->elm = (this->can_code_char + i)->elm;
			new_root->right->code = '0';
			new_root->left->code = '1';
			new_root = new_root->left;
		}
	}

	new_root->left = Generate_newnode();
	new_root->right = Generate_newnode();

	if (this->can_code_char->w > (this->can_code_char + 1)->w) {

		new_root->right->w = this->can_code_char->w;
		new_root->right->elm = this->can_code_char->elm;

		new_root->left->w = (this->can_code_char + 1)->w;
		new_root->left->elm = (this->can_code_char + 1)->elm;
		new_root->left->code = '0';
		new_root->right->code = '1';
	}
	else {

		new_root->left->w = this->can_code_char->w;
		new_root->left->elm = this->can_code_char->elm;

		new_root->right->w = (this->can_code_char + 1)->w;
		new_root->right->elm = (this->can_code_char + 1)->elm;
		new_root->left->code = '1';
		new_root->right->code = '0';
	}

	this->if_hf_created = true;
	cout << "�����ɹ�" << endl;
}

//�������õ�����
void System::Get_code_new() {
	if (!this->if_hf_created) { cout << "��δ����" << endl; return; }
	int code_l = 0;
	for (int i = 0; i < this->char_size; i++) {
		(this->can_code_char + i)->code = (char*)malloc(sizeof(char*) * MAX_CODE_NUM);
	}

	hf_node* p = this->root;
	char* mem_code = (char*)malloc(sizeof(char*) * MAX_CODE_NUM);
	int k = this->char_size - 1;
	while (!(p->left->elm && p->right->elm))
	{

		char* mp = mem_code;
		for (int j = 0; j < code_l; j++) {
			*((this->can_code_char + k)->code + j) = *(mp + j);
		}

		if (p->left) {
			*((this->can_code_char + k)->code + code_l) = '0';
			*(mp + code_l) = '1';
			code_l++;
			(this->can_code_char + k)->code_length = code_l;
			k--;
			p = p->right;
		}
		else {
			*((this->can_code_char + k)->code + code_l) = '1';
			*(mp + code_l) = '0';
			code_l++;
			(this->can_code_char + k)->code_length = code_l + 1;
			k--;
			p = p->left;
		}

	}



	for (int j = 0; j < code_l; j++) {
		*((this->can_code_char + 1)->code + j) = *(mem_code + j);
		*((this->can_code_char)->code + j) = *(mem_code + j);
	}

	if (this->can_code_char->w >= (this->can_code_char + 1)->w) {
		*(this->can_code_char->code + code_l) = '1';
		*((this->can_code_char + 1)->code + code_l) = '0';
	}
	else {
		*(this->can_code_char->code + code_l)='0';
		*((this->can_code_char + 1)->code + code_l) = '1';
	}
	code_l++;
	this->can_code_char->code_length = code_l;
	(this->can_code_char + 1)->code_length = code_l;
	this->if_get_code = true;
}

//��ӡ��
void System::Print_newtree() {
	hf_node* p = this->root;

	cout << endl;
	cout << "���ڴ�ӡ��" << endl;
	int num = this->char_size-1;
	while (num!=1) {
		cout << "����������:" << " " << "����Ԫ��" << p->left->elm << " " << "Ȩ��" << p->left->w << endl;;
		cout << "����������:" << " " << "����Ԫ��" << p->right->elm << " " << "Ȩ��" << p->right->w << endl;;
		cout << "�¸�����" << endl;
		num--;
		if (p->left) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}

	cout << "����������:" << " " << "����Ԫ��" << p->right->elm << " " << "Ȩ��" << p->right->w << endl;;
	cout << "����������:" << " " << "����Ԫ��" << p->left->elm << " " << "Ȩ��" << p->left->w << endl;;


}

void System::Print_input() {
	cout << endl;
	cout << "��ӡϵͳ���" << endl;
	char* p = this->input_char;
	for (int i = 0; i < this->input_size; i++) {
		cout << *(p + i);
	}
	cout << endl;
	cout << "��ӡ����" << endl;
	cout << endl;
}

void System::Check_type() {
	if (!this->if_input) { cout << "û�н�������ĳ�ʼ��" << endl; return;}

	//ʶ��
	char first = *this->input_char;
	if (first >= 48 && first <= 57) {
		this->code_type = 1;             //0�Ǳ���

	}
	else if ((first <= 90 && first >= 65) || (first >= 97 && first <= 122)) {

		this->code_type = 0;          //1�ǽ���

		for (int i = 0; i < this->input_size; i++) {
			if (*(this->input_char + i) <= 90 && *(this->input_char + i) >= 65) {
				*(this->input_char + i) = *(this->input_char + i) + 32;
			}
		}
	}
	else {
		cout << "�޷�ʶ������" << endl;
	}
}





void test0() {
	////�����ַ���Ϊ0�Ƿ�ֹͣ���

	//char char_in[10] = "abdc0dada";
	//char* p = char_in;
	//while (*p) {
	//	cout << *p;
	//	p++;
	//}
	System system;

	//��ȷ
	cout << "********************ϵͳ�ĳ�ʼ��*************" << endl;
	char a[100] = "abbcccddddeeeeeffffff";
	system.System_Init(a);
	system.Print_elm();

	//������
	system.Init_root();
	hf_node* p = system.root;

	system.Get_hftree_new(p);
	system.Print_newtree();
	system.Get_code_new();
	system.Print_code();
	cout << endl;


	cout << "************************ϵͳ�ı���*************" << endl;
	char m[10] = "dadaf";
	system.System_input(m,5);
	system.Print_input();
	system.System_output();




	cout << endl;
	cout << "*******************ϵͳ�Ľ���********************" << endl;
	cout << endl;
	char m1[] = "01011011101111011111";
	system.System_input(m1, sizeof(m1) / sizeof(char));
	system.Print_input();
	system.System_output();
	/*cout << *system.output << endl;*/
	//char m[10]=''
	//system.Get_code();
	//cout << ((system.can_code_char+5)->code_length)<< endl;
	//system.Print_code();
	//system.Print_hftree();
	//system.Search_hftree();
	/*system.Print_elm();*/
}
//�µ����Ĵ���



void main() {
	test0();
	/*cout << int('z')<< endl;*/
}