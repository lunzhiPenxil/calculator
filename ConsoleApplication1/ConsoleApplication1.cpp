#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include <stdlib.h> 
#include <math.h>
#include "stdafx.h"
#include <conio.h>

struct DATA;
struct DATALIST;
struct LISTDETAIL;
struct LISTDETAIL;

void AddDATALIST(struct DATALIST **f, struct DATA *in);
DATALIST* scan2LIST(DATA *in_head, DATA *in_last);
double getnum(DATA *head, DATA *last);
double calculator(DATA *head, DATA *last,double ans_n);
int DATAcompar(DATA *head_1, DATA *last_1, int mod, DATA *head_2, DATA *last_2);
char A2a(char in);
int check(DATA *head, DATA *last);

struct DATA
{
	char text;
	DATA *pre;
	DATA *next;
	void AddNext(char in)
	{
		struct DATA *p;
		p = (struct DATA *)malloc(sizeof(struct DATA));
		p->pre = this;
		if (this->next != NULL)
		{
			p->next = this->next;
			this->next->pre = p;
		}
		else
		{
			p->next = NULL;
		}
		this->next = p;
		p->text = in;
	}
	void AddPre(char in)
	{
		struct DATA *p;
		p = (struct DATA *)malloc(sizeof(struct DATA));
		p->next = this;
		if (this->pre != NULL)
		{
			p->pre = this->pre;
			this->pre->next = p;
		}
		else
		{
			p->pre = NULL;
		}
		this->pre = p;
		p->text = in;
	}
	void printl()
	{
		struct DATA *p = this;
		do
		{
			printf("%c", p->text);
			p = p->next == NULL ? p : p->next;
		} while (p->next != NULL);
		if (p != this)
		{
			printf("%c", p->text);
		}
	}
};

