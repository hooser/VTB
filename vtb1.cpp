#include "vtb1.h"
#include <string>
#include <cstring>
using namespace std;

ofstream fout;

vtb1::vtb1()
{
	fin.open("F://train_half.txt");
	fin1.open("F://test_file.txt");
	//fin1.open("F://tt.txt");
	fout.open("F://result_file.txt");
	c = ' ';
	c1 = ' ';
	count_head = 0;
	len_w = 0;
	total_bet = 0;
	len_test = 0;
	len_best_sx = 0;
	for (int i = 0; i < 40; i++)
	{
		head_sx[i] = 0.0;
		count_head_sx[i] = 0;
		for (int j = 0; j < 40; j++)
		{
			bet[i][j] = 0.0;
			count_bet[i][j] = 0;
		}
	}
}

vtb1::~vtb1()
{
	fin.close();
	fin1.close();
	fout.close();
}

int vtb1::char_to_int(char c[3])     //输入字符(以'\0'结束)，返回该字符对应的数
{
	char s[sx_num][3] = { "a","Ag","b","c","d","Dg","e", "Eg","f",
		"g","h","i","j","k","l","m","n","Ng","nr","ns","nt",
		"o","p","q", "Qg","r", "Rg", "s","t","Tg","u", "Ug","v", "Vg",
		"w","x","y","Yg","z","ad","vn","vd","nx","an","nz"
	};
	for (int i = 0; i < sx_num; i++)
	{
		if (strcmp(s[i], c) == 0)
			return i;
	}
	return -1;
}

string vtb1::int_to_char(int sx)
{
	string p;
	if (sx == 0)
		p = "a";
	else if (sx == 1)
		p = "Ag";
	else if (sx == 2)
		p = "b";
	else if (sx == 3)
		p = "c";
	else if (sx == 4)
		p = "d";
	else if (sx == 5)
		p = "Dg";
	else if (sx == 6)
		p = "e";
	else if (sx == 7)
		p = "Eg";
	else if (sx == 8)
		p = "f";
	else if (sx == 9)
		p = "g";
	else if (sx == 10)
		p = "h";
	else if (sx == 11)
		p = "i";
	else if (sx == 12)
		p = "j";
	else if (sx == 13)
		p = "k";
	else if (sx == 14)
		p = "l";
	else if (sx == 15)
		p = "m";
	//else if (sx == 17)
		//p = "Mg";
	else if (sx == 16)
		p = "n";
	else if (sx == 17)
		p = "Ng";
	else if (sx == 18)
		p = "nr";
	else if (sx == 19)
		p = "ns";
	else if (sx == 20)
		p = "nt";
	else if (sx == 21)
		p = "o";
	else if (sx == 22)
		p = "p";
	else if (sx == 23)
		p = "q";
	else if (sx == 24)
		p = "Qg";
	else if (sx == 25)
		p = "r";
	else if (sx == 26)
		p = "Rg";
	else if (sx == 27)
		p = "s";
	else if (sx == 28)
		p = "t";
	else if (sx == 29)
		p = "Tg";
	else if (sx == 30)
		p = "u";
	else if (sx == 31)
		p = "Ug";
	else if (sx == 32)
		p = "v";
	else if (sx == 33)
		p = "Vg";
	else if (sx == 34)
		p = "w";
	else if (sx == 35)
		p = "x";
	else if (sx == 36)
		p = "y";
	else if (sx == 37)
		p = "Yg";
	else if (sx == 38)
		p = "z";
	else if (sx == 39)
		p = "ad";
	else if (sx == 40)
		p = "vn";
	else if (sx == 41)
		p = "vd";
	else if (sx == 42)
		p = "nx";
	else if (sx == 43)
		p = "an";
	else if (sx == 44)
		p = "nz";
	else
		p = "#";
	return p;
}

int vtb1::word_pos(char c[50])
{
	int i;
	for (i = 0; i < len_w; i++)
	{
		if (strcmp(w[i].value, c) == 0)
			return i;
	}
	return len_w;
}

