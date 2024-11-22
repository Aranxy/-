#include<iostream>
#include<queue>
#include<string>
#include <vector>
using namespace std;
struct Edge {
	int a;
	int q;
	Edge* next;
};
template<class T>
struct Vertex {
	T vertex;
	Edge* firstedge;
};
template<class T>
class ALGraph {
public:
	ALGraph();
	~ALGraph();
	void bfTraverse(int v);
	void dfTraverse(int v);
	void chushihua();
	Vertex<T> a[10];
	int vertexnum, edgenum;
	int visited[10];
private:
};
template<class T>
ALGraph<T>::ALGraph()                     //有向网图
{
	cout << "请输入节点数(6)，边数(15)：";
	cin >> vertexnum >> edgenum;
	int v1, v2, q;
	cout << "请依次输入每个节点的值(Pe N Pa L T M)：";     //Pe N Pa L T M
	for (int i = 0; i < vertexnum ;i++)
	{
		cin >> a[i].vertex;
		a[i].firstedge = nullptr;
	}
	cout << "请输入15个第v1个 到 v2个 的 权重：";              //0 1 109 0 2 82 0 3 81 0 4 21 0 5 124 1 2 58 1 3 55 1 4 108 1 5 32 2 3 3 2 4 97 2 5 92 3 4 95 3 5 89 4 5 113
	for (int i = 0; i < edgenum; i++)
	{
		cin >> v1 >> v2 >> q;
		Edge*s = new Edge;
		s->a = v2;
		s->q = q;
		s->next = a[v1].firstedge;   //头插法
		a[v1].firstedge = s;
		Edge* k = new Edge;
		k->a = v1;
		k->q = q;
		k->next = a[v2].firstedge;   //头插法
		a[v2].firstedge = k;
	}
}
template<class T>
ALGraph<T>::~ALGraph()
{
	Edge* p;
	for (int i = 0; i < vertexnum; i++)
	{
		p = a[i].firstedge;
		while (p != nullptr)
		{
			Edge* q;
			q = p;
			p = p->next;
			delete q;
		}
	}
}
template<class T>
void ALGraph<T>::chushihua()              //对visited 进行初始化，以防错乱
{
	for (int i = 0; i < vertexnum; i++)
	{
		visited[i] = 0;
	}
}
template<class T>
void ALGraph<T>::dfTraverse(int v)
{
	Edge* p = a[v].firstedge;
	visited[v] = 1;                  //第V个点被访问
	cout << a[v].vertex<<" ";            //输出第V个的值
	while (p != nullptr)
	{
		if (visited[p->a] ==0 )      //如果V的邻接点未被访问
		{
			dfTraverse(p->a);		//访问临界点序号
		}
			p = p->next;
	}
}
template<class T>
void ALGraph<T>::bfTraverse(int v)
{
	queue<int> Q;
	Q.push(v);
	visited[v] = 1;
	cout << a[v].vertex<<" ";
	int k;
	while (!Q.empty())
	{
		Edge* p;
		k = Q.front();
		Q.pop();
		p = a[k].firstedge;
		while (p != nullptr)
		{
			if (visited[p->a] != 1)
			{
				Q.push(p->a);
				visited[p->a] = 1;
				cout << a[p->a].vertex<<" ";
			}
			p = p->next;
		}
	}
}
struct{
	int adjvex;
	double lowcost;
}minEdge[10];
template<class T>
void Prim(ALGraph<T> &G, int k)     //从顶点k开始
{
	Edge* p = G.a[k].firstedge;
	//初始化
	for (int i = 0; i < G.vertexnum; i++)
	{
		minEdge[i].lowcost = 100000;
		minEdge[i].adjvex = k;
	}
	while (p!=nullptr) 
	{
		int adj = p->a;                             //遍历k的邻接点
		minEdge[adj].lowcost = p->q;
		p = p->next;
	}
	//
	minEdge[k].lowcost = 0;							//被访问过标记			
	for (int i = 1; i < G.vertexnum; i++)			//访问每一个点入其他点集
	{
		double t=100000;
		//查找最短边 以及对应的外点K
		for (int j = 0; j < G.vertexnum; j++)      
		{
			if (minEdge[j].lowcost!=0&&t > minEdge[j].lowcost)
			{
				t = minEdge[j].lowcost;
				k = j;
			}
		}
		cout << G.a[minEdge[k].adjvex].vertex <<"-" << G.a[k].vertex <<"-";       //输出连接的边
		cout << minEdge[k].lowcost<<",";
		minEdge[k].lowcost = 0;
		//更新minEdge
	    p = G.a[k].firstedge;
		while (p!=nullptr) 
		{
			int adj = p->a;                             //遍历k的邻接点
			if (minEdge[adj].lowcost != 0 && p->q < minEdge[adj].lowcost) 
			{
				minEdge[adj].lowcost = p->q;
				minEdge[adj].adjvex = k;
			}
			p = p->next;
		}
	}
	cout << endl;
}