struct DATALIST
{
	DATA *head;
	DATA *last;
	DATA *mark;
	DATA *back;
	DATALIST *pre;
	DATALIST *next;
	void AddNext(struct DATA *in)
	{
		struct DATALIST *p;
		p = (struct DATALIST *)malloc(sizeof(struct DATALIST));
		p->head = in;
		if (in != NULL)
		{
			DATA *f2 = in;
			for (;; f2 = f2->next)
			{
				if (f2->next == NULL)
				{
					break;
				}
			}
			p->last = f2;
		}
		else
		{
			p->last = NULL;
		}
		p->pre = this;
		if (this->next != NULL)
		{
			p->next = this->next;
			this->next->pre = p;
		}
		else
		{
			p->next = NULL;
		}
		this->next = p;
	}
	void AddPre(struct DATA *in)
	{
		struct DATALIST *p;
		p = (struct DATALIST *)malloc(sizeof(struct DATALIST));
		p->head = in;
		if (in != NULL)
		{
			DATA *f2 = in;
			for (;; f2 = f2->next)
			{
				if (f2->next == NULL)
				{
					break;
				}
			}
			p->last = f2;
		}
		else
		{
			p->last = NULL;
		}
		p->next = this;
		if (this->pre != NULL)
		{
			p->pre = this->pre;
			this->pre->next = p;
		}
		else
		{
			p->pre = NULL;
		}
		this->pre = p;
	}
	void SetLine(char *line)
	{
		if (this->head != NULL)
		{
			DATA *f1, *f2;
			f1 = this->head;
			while (f1 != NULL)
			{
				f2 = f1->next;
				free(f1);
				f1 = f2;
			}
		}
		char *f;
		struct DATA *p1 = NULL;
		struct DATA *p2 = NULL;
		for (f = line; *f != '\0'; f++)
		{
			p1 = (struct DATA *)malloc(sizeof(struct DATA));
			p1->text = *f;
			p1->pre = p2;
			p1->pre == NULL ? 0 : p1->pre->next = p1;
			p1->next = NULL;
			p2 = p1;
		}
		for (; !(p1->pre == NULL); p1 = p1->pre);
		this->head = p1;
		if (p1 != NULL)
		{
			DATA *f2 = p1;
			for (;; f2 = f2->next)
			{
				if (f2->next == NULL)
				{
					break;
				}
			}
			this->last = f2;
		}
		else
		{
			this->last = NULL;
		}
	}
	void SetLineNext(char *line)
	{
		if (this->next == NULL)
		{
			this->AddNext(NULL);
		}
		this->next->SetLine(line);
	}
	void SetLinePre(char *line)
	{
		if (this->pre == NULL)
		{
			this->AddPre(NULL);
		}
		this->pre->SetLine(line);
	}
	void printl()
	{
		this->head->printl();
	}
	void printd()
	{
		DATALIST *f = this;
		do
		{
			f->head->printl();
			printf("\n");
			f = f->next == NULL ? f : f->next;
		} while (f->next != NULL);
		if (f != this)
		{
			f->head->printl();
			printf("\n");
		}
	}
	int DATALIST2str(char **out)
	{
		if (this->head == NULL)
		{
			out = NULL;
			return 0;
		}
		else
		{
			DATA *f = this->head;
			int n = 0;
			char *fs;
			for (;; f = f->next)
			{
				n++;
				if (f == this->last)
				{
					break;
				}
			}
			*out = (char *)malloc(sizeof(char)*(n + 1));
			fs = *out;
			f = this->head;
			for (;; f = f->next, fs++)
			{
				*fs = f->text;
				if (f == this->last)
				{
					break;
				}
			}
			fs++;
			*fs = '\0';
			return 1;
		}
	}
	void stroutal(char **out)
	{
		long long n_list = 0, n_data = 0;
		DATALIST *f_list = this;
		DATA *f_data =NULL;
		for (;;f_list=f_list->next)
		{
			n_list++;
			if (f_list->head == NULL)
			{
				if (f_list->next == NULL)
				{
					break;
				}
				continue;
			}
			for (f_data = f_list->head;;f_data=f_data->next)
			{
				n_data++;
				if (f_data == f_list->last)
				{
					break;
				}
			}
			if (f_list->next == NULL)
			{
				break;
			}
		}
		char *loc = (char *)malloc(sizeof(char)*(n_list+n_data+1));
		char *f_loc = loc;
		*out = loc;
		for (f_list = this;; f_list = f_list->next,f_loc++)
		{
			if (f_list->head == NULL)
			{
				*f_loc = '\n';
				if (f_list->next == NULL)
				{
					break;
				}
				continue;
			}
			for (f_data = f_list->head;; f_data = f_data->next,f_loc++)
			{
				*f_loc = f_data->text;
				if (f_data == f_list->last)
				{
					break;
				}
			}
			f_loc++;
			*f_loc = '\n';
			if (f_list->next == NULL)
			{
				break;
			}
		}
		f_loc++;
		*f_loc = '\0';
	}
	char read(long long num_list_t, long long num_data_t)
	{
		DATALIST *list = this;
		DATA *data;
		long long num_list = num_list_t, num_data = num_data_t;
		if (num_list == 0)
		{
			//暂无
		}
		else if (num_list>0)
		{
			for (; num_list != 0; num_list--)
			{
				if (list->next == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:list_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					list = list->next;
				}
			}
		}
		else if (num_list<0)
		{
			for (; num_list != 0; num_list++)
			{
				if (list->pre == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:list_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					list = list->pre;
				}
			}
		}
		data = list->head;
		if (num_data == 0)
		{
			//暂无
		}
		else if (num_data>0)
		{
			//for(;num_data!=0;data=data->next,num_data--);
			for (; num_data != 0; num_data--)
			{
				if (data->next == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:data_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					data = data->next;
				}
			}
		}
		else if (num_data<0)
		{
			//for(;num_data!=0;data=data->pre,num_data++);
			for (; num_data != 0; num_data++)
			{
				if (data->pre == NULL)
				{
					printf("\n----DATALIST->read(%lld,%lld)\n----ERROR:data_no_found\n", num_list_t, num_data_t);
					return 0;
				}
				else
				{
					data = data->pre;
				}
			}
		}
		return data->text;
	}
	void ConnectLast(DATALIST *in)
	{
		DATALIST *f = this;
		if (f->next != NULL)
		{
			for (; !(f->next == NULL); f = f->next);
		}
		f->next = in;
	}
	DATALIST* getlast()
	{
		DATALIST *f1 = NULL;
		for (f1 = this;;f1=f1->next)
		{
			if (f1->next == NULL)
			{
				break;
			}
		}
		return f1;
	}
	void setNULL()
	{
		head = NULL;
		last = NULL;
		mark = NULL;
		back = NULL;
		pre = NULL;
		next = NULL;
	}
};

