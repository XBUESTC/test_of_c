//����һ������ͣ��n������������ͣ��������ֻ��һ�����ſ��Թ���������������������ͣ����ʱ�������
//�����δ�ͣ��������������ſڴ�ͣ�ţ����ȵ���ĵ�һ��������ͣ�����������棩�����ͣ������ͣ��n����
//��������ĳ���ֻ����ͣ����������ı���ϵȴ���һ��ͣ�������г����ߣ������ڱ���ϵĵ�һ�����ͽ���ͣ������
//ͣ����������ĳ����Ҫ���ߣ�����֮�����ͣ�����ĳ����������˳�ͣ����Ϊ����·�����俪��ͣ��������Щ��������ԭ���Ĵ��������
//ÿ�������뿪ͣ����ʱ����Ӧ��������ͣ������ͣ����ʱ�䳤�̽��ѡ�
//���ͣ���ڱ���ϵĳ�δ��ͣ����Ҫ��ȥ����������ȥ������ͣ���ѣ�
//������Ȼ�����ڱ���ϵȴ��ĳ������򡣱���һ������ģ���ͣ�����Ĺ���

// ˼·
//����ջ��һ�����ͣ�����ڵĳ���һ�����Ϊ�������õ���ͣ������ĳ�
//һ�����У���Ϊ�ڳ�����ͣ��λ�ĳ�

#include<iostream>
#include<string>

using namespace std;

/***************************�����*********************************/
#define YEAR 2023
#define MONTH 10
#define  DAY 27
	
//����ʱ��
class tc {
public:

	//����
	//��������ʱ��
	int start_year, start_month, start_day, start_hour, start_min; //��ʼ��ʱ ������ʱ��
	int end_year, end_month, end_day, end_hour, end_min;//����  ,������ʱ��

	//����
	void Start(int year, int month, int day, int hour, int min);	//��¼��ʼͣ��ʱ��
	void End(int year, int month, int day, int hour, int min);		//��¼ͣ������ʱ��
};

//���峵
class car {
public:

	//��������

		//�����ʶ���־
	string car_id;				//����

	//ͣ�����
	tc stop_time;				//ʱ�䣨�볡�Լ�������
	bool isout;			//�Ƿ��ͣ������Ĭ��ȫ��ͣ������
	int stop_position;			//����ͣ��λ��
	car* last;
	double stop_fee;

	//���Ŷ��й�
	bool iswait;			//�Ƿ��ڵȴ����У�Ĭ�϶����Ŷ�

	//������Ϊ��
	void Init_car(string id);     //��ʼ����
	void Car_in(int position);    //��������ͣ����
	void Car_out();               //������ͣ����
	void Start_time();		     //�õ���ʼͣ��ʱ��	
	void End_time();             //�õ�ֹͣͣ��ʱ��
	void clear();                //���ͣ����Ϣ
	void Spend_stop();           //ͣ��Ǯ
};

//����ͣ����
class Stoping {

	//����
public:
	int stoping_car;	//ͣ����
	int stop_ability;	//���ͣ����
	bool isfilled;		//��λ����
	car* stop_bottom;	//�������ͣ��λ
	car* stop_top;		//�������ͣ��λ

	//��Ϊ
	//ͣ��λ�õĳ�ʼ��
	Stoping()
	{
		this->stoping_car = 0;
		this->stop_ability = 10;
		this->isfilled = false;
		this->stop_bottom = (car*)malloc(sizeof(car));
		this->stop_top = stop_bottom;
	};
	void Car_in(car* new_car);  //������ͣ����
	car* Car_out(); //������ͣ����
	void Car_in(car* new_car, int position);
};

//��תջ
class Mid {
public:
	car* stop_bottom;	//�������ͣ��λ
	car* stop_top;		//�������ͣ��λ

	Mid();
	void Car_in(car* new_car); 
	car* Car_out(); 
};

//�ȴ�����
class Waiting_queue {
public:
	int waiting_car;//�ȴ�������

	car* queue_begin;	//��ͷ
	car* queue_end;		//��β


	Waiting_queue();
	void Car_in(car* new_car);  //���
	car* Car_out();     //����
	void Print_waiting();//��ӡ����
	bool isempty();

};

/***********************************������ **************/

//���������������
//���� �߽�ֵ�����ڼ������
//����������� �����������������
int  get_random(int min,int max) {
	return rand() % (max - min + 1) + min;
}

//tc
void tc::Start(int year, int month, int day, int hour, int min) {
	this->start_year = year;
	this->start_month = month;
	this->start_day = day;
	this->start_hour = hour;
	this->start_min = min;
}

void tc::End(int year, int month, int day, int hour, int min) {
	this->end_year = year;
	this->end_month = month;
	this->end_day = day;
	this->end_hour = hour;
	this->end_min = min;
}

//car
//��ʼ����
void car::Init_car(string id) {
	this->car_id = id;
	this->isout = true;
	this->iswait = false;
}

//������ͣ����
void car::Car_in(int position) {
	this->stop_position = position;
	this->isout = false;
	this->Start_time();
}

//��¼������ͣ����ʱ��
void car::Start_time() {
	this->stop_time.Start(YEAR, MONTH, DAY,get_random(0, 23),get_random(0, 59));
}

void car::End_time() {
	this->stop_time.End(YEAR, MONTH, DAY, get_random(
		this->stop_time.start_hour, 23),get_random(0, 59));
}

//����ͣ������
void car::Spend_stop() {
	int year, month, day, hour, min;
	year = this->stop_time.end_year - this->stop_time.start_year;
	month = this->stop_time.end_month - this->stop_time.start_month;
	day = this->stop_time.end_day - this->stop_time.start_day;
	hour = this->stop_time.end_hour - this->stop_time.start_hour;
	min = this->stop_time.end_hour - this->stop_time.start_hour;

	int all_hour=0;
	if (min>0) {all_hour = 1;}
	else { all_hour = 0; }

	all_hour += year * 24 * 360 + month * 30 * 24 + day * 24 + hour;
	if (all_hour<=2) {this->stop_fee = 2;}
	else { this->stop_fee = 2 + 0.5 * (all_hour - 2);}
}

//������ͣ����
void car::Car_out() {
	this->End_time();
	this->isout = true;
	this->Spend_stop();
}

//���������ʱ���¼�Լ���ծ��¼
void car::clear() {
	this->stop_fee = 0;
	this->stop_time.Start(0, 0, 0, 0, 0);
	this->stop_time.End(0, 0, 0, 0, 0);
	this->stop_position = -1;
	this->isout = false;
	this->iswait = false;
}


void Stoping::Car_in(car* car_in, int position) {
	if (this->stoping_car >= this->stop_ability) {
		cout << "��λ����" << endl;
		return;
	}
	car* p= this->stop_top;
	for (int i = position; i < this->stoping_car; i++) {
		p = p->last;
	}
	car_in->last = p->last;
	p->last = car_in;
	car_in->Car_in(car_in->stop_position);
}

void Stoping::Car_in(car* new_car) {

	if (this->stoping_car >= this->stop_ability) {
		cout << "��λ����" << endl;
		return;
	}
	this->stoping_car++;
	new_car->Car_in(stoping_car);
	new_car->last = this->stop_top;
	this->stop_top = new_car;
}

car* Stoping::Car_out() {
	car* p = this->stop_top;
	this->stop_top = this->stop_top->last;
	p->Car_out();
	this->stoping_car--;
	return p;
}

Mid::Mid() {
	this->stop_bottom = (car*)malloc(sizeof(car));
	this->stop_top = this->stop_bottom;
}
void  Mid::Car_in(car* new_car) {
	new_car->last = this->stop_top;
	this->stop_top = new_car;
}
car* Mid::Car_out() {
	car* p = this->stop_top;
	this->stop_top = this->stop_top->last;
	return p;
}

