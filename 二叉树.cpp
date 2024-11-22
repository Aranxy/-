#include<iostream>
#include<vector>
#include<string>
using namespace std;
template<class T>
class BiNode
{
public:
	T data;
	BiNode* lchild;
	BiNode* rchild;
private:
};
template<class T>
class Bitree
{
private:
	BiNode<T>* Create(BiNode<T>* bt); //创建结点函数
	void Release(BiNode<T>* bt);      //删除结点函数
public:
	BiNode<T>* root;
	Bitree();						//无参构造函数
	~Bitree();						//采用递归方法;均调用其他函数
	void PreOrder(BiNode<T>* bt);
	void PreOrder0(BiNode<T>* bt);
	void InOrder(BiNode<T>* bt);
	void PostOrder(BiNode<T>* bt);
	void LeverOrder();
};
template<class T>
Bitree<T>::Bitree()
{
	root = Create(root);
}
template<class T>
Bitree<T>::~Bitree()
{
	Release(root);
}
template<class T>
BiNode<T>* Bitree<T>::Create(BiNode<T>* bt)      //这里的参数可有可无，可以放在函数体中，传递无意义,主要是为了增加辨识
{
	string ch;
	int a;
	if(bt==root)
	cout << "请使用前序方法创建树（可以以 1 2 3 # # 4 5 # 6 # # 7 # # #为例）："<<endl;                //                       1
	cin >> ch;																					   //	          2           
	if (ch == "#")																				   //          3      4           
		bt = nullptr;																			   //              5      7     
	else                                                                                           //                6
	{
		a = stoi(ch);                          //将字符串转化为整型
		bt = new BiNode<T>;
		bt->data = a;
		bt->lchild = Create(bt->lchild);       //按照前序输入序列生成二叉树
		bt->rchild = Create(bt->rchild);
	}
	return bt;
}
template<class T>
void Bitree<T>::Release(BiNode<T>* bt)
{
	if (bt != nullptr)
	{
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
}
template<class T>
void Bitree<T>::PreOrder(BiNode<T>* bt)
{
	if (bt == nullptr)
		return;
	else
	{
		cout << bt->data << " ";
		PreOrder(bt->lchild);         //有参传递是在这里体现的
		PreOrder(bt->rchild);
	}
}
template<class T>
void Bitree<T>::PreOrder0(BiNode<T>* bt)
{
	BiNode<T>* k;
	while (bt != nullptr)
	{
		cout << bt->data;
		bt = bt->lchild;
		while (bt != nullptr)
		{
			cout << bt->data;

			bt = bt->lchild;
		}
	}
}
template<class T>
void Bitree<T>::InOrder(BiNode<T>* bt)
{
	if (bt == nullptr)
		return;
	else
	{
		InOrder(bt->lchild);
		cout << bt->data << " ";
		InOrder(bt->rchild);
	}
}
template<class T>
void Bitree<T>::PostOrder(BiNode<T>* bt)
{
	if (bt == nullptr)
		return;
	else
	{
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		cout << bt->data << " ";
	}
}
template<class T>
void Bitree<T>::LeverOrder()
{
	int front = -1, rear = -1;
	BiNode<T>* q;
	vector<BiNode<T>*> Q;
	if (root == nullptr)
		return;
	rear++;
	Q.push_back(root);
	while (front != rear)                         //当前的 while (front != rear) 条件在某些情况下会导致问题，不如直接使用 while (!Q.empty()) 来判断队列是否为空。
	{
		q = Q[++front];
		cout << q->data << " ";
		if (q->lchild != nullptr)               //队列初始化问题：在你的代码中使用了 front 和 rear 来模拟队列的头尾，但实际上不需要使用这两个变量，因为 vector 本身就可以实现队列功能。你可以直接在 Q 上进行 push_back 和 pop_front 操作，简化代码逻辑。
		{
			rear++;
			Q.push_back(q->lchild);
		}
		if (q->rchild != nullptr)
		{
			rear++;
			Q.push_back(q->rchild);
		}
	}

}
int main()
{
	Bitree<int> Tree;
	int choice ;
	while (true)
	{
		cout << "\t\t--------------------------------------------\n";
		cout << "\t\t             数值操作系统               \n";
		cout << " \t\t--------------------------------------------\n";
		cout << " \t\t*            1.前序遍历                                 *\n";
		cout << " \t\t*            2.中序遍历								*\n";
		cout << " \t\t*            3.后序遍历								*\n";
		cout << " \t\t*            4.层次遍历								*\n";
		cout << " \t\t*            5.退出系统                                *\n";
		cout << "输入序号进行操作：";
		cin >> choice;
		switch (choice)
		{
		case 1:Tree.PreOrder(Tree.root);
			break;
		case 2:Tree.InOrder(Tree.root);
			break;
		case 3:Tree.PostOrder(Tree.root);
			break;
		case 4:Tree.LeverOrder();
			break;
		default:
			exit(0);
		}
	}
	return 0;
}









//动态数组 vector  vector<BiNode<T>*> Q;   Q.push_back(root);   Q[++front];
//将字符串转化为整形  stoi(string);
//getline(cin,input)  整行读入  以便读入空格
//istringstream iss(line) 将整行字符串转化为字符串流，以便整个读取
//iss>>input 逐个读取line中以空格分隔的元素