bool vtb1::read_czsx()      //
{
	int sentence_end = 0;
	while (c == ' ' || c == '\r')
		c = fin.get();
	if (fin.eof())
		return false;
	char temp_value[50];
	int len_temp_value = 0;
	while (c != '/')
	{
		if (c == '\n')
			return false;

		temp_value[len_temp_value++] = c;
		c = fin.get();
	}
	temp_value[len_temp_value] = '\0';
	cout << temp_value << " ";
	
	/*********
	*句子终止处理*
	*********/
	if (strcmp(temp_value, "。") == 0 || strcmp(temp_value, "？") == 0 || strcmp(temp_value, "！") == 0 || strcmp(temp_value, "；") == 0 || strcmp(temp_value, "：") == 0)
		sentence_end = 1;

	/*********
	*处理w*
	*********/
	//count_head++;      //首词组总数加1
	int pos = word_pos(temp_value);     //if(pos == len_w)->新词组，将改词添加后还需要对w[len_w]做初始化

											  /*新词组处理*/
	if (pos == len_w)
	{

		strcpy_s(w[len_w].value, temp_value);
		w[pos].total_value = 1;        //出现总数为1
		for (int i = 0; i < sx_num; i++)
		{
			w[pos].count_sx[i] = 0;
			w[pos].sx[i] = 0;
		}
		len_w++;
	}

	/*已有词处理*/
	else
	{
		w[pos].total_value++;
	}


	/*********************
	*处理属性，此时c为'/'*
	**********************/
	char temp_sx[3];
	int len_temp_sx = 0;
	c = fin.get();
	while (c != ' ')
	{
		temp_sx[len_temp_sx++] = c;
		c = fin.get();
	}
	temp_sx[len_temp_sx] = '\0';
	int sx = char_to_int(temp_sx);
	//cout << "sx =" << int_to_char(sx) << " " << sx<<endl;
	if (sx == -1)
	{
		cout << "未标识属性！";
		system("pause");
	}
	w[pos].count_sx[sx]++;
	//cout << w[pos].count_sx[sx]<<endl;
	/************
	*处理bet[][]*
	************/
	count_bet[last][sx]++;
	last = sx;                     //记录sx1

	if (sentence_end == 0)
	{
		total_bet++;
		return true;               //句子没有结束
	}
	else
	{
		return false;              //句子结束
	}

}

bool vtb1::read_head()
{
	//c = ' ';
	while (c == ' ' || c == '\n' || c == '\r')
		c = fin.get();

	if (fin.eof())
		return false;

	char temp_value[50];
	int len_temp_value = 0;
	while (c != '/')                   //读取词组
	{
		if (c != ' ' && c != '\n' && c != '\r')
			temp_value[len_temp_value++] = c;

		c = fin.get();
	}
	temp_value[len_temp_value] = '\0';

	cout << temp_value << " ";

	/*********
	*处理head*
	*********/
	count_head++;      //首词组总数加1
	int pos = word_pos(temp_value);     //if(pos == len_w)->新词组，将改词添加后还需要对w[len_w]做初始化

											  /*新词组处理*/
	if (pos == len_w)
	{
		strcpy_s(w[len_w].value, temp_value);
		w[len_w].total_value = 1;        //出现总数为1
		for (int i = 0; i < sx_num; i++)
		{
			w[len_w].count_sx[i] = 0;
			w[len_w].sx[i] = 0;
		}
		len_w++;
	}

	/*已有词处理*/
	else
	{
		w[pos].total_value++;
	}


	/*********************
	*处理属性，此时c为'/'*
	**********************/
	char temp_sx[3];
	int len_temp_sx = 0;
	c = fin.get();
	while (c != ' ' && c != '\n' && c != '\r')
	{
		temp_sx[len_temp_sx++] = c;
		c = fin.get();
	}
	temp_sx[len_temp_sx] = '\0';
	int sx = char_to_int(temp_sx);
	if (sx == -1)
	{
		cout << "未标识属性！";
		system("pause");
	}
	count_head_sx[sx]++;           //head处理
	w[pos].count_sx[sx]++;

	/************
	*处理bet[][]*
	************/
	last = sx;                     //记录sx1
	total_bet++;                   //首算尾不算
	return true;

}

void vtb1::read_rest()
{
	int end_sentence = read_czsx();
	while (end_sentence)
	{
		end_sentence = read_czsx();
	}
}

void vtb1::show_sx(int pos)
{
	for (int i = 0; i < sx_num; i++)
	{
		cout << int_to_char(i) << "->" << w[pos].sx[i];
	}
}

void vtb1::train()
{
	int end_flag = read_head();
	//cout << "over0";
	while (end_flag)
	{
		read_rest();
		end_flag = read_head();
	}
	//cout << "over1";
	/*训练结果汇总*/

	//head_sx[]
	for (int i = 0; i < sx_num; i++)
	{
		head_sx[i] = count_head_sx[i] / count_head;
	}

	//w[]
	for (int i = 0; i < len_w; i++)
	{
		for (int j = 0; j < sx_num; j++)
		{
			w[i].sx[j] = w[i].count_sx[j] / w[i].total_value;
		}
	}

	//bet[][]
	for (int i = 0; i < sx_num; i++)
	{
		for (int j = 0; j < sx_num; j++)
		{
			bet[i][j] = count_bet[i][j] / total_bet;
		}
	}

	ofstream ff;
	ff.open("F://jz.txt");

	/*共享数据*/

	/*

	char temp[50];
	//int i;
	int temp_pos;
	cout << "下面显示\"是\"的属性信息：" << endl;
	strcpy_s(temp,"是");
	temp_pos = word_pos(temp);
	cout << "temp_pos = " << temp_pos << endl;
	show_sx(temp_pos);
	
	*/

	ff << "状态转换矩阵如下：" << endl;
	for (int f1 = 0; f1 < sx_num; f1++)
	{
		for (int f2 = 0; f2 < sx_num; f2++)
		{
			ff << int_to_char(f1) << "->" << int_to_char(f2) << " " << bet[f1][f2] << endl;
		}
	}
	ff.close();
}

