#include <iostream>
using namespace std;

// 单项式结点
struct PolyNode
{
	int c;
	int e;
	PolyNode* next;
};

// 一元多项式单链表
typedef PolyNode* Poly;

// 初始化带头结点的单链表
int InitPoly(Poly& aPoly)
{
	aPoly = new PolyNode;
	aPoly->next = nullptr;
	return 0;
}

// 撤销单链表
int DestroyPoly(Poly& aPoly)
{
	while (aPoly != nullptr)
	{
		PolyNode* temp = aPoly;
		aPoly = aPoly->next;
		delete temp;
	}
	return 0;
}

// 在指定结点后面插入一个新结点
// 不检查插入单项是否符合降序规则
int InsertAfter(PolyNode* p, int c, int e)
{
	// 检查参数
	if (p == nullptr) return -1;

	// 创建新结点
	PolyNode* q = new PolyNode;
	q->c = c;
	q->e = e;

	// 将新结点插入到指定结点的后面
	q->next = p->next;
	p->next = q;

	return 1;
}

// 删除指定结点的下一个结点
int DeleteAfter(PolyNode* p)
{
	if (p == nullptr || p->next == nullptr) return -1;

	PolyNode* temp = p->next;
	p->next = p->next->next;
	delete temp;

	return 0;
}

// 判断一元多项式链表是否为已撤销的无效链表
int IsNull(Poly aPoly)
{
	return aPoly == nullptr;
}

// 判断一元多项式是否为有效（有头结点）且空的单链表
bool IsEmpty(Poly aPoly)
{
	return aPoly != nullptr && aPoly->next == nullptr;
}

// 从标准输入流输入一元多项式
// 约定按降序输入，-1 -1为输入结束标志，输入单项直接追加到链表尾部
int InputPoly(Poly aPoly)
{
	if (IsNull(aPoly) || !IsEmpty(aPoly)) return -1;

	int c, e;
	PolyNode* tail = aPoly;
	while (cin >> c >> e, e >= 0)
	{
		InsertAfter(tail, c, e);
		tail = tail->next;
	}

	return 0;
}

// 将指定一元多项式单链表输出到标准输出流
int OutputPoly(const Poly aPoly)
{
	if (IsNull(aPoly)) return -1;
	
	if (IsEmpty(aPoly))
	{
		cout << '0' << endl;
		return 0;
	}

	for (PolyNode* p = aPoly; p->next != nullptr; p = p->next)
	{
		cout << p->next->c << ' ' << p->next->e << ' ';
	}
	cout << endl;

	return 0;
}

// 在指定一元多项式上求导：A = A'
Poly Derivative(Poly aPoly)
{
	if (IsNull(aPoly)) return aPoly;

	for (PolyNode* q = aPoly; q->next != nullptr;)
	{
		if (q->next->e == 0)
		{
			// 对0次项，直接删除，这时不需要向前移动遍历指针
			DeleteAfter(q);
		}
		else
		{
			// 对非0次项，求导，然后前进到下一项
			q->next->c *= q->next->e;
			q->next->e--;
			q = q->next;
		}
	}

	return aPoly;
}

// 计算并返回两个一元多项式的累加和：A += B
Poly PolyAdd(Poly A, Poly B)
{
	if (IsNull(A) || IsNull(B)) return A;

	// 同步遍历两个一元多项式
	PolyNode* pa = A, * pb = B->next;
	while (pa->next != nullptr && pb != nullptr)
	{
		if (pa->next->e > pb->e)
		{
			pa = pa->next;
		}
		else if (pa->next->e < pb->e)
		{
			InsertAfter(pa, pb->c, pb->e);
			pa = pa->next;
			pb = pb->next;
		}
		else
		{
			pa->next->c += pb->c;
			if (pa->next->c == 0)
			{
				DeleteAfter(pa);
			}
			else
			{
				pa = pa->next;
			}
			pb = pb->next;
		}
	}

	// 将B多项式中剩余项加到A中
	while (pb != nullptr)
	{
		InsertAfter(pa, pb->c, pb->e);
		pa = pa->next;
		pb = pb->next;
	}

	return A;
}

// 计算并返回一个单项式乘一个一元多项式：A = B * (c,e)
Poly SPolyMulti(Poly B, int c, int e)
{   
	if (IsNull(B)) return nullptr;
	Poly A;
	InitPoly(A);
	PolyNode* pa = A;

	for (PolyNode* pb = B->next; pb != nullptr; pb = pb->next)
	{
		InsertAfter(pa, pb->c * c, pb->e + e);
		pa = pa->next;
	}

	return A;
}

// 计算并返回两个多项式相乘：C = A * B
Poly PolyMulti(Poly A, Poly B)
{   
	Poly C;
	InitPoly(C);
	for (PolyNode* pb = B->next; pb != NULL; pb = pb->next)
	{
		Poly D = SPolyMulti(A, pb->c, pb->e);

		PolyAdd(C, D);
		
		DestroyPoly(D);
	}
	return C;
}

int main()
{
	Poly A, B;
	InitPoly(A);
	InitPoly(B);
	InputPoly(A);
	InputPoly(B);

	Poly C = PolyMulti(A, B);
	OutputPoly(C);

	DestroyPoly(A);
	DestroyPoly(B);
	DestroyPoly(C);
	return 0;
}