template<class T>
void Dijkstra(ALGraph<T> &G, int s) 
{
	Edge* p = G.a[s].firstedge;
	double dis[10];
	string path[10];
	int num,k,t;
	//初始化dis[]和path[]  出发点到目标点i的。。。。
	for (int i = 0; i < G.vertexnum; i++)
	{
		dis[i] = 100000;
		path[i] = " ";
	}
	while (p != nullptr)
	{
		dis[p->a] = p->q;
		path[p->a]=G.a[s].vertex+"-"+G.a[p->a].vertex;
		p = p->next;
	}
	dis[s] = 0;          //顶点s加入集合S
	num = 1;             //记录遍历过的顶点数.
	while (num < G.vertexnum)
	{
		//在dis[]中查找非0最小值,并得到序号k
		t = 1000000;
		for (int i = 0; i < G.vertexnum; i++)
		{
			if ((dis[i] != 0) && (dis[i] < t))
			{
				t = dis[i];
				k = i;
			}
		}
		num++;
		//输出
		cout << dis[k] << path[k] << endl;
		p = G.a[k].firstedge;
		//更新dis[]和path[]
		while (p != nullptr)
		{
			if (dis[p->a] > dis[k] + p->q)
			{
				dis[p->a] = dis[k] + p->q;
				path[p->a] = path[k]+"-"+G.a[p->a].vertex;
			}
			p = p->next;
		}
		//将顶点k加入集合S
		dis[k] = 0;
	}
}

int main()
{
	ALGraph<string> Tu;
	int choice,v;
	while (true)
	{
		cout << endl;
		cout << "\t\t--------------------------------------------\n";
		cout << "\t\t             数值操作系统               \n";
		cout << " \t\t--------------------------------------------\n";
		cout << " \t\t*            1.广度遍历                                 *\n";
		cout << " \t\t*            2.深度遍历								*\n";
		cout << " \t\t*            3.Prim最小生成树算法								*\n";
		cout << " \t\t*            4.Kruskal最小生成树算法								*\n";
		cout << " \t\t*            4.最短路径								*\n";
		cout << " \t\t*            5.退出系统                                *\n";
		cout << "输入序号进行操作：";
		cin >> choice;
		switch (choice)
		{
		case 1:
			Tu.chushihua();
			cout << "请输入遍历开始的节点序号:";
			cin >> v;
			Tu.bfTraverse(v);
			break;
		case 2:
			Tu.chushihua();
			cout << "请输入遍历开始的节点序号:";
			cin >> v;
			Tu.dfTraverse(v);
			break;
		case 3:
			cout << "请输入遍历开始的节点序号:";
			cin >> v;
			Prim(Tu, v);
			break;
		case 4:
			cout << "请输入起点的节点序号:";
			cin >> v;
			Dijkstra(Tu, v);
			break;
		default:
			exit(0);
		}
	}
	return 0;
}





//ctrl+a一件选中所有代码.
//研究一下类作为函数的参数时的值传递和引用传递，以及赋值          值传递的函数为什么只能调用一次?
//因为我的类中使用了指针，按值传递时可能会共享空间，导致下一次调用失败。