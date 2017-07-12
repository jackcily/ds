#include <stdio.h>  
#include "HashTable.h"  
  
#define N 15//��������ɵļ�¼����  
int main(void)  
{  
    ElemType r[N];//��¼����  
    HashTable h;  
    int i,n = 0,p = 0;  
    Status s;  
    KeyType k;  
    FILE *f;//�ļ�ָ������  
    f = fopen("Records.txt","r");//�򿪼�¼�ļ�Record.txt  
    do  
    {  
        i = fscanf(f,"%d%d",&r[p].key,&r[p].order);//�Ƚ���¼�ݴ����¼����r[p]  
        if (i != -1)  
        {//�������ݳɹ�  
            p++;  
        }  
    } while (!feof(f) && p < N);//δ���������ļ���β�Ҽ�¼����δ��  
    fclose(f);//�ر������ļ�  
    InitHashTable(h);  
    for (i = 0; i < p - 1; ++i)  
    {//��h�в���ǰp-1����¼(���һ����¼������,�������һ����¼���ؽ���ϣ��)  
        s = InsertHash(h,r[i]);  
        if (DUPLICATE == s)  
        {  
            printf("�������йؼ���Ϊ%d�ļ�¼���޷��ٲ����¼��%d,%d��\n",r[i].key,r[i].key,r[i].order);  
        }  
    }  
    printf("����ϣ��ַ��˳�������ϣ��:\n");  
    TraverseHash(h,Visit);  
    printf("����������Ҽ�¼�Ĺؼ��֣�");  
    scanf("%d",&k);  
    s = SearchHash(h,k,p,n);  
    if (SUCCESS == s)  
    {//���ҳɹ�  
        Visit(p,h.elem[p]);//����ü�¼  
    }  
    else  
    {//����ʧ��  
        printf("δ�ҵ�\n");  
    }  
    s = InsertHash(h,r[i]);//�������һ����¼�����ؽ���ϣ��  
    if (UNSUCCESS == s)  
    {//���벻�ɹ�  
        s = InsertHash(h,r[i]);//�ؽ���ϣ������²���  
    }  
    printf("����ϣ���ַ��˳������ؽ���Ĺ�ϣ��:\n");  
    TraverseHash(h,Visit);  
  
    printf("����������Ҽ�¼�Ĺؼ��֣�");  
    scanf("%d",&k);  
    s = SearchHash(h,k,p,n);  
    if (SUCCESS == s)  
    {//���ҳɹ�  
        Visit(p,h.elem[p]);//����ü�¼  
    }  
    else  
    {//����ʧ��  
        printf("δ�ҵ�\n");  
    }  
    DestroyHashTable(h);  
    return 0;  
}  