Waiting_queue::Waiting_queue() {
	this->waiting_car = 0;
	queue_begin = (car*)malloc(sizeof(car));
	queue_end = queue_begin;
}

void Waiting_queue::Car_in(car* new_car){
	this->queue_end->last = new_car;
	this->queue_end = new_car;
	this->waiting_car++;
	new_car->iswait = true;
}
car* Waiting_queue::Car_out() {
	car* p =this->queue_begin->last;
	this->queue_begin->last = this->queue_begin->last->last;
	p->iswait = false;
	this->waiting_car--;
	return p;
}

void Waiting_queue::Print_waiting() {
	car* p = this->queue_begin->last;
	for (int i = 0; i < this->waiting_car; i++) {
		cout << p->car_id << endl;
		p = p->last;
	}
}

bool Waiting_queue::isempty(){
	return this->queue_begin == this->queue_end;
}

//���ݽ���
//Stoping->Stack;
// 
//Waiting_queue->Stoping
//Stoping->Waiting_queue

//����ͣ��������תջ������ͣ�����е�λ��
//����Ŀ�공��ͬʱ������ջ��ԭ
car* CD_Stoping_Mid(Stoping &stop_stack, Mid& mid_stack,int position){
	car* p;
	for (int i = position; i < stop_stack.stoping_car; i++) {
		p = stop_stack.Car_out();
		mid_stack.Car_in(p);
	}
	car* aimed = stop_stack.Car_out();
	while (mid_stack.stop_top != mid_stack.stop_bottom) {
		p = mid_stack.Car_out();
		stop_stack.Car_in(p);
	}
	return aimed;
};

//��ӡ���복������Ϣ
void Print_car(car iocar) {
	cout << "������Ϣ" << endl;
	cout << "����id:" << iocar.car_id << endl;
	if (!iocar.isout) cout << "����״̬:" << "����ͣ��" << endl;
	else if (iocar.isout)cout << "����״̬��" << "�ѳ���" << endl;
	else if (iocar.iswait)cout << "����״̬�����ڵȴ�ͣ��" << endl;
	
	cout << "ʱ����Ϣ" << endl;
	cout << "���ʱ��:" << iocar.stop_time.start_year << '.' << iocar.stop_time.start_month << '.' << iocar.stop_time.start_day << '.' << iocar.stop_time.start_hour << '.' << iocar.stop_time.start_min;
	if (iocar.isout) {
		cout << "����ʱ�䣺" << iocar.stop_time.end_year << '.' << iocar.stop_time.end_month << '.' << iocar.stop_time.end_day << '.' << iocar.stop_time.end_hour << '.' << iocar.stop_time.end_min;
		cout << "Ƿ��״̬:" << iocar.stop_fee << endl;
	}

}

//��������ȴ����С�ͣ������λ��
//���ȴ����ж�ͷ�ĳ�������ͣ����
//��֤λ����ȷ
void CD_Waiting_Stoping(Waiting_queue &wait_queue,Stoping stop_stack,car &out_car){
	if (wait_queue.isempty()) { cout << "�����Ѿ�����" << endl; return; }
	car* car_in = wait_queue.Car_out();

	car_in->iswait = false;
	car_in->isout = false;
	car_in->stop_position = out_car.stop_position;
	out_car.clear();
	wait_queue.Car_in(&out_car);  //���ճ����ĳ��ַŵ��ȴ�����

	stop_stack.Car_in(car_in,car_in->stop_position);

	Print_car(*car_in);

}

//��ӡ����
//��ӡ�ڶ����еĳ�����Ϣ
void Print_Waiting(Waiting_queue queue) {
	car* p = queue.queue_begin->last;
	cout << "Ŀǰ�ڵȴ������еĳ���: ";
	while(1){
		cout << p->car_id;
		cout << " ";
		if (queue.queue_end == p) { break;}
		p = p->last;
	} 
	cout << endl;
}
//��ӡ��ͣ�����еĳ���Ϣ
void Print_Stoping(Stoping stack) {
	car* p = stack.stop_top;
	cout << "Ŀǰ��ͣ�����еĳ���: ";
	while (p != stack.stop_bottom){
		cout << p->car_id;
		cout << " ";
		p = p->last;
	}
	cout << endl;
}