struct LISTDETAIL
{
	struct OFLIST
	{
		DATALIST *head;
		long long length;
	}oflist;
	struct OFSTREAM
	{
		DATALIST *loc;
		long long listloc;
	}ofstream;
	void getdetail(DATALIST *in)
	{
		DATALIST *stream_list = NULL;
		long long n_up=0, n_down=0;
		if (in->pre == NULL)
		{
			this->oflist.head = in;
			this->ofstream.listloc = 0;
		}
		else
		{
			DATALIST *f_up = NULL;
			for (f_up = in;;f_up=f_up->pre)
			{
				if (f_up->pre == NULL)
				{
					break;
				}
				n_up++;
			}
			this->oflist.head = f_up;
			this->ofstream.listloc = n_up;
		}
		if (in->next == NULL)
		{
			//暂无
		}
		else
		{
			DATALIST *f_down = NULL;
			for (f_down = in;; f_down = f_down->next)
			{
				if (f_down->next == NULL)
				{
					break;
				}
				n_down++;
			}
		}
		this->oflist.length = n_up + n_down + 1;
		this->ofstream.loc = in;
	}
	void printal()
	{
		printf("\n---LISTDETAIL---\n OFLIST:\n  head=%x\n  length=%lld\n OFSTREAM\n  loc=%x\n  listloc=%lld\n", this->oflist.head, this->oflist.length, this->ofstream.loc, this->ofstream.listloc);
	}
};

struct DATADETAIL
{
	struct OFDATA
	{
		DATA *head;
		DATA *last;
		long long length;
	}ofdata;
	struct OFSTREAM
	{
		DATALIST *loc;
	}ofstream;
	void getdetail(DATALIST *in)
	{
		this->ofstream.loc = in;
		this->ofdata.head = in->head;
		this->ofdata.last = in->last;
		if (in->head == NULL)
		{
			this->ofdata.length = 0;
		}
		else
		{
			DATA *f=in->head;
			long long n = 0;
			for (;;f=f->next)
			{
				n++;
				if (f == in->last)
				{
					break;
				}
			}
			this->ofdata.length = n;
		}
	}
	void printal()
	{
		printf("\n---DATADETAIL---\n OFDATA:\n  head=%x\n  last=%x\n  length=%lld\n OFSTREAM\n  loc=%x\n", this->ofdata.head, this->ofdata.last, this->ofdata.length, this->ofstream.loc);
	}
};

void AddDATALIST(struct DATALIST **f1, struct DATA *in)
{
	struct DATALIST *f = (struct DATALIST *)malloc(sizeof(struct DATALIST));
	f->head = in;
	if (in != NULL)
	{
		DATA *f2 = in;
		for (;; f2 = f2->next)
		{
			if (f2->next == NULL)
			{
				break;
			}
		}
		f->last = f2;
	}
	else
	{
		f->last = NULL;
	}
	f->pre = NULL;
	f->next = NULL;
	f->mark = NULL;
	f->back = NULL;
	*f1 = f;
}

