#include <iostream>
#include <stack>
#include <vector>
#include <cctype>
#include <string>
#include <cmath>
using namespace std;

/*
中缀表达式

只有当前操作符的优先级高于操作符栈栈顶的操作符的优先级，才入栈，
否则弹出操作符以及操作数进行计算直至栈顶操作符的优先级低于当前操作符，
然后将当前操作符压栈。当所有的操作符处理完毕（即操作符栈为空时），
操作数栈中剩下的唯一一个元素便是最终的表达式的值。

操作数仅为正整数
*/
//获取操作符优先级
int getPriority(char opt)
{
	int priority;
	if (opt == '^')
		priority = 3;
	else if (opt == '*' || opt == '/')
		priority = 2;
	else if (opt == '+' || opt == '-')
		priority = 1;
	else if (opt == '(')
		priority = 0;
	return priority;
}

int calculate(int a,int b,char opt)
{
	cout << a << opt << b << endl;
	if (opt == '+')
		return a + b;
	else if (opt == '-')
		return a - b;
	else if (opt == '*')
		return a*b;
	else if (opt == '/')
		return a / b;
	else if (opt == '^')
		return pow(a, b);
	else
		throw "error";
}

int evaluateExpression(char* str)
{
	stack<char> operator_stack;
	stack<int> operand_stack;

	int len = strlen(str);
	int i = 0;
	int j = 0;
	char temp[11];
	char opt;
	while (i < len)
	{
		if (isspace(str[i]))//跳过空白
			;
		else if (isdigit(str[i]))//读取操作数
		{
			temp[0] = str[i];
			j = 1;
			while (isdigit(str[i + j]))
			{
				temp[j] = str[i + j];
				j++;
			}
			i = i + j - 1;
			temp[j] = '\0';
			operand_stack.push(stoi(temp));
		}
		else if (str[i] == '(')
			operator_stack.push(str[i]);
		else if (str[i] == ')')//一直弹出，直到另一半括号
		{
			while (operator_stack.top() != '(')
			{
				opt = operator_stack.top();
				operator_stack.pop();
				int b = operand_stack.top();//注意操作数的左右
				operand_stack.pop();
				int a = operand_stack.top();
				operand_stack.pop();
				operand_stack.push(calculate(a, b, opt));
			}
			operator_stack.pop();
		}
		else
		{
			while (!operator_stack.empty() && getPriority(operator_stack.top()) > getPriority(str[i]))//如果栈顶操作符优先级高
			{
				opt = operator_stack.top();
				operator_stack.pop();
				int b = operand_stack.top();
				operand_stack.pop();
				int a = operand_stack.top();
				operand_stack.pop();
				operand_stack.push(calculate(a, b, opt));
			}
			
			operator_stack.push(str[i]);
		}
		i++;
	}

	while (!operator_stack.empty())//处理栈的剩余操作符
	{
		opt = operator_stack.top();
		operator_stack.pop();
		int b = operand_stack.top();
		operand_stack.pop();
		int a = operand_stack.top();
		operand_stack.pop();
		operand_stack.push(calculate(a, b, opt));
	}
	return operand_stack.top();

}


/*
补充：
运算符相对与操作数的位置不同：前缀表达式的运算符位于与其相关的操作数之前；中缀和后缀同理。
(3 + 4) × 5 - 6 就是中缀表达式
- × + 3 4 5 6 前缀表达式
3 4 + 5 × 6 - 后缀表达式


前缀表达式（前缀记法、波兰式）
前缀表达式的计算机求值：
从右至左扫描表达式，遇到数字时，将数字压入堆栈，遇到运算符时，弹出栈顶的两个数，用运算符对它们做相应的计算，
并将结果入栈；重复上述过程直到表达式最左端，最后运算得出的值即为表达式的结果。
例如前缀表达式“- × + 3 4 5 6”：
(1) 从右至左扫描，将6、5、4、3压入堆栈；
(2) 遇到+运算符，因此弹出3和4（3为栈顶元素，4为次顶元素，注意与后缀表达式做比较），计算出3+4的值，得7，再将7入栈；
(3) 接下来是×运算符，因此弹出7和5，计算出7×5=35，将35入栈；
(4) 最后是-运算符，计算出35-6的值，即29，由此得出最终结果。
可以看出，用计算机计算前缀表达式的值是很容易的。

后缀表达式（后缀记法、逆波兰式）
后缀表达式的计算机求值：
与前缀表达式类似，只是顺序是从左至右：
从左至右扫描表达式，遇到数字时，将数字压入堆栈，遇到运算符时，弹出栈顶的两个数，用运算符对它们做相应的计算，
并将结果入栈；重复上述过程直到表达式最右端，最后运算得出的值即为表达式的结果。
例如后缀表达式“3 4 + 5 × 6 -”：
(1) 从左至右扫描，将3和4压入堆栈；
(2) 遇到+运算符，因此弹出4和3（4为栈顶元素，3为次顶元素，注意与前缀表达式做比较），计算出3+4的值，得7，再将7入栈；
(3) 将5入栈；
(4) 接下来是×运算符，因此弹出5和7，计算出7×5=35，将35入栈；
(5) 将6入栈；
(6) 最后是-运算符，计算出35-6的值，即29，由此得出最终结果。


*/


int main()
{
	char* str = "2+ 2*2^4 - 1";
	cout << str << " = " << evaluateExpression(str) << endl;

	str = "10+8*(6-1)^2-(7-1)";
	cout << str << " = " << evaluateExpression(str) << endl;
	system("pause");
	return 0;
}