//��ӡ����תջ�еĳ�������Ϣ
void Print_Mid(Mid stack) {
	car* p = stack.stop_top;
	while (p != stack.stop_bottom) {
		cout << p->car_id;
		cout << " ";
		p = p->last;
	}
	cout << endl;
}

/******************************************���Զ�*****************************/

//����ͣ�����ε��������
void test0() {

	//������ʼ��
	car cars[10];

	char a = 'a';
	string name;
	for (int i = 0; i < 10; i++) {
		name = a+i;
		cars[i].Init_car(name);
		name = " ";
	}
	//�����
	Stoping car_stack;
	car car_in;
	for (int i = 0; i < 10; i++) {
		car_stack.Car_in(&cars[i]);
	}

	Mid mid_stack;
	for (int i = 0; i < 10; i++) {
		car* p = car_stack.Car_out();
		mid_stack.Car_in(p);
	}

	Waiting_queue  car_queue;
	car car_waiting[10];

	string name_1;
	for (int i = 0;i < 10; i++) {
		name_1='A'+i;
		car_waiting[i].Init_car(name_1);
	}
	for (int i = 0; i < 10;i++) {
		car_queue.Car_in(&car_waiting[i]);
	}

	car_queue.Print_waiting();
}

//ȫ���̵Ĳ��Ժ���
void test1() {

	//���Ķ����Լ���ʼ��
	car cars[20];

	string name;
	for (int i = 0; i < 20; i++) {
		if (i < 10) {
			name = 'a' + i;
			cars[i].Init_car(name);
		}
		else {
			name = 'A' + i - 10;
			cars[i].Init_car(name);
		}
	}

	//ǰ��ĳ���ͣ����
	//����ĳ���ȴ�����
	//��ʾ����
	Stoping car_stack;

	for (int i = 0; i < 10; i++) {
		car_stack.Car_in(&cars[i]);
	}

	Waiting_queue car_queue;

	for (int i = 10; i < 20; i++) {
		car_queue.Car_in(&cars[i]);
	}
	Print_Stoping(car_stack);
	Print_Waiting(car_queue);

	//��ʼ����תջ
	Mid mid_stack;

	cout << endl;
	//10�����ݽ���
	car* p;

	for (int i = 0; i < 10; i++) {

		cout << "*******************************************************" << endl;
		cout << "��ʼ" << endl;
		cout << "��" << i << "��ѭ��" << endl;
		cout << endl;

		cout << "ͣ�����еĳ�����" << endl;
		cout << endl;

		int position = get_random(0, 10);
		p = CD_Stoping_Mid(car_stack, mid_stack, position); //�������һ����

		Print_Stoping(car_stack);
		cout << endl;


		cout << "��ͣ����������Ϣ" << endl;
		Print_car(*p);
		cout << endl;

		////�����ĳ�����ȴ����У�ͬʱ��ͷ�ĳ�����ͣ����
		cout << "�����Զ�����ȴ����У�����ͷ�ĳ�������ͣ����" << endl;
		CD_Waiting_Stoping(car_queue, car_stack, *p);
		cout << endl;

		////�鿴ͣ�����仯
		Print_Stoping(car_stack);
		//////�鿴�ȴ����еı仯
		cout << endl;
		Print_Waiting(car_queue);
		cout << endl;
		//////�鿴�������ݱ仯

		cout << "����ȴ����к�������Ϣ�仯" << endl;
		Print_car(*p);
		cout << endl;

		cout << "����" << endl;

		cout << "***************************************************************" << endl;
	}

}

/*****************************************������********************************/
#include<ctime>
#include<cstdlib>
void main() {
	srand(time(0));
	test1();
}