int DATAcompar(DATA *head_1, DATA *last_1, int mod, DATA *head_2, DATA *last_2)
{
	DATA *f1 = head_1, *f2 = head_2;

	for (;; f1 = f1->next, f2 = f2->next)
	{
		switch (mod)
		{
			case 0:
			{
				if (((f1->text >= 'a'&&f1->text <= 'z') || (f1->text >= 'A'&&f1->text <= 'Z')) || ((f2->text >= 'a'&&f2->text <= 'z') || (f2->text >= 'A'&&f2->text <= 'Z')))
				{
					if (((f1->text >= 'a'&&f1->text <= 'z') || (f1->text >= 'A'&&f1->text <= 'Z')) && ((f2->text >= 'a'&&f2->text <= 'z') || (f2->text >= 'A'&&f2->text <= 'Z')))
					{
						if (f1->text != f2->text&& A2a(f1->text) != f2->text)
						{
							return 0;
						}
						break;
					}
					else
					{
						return 0;
						break;
					}
				}
			}
			case 1:
			{
				if (f1->text != f2->text)
				{
					return 0;
				}
			}
		}
		if (f1 == last_1 || f2 == last_2)
		{
			if (f1 == last_1 && f2 == last_2)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}

int main()
{
	char table1[] = { '0','1','2','3','4','5','6','7','8','9' };
	char table2[] = { '+','-','*','/','\\','^' };
	char table3[] = { '(',')' };
	char str1[100] = { 0 };
	double ans = 0;

	while (1)
	{
		printf("Enter:\n");
		scanf_s("%s", str1, 100);
		DATALIST *L1;
		AddDATALIST(&L1, NULL);
		L1->SetLine(str1);
		if (check(L1->head, L1->last) != 1)
		{
			printf("=Error\n\n");
		}
		else
		{
			printf("=%lf\n\n", ans = calculator(L1->head, L1->last, ans));
		}
	}

	//测试阶段留下的范例
	/*DATALIST *L1;
	AddDATALIST(&L1, NULL);
	DATALIST *f1 = L1;
	f1->SetLine("(1+1)*10/((1+1)*4)");
	printf("%lf\n", calculator(L1->head,L1->last));*/
	
	/*DATALIST *s1 = scan2LIST(f1->head, f1->last);
	char *f = NULL;
	s1->stroutal(&f);
	printf("%s", f);*/

}

DATALIST* scan2LIST(DATA *in_head,DATA *in_last)
{
	char table1[] = { '0','1','2','3','4','5','6','7','8','9' };
	char table2[] = { '+','-','*','/','\\','^' };
	char table3[] = { '(',')' };
	DATALIST *out = (DATALIST *)malloc(sizeof(DATALIST));
	DATA *f1 = NULL, *f2 = NULL, *f_head = NULL, *f_last = NULL;

	out->pre = NULL;
	out->next = NULL;
	out->mark = NULL;
	out->back = NULL;
	out->head = NULL;
	out->last = NULL;

	int n_on_1 = 0, n_on_2 = 0, n_on_3 = 0;
	int n_1=0,n_2=0,n_3 = 0;

	for (f1 = in_head;; f1 = f1->next)
	{
		if (f1->text == table3[0])
		{
			if (n_on_3 == 0)
			{
				n_on_3 = 1;
				f_head = f1;
			}
			n_3++;
		}
		else if (f1->text == table3[1])
		{
			n_3--;
		}
		if (n_on_3 == 1&&n_3==0)
		{
			f_last = f1;
			out->head = f_head->next;
			out->last = f_last->pre;
			out->ConnectLast(scan2LIST(out->head, out->last));//纵向递归
			out->ConnectLast(f_last == in_last ? NULL : scan2LIST(f_last->next, in_last));//横向递归
			break;
		}
		if (f1 == in_last)
		{
			break;
		}
	}

	return out;
}

double calculator(DATA *head,DATA *last,double ans_n)
{
	DATA *f1 = NULL;
	DATALIST A,B;A.setNULL();B.setNULL();
	DATALIST ANS; ANS.setNULL(); ANS.SetLine("ANS");
	double n1 = 0, n2 = 0, n3 = 0, A_n = 0, B_n = 0;
	int re_A = 0, re_B = 0, mod = 0, mod_l = 0, mod_s = 0, mod_u = 0, con = 0;

	for (f1 = head;; f1 = f1->next)
	{
		if ((f1->text >= '0'&&f1->text <= '9') || f1->text == '.')
		{
			if (re_B == 0)
			{
				B.head = f1;
				re_B = 1;
			}
			if (f1 == last)
			{
				if (re_B == 1)
				{
					re_B = 0;
					B.last = f1;
					B_n = getnum(B.head, B.last);
				}
				mod_l = mod;
				mod = 0;
			}
		}
		else if (f1->text == 'a' || f1->text == 'A')//ans
		{
			DATA *f2 = f1;
			int i = 0;
			for (;; i++, f2 = f2->next)
			{
				if (f2 == last || i == 2)
				{
					break;
				}
			}
			if (DATAcompar(f1, f2, 0, ANS.head, ANS.last))
			{
				re_B = 1;
				con = 1;
				B_n = ans_n;
				f1 = f2;
				if (f1 == last)
				{
					re_B = 0;
					con = 0;
					mod_l = mod;
					mod = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if (f1->text == '+')
		{
			if (re_B == 1 && con == 0)
			{
				re_B = 0;
				B.last = f1->pre;
				B_n = getnum(B.head, B.last);
			}
			else if(re_B == 1 && con == 1)
			{
				re_B = 0;
				con = 0;
			}
			mod_l = mod;
			mod = 0;
		}
		else if (f1->text == '-')
		{
			if (re_B == 1 && con == 0)
			{
				re_B = 0;
				B.last = f1->pre;
				B_n = getnum(B.head, B.last);
			}
			else if (re_B == 1 && con == 1)
			{
				re_B = 0;
				con = 0;
			}
			mod_l = mod;
			mod = 1;
		}
		else if (f1->text == '*')
		{
			if (re_B == 1 && con == 0)
			{
				re_B = 0;
				B.last = f1->pre;
				B_n = getnum(B.head, B.last);
			}
			else if (re_B == 1 && con == 1)
			{
				re_B = 0;
				con = 0;
			}
			mod_l = mod;
			mod = 2;
		}
		else if (f1->text == '/')
		{
			if (re_B == 1 && con == 0)
			{
				re_B = 0;
				B.last = f1->pre;
				B_n = getnum(B.head, B.last);
			}
			else if (re_B == 1 && con == 1)
			{
				re_B = 0;
				con = 0;
			}
			mod_l = mod;
			mod = 3;
		}
		else if (f1->text == '^')
		{
			if (re_B == 1 && con == 0)
			{
				re_B = 0;
				B.last = f1->pre;
				B_n = getnum(B.head, B.last);
			}
			else if (re_B == 1 && con == 1)
			{
				re_B = 0;
				con = 0;
			}
			mod_l = mod;
			mod = 4;
		}
		else if (f1->text == '(')
		{
			DATALIST *in = scan2LIST(f1, last);
			re_B = 1;
			con = 1;
			B_n = calculator(in->head, in->last,ans_n);
			f1 = in->last->next;
			if (f1 == last)
			{
				re_B = 0;
				con = 0;
				mod_l = mod;
				mod = 0;
			}
			else
			{
				continue;
			}
		}
		if (re_B != 1)
		switch (mod)
		{
			case 0:
			case 1:
			{
				switch (mod_l)
				{
					case 0:
					{
						n1 += B_n;
						break;
					}
					case 1:
					{
						n1 -= B_n;
						break;
					}
					case 2:
					{
						n2 *= B_n;
						switch (mod_u)
						{
							case 0:
							{
								n1 += n2;
								break;
							}
							case 1:
							{
								n1 -= n2;
								break;
							}
						}
						break;
					}
					case 3:
					{
						n2 /= B_n;
						switch (mod_u)
						{
							case 0:
							{
								n1 += n2;
								break;
							}
							case 1:
							{
								n1 -= n2;
								break;
							}
						}
						break;
					}
					case 4:
					{
						n3 = pow(n3, B_n);
						switch (mod_s)
						{
							case 0:
							{
								n1 += n3;
								break;
							}
							case 1:
							{
								n1 -= n3;
								break;
							}
							case 2:
							{
								n2 *= n3;
								switch (mod_u)
								{
									case 0:
									{
										n1 += n2;
										break;
									}
									case 1:
									{
										n1 += n2;
										break;
									}
								}
								break;
							}
							case 3:
							{
								n2 /= n3;
								switch (mod_u)
								{
									case 0:
									{
										n1 += n2;
										break;
									}
									case 1:
									{
										n1 += n2;
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
				break;
			}
			case 2:
			case 3:
			{
				switch (mod_l)
				{
					case 0:
					case 1:
					{
						mod_u = mod_l;
						n2 = B_n;
						break;
					}
					case 2:
					{
						n2 *= B_n;
						break;
					}
					case 3:
					{
						n2 /= B_n;
						break;
					}
					case 4:
					{
						n3 = pow(n3, B_n);
						switch (mod_s)
						{
							case 0:
							case 1:
							{
								mod_u = mod_s;
								n2 = n3;
								break;
							}
							case 2:
							{
								n2 *= n3;
								break;
							}
							case 3:
							{
								n2 /= n3;
								break;
							}
						}
						break;
					}
				}
				break;
			}
			case 4:
			{
				if (mod_l == 4)
				{
					n3 = pow(n3, B_n);
				}
				else
				{
					mod_s = mod_l;
					n3 = B_n;
				}
			}
		}
		if (f1 == last)
		{
			break;
		}
	}

	return n1;
}

double getnum(DATA *head, DATA *last)
{
	DATA *f1 = head;
	double out = 0, n1 = 0;
	int on = 0;
	for (;; f1 = f1->next)
	{
		if (f1->text == '.')
		{
			on++;
		}
		else if (on == 0)
		{
			n1 = (double)(f1->text) - 48;
			out = out * 10 + n1;
		}
		else if (on != 0)
		{
			n1 = (double)(f1->text) - 48;
			n1 *= pow(10, -on);
			on++;
			out += n1;
		}
		if (f1 == last)
		{
			break;
		}
	}
	return out;
}

char A2a(char in)
{
	if (in >= 'a' || in <= 'z')
	{
		return in - 32;
	}
	else if (in >= 'A' || in <= 'Z')
	{
		return in + 32;
	}
}

int check(DATA *head, DATA *last)
{
	DATA *f1 = head;
	long long dim1 = 0, dim2 = 0, dim3 = 0;
	long long up1 = 0, down1 = 0, tri = 0;
	long long no = 0;
	for (;; f1 = f1->next)
	{
		switch (f1->text)
		{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '.':
			{
				if (dim2 == 1)
				{
					dim2 = 0;
					down1++;
				}
				dim1 = 1;
				break;
			}
			case '+':
			case '-':
			case '*':
			case '/':
			{
				if (dim1 == 1)
				{
					dim1 = 0;
					up1++;
				}
				if (dim2 == 1)
				{
					no = 1;
				}
				if (tri == 1)
				{
					tri = 0;
				}
				dim2 = 1;
				break;
			}
			case '^':
			{
				if (dim1 == 1)
				{
					dim1 = 0;
					up1++;
				}
				if (dim2 == 1)
				{
					no = 1;
				}
				if (tri == 1)
				{
					tri = 0;
				}
				dim2 = 1;
				break;
			}
			case '(':
			{
				dim3++;
				if (tri == 1)
				{
					tri = 0;
				}
				if (dim1 == 1)
				{
					no = 1;
				}
				break;
			}
			case ')':
			{
				dim3--;
				if (tri == 1)
				{
					tri = 0;
				}
				break;
			}
			default:
			{
				no = 1;
			}
		}
		if (f1 == last)
		{
			break;
		}
	}
	if (up1 - down1 != 0)
	{
		no = 1;
	}
	if (dim3 != 0)
	{
		no = 1;
	}
	if (no == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}