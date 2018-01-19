#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include <stdlib.h> 
#include <math.h>
#include "stdafx.h"

struct DATA;
struct DATALIST;

void AddDATALIST(struct DATALIST **f, struct DATA *in);

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
	char read(long long num_list_t, long long num_data_t)
	{
		DATALIST *list = this;
		DATA *data;
		long long num_list = num_list_t, num_data = num_data_t;
		if (num_list == 0)
		{
			//ÔÝÎÞ 
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
			//ÔÝÎÞ 
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


int main()
{
	char table1[] = { '0','1','2','3','4','5','6','7','8','9' };
	char table2[] = { '+','-','*','/','\\','^' };
	char table3[] = { '(',')' };
	char *str1;

	DATALIST *L1;
	AddDATALIST(&L1, NULL);
	DATALIST *f1 = L1;
	f1->SetLine("12345");
	f1->SetLineNext("!?@#");
	f1->printd();
	printf("%c\n", f1->head->text);
	printf("%c\n", f1->last->text);
	L1->DATALIST2str(&str1);
	printf("%s\n", str1);
	printf("%c", L1->read(0, 1));
	printf("%c", L1->read(2, 1));
	printf("%c", L1->read(1, -10));
	LISTDETAIL ofL1;
	ofL1.getdetail(L1);
	ofL1.printal();
	DATADETAIL ofL1_;
	ofL1_.getdetail(L1);
	ofL1_.printal();
}

