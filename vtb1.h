#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#define sx_num 50
using namespace std;

struct word
{
	char value[100];         //词组
	double sx[sx_num];          //value的属性为sx[i]的概率  sx[i]=count_sx[i]/show_times
	double total_value;        //value在训练集中的出现次数
	double count_sx[sx_num];       //value的属性为sx[i]的次数
};

class vtb1
{
private:

	/*对首词组的处理*/
	double head_sx[sx_num];    //训练集首词组为sx[i]的概率   head_sx[i]=count_head_sx[i]/count_head
	double count_head;        //训练集首词组的数目
	double count_head_sx[sx_num]; //训练集首词组为sx[i]的次数

	/*对每个词组的处理*/
	word w[50000];         //暂定5q个词组
	int len_w;

	/*对相邻两个词组的转移概率的处理*/
	double bet[sx_num][sx_num];   //bet[sx1][sx2]：sx1->sx2的转移概率  bet[i][j]=count_bet[i][j]/total_bet
	double count_bet[sx_num][sx_num];
	double total_bet;        //训练集中的总的转移次数

	/*打开文件*/
	ifstream fin;         //训练文件
	ifstream fin1;        //测试文件
	ofstream fout;        //结果文件

	/*共享字符*/
	char c;              //训练文件
	char c1;             //测试文件
	int last;            //bet[last][present]，上一个字符的下标序号

	/*概率乘积*/
	double max_pro;      //一个句子的最大概率

	/*读入测试文件，并存储*/
	char test[100][50];       //一个词组50个字节，一句话最多100个词组
	int len_test;

	/*记录当前属性*/
	int pre_sx[50];
	//int level;         //当前层数 <=> len_pre_sx

	/*记录最优属性*/
	int best_sx[50];
	int len_best_sx;

public:
	vtb1();
	~vtb1();
	int char_to_int(char c[3]);     //输入字符(以'\0'结束)，返回该字符对应的数
	string int_to_char(int sx);      //输入属性的int值，输出对应的属性字符串
	int word_pos(char c[50]);     //判断词组是否为新的词组（是否存在w[i].value == c），返回i(若不存在，则返回len_w)
	bool read_head();   //读取头词组
	bool read_czsx();   //读取剩余部分的一个词组和属性。读到终止符返回false，否则返回true
	void read_rest();   //读取剩余部分
	void train();       //读取训练文件，最终得到head_sx[]、w[]、bet[][]
	void head_handle(); //计算句首的概率乘积，并且调用body_handle()，处理剩余的概率乘积
	void body_handle(int last,double probability, int level); //递归调用，直至该句子处理结束. last：前一个元素的属性在sx数组中的下标
	bool read_a_sentence();                          //将测试文件的一个句子读入
	void analyze();     //对读入的句子进行分析并标注
	void show_sx(int pos);     //显示所有属性
};