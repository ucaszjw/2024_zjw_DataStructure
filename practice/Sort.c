// Creator: 王泽黎
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 10000
#define MAXKEY 5
#define BUCKETNUM 101

// 桶元素结点
typedef struct Node *PtrToNode;
struct Node
{
    int data[MAXKEY]; // 关键字内容
    PtrToNode next; // 桶中下一个记录的位置
};

// 桶头结点
typedef struct HeadNode
{
    PtrToNode head; // 桶头结点
    PtrToNode tail; // 桶尾结点
} HeadNode;

typedef struct HeadNode Bucket[BUCKETNUM];

// LSD排序(使用插入排序)
void LSD_sort(int count1[][MAXKEY], int len, int mykey, int keynum)
{
    for(int i = 0; i < len; i++)
    {
        int temp[keynum];
        for(int j = 0; j < keynum; j++)
        {
            temp[j] = count1[i][j];
        }
        int j = i - 1;
        while(j >= 0 && count1[j][mykey] > temp[mykey])
        {
            for(int k = 0; k < keynum; k++)
            {
                count1[j + 1][k] = count1[j][k];
            }
            j--;
        }
        for(int k = 0; k < keynum; k++)
        {
            count1[j + 1][k] = temp[k];
        }
    }
}

// LSD排序（使用“分配”和“收集”方法）
void LSD_Radix_Sort(int num[][MAXKEY], int size, int key, int priority[])
{
    int number = 0;
    Bucket bucket;
    PtrToNode temp, p, list = NULL;
    // 初始化桶
    for (int i = 0; i < BUCKETNUM; i++)
    {
        bucket[i].head = bucket[i].tail = NULL;
    }
    // 将待排序记录逆序存入初始链表list
    for(int i = 0; i < size; i++)
    {
        temp = (PtrToNode)malloc(sizeof(struct Node));
        for(int j = 0; j < key; j++)
        {
            temp->data[j] = num[i][j];
        }
        temp->next = list;
        list = temp;
    }
    // LSD排序
    for(int i = key - 1; i >= 0; i--)
    {
        // 分配
        p = list;
        while(p)
        {
            // 获取关键字
            number = p->data[priority[i]];
            // 将结点从list中摘除
            temp = p;
            p = p->next;
            // 将结点插入到桶中
            temp->next = NULL;
            if(bucket[number].head == NULL)
            {
                bucket[number].head = bucket[number].tail = temp;
            }
            else
            {
                bucket[number].tail->next = temp;
                bucket[number].tail = temp;
            }
        }
        // 收集
        list = NULL;
        for(int j = BUCKETNUM - 1; j >= 0; j--)
        {
            // 将桶中结点逆序存入list
            if(bucket[j].head) // 桶不为空
            {
                // 将整个桶插入到list
                if(list == NULL)
                {
                    list = bucket[j].head;
                }
                else
                {
                    bucket[j].tail->next = list;
                    list = bucket[j].head;
                }
                // 清空桶
                bucket[j].head = bucket[j].tail = NULL;
            }
        }
    }

    // 将排序后的记录存入num, 并释放空间
    for(int i = 0; i < size; i++)
    {
        temp = list;
        for(int j = 0; j < key; j++)
        {
            num[i][j] = temp->data[j];
        }
        list = list->next;
        free(temp);
    }
}

// MSD排序(使用插入排序)
void MSD_sort(int num[][MAXKEY], int keynum, int priority[], int pri, int left, int right)
{
    // 核心递归函数：对num数组的priority[pri]关键字进行排序
    if(pri == keynum || left >= right)
    {
        return;
    }
    // 插入排序
    for(int i = left + 1; i <= right; i++)
    {
        int temp[keynum];
        for(int j = 0; j < keynum; j++)
        {
            temp[j] = num[i][j];
        }
        int j = i - 1;
        while(j >= left && num[j][priority[pri]] > temp[priority[pri]])
        {
            for(int k = 0; k < keynum; k++)
            {
                num[j + 1][k] = num[j][k];
            }
            j--;
        }
        for(int k = 0; k < keynum; k++)
        {
            num[j + 1][k] = temp[k];
        }
    }
    // 递归
    int i = left;
    int j = left;
    while(j <= right)
    {
        while(j <= right && num[j][priority[pri]] == num[i][priority[pri]])
        {
            j++;
        }
        MSD_sort(num, keynum, priority, pri + 1, i, j - 1);
        i = j;
    }
}

