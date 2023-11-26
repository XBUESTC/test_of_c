#include<iostream>
#define MAX_CODE_NUM 100//最大能够识别字符数
using namespace std;


//存储字符单元
struct  system_elm {          //系统能够识别的字符
	char elm;					//字符
	int w;						//权重
	char* code;                 //编码
	int code_length;            //编码长度 
};
typedef struct system_elm   system_elm;

//树节点
struct hf_node;
typedef struct hf_node hf_node;
struct hf_node {             //定义哈夫曼树的节点
	char elm;                   //字符     初始化为" "
	int w;                      //初始化为0
	char code;                //编码
	hf_node* right;           //右子树
	hf_node* left;          //左子树
};
typedef  hf_node* hf_root;


//系统定义
class System {
public:
	system_elm* can_code_char;       //用来存放系统能够识别的字符，在初始化时确定大小
	hf_root  root;             //存放哈夫曼树的根
	bool if_hf_created;        //哈夫曼树建立标志
	bool if_input;             //是否输入
	int char_size;               //识别的数据量
	char* input_char;           //系统输入
	char* output;               //系统输出

	int code_type;               //输入的是字符还是数字          0表示数字需要解码  1表示字符需要编码

	bool if_get_code;            //是否已经完成编码初始化
	int input_size;
	int output_size;

	System();

	void System_Init(char* p); //初始化字符串,将扫描到的数据放到SYS_ELM中     
	void System_Init(system_elm* init_input);        //初始化,将扫描到的数据放到SYS_ELM中,需要自己输入字符集


	//void Creat_hftree();    //创建哈夫曼树，将root更新
	//void Search_hftree();  //遍历哈夫曼树，得到编码
	//void Print_hftree();  //打印哈夫曼树.


	void System_input(char* want_code,int want_code_num);//系统输入
	void System_output();//系统输出      返回0：编码  返回1：解码

	void Clear(); //回归初始状态
	void Print_elm(); //显示能编码/解码字符


	hf_node* Generate_newnode(); //将节点进行初始化    //规定字符为'/0'的为空
	void get_hftree(hf_node* &new_root,int &elm_num);  //创建树
	void Print_tree();                                //打印树
	void Init_root();                                 //初始化根
	void Get_code();                               //遍历树得到编码
	void Print_code();                              //打印编码


	//哈夫曼建立原理出错
	//更改后的
	void Get_hftree_new(hf_node* new_root);        //创建树
	void Get_code_new();                     //得到编码
	void Print_newtree();                   //打印树
	void Print_input();									

	//对输入系统的识别以及解码
	void Check_type();

};

//其它函数定义
//char Find_min(int* int_list, int list_size, int& num);
system_elm NULL_elm;
hf_node* NULL_node;

//初始化哈夫曼数的节点
//遍历字符串
//输入字符串的头，以及大小（定义长度很大）
char* Get_code(char* p, int size);


//类实例化后的初始化
System::System() {
	this->if_hf_created = false;
	this->if_input = false;
	this->if_get_code = false;
}

//输出类存储的节点
void System::Print_elm() {
	cout << "正在打印元素" << endl;
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
	cout << "打印完成" << endl;
	cout << endl;
}

//编码初始化

