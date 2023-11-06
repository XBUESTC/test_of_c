//设有一个可以停放n辆汽车的狭长停车场，它只有一个大门可以供车辆进出。车辆按到达停车场时间的早晚
//，依次从停车场最里面向大门口处停放（最先到达的第一辆车放在停车场的最里面）。如果停车场已停放n辆车
//，则后来的车辆只能在停车场大门外的便道上等待，一旦停车场内有车开走，则排在便道上的第一辆车就进入停车场。
//停车场内如有某辆车要开走，在它之后进入停车场的车都必须先退出停车场为它让路，待其开出停车场后，这些车辆再依原来的次序进场。
//每辆车在离开停车场时，都应根据它在停车场内停留的时间长短交费。
//如果停留在便道上的车未进停车场要离去，允许其离去，不收停车费，
//并且仍然保持在便道上等待的车辆次序。编制一个程序模拟该停车场的管理。

// 思路
//两个栈：一个存放停车场内的车，一个存放为出来车让道的停车场里的车
//一个队列：作为在车道上停车位的车

#include<iostream>
#include<string>

using namespace std;

/***************************定义段*********************************/
#define YEAR 2023
#define MONTH 10
#define  DAY 27
	
//定义时间
class tc {
public:

	//属性
	//定义出入的时间
	int start_year, start_month, start_day, start_hour, start_min; //开始计时 年月日时分
	int end_year, end_month, end_day, end_hour, end_min;//结束  ,年月日时分

	//函数
	void Start(int year, int month, int day, int hour, int min);	//记录开始停车时间
	void End(int year, int month, int day, int hour, int min);		//记录停车结束时间
};

//定义车
class car {
public:

	//车的属性

		//车身份识别标志
	string car_id;				//车牌

	//停车相关
	tc stop_time;				//时间（入场以及出场）
	bool isout;			//是否出停车场，默认全在停车场外
	int stop_position;			//车辆停的位置
	car* last;
	double stop_fee;

	//与排队有关
	bool iswait;			//是否在等待队列，默认都在排队

	//车的行为：
	void Init_car(string id);     //初始化车
	void Car_in(int position);    //车辆进入停车场
	void Car_out();               //车辆出停车场
	void Start_time();		     //得到开始停车时间	
	void End_time();             //得到停止停车时间
	void clear();                //清除停车信息
	void Spend_stop();           //停车钱
};

//定义停车场
class Stoping {

	//属性
public:
	int stoping_car;	//停车数
	int stop_ability;	//最大停车数
	bool isfilled;		//车位已满
	car* stop_bottom;	//最里面的停车位
	car* stop_top;		//最外面的停车位

	//行为
	//停车位置的初始化
	Stoping()
	{
		this->stoping_car = 0;
		this->stop_ability = 10;
		this->isfilled = false;
		this->stop_bottom = (car*)malloc(sizeof(car));
		this->stop_top = stop_bottom;
	};
	void Car_in(car* new_car);  //车辆进停车场
	car* Car_out(); //车辆出停车场
	void Car_in(car* new_car, int position);
};

//中转栈
class Mid {
public:
	car* stop_bottom;	//最里面的停车位
	car* stop_top;		//最外面的停车位

	Mid();
	void Car_in(car* new_car); 
	car* Car_out(); 
};

//等待队列
class Waiting_queue {
public:
	int waiting_car;//等待车辆数

	car* queue_begin;	//队头
	car* queue_end;		//队尾


	Waiting_queue();
	void Car_in(car* new_car);  //入队
	car* Car_out();     //出队
	void Print_waiting();//打印队列
	bool isempty();

};

/***********************************函数段 **************/

//随机函数生成器：
//输入 边界值返回期间的整数
//随机数的种子 必须放在主函数当中
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
//初始化车
void car::Init_car(string id) {
	this->car_id = id;
	this->isout = true;
	this->iswait = false;
}

//车辆出停车场
void car::Car_in(int position) {
	this->stop_position = position;
	this->isout = false;
	this->Start_time();
}

//记录车辆进停车场时间
void car::Start_time() {
	this->stop_time.Start(YEAR, MONTH, DAY,get_random(0, 23),get_random(0, 59));
}

void car::End_time() {
	this->stop_time.End(YEAR, MONTH, DAY, get_random(
		this->stop_time.start_hour, 23),get_random(0, 59));
}

//计算停车费用
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

//车辆出停车场
void car::Car_out() {
	this->End_time();
	this->isout = true;
	this->Spend_stop();
}

//清除车辆的时间记录以及负债记录
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
		cout << "车位已满" << endl;
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
		cout << "车位已满" << endl;
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

//数据交换
//Stoping->Stack;
// 
//Waiting_queue->Stoping
//Stoping->Waiting_queue

