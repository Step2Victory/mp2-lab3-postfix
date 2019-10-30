#include "postfix.h"
#include "stack.h"
#include "map"
 

string StringDecoder(string s)
{
	string word = "";
	string ans = "";
	int dot = 0;
	int count_vars = 0, count_ops = 0, count_brackets = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == ' ')
		{
			if (word != "")
			{
				ans += word + " ";
				count_vars++;
			}
			word = "";
			dot = 0;
		}
		else if ((s[i] >= '0' && s[i] <= '9' && word == "") || ((s[i] >= '0' && s[i] <= '9' || s[i] == '.') && word != "" && word[0] >= '0' && word[0] <= '9'))
		{
			if (s[i] == '.' && !dot)
			{
				word += s[i];
				dot++;
			}
			else if (s[i] == '.')
			{
				throw 1;
			}
			else
			{
				word += s[i];
			}
		}
		else if (s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-' || s[i] == '(' || s[i] == ')')
		{
			if (word != "")
			{
				ans += word + " " + s[i] + " ";
				count_vars++;
			}
			else
				ans = ans + s[i] + " ";
			if (s[i] != '(' && s[i] != ')')
				count_ops++;
			if (s[i] == '(')
				count_brackets++;
			else if (s[i] == ')')
				count_brackets--;
			if (count_brackets < 0)
				throw 1;
			word = "";
			dot = 0;
		}
		else if ((s[i] < '0' || s[i] > '9') && word != "" && word[0] >= '0' && word[0] <= '9')
		{
			throw 1;
		}
		else
		{
			word += s[i];
		}
	}
	if (word != "")
	{
		ans += word + " ";
		count_vars++;
	}
	if (count_vars - 1 != count_ops || count_brackets != 0)
		throw 1;
	ans.erase(ans.size() - 1, 1);
	return ans;

}


string TPostfix::ToPostfix()
{
  //postfix = string("ab+");
	postfix = "";
	TStack<string> stack;
	string word;
	string op = "*/-+(";
	for (stringstream is(infix); is >> word;)
	{
		if (word == "*" || word == "/" || word == "(")
			stack.push(word);
		else if (word == ")")
		{
			while (stack.Top() != "(")
				postfix += stack.pop() + " ";
			stack.pop();
		}
		else if ((word == "+" || word == "-") && stack.isEmpty())
			stack.push(word);
		else if ((word == "+" || word == "-") && !(stack.isEmpty()))
		{
			if (stack.Top() == "/" || stack.Top() == "*")
			{
				while (!stack.isEmpty() && stack.Top() != "(")
					postfix += stack.pop() + " ";
			}
			stack.push(word);
		}
		else
		{
			postfix += word + " ";
		}
	}
	while (!stack.isEmpty())
		postfix += stack.pop() + " ";
	postfix.erase(postfix.size() - 1, 1);
	return postfix;
}

double TPostfix::Calculate()
{
	map<string, double> vars;
	string word;
	for (stringstream is(infix); is >> word;)
	{
		if (word != "+" && word != "-" && word != "*" && word != "/" && word != "(" && word != ")" && (word[0] < '0' || word[0] > '9') && vars.find(word) == vars.end())
		{	
			double a;
			cout << "Введите переменную " << word << ": ";
			cin >> a;
			vars[word] = a;
		}
		else
		{
			double a;
			stringstream tmp(word);
			tmp >> a;
			vars[word] = a;
		}
	}
	TStack<double> stack;
	for (stringstream is(postfix); is >> word;)
	{
		if (word == "+")
		{
			double a = stack.pop();
			double b = stack.pop();
			stack.push(b + a);
		}
		else if (word == "-")
		{
			double a = stack.pop();
			double b = stack.pop();
			stack.push(b - a);
		}
		else if (word == "*")
		{
			double a = stack.pop();
			double b = stack.pop();
			stack.push(b * a);
		}
		else if (word == "/")
		{
			double a = stack.pop();
			double b = stack.pop();
			stack.push(b / a);
		}
		else
		{
			stack.push(vars[word]);
		}
	}
	return stack.Top();
}
