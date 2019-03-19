#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#define sx_num 50
using namespace std;

struct word
{
	char value[100];         //����
	double sx[sx_num];          //value������Ϊsx[i]�ĸ���  sx[i]=count_sx[i]/show_times
	double total_value;        //value��ѵ�����еĳ��ִ���
	double count_sx[sx_num];       //value������Ϊsx[i]�Ĵ���
};

class vtb1
{
private:

	/*���״���Ĵ���*/
	double head_sx[sx_num];    //ѵ�����״���Ϊsx[i]�ĸ���   head_sx[i]=count_head_sx[i]/count_head
	double count_head;        //ѵ�����״������Ŀ
	double count_head_sx[sx_num]; //ѵ�����״���Ϊsx[i]�Ĵ���

	/*��ÿ������Ĵ���*/
	word w[50000];         //�ݶ�5q������
	int len_w;

	/*���������������ת�Ƹ��ʵĴ���*/
	double bet[sx_num][sx_num];   //bet[sx1][sx2]��sx1->sx2��ת�Ƹ���  bet[i][j]=count_bet[i][j]/total_bet
	double count_bet[sx_num][sx_num];
	double total_bet;        //ѵ�����е��ܵ�ת�ƴ���

	/*���ļ�*/
	ifstream fin;         //ѵ���ļ�
	ifstream fin1;        //�����ļ�
	ofstream fout;        //����ļ�

	/*�����ַ�*/
	char c;              //ѵ���ļ�
	char c1;             //�����ļ�
	int last;            //bet[last][present]����һ���ַ����±����

	/*���ʳ˻�*/
	double max_pro;      //һ�����ӵ�������

	/*��������ļ������洢*/
	char test[100][50];       //һ������50���ֽڣ�һ�仰���100������
	int len_test;

	/*��¼��ǰ����*/
	int pre_sx[50];
	//int level;         //��ǰ���� <=> len_pre_sx

	/*��¼��������*/
	int best_sx[50];
	int len_best_sx;

public:
	vtb1();
	~vtb1();
	int char_to_int(char c[3]);     //�����ַ�(��'\0'����)�����ظ��ַ���Ӧ����
	string int_to_char(int sx);      //�������Ե�intֵ�������Ӧ�������ַ���
	int word_pos(char c[50]);     //�жϴ����Ƿ�Ϊ�µĴ��飨�Ƿ����w[i].value == c��������i(�������ڣ��򷵻�len_w)
	bool read_head();   //��ȡͷ����
	bool read_czsx();   //��ȡʣ�ಿ�ֵ�һ����������ԡ�������ֹ������false�����򷵻�true
	void read_rest();   //��ȡʣ�ಿ��
	void train();       //��ȡѵ���ļ������յõ�head_sx[]��w[]��bet[][]
	void head_handle(); //������׵ĸ��ʳ˻������ҵ���body_handle()������ʣ��ĸ��ʳ˻�
	void body_handle(int last,double probability, int level); //�ݹ���ã�ֱ���þ��Ӵ������. last��ǰһ��Ԫ�ص�������sx�����е��±�
	bool read_a_sentence();                          //�������ļ���һ�����Ӷ���
	void analyze();     //�Զ���ľ��ӽ��з�������ע
	void show_sx(int pos);     //��ʾ��������
};