//参数停车场、中转栈、车在停车场中的位置
//返回目标车辆同时将两个栈复原
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

//打印进入车辆的信息
void Print_car(car iocar) {
	cout << "车辆信息" << endl;
	cout << "车辆id:" << iocar.car_id << endl;
	if (!iocar.isout) cout << "车辆状态:" << "正在停车" << endl;
	else if (iocar.isout)cout << "车辆状态：" << "已出库" << endl;
	else if (iocar.iswait)cout << "车辆状态：正在等待停车" << endl;
	
	cout << "时间信息" << endl;
	cout << "入库时间:" << iocar.stop_time.start_year << '.' << iocar.stop_time.start_month << '.' << iocar.stop_time.start_day << '.' << iocar.stop_time.start_hour << '.' << iocar.stop_time.start_min;
	if (iocar.isout) {
		cout << "出库时间：" << iocar.stop_time.end_year << '.' << iocar.stop_time.end_month << '.' << iocar.stop_time.end_day << '.' << iocar.stop_time.end_hour << '.' << iocar.stop_time.end_min;
		cout << "欠费状态:" << iocar.stop_fee << endl;
	}

}

//输入参数等待队列、停车场、位置
//将等待队列队头的车辆加入停车场
//保证位置正确
void CD_Waiting_Stoping(Waiting_queue &wait_queue,Stoping stop_stack,car &out_car){
	if (wait_queue.isempty()) { cout << "队列已经空了" << endl; return; }
	car* car_in = wait_queue.Car_out();

	car_in->iswait = false;
	car_in->isout = false;
	car_in->stop_position = out_car.stop_position;
	out_car.clear();
	wait_queue.Car_in(&out_car);  //将刚出来的车又放到等待队列

	stop_stack.Car_in(car_in,car_in->stop_position);

	Print_car(*car_in);

}

//打印函数
//打印在队列中的车辆信息
void Print_Waiting(Waiting_queue queue) {
	car* p = queue.queue_begin->last;
	cout << "目前在等待队列中的车辆: ";
	while(1){
		cout << p->car_id;
		cout << " ";
		if (queue.queue_end == p) { break;}
		p = p->last;
	} 
	cout << endl;
}
//打印在停车场中的车信息
void Print_Stoping(Stoping stack) {
	car* p = stack.stop_top;
	cout << "目前在停车场中的车辆: ";
	while (p != stack.stop_bottom){
		cout << p->car_id;
		cout << " ";
		p = p->last;
	}
	cout << endl;
}

//打印在中转栈中的车辆的信息
void Print_Mid(Mid stack) {
	car* p = stack.stop_top;
	while (p != stack.stop_bottom) {
		cout << p->car_id;
		cout << " ";
		p = p->last;
	}
	cout << endl;
}

/******************************************测试段*****************************/

//测试停车场段的正常与否
void test0() {

	//车辆初始化
	car cars[10];

	char a = 'a';
	string name;
	for (int i = 0; i < 10; i++) {
		name = a+i;
		cars[i].Init_car(name);
		name = " ";
	}
	//进入库
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

//全流程的测试函数
void test1() {

	//车的定义以及初始化
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

	//前面的车入停车场
	//后面的车入等待队列
	//显示车辆
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

	//初始化中转栈
	Mid mid_stack;

	cout << endl;
	//10次数据交换
	car* p;

	for (int i = 0; i < 10; i++) {

		cout << "*******************************************************" << endl;
		cout << "开始" << endl;
		cout << "第" << i << "次循环" << endl;
		cout << endl;

		cout << "停车场中的车辆出" << endl;
		cout << endl;

		int position = get_random(0, 10);
		p = CD_Stoping_Mid(car_stack, mid_stack, position); //随机出来一辆车

		Print_Stoping(car_stack);
		cout << endl;


		cout << "出停车场车辆信息" << endl;
		Print_car(*p);
		cout << endl;

		////出来的车进入等待队列，同时队头的车进入停车场
		cout << "车辆自动进入等待队列，队列头的车辆进入停车场" << endl;
		CD_Waiting_Stoping(car_queue, car_stack, *p);
		cout << endl;

		////查看停车场变化
		Print_Stoping(car_stack);
		//////查看等待队列的变化
		cout << endl;
		Print_Waiting(car_queue);
		cout << endl;
		//////查看车辆数据变化

		cout << "进入等待队列后车辆的信息变化" << endl;
		Print_car(*p);
		cout << endl;

		cout << "结束" << endl;

		cout << "***************************************************************" << endl;
	}

}

/*****************************************主函数********************************/
#include<ctime>
#include<cstdlib>
void main() {
	srand(time(0));
	test1();
}