#include <iostream>
#include <stack>
#include <vector>
#include <cctype>
#include <string>
#include <cmath>
using namespace std;

/*
��׺���ʽ

ֻ�е�ǰ�����������ȼ����ڲ�����ջջ���Ĳ����������ȼ�������ջ��
���򵯳��������Լ����������м���ֱ��ջ�������������ȼ����ڵ�ǰ��������
Ȼ�󽫵�ǰ������ѹջ�������еĲ�����������ϣ���������ջΪ��ʱ����
������ջ��ʣ�µ�Ψһһ��Ԫ�ر������յı��ʽ��ֵ��

��������Ϊ������
*/
//��ȡ���������ȼ�
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
		if (isspace(str[i]))//�����հ�
			;
		else if (isdigit(str[i]))//��ȡ������
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
		else if (str[i] == ')')//һֱ������ֱ����һ������
		{
			while (operator_stack.top() != '(')
			{
				opt = operator_stack.top();
				operator_stack.pop();
				int b = operand_stack.top();//ע�������������
				operand_stack.pop();
				int a = operand_stack.top();
				operand_stack.pop();
				operand_stack.push(calculate(a, b, opt));
			}
			operator_stack.pop();
		}
		else
		{
			while (!operator_stack.empty() && getPriority(operator_stack.top()) > getPriority(str[i]))//���ջ�����������ȼ���
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

	while (!operator_stack.empty())//����ջ��ʣ�������
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
���䣺
�����������������λ�ò�ͬ��ǰ׺���ʽ�������λ��������صĲ�����֮ǰ����׺�ͺ�׺ͬ��
(3 + 4) �� 5 - 6 ������׺���ʽ
- �� + 3 4 5 6 ǰ׺���ʽ
3 4 + 5 �� 6 - ��׺���ʽ


ǰ׺���ʽ��ǰ׺�Ƿ�������ʽ��
ǰ׺���ʽ�ļ������ֵ��
��������ɨ����ʽ����������ʱ��������ѹ���ջ�����������ʱ������ջ�����������������������������Ӧ�ļ��㣬
���������ջ���ظ���������ֱ�����ʽ����ˣ��������ó���ֵ��Ϊ���ʽ�Ľ����
����ǰ׺���ʽ��- �� + 3 4 5 6����
(1) ��������ɨ�裬��6��5��4��3ѹ���ջ��
(2) ����+���������˵���3��4��3Ϊջ��Ԫ�أ�4Ϊ�ζ�Ԫ�أ�ע�����׺���ʽ���Ƚϣ��������3+4��ֵ����7���ٽ�7��ջ��
(3) �������ǡ����������˵���7��5�������7��5=35����35��ջ��
(4) �����-������������35-6��ֵ����29���ɴ˵ó����ս����
���Կ������ü��������ǰ׺���ʽ��ֵ�Ǻ����׵ġ�

��׺���ʽ����׺�Ƿ����沨��ʽ��
��׺���ʽ�ļ������ֵ��
��ǰ׺���ʽ���ƣ�ֻ��˳���Ǵ������ң�
��������ɨ����ʽ����������ʱ��������ѹ���ջ�����������ʱ������ջ�����������������������������Ӧ�ļ��㣬
���������ջ���ظ���������ֱ�����ʽ���Ҷˣ��������ó���ֵ��Ϊ���ʽ�Ľ����
�����׺���ʽ��3 4 + 5 �� 6 -����
(1) ��������ɨ�裬��3��4ѹ���ջ��
(2) ����+���������˵���4��3��4Ϊջ��Ԫ�أ�3Ϊ�ζ�Ԫ�أ�ע����ǰ׺���ʽ���Ƚϣ��������3+4��ֵ����7���ٽ�7��ջ��
(3) ��5��ջ��
(4) �������ǡ����������˵���5��7�������7��5=35����35��ջ��
(5) ��6��ջ��
(6) �����-������������35-6��ֵ����29���ɴ˵ó����ս����


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
