#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_VERTEX_NUM 18
#define MAX_ARC_SIZE 100
#define MAX_ROUTE_NUM 5
#define MAX_CITY_NAME_LEN 15
#define MAX_TRANSPORT_ID_LEN 6
#define False 0
#define True 1
#define INFINITY 10000

struct arc
{
    char id[MAX_TRANSPORT_ID_LEN];
    char StartCity[MAX_CITY_NAME_LEN];
    char EndCity[MAX_CITY_NAME_LEN];
    int BeginTime[2];
    int ArriveTime[2];
    float price;
}a[MAX_ARC_SIZE]; //临时存放飞机或列车信息

typedef struct
{
    char number[MAX_TRANSPORT_ID_LEN];
    float expenditure;
    int begintime[2];
    int arrivetime[2];
}Vehide; //记录每一个航班或车次的信息 

typedef struct
{
    Vehide stata[MAX_ROUTE_NUM];
    int last;
}infolist;

typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    infolist info;
}ArcNode;

typedef struct VNode
{
    char cityname[MAX_CITY_NAME_LEN];
    ArcNode *planefirstarc, *trainfirstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum, planearcnum, trainarcnum;
}ALGraph;  //存放交通图 

typedef struct Node
{
    int adjvex;
    int route;
    struct Node *next;
}Node;

typedef struct QNode
{
    int adjvex;
    struct QNode *next;
}QNode;

typedef struct
{
    QNode *front;
    QNode *rear;
}LinkQueue;
char city[MAX_VERTEX_NUM][MAX_CITY_NAME_LEN];

void Administer(ALGraph *G); //显示管理员管理项目选择界面
void initgraph(ALGraph *G); //初始化交通系统
void createcityfile(); //创建城市名称文档
void createfile(int flag_choose); // 创建车次文档 flag为1时表示飞机航班；2是表示列车车次 
int LocateVertex(ALGraph *G,char *v); //城市名在交通系统中定位操作，找出城市名在图中对应结点位置
void CreateGraph(ALGraph *G); //用city，plan，train三个文档创建城市交通系统
int save(ALGraph *G); //保存城市交通系统到相应的文档
void cityedit(ALGraph *G); //增加城市 
void flight_trainedit(ALGraph *G, int flag); //增加飞机航班和列车车次 