//第一种带参获得初始化的编码
void System::System_Init(char* p) {
	cout << "正在初始化" << endl;
	char get_char[100];	//存储字符串
	int get_count[100];		//记录字符串出现个数
	int get_size = 0;												//记录字符目前出现的类数
	while (*p) {
		if (!get_size) {*get_char = *p; *get_count = 1;get_size++; p++;} //还没实例化，自动用第一个字符进行实例化
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
	//cout << "识别完成" << endl;
	this->char_size = get_size;     //将识别字符的类型个数存储
	//将得到的数据保存到系统中
	//按出现次数的小到大进行排序
	//save_size 存储位置
	int save_size = 0;
	int sort_num[100];
	this->can_code_char = (system_elm*)malloc(sizeof(system_elm) * get_size);
	*sort_num = -1;
	while (save_size!=get_size){
		//找最小值
		int num = 1000;
		for (int i = 0; i < get_size; i++) {
			//增加识别 
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
	cout << "初始化完成" << endl;
	cout << endl;
}

////创建树
//void System::Creat_hftree() {
//
//	if (!this->if_input) { cout << "还未输入数据进行系统的初始化" << endl; return; }
//	//先写自动识别的吧，从小到大排序
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




////遍历哈夫曼树，得到编码
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


//新生成方法

//生成空节点
//定义器元素值为\0的值为空节点
hf_node* System::Generate_newnode() {
	hf_node* p = (hf_node*)malloc(sizeof(hf_node));
	p->elm = '\0';
	p->code = '0';
	return p;
}
//初始化根节点
void System::Init_root() {
	this->root = Generate_newnode();
}


//生成树
//输入参数，根节点，以及对应新节点存储位置
void System::get_hftree(hf_node* &new_root,int &elm_num) {
	cout << "正在生成树......" << endl;
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
	cout << "树已经生成" << endl;
	cout << endl;
}


//打印树
void System::Print_tree() {
	hf_node* p = this->root;
	while (!(p->elm)) {
		cout << "根节点值" << p->elm;
		cout << "左节点数" << p->left->elm << endl;;
		cout << "新根节点为原根节点的右子" << endl;
		p = p->right;
	}
	cout << "最后的节点" << p->elm << endl;;
	cout << "结束" << endl;
}


//void System_input(char* want_code);
//系统输入
//输入字符串指针       想要编码的字符串长度
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
	if (!this->if_hf_created){cout << "树未建立" << endl; return;}
	cout << "正在遍历树得到编码" << endl;
	//遍历树
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

	cout << "已经得到编码可以对输入进行编码" << endl;
}

void System::System_output() {
	if (!(*this->input_char)) { cout << "未输入" << endl; return; }
	if (!this->if_get_code) { cout << "未遍历树得到编码" << endl; return; }

	if (!this->code_type) {
		cout << "正在对输入进行编码....." << endl;
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

		cout << "编码结束，自动打印结果" << endl;
		cout << endl;
		cout << "输出最后结果" << endl;
		p1 = this->output;

		for (int i = 0; i < num; i++) {
			cout << *(p1 + i);
		}
		cout << endl;
		this->output_size = num;
	}
	else
	{
		cout << "正在进行解码" << endl;
		//对于解码不需要用空格进行分割
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

		cout << "解码结束，自动打印结果" << endl;
		cout << "输出最后结果" << endl;
		p1 = this->output;

		for (int i = 0; i < size; i++) {
			cout << *(p1 + i);
		}
		cout << endl;
		cout << endl;

		this->output_size = size;
	};
}
//系统重置
void System::Clear() {
	free(this->input_char);
	free(this->output);
	free(this->can_code_char);
	free(this->root);
	this->if_input = false;
	this->if_hf_created = false;
	this->if_get_code = false;
}


//打印编码
void System::Print_code() {
	cout << endl;
	cout << "正在打印代码" << endl;

	for (int i = 0; i < this->char_size; i++) {
		char* p = (this->can_code_char + i)->code;
		cout << "元素为:" << (this->can_code_char + i)->elm;
		cout << "     ";
		cout << "代码为： ";
		int j = (this->can_code_char + i)->code_length;
		for (int k = 0; k < j; k++) {
			cout << *(p + k);
		}
		cout << endl;
	}
	cout << "打印完成" << endl;
	cout << endl;
}

//新的树的创建

void System::Get_hftree_new(hf_node* new_root) {
	cout << "正在创建树....." << endl;
	int sum_w = 0;
	for (int i = 0; i < this->char_size; i++) {
		sum_w += (this->can_code_char + i)->w;
	}
	new_root->w = sum_w;

	//右大左小
	//且大为 1 小为0
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
	cout << "创建成功" << endl;
}

//遍历树得到编码
void System::Get_code_new() {
	if (!this->if_hf_created) { cout << "树未建立" << endl; return; }
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

//打印树
void System::Print_newtree() {
	hf_node* p = this->root;

	cout << endl;
	cout << "正在打印树" << endl;
	int num = this->char_size-1;
	while (num!=1) {
		cout << "根的左子树:" << " " << "根的元素" << p->left->elm << " " << "权重" << p->left->w << endl;;
		cout << "根的右子树:" << " " << "根的元素" << p->right->elm << " " << "权重" << p->right->w << endl;;
		cout << "新根生成" << endl;
		num--;
		if (p->left) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}

	cout << "根的右子树:" << " " << "根的元素" << p->right->elm << " " << "权重" << p->right->w << endl;;
	cout << "根的左子树:" << " " << "根的元素" << p->left->elm << " " << "权重" << p->left->w << endl;;


}

void System::Print_input() {
	cout << endl;
	cout << "打印系统输出" << endl;
	char* p = this->input_char;
	for (int i = 0; i < this->input_size; i++) {
		cout << *(p + i);
	}
	cout << endl;
	cout << "打印结束" << endl;
	cout << endl;
}

void System::Check_type() {
	if (!this->if_input) { cout << "没有进行输入的初始化" << endl; return;}

	//识别
	char first = *this->input_char;
	if (first >= 48 && first <= 57) {
		this->code_type = 1;             //0是编码

	}
	else if ((first <= 90 && first >= 65) || (first >= 97 && first <= 122)) {

		this->code_type = 0;          //1是解码

		for (int i = 0; i < this->input_size; i++) {
			if (*(this->input_char + i) <= 90 && *(this->input_char + i) >= 65) {
				*(this->input_char + i) = *(this->input_char + i) + 32;
			}
		}
	}
	else {
		cout << "无法识别输入" << endl;
	}
}





void test0() {
	////测试字符串为0是否停止输出

	//char char_in[10] = "abdc0dada";
	//char* p = char_in;
	//while (*p) {
	//	cout << *p;
	//	p++;
	//}
	System system;

	//正确
	cout << "********************系统的初始化*************" << endl;
	char a[100] = "abbcccddddeeeeeffffff";
	system.System_Init(a);
	system.Print_elm();

	//建立树
	system.Init_root();
	hf_node* p = system.root;

	system.Get_hftree_new(p);
	system.Print_newtree();
	system.Get_code_new();
	system.Print_code();
	cout << endl;


	cout << "************************系统的编码*************" << endl;
	char m[10] = "dadaf";
	system.System_input(m,5);
	system.Print_input();
	system.System_output();




	cout << endl;
	cout << "*******************系统的解码********************" << endl;
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
//新的树的创建



void main() {
	test0();
	/*cout << int('z')<< endl;*/
}