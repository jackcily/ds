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
		*t = (BiTree)malloc(sizeof(BitNode));//����ռ���д洢
		if (!(*t))//�������ʧ��
		{
			exit(-1);
		}
		(*t)->date = ch;//���ɸ��ڵ�
		CreatBiTree(&(*t)->lChild, x);//����������
		CreatBiTree(&(*t)->rChild, x);//����������	
	}
	return 1;
}
//�����ǲ�����ȫ������
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
	int  m = 0;//����Ҷ�ӽ���ͳ��
	int k;
	printf("��ѡ��Ҫ����ת�����ַ���������1Ϊabd*f***ce***������2Ϊabdg**eh***k**c*f**, ����3Ϊab**c**(�ǵ����ӣ�����4Ϊab**c*d**(�������)   *����Ϊ��\n ");
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
	printf("*�����\n");
	CreatBiTree(&t, n);//���������� 
	printf("\n�ǲ�����ȫ������   %s", judge(t));
	return 0;
}