void UserDemand(ALGraph G);  //用户咨询项目选择界面
void DemandDispose(int n, ALGraph G);  //用户咨询选择信息输入界面
void MinExpenditure(infolist arcs, float *expenditure, int *route); //两直达城市之间最少旅行费用和相应路径
void ExpenditureDispose(int k, infolist (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final); //最少旅行费用处理 

void InitQueue(LinkQueue *Q);  //初始化链队列
void EnterQueue(LinkQueue *Q, int x); //入队操作
void DeleteQueue(LinkQueue *Q,int *x); //出队操作
int IsEmpty(LinkQueue *Q); //队列判空操作
void TransferDispose(int k,infolist (*arcs)[MAX_VERTEX_NUM],ALGraph G,int v0,int v1); //最少中转次数 

void PrintGraph(ALGraph *G); //显示城市交通系统

//显示程序功能选择界面
int main()
{
    ALGraph G;
    int i;
    //初始化界面 
    printf("===================欢迎使用交通资讯系统===============\n");
    printf("系统功能如下所示： \n");
    printf("------------------------------------------------------\n");
    printf("|    1=管理员管理                   2=用户咨询       |\n");
    printf("|    3=显示交通系统                 4=退出           |\n");
    printf("------------------------------------------------------\n");
    printf("请选择程序功能: ");
    scanf("%d",&i);
    getchar();
    //执行用户选择的功能 
    while(i != 4)
    {
        switch(i)
        {
            case 1: Administer(&G); break;
            case 2: UserDemand(G); break;
            case 3: PrintGraph(&G); break;
        }
    printf("------------------------------------------------------\n");
    printf("|    1=管理员管理                   2=用户咨询       |\n");
    printf("|    3=显示交通系统                 4=退出           |\n");
    printf("------------------------------------------------------\n");
    printf("请选择程序功能: ");
    scanf("%d", &i);
    getchar();
    }
    return 0;
}

//显示管理员管理项目选择界面
void Administer(ALGraph *G)
{
    int i;
    //初始化界面 
    printf("\n管理项目如下所示:\n");
    printf("-------------------------------------------------------\n");
    printf("|    1=初始化交通系统              2=增加城市         |\n");
    printf("|    3=增加飞机航班                4=增加列车车次     |\n");
    printf("|    5=返回上一级菜单                                 |\n");
    printf("-------------------------------------------------------\n");
    printf("请选择管理项目: ");
    scanf("%d", &i);
    getchar();
    while(i != 5)
    { 
        switch(i)
        {
            case 1:
                initgraph(G);    //初始化交通系统
                break;
            case 2:
                cityedit(G);     //增加城市
                break;
            case 3:
                flight_trainedit(G, 1);   //增加飞机航班
                break;
            case 4:
                flight_trainedit(G, 2);    //增加列车车次
                break;
        }
        printf("-------------------------------------------------------\n");
        printf("|    1=初始化交通系统              2=城市编辑         |\n");
        printf("|    3=飞机航班编辑                4=列车车次编辑     |\n");
        printf("|    5=返回上一级菜单                                 |\n");
        printf("-------------------------------------------------------\n");
        printf("请选择管理项目: ");
        scanf("%d", &i);
        getchar();
    }
}

//初始化交通系统
void initgraph(ALGraph *G)     
{
    int i;
    printf("请选择初始化方式(1=键盘输入; 2=文档读入): ");
    scanf("%d", &i);
    getchar();
    switch(i)
    {
        case 1:
            createcityfile();   //创建城市文件 
            createfile(1);  //创建航班文件 
            createfile(2);  //创建列车文件 
            CreateGraph(G);     //初始化交通系统
            break;
        case 2:
            CreateGraph(G);
            break;
    }
}

void createcityfile()
{
    int i = 0, j;
    char flag = 'y';
    FILE *fp;
    printf("请输入城市名称的信息:\n");
    while(flag == 'y' || flag == 'Y')
    {
        printf("城市名称:");
        scanf("%s", city[i]); // 限制输入长度，避免溢出
        i++;
        getchar(); 
        printf("继续输入?(Y/N)");
        scanf(" %c", &flag); // 读取用户选择前跳过空白字符
    }
    printf("城市名称的输入已结束！\n\n");
    if((fp = fopen("city.txt", "w")) == NULL)
    {
        printf("无法打开文件city.txt!\n");
        return;
    }
    for(j = 0; j < i; j++)
        fprintf(fp, "%s", city[j]);
    fclose(fp);
}

// 创建车次文档 flag为1时表示飞机航班；2是表示列车车次 
void createfile(int flag_choose)
{
    char code[MAX_CITY_NAME_LEN];
    int starttime[2], endtime[2], i, count = 0;
    float money;
    char startcity[MAX_CITY_NAME_LEN], endcity[MAX_CITY_NAME_LEN], flag = 'y';
    FILE *fp;
    // 输入所有的航班信息 
    while(flag == 'Y' || flag == 'y')
    {
        //提示输入信息
        if(flag_choose == 1)
        {
            printf("请输入飞机航班的信息:\n");
            printf("航班编号:");
        }
        else
        {
            printf("请输入列车车次的信息:\n");
            printf("车次编号:");
        }
        scanf("%s", code);
        getchar();
        printf("起始城市:");
        scanf("%s", startcity);
        getchar();
        printf("目的城市:");
        scanf("%s", endcity);
        getchar();
        if (flag_choose == 1)
            printf("航班费用:");
        else
            printf("车次费用:");
        scanf("%f", &money);
        getchar();
        printf("起始时间:");
        scanf("%d:%d",&starttime[0], &starttime[1]);
        getchar();
        //判断时间是否合理 
        while(starttime[0] < 0 || starttime[0] >= 24 || starttime[1] < 0 || starttime[1] >= 60)
        {
            printf("时间输入有误，请重新输入！\n");
            scanf("%d:%d", &starttime[0], &starttime[1]);
            getchar();
        }
        printf("到达时间:");  //输入航班的到达时间at
        scanf("%d:%d", &endtime[0], &endtime[1]);
        getchar();
        while(endtime[0] < 0 || endtime[0] >= 24 || endtime[1] < 0 || endtime[1] >= 60)
        {
            printf("时间输入有误，请重新输入！\n");
            scanf("%d:%d", &endtime[0], &endtime[1]);
            getchar();
        }
        //将每一个航班信息存放在结构体a中
        strcpy(a[count].id, code);
        strcpy(a[count].StartCity, startcity);
        strcpy(a[count].EndCity, endcity);
        a[count].BeginTime[0] = starttime[0];
        a[count].BeginTime[1] = starttime[1];
        a[count].ArriveTime[0] = endtime[0];
        a[count].ArriveTime[1] = endtime[1];
        a[count].price=money;
        count++; 
        printf("继续输入?(Y/N)");
        scanf("%c",&flag);
        getchar();
    }  
    printf("\n");
    //打开文件
    if (flag_choose == 1)
        fp = fopen("plane.txt","w");
    if (flag_choose == 2)
        fp = fopen("train.txt","w");
    if(fp == NULL) 
        printf("\n无法打开相应文件！\n");
    fprintf(fp,"%d",count);    //将计数值count写入航班车文件
    //写入文件 
    for(i = 0; i < count; i++)
        if(fwrite(&a[i], sizeof(struct arc), 1, fp) != 1)
            printf("File write error!\n");
    fclose(fp);
}


//城市名在交通系统中定位操作，找出城市名在图中对应结点位置
int LocateVertex(ALGraph *G,char *v)
{
    int j = -1, k;
    for(k = 0; k < G->vexnum; k++)
    {
        if(strcmp(G->vertices[k].cityname, v) == 0)  //第k个结点中的城市名与传过来的城市名相同
        {
            j = k;    //记录位置
            break;
        }
        printf("无法找到该城市！\n");
        return j;
    }
}

//用city，plan，train三个文档创建城市交通系统
void CreateGraph(ALGraph *G)
{
    int i = 0, j = 0, k = 0, arc_num = 0, count1, count2, m, t;
    ArcNode *p,*q;
    FILE *fp;
    //打开city.txt文档 
    if((fp = fopen("city.txt", "rb")) == NULL)
    {
        printf("\ncannot open the file!\n");
        return;
    }
    //读取city文档中的内容到数组中 
    while(!feof(fp))
    {
        fscanf(fp, "%10s", city[i]);
        i++;
    }
    fclose(fp);
    //把读取的数据存放到图G中
    while(j < i)
    {
        strcpy(G->vertices[j].cityname, city[j]);
        G->vertices[j].planefirstarc = NULL;
        G->vertices[j].trainfirstarc = NULL;
        j++;
    }
    G->vexnum = i;
    //打开plane.txt文档 
    if((fp = fopen("plane.txt", "rb")) == NULL)
        printf("cannot open the file!\n");
    fscanf(fp, "%d", &count1);
    //将文档中的内容读取到数组a中 
    while(k < count1)
    {
        if(fread(&a[k], sizeof(struct arc), 1, fp) != 1)
            printf("file write error!\n");
        k++;
    }
    fclose(fp);
    //绘制飞机航线图 
    while(k < count1)
    {
        i = LocateVertex(G, a[k].StartCity); //调用函数 LocateVertex(G,a[k].StartCity)得到起始结点的位置 i
        j = LocateVertex(G, a[k].EndCity); //调用函数 LocateVertex(G,a[k].EndCity)得到起始结点的位置 j
        q = G->vertices[i].planefirstarc;
        m = 0;
        while(q != NULL)
        {
            if(q->adjvex == j)  //弧 q中的邻接顶点与j相等
            {
                t = q->info.last+1;  // 将数组a[i] 中的内容都复制到弧q中
                strcpy(q->info.stata[t].number, a[k].id);
                q->info.stata[t].expenditure = a[k].price;
                q->info.stata[t].begintime[0] = a[k].BeginTime[0];
                q->info.stata[t].begintime[1] = a[k].BeginTime[1];
                q->info.stata[t].arrivetime[0] = a[k].ArriveTime[0];
                q->info.stata[t].arrivetime[1] = a[k].ArriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextarc;
        }
        if(m == 0)
        {
            p = (ArcNode*)malloc(sizeof(ArcNode));  //开辟一个弧结点
            p->adjvex = j;   //将数组a[i]中的内容都复制到新的弧结点中
            strcpy(p->info.stata[0].number, a[k].id);
            p->info.stata[0].expenditure = a[k].price;
            p->info.stata[0].begintime[0] = a[k].BeginTime[0];
            p->info.stata[0].begintime[1] = a[k].BeginTime[1];
            p->info.stata[0].arrivetime[0] = a[k].ArriveTime[0];
            p->info.stata[0].arrivetime[1] = a[k].ArriveTime[1];
            p->info.last = 0;
            p->nextarc = G->vertices[i].planefirstarc;
            G->vertices[i].planefirstarc = p;  // 将弧结点连接到适当的位置中去
            arc_num ++;
        }
        k ++;
    }
    G->planearcnum = arc_num;
    //打开train.txt文档 
    if((fp = fopen("train.txt","rb")) == NULL)
    {
        printf("cannot open the file!\n");
        return ;
    }
    k = 0;
    fscanf(fp, "%d", &count2);
    //将文件中的信息存入数组a中 
    while(k < count2)
    {
        if(fread(&a[k], sizeof(struct arc), 1, fp) != 1)
            printf("file write error!\n");
        k++;
    }
    fclose(fp);
    k = 0;       //a的计数变量k=0;
    arc_num = 0;  // 弧的计数变量 arc_num=0;
    //绘制列车车次图 
    while(k < count2)
    {
        i = LocateVertex(G,a[k].StartCity);  // 调用函数 LocateVertex(G,a[k].StartCity)得到起始结点的位置 i
        j = LocateVertex(G,a[k].EndCity);  // 调用函数 LocateVertex(G,a[k].EndCity)得到起始结点的位置 j
        q = G->vertices[i].trainfirstarc;
        m = 0;
        while(q != NULL)
        {
            if(q->adjvex == j)  //弧 q中的邻接顶点与j相等
            {
                t = q->info.last+1;  //将数组a[i] 中的内容都复制到弧q中
                strcpy(q->info.stata[t].number, a[k].id);
                q->info.stata[t].expenditure = a[k].price;
                q->info.stata[t].begintime[0] = a[k].BeginTime[0];
                q->info.stata[t].begintime[1] = a[k].BeginTime[1];
                q->info.stata[t].arrivetime[0] = a[k].ArriveTime[0];
                q->info.stata[t].arrivetime[1] = a[k].ArriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextarc;
        }
        if(m == 0)
        {
            p = (ArcNode*)malloc(sizeof(ArcNode));  //开辟一个弧结点
            p->adjvex = j;  //将数组a[i]中的内容都复制到新的弧结点中
            strcpy(p->info.stata[0].number, a[k].id);
            p->info.stata[0].expenditure = a[k].price;
            p->info.stata[0].begintime[0] = a[k].BeginTime[0];
            p->info.stata[0].begintime[1] = a[k].BeginTime[1];
            p->info.stata[0].arrivetime[0] = a[k].ArriveTime[0];
            p->info.stata[0].arrivetime[1] = a[k].ArriveTime[1];
            p->info.last = 0;
            p->nextarc = G->vertices[i].trainfirstarc;
            G->vertices[i].trainfirstarc = p;  //将弧结点连接到适当的位置中去
            arc_num++;
        }
        k++;
    }
    G->trainarcnum = arc_num;
}

//保存城市交通系统到相应的文档
int save(ALGraph *G)
{
    int i, j, k, t;
    ArcNode *q;
    FILE *fp;
    j = 0;
    //将G中的城市名称保存到数组cty中 
    while(j < G->vexnum)
    {
        strcpy(city[j], G->vertices[j].cityname);
        j++;
    }
    i = 0;
    //打开city.txt文档 
    if((fp = fopen("city.txt", "wb")) == NULL)
        printf("cannot open the file\n");
    //将数组city中的信息存储到文件city中 
    while(i < G->vexnum)
    {
        fprintf(fp, "%10s", city[i]);
        i++;
    }
    fclose(fp);
    k = 0;
    //遍历图中的每一个结点 
    for(i = 0; i < G->vexnum; i++)
    {
        q = G->vertices[i].planefirstarc;
        //将每一个航班信息存储到数组中 
        while(q != NULL)
        {
            for(t = 0; t <= q->info.last; t++)
            {
                strcpy(a[k].StartCity, G->vertices[i].cityname);
                strcpy(a[k].EndCity, G->vertices[q->adjvex].cityname);
                strcpy(a[k].id, q->info.stata[t].number);
                a[k].price = q->info.stata[t].expenditure;
                a[k].BeginTime[0] = q->info.stata[t].begintime[0];
                a[k].BeginTime[1] = q->info.stata[t].begintime[1];
                a[k].ArriveTime[0] = q->info.stata[t].arrivetime[0];
                a[k].ArriveTime[1] = q->info.stata[t].arrivetime[1];
                k++;
            }
            q = q->nextarc;
        }
    }
    //打开plane.txt文件 
    if((fp = fopen("plane.txt", "wb")) == NULL)
    {
        printf("cannot open the file\n");
        return -1;
    }
    i = 0;
    fprintf(fp, "%d", k);
    //将数组a中的航班信息写入文件中 
    while(i < k)
    {
        if(fwrite(&a[i], sizeof(struct arc), 1, fp) != 1)
            printf("file write error\n");
        i++;
    }
    fclose(fp);
    k = 0;
    //遍历图中的每一个结点 
    for(i = 0; i < G->vexnum; i++)
    {
        q = G->vertices[i].trainfirstarc;
        //将每一个车次信息存储到数组中 
        while(q != NULL)
        {
            for(t = 0; t <= q->info.last; t++)
            {
                strcpy(a[k].StartCity, G->vertices[i].cityname);
                strcpy(a[k].EndCity, G->vertices[q->adjvex].cityname);
                strcpy(a[k].id, q->info.stata[t].number);
                a[k].price = q->info.stata[t].expenditure;
                a[k].BeginTime[0] = q->info.stata[t].begintime[0];
                a[k].BeginTime[1] = q->info.stata[t].begintime[1];
                a[k].ArriveTime[0] = q->info.stata[t].arrivetime[0];
                a[k].ArriveTime[1] = q->info.stata[t].arrivetime[1];
                k++;    
            }
            q = q->nextarc;
        }
    }
    //打开train.txt文件 
    if((fp = fopen("train.txt","wb")) == NULL)
    {
        printf("cannot open the file\n");
        return -1;
    }
    i = 0;
    fprintf(fp, "%d", k);
    //将数组a中的车次信息存储到文件中 
    while(i < k)
    {
        if(fwrite(&a[i], sizeof(struct arc), 1, fp) != 1)
            printf("file write error\n");
        i++;
    }
    fclose(fp);
    return 0;
}

//增加城市 
void cityedit(ALGraph *G)
{
    char v[10], c;
    int i;
    printf("请输入新增城市的名称:");
    scanf("%s", v);
    i = LocateVertex(G, v);
    //若城市已经存在 
    if(i >= 0 && i < G->vexnum)
    {
        printf("错误！此城市已存在!\n");
        return ;
    }
    else
    {
        printf("确认?(Y/N)");
        c = getchar();
        getchar();
        if(c == 'Y' || c == 'y')
        {
            //将输入的城市名称复制到G中对应的地方 
            i = G->vexnum;
            strcpy(G->vertices[i].cityname, v);
            G->vertices[i].planefirstarc = NULL;
            G->vertices[i].trainfirstarc = NULL;
            G->vexnum = i + 1;
            save(G);
        }
        else
            return;
    }
}

//增加飞机航班flag = 1；增加列车车次flag = 2 
void flight_trainedit(ALGraph *G, int flag)
{
    int i, j, BeginTime[2], ArriveTime[2], m, t;
    char code[5];
    float money;
    char StartCity[10], EndCity[10], c;
    ArcNode *p, *q;
    //提示用户输入信息
    if (flag == 1)
    {
        printf("请输入新增飞机航班的信息:\n");
        printf("飞机航班编号:");
    }
    else
    {
        printf("请输入新增列车车次的信息:\n");
        printf("列车车次编号:");
    }
    scanf("%s", code);
    getchar();
    printf("起始城市:");
    scanf("%s", StartCity);
    printf("目的城市:");
    scanf("%s", EndCity);
    if (flag == 1)
        printf("航班费用:");
    else
        printf("车次费用:");
    scanf("%f", &money);
    getchar();
    printf("起始时间:");
    scanf("%d:%d", &BeginTime[0], &BeginTime[1]);
    getchar();
    //判断输入时间是否合理 
    while(BeginTime[0] < 0 || BeginTime[0] >= 24 || BeginTime[1] < 0 || BeginTime[1] >= 60)
    {
        printf("时间输入有误，请重新输入\n");
        scanf("%d:%d", &BeginTime[0], &BeginTime[1]);
        getchar();
    }
    printf("到达时间:");
    scanf("%d:%d", &ArriveTime[0], &ArriveTime[1]);
    getchar();
    while(ArriveTime[0] < 0 || ArriveTime[0] >= 24 || ArriveTime[1] < 0 || ArriveTime[1] >= 60)
    {
        printf("时间输入有误，请重新输入\n");
        scanf("%d:%d", &ArriveTime[0], &ArriveTime[1]);
        getchar();
    }
    printf("确认?(Y/N)");
    c = getchar();
    getchar();
    //将输入的信息存储到图中 
    if(c == 'Y' || c == 'y')
    {
        i = LocateVertex(G, StartCity);
        j = LocateVertex(G, EndCity);
        if(i == -1)
        {
            printf("错误！无法找到起始城市\n");
            return;
        }
        if(j == -1)
        {
            printf("错误！无法找到到达城市\n");
            return;
        }
        //判断是飞机航班还是列车车次 
        if (flag == 1)
            q = G->vertices[i].planefirstarc;
        if (flag == 2)
            q = G->vertices[i].trainfirstarc;
        m = 0;
        while(q != NULL)
        {
            //如果到达城市相同 
            if(q->adjvex == j)
            {
                t = q->info.last + 1;
                strcpy(q->info.stata[t].number, code);
                q->info.stata[t].expenditure = money;
                q->info.stata[t].begintime[0] = BeginTime[0];
                q->info.stata[t].begintime[1] = BeginTime[1];
                q->info.stata[t].arrivetime[0] = ArriveTime[0];
                q->info.stata[t].arrivetime[1] = ArriveTime[1];
                q->info.last = t;
                m = 1;
                break;
            }
            q = q->nextarc;
        }
        if(m == 0)
        {
            p = (ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex = j;
            strcpy(p->info.stata[0].number, code);
            p->info.stata[0].expenditure = money;
            p->info.stata[0].begintime[0] = BeginTime[0];
            p->info.stata[0].begintime[1] = BeginTime[1];
            p->info.stata[0].arrivetime[0] = ArriveTime[0];
            p->info.stata[0].arrivetime[1] = ArriveTime[1];
            p->info.last = 0;
            //将结点p添加到交通图中 
            if (flag == 1)
            {
                p->nextarc = G->vertices[i].planefirstarc;
                G->vertices[i].planefirstarc = p;
                G->planearcnum++;
            }
            if (flag == 2)
            {
                p->nextarc = G->vertices[i].trainfirstarc;
                G->vertices[i].trainfirstarc = p;
                G->trainarcnum++;
            }
        }
        save(G);
    }
    else
        return;
}

//用户咨询项目选择界面
void UserDemand(ALGraph G)
{
    int i;
    char q;
    printf("咨询项目如下所示:\n");
    printf("-------------------------------------------------------\n"); 
    printf("|      1=最少行程费用              2=最少中转次数     |\n");
    printf("|      3=返回上一级菜单                               |\n");
    printf("-------------------------------------------------------\n");
    printf("请选择咨询项目: ");
    scanf("%d",&i);
    getchar();
    while(i != 3)
    {
        switch(i)
        {
            case 1: DemandDispose(1, G); break;  //最少费用 
            case 2: DemandDispose(2, G); break;   //最少中转 
        }
        printf("按回车继续\n");
        scanf("%c", &q);
        scanf("%c", &q);
        printf("-------------------------------------------------------\n"); 
        printf("|      1=最少行程费用              2=最少行程时间     |\n");
        printf("|      3=返回上一级菜单                               |\n");
        printf("-------------------------------------------------------\n");
        printf("请选择咨询项目:");
        scanf("%d", &i);
        getchar();
    }
    return ;
}

//用户咨询选择信息输入界面,通过该子程序调用其他咨询子程序
void DemandDispose(int n, ALGraph G)
{
    char q;
    ArcNode *plane, *train;
    infolist planearcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM], trainarcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int i, j, k, final[MAX_VERTEX_NUM], T[MAX_VERTEX_NUM][2];
    float M[MAX_VERTEX_NUM];
 
    //将planearcs和trainarcs赋初值 
    for(i = 0; i < G.vexnum; i++)
        for(j = 0; j < G.vexnum; j++)
            for(k = 0; k < MAX_ROUTE_NUM; k++)
            {
                planearcs[i][j].stata[k].expenditure = INFINITY;
                planearcs[i][j].stata[k].begintime[0] = 0;
                planearcs[i][j].stata[k].begintime[1] = 0;
                planearcs[i][j].stata[k].arrivetime[0] = INFINITY;
                planearcs[i][j].stata[k].arrivetime[1] = INFINITY;
                planearcs[i][j].last = -1;
                trainarcs[i][j].stata[k].expenditure = INFINITY;
                trainarcs[i][j].stata[k].begintime[0] = 0;
                trainarcs[i][j].stata[k].begintime[1] = 0;
                trainarcs[i][j].stata[k].arrivetime[0] = INFINITY;
                trainarcs[i][j].stata[k].arrivetime[1] = INFINITY;
                trainarcs[i][j].last = -1;
            }
 
    //将交通图中的信息保存到planearcs和trainarcs中 
    for(i = 0; i < G.vexnum; i++)
    {
        plane = G.vertices[i].planefirstarc;
        train = G.vertices[i].trainfirstarc;
        while(plane != NULL)
        {
            planearcs[i][plane->adjvex] = plane->info;
            plane = plane->nextarc;
        }
        while(train != NULL)
        {
            trainarcs[i][train->adjvex] = train->info;
            train = train->nextarc;
        }
    }
 
    //打印所有城市，并提示用户选择起始城市和到达城市 
    printf("该交通图中所有城市及编号如下所示：\n");
    for(k = 0; k < G.vexnum; k++)
        printf("%3d=%10s\n", k, G.vertices[k].cityname);
    printf("请选择行程起始城市: ");
    scanf("%d", &i);
    printf("请选择行程到达城市: ");
    scanf("%d",&j);
 
    //确定交通工具 
    printf("请选择交通工具(1=列车; 2=飞机): ");
    scanf("%d", &k);
    //确定是否查询 
    printf("确认? (Y/N) ");
    scanf("%c", &q);
    scanf("%c", &q);
 
    //若确认查询 
    if(q == 'Y' || q == 'y')
    {
        if(k == 1 && n == 1)   //列车最少费用 
            ExpenditureDispose(1, trainarcs, G, i, j, M, final);
        else if(k == 1 && n == 2)  //列车最少中转 
            TransferDispose(1,trainarcs,G,i,j);
        else if(k == 2 && n == 1)  //飞机最少费用 
            ExpenditureDispose(2, planearcs, G, i, j, M, final);
        else if(k == 2 && n == 2)  //飞机最少中转 
            TransferDispose(2,planearcs,G,i,j); 
    }
    //若不查询，则重新显示用户咨询界面 
    else if(q == 'N' || q == 'n')
        UserDemand(G);
    //其他情况则重新查询 
    else
    {
        printf("确认输入错误！\n\n");
        DemandDispose(k,G);
    }
    return ;
}

//最少旅行费用处理
void ExpenditureDispose(int k, infolist (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1, float *M, int *final)
{
    int v = -1, w, i, route;
    float m, expenditure;
    Node *p, *q, *r, *s;
    p = (Node *) malloc (G.vexnum * sizeof(Node));
    //遍历图中的每一个结点，标志未求城市的最少费用 
    for(v = 0; v < G.vexnum; v++)
    {
        *(final + v) = False;  //城市v还未求得最少费用
        //调用函数求得城市v0到v的最少费用
        MinExpenditure(*(*(arcs + v0) + v), M + v, &route);
        p[v].next = NULL;     //将城市v的路径设置为空
        //如果求得的费用小于设置的初始值，则将城市v0和v加入到城市v的路径中
        if(*(M + v) < INFINITY)
        {
            q = (Node *) malloc (sizeof(Node)); 
            s = (Node *) malloc (sizeof(Node));
            q->adjvex = v0;
            s->adjvex = v;
            s->route = route;
            p[v].next = q;
            q->next = s;
            s->next = NULL;
        }                          
    }
    *(M + v0) = 0;        // 城市v0到城市v0的最少费用为0
    *(final + v0) = True; //城市v0设为已求得最少费用
    //遍历图中除vo的所有结点 
    for(i = 1; i < G.vexnum; i++)
    {
        m = INFINITY;
        v = -1;
        //找到未求最小费用的节点中，费用最小的城市结点v 
        for(w = 0; w < G.vexnum; w++)
            if(*(final + w) == False)
                if(*(M + w) < m)
                {
                    v = w;
                    m = *(M + w);
                }
        //v等于v1，则表示v0到v1直达的费用最少 
        if(v == v1)          
        {
            q = p[v].next;
            r = q->next;
            printf("行程路线是:\n");
            while(r != NULL)
            {
                if(k == 1)
                    printf("乘坐%s列车车次在%d:%d从%s到%s\n", (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].number, (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].begintime[0], (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].begintime[1], G.vertices[q->adjvex].cityname, G.vertices[r->adjvex].cityname);
                else
                    printf("乘坐%s飞机航班在%d:%d从%s到%s\n", (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].number, (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].begintime[0], (*(*(arcs + q->adjvex) + r->adjvex)).stata[r->route].begintime[1], G.vertices[q->adjvex].cityname, G.vertices[r->adjvex].cityname);
                
                q = r;
                r = r->next;
            }
            printf("最少旅行费用是%f元\n\n", m);
            for(v = 0; v < G.vexnum; v++)
            {
                q = p[v].next;
                while(q != NULL)
                {
                    s = q;
                    q = q->next;
                    free(s);
                }
                p[v].next = NULL;
            }
            free(p);
            return;
        }
        else if(v != -1)
        {
            *(final + v) = True;   //将城市v设为已求得最少费用
            //遍历图中的每一个结点 
            for(w = 0; w < G.vexnum; w++)
                if(*(final + w) == False && (*(*(arcs + v) + w)).last > -1)
                {
                    //找到从v到v1最小费用的路径 
                    MinExpenditure(*(*(arcs + v) + w), &expenditure, &route);
                    if(*(M + w) > m + expenditure)
                    {
                        *(M + w) = m + expenditure;
                        q = p[w].next;
                        
                        while(q != NULL)
                        {
                            s = q;
                            q = q->next;
                            free(s);
                        }
                        q = &p[w];
                        s = p[v].next;
                        
                        while(s != NULL)
                        {
                            r = (Node *) malloc (sizeof(Node));
                            r->adjvex = s->adjvex;
                            r->route = s->route;
                            q->next = r;
                            q = r;
                            s = s->next;
                        }
                        
                        r = (Node *) malloc (sizeof(Node));
                        r->adjvex = w;
                        r->route = route;
                        r->next = NULL;
                        q->next = r;
                    }//if
                }//if
        }//else
    }//for
    //释放掉占用的空间 
    for(v = 0; v < G.vexnum; v++)
    {
        q = p[v].next;
        while(q != NULL)
        {
            s = q;
            q = q->next;
            free(s);
        }
        p[v].next = NULL;
    }
    free(p);
 //最后没找到符合条件的路径，则输出提示信息
    if(k == 1)
        printf("不存在列车车次从%s到%s\n\n", G.vertices[v0].cityname, G.vertices[v1].cityname);
    else
        printf("不存在飞机航班从%s到%s\n\n", G.vertices[v0].cityname, G.vertices[v1].cityname);
}

//两直达城市之间最少旅行费用和相应路径
void MinExpenditure(infolist arcs, float *expenditure, int *route)
{
    int i;
    *expenditure = arcs.stata[0].expenditure;
    
    if(*expenditure < INFINITY)
        *route = 0;
    else
        *route = -1;
    
    for(i = 1; i <= arcs.last; i++)
        if(arcs.stata[i].expenditure < *expenditure)
        {
            *expenditure = arcs.stata[i].expenditure;
            *route = i;
        }
}

//最少旅行中转次数处理
void TransferDispose(int k, infolist (*arcs)[MAX_VERTEX_NUM], ALGraph G, int v0, int v1)
{
    int visited[MAX_VERTEX_NUM], v, w, n = 1;
    LinkQueue Q;
    ArcNode *t;
    Node *p, *q, *r, *s;
    p = (Node *)malloc(G.vexnum * sizeof(Node));
    //遍历图中每一个结点，将是否访问过设置为0 
    for(v = 0; v < G.vexnum; v++)
    {
        visited[v] = 0;
        p[v].next = NULL;
    }
  
    InitQueue(&Q);  //初始化队列
    visited[v0] = 1;  //将第一个结点访问设置为1
    //对q赋值 
    q = (Node *)malloc(sizeof(Node));
    q->adjvex = v0;
    q->next = NULL;
    p[v0].next = q;
    EnterQueue(&Q, v0);  //将vo结点插入到队列中
    //若队列不为空，则表示中间有访问的城市结点 
    while(!IsEmpty(&Q))
    {
        DeleteQueue(&Q, &v);
        if(k == 1)
            t = G.vertices[v].trainfirstarc;
        else
            t = G.vertices[v].planefirstarc;
        while(t != NULL)
        {
            w = t->adjvex;   //w为与城市v相连的第一个城市
            if(!visited[w])  //城市w未访问
            {
                visited[w] = 1;   //将城市w设为已访问
                q = &p[w];
                s = p[v].next;
                while(s != NULL)
                {
                    r = (Node *)malloc(sizeof(Node));
                    r->adjvex = s->adjvex;
                    q->next = r;
                    q = r;
                    s = s->next;
                }
                r = (Node *)malloc(sizeof(Node));
                r->adjvex = w;
                r->next = NULL;
                q->next = r;
                if(w == v1)
                {
                    q = p[w].next;
                    r = q->next;
                    printf("行程路线是:\n");
                    while(r != NULL)
                    {
                        if(k == 1)
                            printf("乘坐%s列车车次在%d:%d从%s到%s\n",(*(*(arcs+q->adjvex)+r->adjvex)).stata[0].number,(*(*(arcs+q->adjvex)+r->adjvex)).stata[0].begintime[0],(*(*(arcs+q->adjvex)+r->adjvex)).stata[0].begintime[1],G.vertices[q->adjvex].cityname,G.vertices[r->adjvex].cityname);
                        else
                            printf("乘坐%s飞机航班在%d:%d从%s到%s\n",(*(*(arcs+q->adjvex)+r->adjvex)).stata[0].number,(*(*(arcs+q->adjvex)+r->adjvex)).stata[0].begintime[0],(*(*(arcs+q->adjvex)+r->adjvex)).stata[0].begintime[1],G.vertices[q->adjvex].cityname,G.vertices[r->adjvex].cityname);
                        q = r;
                        r = r->next;
                        n++;
                    }
                    printf("最少中转次数是%d次\n\n",n-2);
                    for(v = 0;v < G.vexnum;v++)
                    {
                        q = p[v].next;
                        while(q != NULL)
                        {
                            s = q;
                            q = q->next;
                            free(s);
                        }
                        p[v].next = NULL;
                    }
                    free(p);
                    return;
                }
                EnterQueue(&Q,w);    // 将城市w入队
            }
            t = t->nextarc;        //w等于城市v相连的下一个城市
        }
    }
    for(v = 0; v < G.vexnum; v++)
    {
        q = p[v].next;
        while(q != NULL)
        {
            s = q;
            q = q->next;
            free(s);
        }
        p[v].next = NULL;
    }
    free(p);
    //若最后没有找到符合条件的则输出提示信息 
    if(k == 1)
        printf("不存在列车车次从%s到%s\n\n",G.vertices[v0].cityname, G.vertices[v1].cityname);
    else
        printf("不存在飞机航班从%s到%s\n\n",G.vertices[v0].cityname, G.vertices[v1].cityname);
}

//初始化链队列
void InitQueue(LinkQueue *Q)
{
    Q->front = (QNode *) malloc (sizeof(QNode));
    Q->rear = Q->front;
    Q->front->next = NULL;
}

//入队操作
void EnterQueue(LinkQueue *Q, int x)
{
    QNode *newnode;
    newnode = (QNode *) malloc (sizeof(QNode));
    newnode->adjvex = x;
    newnode->next = NULL;
    Q->rear->next = newnode;
    Q->rear = newnode;
}

//出队操作
void DeleteQueue(LinkQueue *Q, int *x)
{
    QNode *p;
    p = Q->front->next;
    Q->front->next = p->next;
    
    if(Q->rear == p)
        Q->rear = Q->front;
    
    *x = p->adjvex;
    free(p);
}

//队列判空操作
int IsEmpty(LinkQueue *Q)
{
    if(Q->front == Q->rear)
        return(1);
    else
        return(0);
}


//显示城市交通系统
void PrintGraph(ALGraph *G)
{
    int i, j, k;
    ArcNode *q;
    //显示选择的界面 
    printf("显示项目如下所示：\n");
    printf("-------------------------------------------------------\n");
    printf("|      0=显示城市                 1=显示飞机航班      |\n");
    printf("|      2=显示列车车次             3=返回上一级菜单    |\n");
    printf("-------------------------------------------------------\n");
    printf("请选择显示项目: ");
    scanf("%d", &i);
    getchar();
    //进入选择
    while(i != 3)
    {
        switch(i)
        {
            case 0:  //展示城市信息 
                printf("城市:\n");
                for (j = 0; j < G->vexnum; j++)
                printf("%s  ", G->vertices[j].cityname);
                printf("\n");
                break;
            case 1:  //展示飞机信息 
                printf("飞机航班:\n");
                for(j = 0; j < G->vexnum; j++)
                {
                    q = G->vertices[j].planefirstarc;
                    while(q != NULL)
                    {
                        printf("%s---->%s\n", G->vertices[j].cityname, G->vertices[q->adjvex].cityname);
                        for(k = 0; k <= q->info.last; k++)
                            printf("     航班编号:%s  费用:%5.2f 起飞时间:%d:%d  到达时间:%d:%d\n", q->info.stata[k].number, q->info.stata[k].expenditure, q->info.stata[k].begintime[0], q->info.stata[k].begintime[1], q->info.stata[k].arrivetime[0], q->info.stata[k].arrivetime[1]);
                        q = q->nextarc;
                    }
                }
                break;
            case 2:  //展示列车信息 
                printf("列车车次:\n");
                for(j = 0; j < G->vexnum; j++)
                {
                    q = G->vertices[j].trainfirstarc;
                    while(q != NULL)
                    {
                        printf("%s---->%s\n", G->vertices[j].cityname, G->vertices[q->adjvex].cityname);
                        for(k = 0; k <= q->info.last; k++)
                            printf("    车次编号:%s  费用:%5.2f 起飞时间:%d:%d  到达时间:%d:%d\n", q->info.stata[k].number, q->info.stata[k].expenditure, q->info.stata[k].begintime[0], q->info.stata[k].begintime[1], q->info.stata[k].arrivetime[0], q->info.stata[k].arrivetime[1]);
                        q = q->nextarc;
                    }
                }
                break;
        }
        printf("-------------------------------------------------------\n");
        printf("|      0=显示城市                 1=显示飞机航班      |\n");
        printf("|      2=显示列车车次             3=返回上一级菜单    |\n");
        printf("-------------------------------------------------------\n");
        printf("请选择显示项目: ");
        scanf("%d", &i); 
        getchar();
    }
}
