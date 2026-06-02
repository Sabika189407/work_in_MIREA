#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <queue>

bool is_number(const std::string& token)
{
	if (token.length() == 0)
    {
        return false;
    }
	size_t i = 0;
	if (token[0] == '-')
    {
			if (token.length() == 1) return false;
			i++;
	}
	for (; i < token.length(); i++)
    {
		if (!std::isdigit(token[i]))
        {
            return false;
        }
	}
	return true;
}

bool isOperator(const std::string& token)
{
	return (token == "+") || (token == "-") || (token == "*") || (token == "/") || (token == "%");
}

int priority(const std::string& op)
{
	if (op == "+" || op == "-")
    {
        return 0;
    }
	return 1;
}

int main()
{
    std::string line;
	std::getline(std::cin, line);
	std::istringstream input_s(line);
	std::stack<std::string> operands;
	std::string token;
	while (input_s >> token)
    {
		if (is_number(token))
        {
			std::cout << token << ' ';
			continue;
		}
		if (isOperator(token))
        {
			while (operands.size() && isOperator(operands.top()) && (priority(operands.top()) >= priority(token)))
            {
					std::cout << operands.top() << ' ';
					operands.pop();
			}
			operands.push(token);
			continue;
		}
		if (token == "(")
        {
			operands.push(token);
			continue;
		}
		if (token == ")")
        {
			if (!operands.size())
            {
					throw std::runtime_error("missed \")\" operand");
			}
			while (operands.top() != "(")
            {
				std::cout << operands.top() << ' ';
				operands.pop();
				if (operands.size() == 0) {
						throw std::runtime_error("missed \")\" operand");
				}
			}
			operands.pop();
			continue;
		}
		throw std::runtime_error("unknown operand");
	}
	while (operands.size())
    {
		if (operands.top() == "(")
        {
				throw std::runtime_error("missed \")\" operand");
		}
		std::cout << operands.top() << ' ';
		operands.pop();
	}
	std::cout << std::endl;
}