void vtb1::body_handle(int last,double pro, int level)
{
	//level++;
	
	if (level >= len_test)
	{
		
		//比较当前的pro与最大pro，判断是否需要记录此时的属性数组
		if (pro > max_pro)
		{
			
			for (len_best_sx = 0; len_best_sx < level; len_best_sx++)
			{
				best_sx[len_best_sx] = pre_sx[len_best_sx];
			}
		}
		max_pro = pro;
		//level--;
		return;
	}
	int pos = word_pos(test[level]);

	//cout << "go into 1.5" << endl;

	int i;
	int exist = 0;                        //不存在满足if (w[pos].sx[i] != 0 && bet[last][i] != 0)的i
	int exist1 = 0;
	for (i = 0; i < sx_num; i++)
	{
		if (w[pos].sx[i] != 0 && bet[last][i] != 0)
		{
			//cout << "go into 1.75" << endl;
			exist = 1;
			//last = i;
			pre_sx[level] = i;
			double new_pro = pro * w[pos].sx[i] * bet[last][i];
			//cout << "go into 2" << endl;
			body_handle(i,new_pro,level+1);
			//cout << "go into 3" << endl;
			//level--;
		}
	}

	//cout << "go into 3.5" << endl;

	if (exist == 0)             //
	{
		//cout << "go into 3.75" << endl;
		for (i = 0; i < sx_num; i++)
		{
			if (w[pos].sx[i] != 0)
			{
				//last = i;
				//cout << "i ==" << i<<endl;
				exist1 = 1;
				pre_sx[level] = i;
				double new_pro = pro * w[pos].sx[i];
				//cout << "go into 4" << endl;
				body_handle(i, new_pro,level + 1);
				//cout << "go into 5" << endl;
				//level--;
			}
		}
		if (exist1 == 0)
		{
			pre_sx[level] = 16;                 //名词
			double new_pro = pro;
			body_handle(16, new_pro, level + 1);
		}
	}
	//cout << "go into 6" << endl;
}

void vtb1::head_handle()
{
	int pos = word_pos(test[0]);                //句首词组在w[]中的标号
	int level = 0;            //当前属性数组长度(层数)记为0
	max_pro = 0;          //最大属性置0

	int i;
	int exist = 0;
	int exist1 = 0;
	for (i = 0; i < sx_num; i++)
	{
		if (w[pos].sx[i] != 0 && head_sx[i] != 0)     
		{
			exist = 1;
			pre_sx[level] = i;
			double pro = w[pos].sx[i] * head_sx[i];
			body_handle(i,pro,level+1);
		}
	}
	if (exist == 0)           //不存在两个都满足
	{
		for (i = 0; i < sx_num; i++)
		{
			if (w[pos].sx[i] != 0)
			{
				exist1 = 1;
				pre_sx[level] = i;
				//cout << "i = " << i << endl;
				double pro = w[pos].sx[i];
				body_handle(i, pro,level+1);
			}
		}
		if (exist1 == 0)     //未登陆词
		{
			pre_sx[level] = 16;                 //名词
			double pro = 1.0;
			body_handle(16, pro, level + 1);
		}
	}
}

bool vtb1::read_a_sentence()
{
	//cout << "read_a_sentence start" << endl;
	len_test = 0;           //读句子之前，先将读入词组数清零
	int sentence_end = 0;
	
	if (fin1.eof())        //测试文件读取完毕
		return false;

	max_pro = 0;

	//cout << "still alive1" << endl;

	while (sentence_end == 0)
	{
		char temp_value[50];
		int len_temp_value = 0;
		while (c1 == '\n' || c1 == '\r' || c1 == ' ')
			c1 = fin1.get();

		while (c1 != ' ')
		{
			if (fin1.eof())
				return false;                           

			//cout << "still alive2" << endl;

			temp_value[len_temp_value++] = c1;
			c1 = fin1.get();
		}

		temp_value[len_temp_value] = '\0';
		strcpy_s(test[len_test++], temp_value);

		//cout << "len_test = " << len_test<<endl;

		if (strcmp(temp_value, "。") == 0 || strcmp(temp_value, "？") == 0 || strcmp(temp_value, "！") == 0 || strcmp(temp_value, "；") == 0)
			sentence_end = 1;
	}
	return true;
}

void vtb1::analyze()
{
	cout << endl << endl << endl << "------------------测试结果------------------" << endl << endl;
	int flag = read_a_sentence();

	//cout <<endl<< "analyze start" << endl;
	//cout << "flag = " << flag;
	while (flag == true)
	{
		
		head_handle();
		int i;
		for (i = 0; i < len_test; i++)
		{
			fout << test[i] << "/"<<int_to_char(best_sx[i]) << " ";
			cout << test[i] << "/"<<int_to_char(best_sx[i]) << " ";
		}
		cout << endl;
		flag = read_a_sentence();
	}
}
