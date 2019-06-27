#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// 定义表示分词类型的枚举类型
enum TokenType { Token_Operator, Token_Value };

// 表示一个分词的结构体，分词可能是一个运算符，可能是一个操作数。
struct Token
{
	TokenType Type;   // 分词类型
	union
	{
		int Operator; // 运算符编码
		double Value; // 操作数的值
	};
};

// 返回运算符的编码，如果是不可识别的运算符，返回-1。
int GetOperator(char op)
{
	static char Operators[] = "+-*/()";
	if (op == '\0') return 0;
	for (int i = 0; Operators[i] != '\0'; i++)
		if (Operators[i] == op) return i + 1;   // 起止运算符编码约定为0，实际运算符编码从1开始。
	return -1;
}

// 从表达式串中提取并返回一个词，并修改exp参数指向取词之后的串。
int GetToken(Token &aToken, char *&exp)
{
	char *p = exp;
	
	// 略过空白符
	while (isspace(*p)) p++;

	// 如果表达式串已经结束，则生成一个结束运算符
	if (*p == '\0')
	{
		aToken.Type = Token_Operator;
		aToken.Operator = 0;
		return 0;
	}

	// 检查是否为数字，这里约定不支持以小数点开始的数值写法，即不支持如".13"的操作数写法。
	if (isdigit(*p))
	{
		// 提取一个操作数
		aToken.Type = Token_Value;
		double aValue = 0.0;
		// 逐字符提取整数部分，换算成数值
		for (; *p != '\0' && isdigit(*p); p++)
		{
			aValue = aValue * 10 + (*p - '0');
		}
		// 提取小数部分
		if (*p == '.')
		{
			// 跳过小数点
			p++;
			// 逐字符读取小数部分，换算成数值
			double aDecimal = 0.1;
			for (; *p != '\0' && isdigit(*p); p++)
			{
				aValue += (*p - '0') * aDecimal;
				aDecimal /= 10.0;
			}
			if (*p == '.') return -1;
		}
		aToken.Value = aValue;
	}
	else
	{
		// 提取一个运算符
		aToken.Type = Token_Operator;
		int aOperator = GetOperator(*p);
		if (aOperator < 0) return -2;
		aToken.Operator = aOperator;
		p++;
	}

	exp = p;
	return 0;
}

char *priorities[] = 
{
	//       #+-*/()
	/* # */ "E<<<<<X",
	/* + */ ">>><<<>",
	/* - */ ">>><<<>",
	/* * */ ">>>>><>",
	/* / */ ">>>>><>",
	/* ( */ "X<<<<<=",
	/* ) */ "XXXXXXX",
};

double calc(double aValue1, int aOperator, double aValue2)
{
	switch (aOperator)
	{
	case 1:
		return aValue1 + aValue2;
	case 2:
		return aValue1 - aValue2;
	case 3:
		return aValue1 * aValue2;
	case 4:
		return aValue1 / aValue2;
	default:
		throw "不可识别的运算符";
	}
}

double calc(char exp[])
{
	char *p = exp;
	
	stack<int> sOp;   // 运算符栈
	stack<double> sValue; // 操作数栈
	sOp.push(0);  // 起始运算符入栈
	
	while (true)
	{
		Token aToken;
		// 读取一个分词
		if (GetToken(aToken, p) != 0) throw "解析表达式错误(不可识别的运算符)！";

		// 处理读到的分词
		switch (aToken.Type)
		{
		case Token_Operator:
			// 读到运算符时，计算运算符栈的栈顶优先级高的运算符
			while (priorities[sOp.top()][aToken.Operator] == '>')
			{
				if (sValue.empty()) throw "解析表达式错误(没有足够的操作数)！";
				double aValue2 = sValue.top(); sValue.pop();
				if (sValue.empty()) throw "解析表达式错误(没有足够的操作数)！";
				double aValue1 = sValue.top(); sValue.pop();
				int aOperator = sOp.top(); sOp.pop();
				sValue.push(calc(aValue1, aOperator, aValue2));
			}
			switch (priorities[sOp.top()][aToken.Operator])
			{
			case '<':
				sOp.push(aToken.Operator);
				break;
			case '=':
				sOp.pop();
				break;
			case 'E':
			{
				if (sValue.empty()) throw "解析表达式错误(缺少结果)！";
				double aResult = sValue.top(); sValue.pop();
				if (!sValue.empty()) throw "解析表达式错误(有多余的操作数)！";
				return aResult;
			}
			case 'X':
				throw "解析表达式错误(错误的运算符顺序)！";
			}
			break;
		case Token_Value:
			// 读到操作数时，操作数入栈保留
			sValue.push(aToken.Value);
			break;
		}
	}
}

int main()
{
	char exp[1024];

	cout << "输入表达式：" << endl;
	while (cin.getline(exp, sizeof(exp) / sizeof(*exp)))
	{
		try
		{
			double result = calc(exp);
			cout << exp << " = " << result << endl;
		}
		catch (char *err)
		{
			cerr << err << endl;
		}
		catch (...)
		{
			cerr << "解析表达式失败！" << endl;
		}
	}
	return 0;
}