// MSD排序（使用“分配”和“收集”方法）
void MSD_Radix_Sort(int num[][MAXKEY], int size, int key, int priority[], int pri, int left, int right)
{
    // 核心递归函数：对num数组的priority[pri]关键字进行排序
    int number = 0, i = 0, j = 0;
    Bucket bucket;
    PtrToNode temp, p, list = NULL;
    // 递归终止条件
    if(pri == key || left >= right)
    {
        return;
    }
    // 初始化桶
    for (int i = 0; i < BUCKETNUM; i++)
    {
        bucket[i].head = bucket[i].tail = NULL;
    }
    // 将待排序记录逆序存入初始链表list
    for(int m = left; m <= right; m++)
    {
        temp = (PtrToNode)malloc(sizeof(struct Node));
        for(int n = 0; n < key; n++)
        {
            temp->data[n] = num[m][n];
        }
        temp->next = list;
        list = temp;
    }
    // MSD排序
    // 分配
    p = list;
    while(p)
    {
        // 获取关键字
        number = p->data[priority[pri]];
        // 将结点从list中摘除
        temp = p;
        p = p->next;
        // 将结点插入到桶中
        if(bucket[number].head == NULL)
        {
            bucket[number].head = bucket[number].tail = temp;
            bucket[number].tail->next = NULL;
        }
        else
        {
            bucket[number].tail->next = temp;
            bucket[number].tail = temp;
            bucket[number].tail->next = NULL;
        }
    }
    // 收集
    // i和j记录当前处理的num数组的左右端下标
    i = j = left;
    for(int m = 0; m < BUCKETNUM; m++)
    {
        // 将非空的桶中的元素收集到num数组中，递归排序
        if(bucket[m].head)
        {
            p = bucket[m].head;
            while(p)
            {
                for(int n = 0; n < key; n++)
                {
                    num[j][n] = p->data[n];
                }
                j++;
                temp = p;
                p = p->next;
                free(temp);
            }
            // 递归排序
            MSD_Radix_Sort(num, size, key, priority, pri + 1, i, j - 1);
            // 为下一个桶对应num数组的左端下标赋值
            i = j;
        }
    }
}

int main()
{
    // 记录时间
    clock_t start1, finish1, start2, finish2, start3, finish3, start4, finish4;
    double Total_time1, Total_time2, Total_time3, Total_time4;

    // 读取记录数和关键字数
    int size, key;
    printf("Please input the size and key: ");
    scanf("%d %d", &size, &key);
    getchar(); // 读取换行符

    // 读取优先级数组
    int priority[key], count = 0;

    char ch;

    printf("Please input the priority: ");
    while((ch = getchar()) != '\n')
    {
        if(ch >= '0' && ch <= '9')
        {
            priority[count] = ch - '0';
            priority[count]--;
            count++;
        }
    }

    // 确定记录数和关键字数的合法性
    if(size > MAXSIZE || key > MAXKEY)
    {
        printf("Error: size or key is too large!\n");
        return 0;
    }
    else if(size <= 0 || key <= 0)
    {
        printf("Error: size or key is too small!\n");
        return 0;
    }

    // 选择升序输出或降序输出
    int sign;
    printf("Please input the order(ascending(1) or descending(2)): ");
    scanf("%d", &sign);
    
    // 声明待排序记录
    int num1[size][MAXKEY], num2[size][MAXKEY], num3[size][MAXKEY], num4[size][MAXKEY];

    // 生成待排序记录
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < key; j++)
        {
            num1[i][j] = rand() % 101;
            num2[i][j] = num1[i][j];
            num3[i][j] = num1[i][j];
            num4[i][j] = num1[i][j];
        }
    }

    // LSD(插入排序)排序
    // 记录开始时间
    start1 = clock();
    // LSD排序
    for(int i = key - 1; i >= 0; i--)
    {
        LSD_sort(num1, size, priority[i], key);
    }
    // 结束计时
    finish1 = clock();

    // LSD(“分配”和“收集”)排序
    // 记录开始时间
    start2 = clock();
    // LSD排序
    LSD_Radix_Sort(num2, size, key, priority);
    // 结束计时
    finish2 = clock();

    // MSD(插入排序)排序
    // 记录开始时间
    start3 = clock();
    // MSD排序
    MSD_sort(num3, key, priority, 0, 0, size - 1);
    // 结束计时
    finish3 = clock();

    // MSD(“分配”和“收集”)排序
    // 记录开始时间
    start4 = clock();
    // MSD排序
    MSD_Radix_Sort(num4, size, key, priority, 0, 0, size - 1);
    // 结束计时
    finish4 = clock();

    // 输出排序结果
    int write_sign = 0;
    printf("Write Result(1) or Not(0): ");
    scanf("%d", &write_sign);
    if(write_sign)
    {
        printf("Sort Result:\n");
        if(sign == 1)
        {
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < key; j++)
                {
                    if(j != key - 1)
                    {
                        printf("%d ", num1[i][j]);
                    }
                    else
                    {
                        printf("%d\n", num1[i][j]);
                    }
                }
            }   
        }
        else if(sign == 2)
        {
            for(int i = size - 1; i >= 0; i--)
            {
                for(int j = 0; j < key; j++)
                {
                    if(j != key - 1)
                    {
                        printf("%d ", num1[i][j]);
                    }
                    else
                    {
                        printf("%d\n", num1[i][j]);
                    }
                }
            }
        }
    }

    // 计算时间
    Total_time1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;
    Total_time2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;
    Total_time3 = (double)(finish3 - start3) / CLOCKS_PER_SEC;
    Total_time4 = (double)(finish4 - start4) / CLOCKS_PER_SEC;

    // 输出时间
    printf("LSD(Insertion Sort) Time: %fs\n", Total_time1);
    printf("LSD(Radix Sort) Time: %fs\n", Total_time2);  
    printf("MSD(Insertion Sort) Time: %fs\n", Total_time3);
    printf("MSD(Radix Sort) Time: %fs\n", Total_time4);

    return 0;
}