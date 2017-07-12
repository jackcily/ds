#include"bitree.h"
status CreatBiTree(BiTree *t, char *x)
{
	ElemType ch, temp;
	ch = x[number];
	number++;
	if (ch == '*')
	{
		*t = NULL;
	}
	else
	{
		*t = (BiTree)malloc(sizeof(BitNode));//分配空间进行存储
		if (!(*t))//如果分配失败
		{
			exit(-1);
		}
		(*t)->date = ch;//生成根节点
		CreatBiTree(&(*t)->lChild, x);//构造左子树
		CreatBiTree(&(*t)->rChild, x);//构造右子树	
	}
	return 1;
}
//检验是不是完全二叉树
	char x[3]="yes";
char*  judge(BiTree t)
{
	if (t == NULL)
	{
		return x;
	}
	else if (t->lChild ==NULL&&t->rChild!=NULL)
	{
		strcpy(x, "no");
		return  x;
		
	}
	judge(t->lChild);
	judge(t->rChild);
	return x;
}
int main()
{
	BiTree t;
	ElemType  n[num];
	int  m = 0;//进行叶子结点的统计
	int k;
	printf("请选择要进行转化的字符串，输入1为abd*f***ce***，输入2为abdg**eh***k**c*f**, 输入3为ab**c**(是的例子）输入4为ab**c*d**(否的例子)   *代表为空\n ");
	scanf("%d", &k);
	if (k == 1)
	{
		strcpy(n, "abd*f***ce***");
	}
	if (k == 2)
	{
		strcpy(n, "abdg**eh***k**c*f**");
	}
	if (k == 4)
	{
		strcpy(n, "ab**c*d** ");
	}
	else
	{
		strcpy(n, "ab**c**");
	}
	printf("*代表空\n");
	CreatBiTree(&t, n);//产生二叉树 
	printf("\n是不是完全二叉树   %s", judge(t));
	return 0;
}
