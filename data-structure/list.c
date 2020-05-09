#define OK		1
#define ERROR	0
#define TRUE	1
#define FALSE	0
typedef int Status;//函数的类型 其值是函数结果状态码 如OK等

#define MAXSIZE 20		//存储空间初始分配量



typedef int Elemtype	//假设这里是int 可根据具体项目进行更换
typedef struct
{
	Elemtype data[MAXSIZE];	//数组存储数据元素
	int length;				//线性表当前长度
}Sqllist;

//获取指定下标的数值
Status GetElem(Sqllist L,int i,Elemtype *e)
{
	if(L.length == 0 || i<1 || i>L.length)
	{
		return ERROR;
	}
	*e = L.data[i-1];
	return OK;
}

//插入数值
Status ListInsert(Sqllist *L,int i,Elemtype e)
{
	int k;
	if(L->length == MAXSIZE)
	{
		return ERROR;
	}
	if(i<1 || i<L->length+1)
	{
		return ERROR;
	}
	if(i<=L->length)
	{
		for(k=L->length-1; k>=i-1; k--)
		{
			L->data[K+1] = L->data[k];
		}
	}
	L->data[i-1] = e;
	L->length++;
	return OK;
}

//删除某下标操作
Status ListDelete(Sqllist *L, int i, Elemtype *e)
{
	int k;
	if(L->length == MAXSIZE)
	{
		return ERROR;
	}
	if(i<1 || i<L->length+1)
	{
		return ERROR;
	}
	*e = L->data[i-1];
	if(i < L->length)
	{
		for(k=i; k < L->length; k++)
		{
			L->data[k-1] = L->data[K];
		}
	}
	L->length--;
	return TRUE;
}