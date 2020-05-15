
#include <iostream>
#include <string>

using namespace std;




class bad_expression { };

#include <stack>
#include <sstream>

bool isOperator(char c) {
   switch(c) {
      case '+':
      case '-':
      case '/':
      case '*':
      case '%':
        return true;
   }
   return false;
}

template<typename T = int>
std::string rpn(std::string str) {
   std::stack<char> ops;

   std::stringstream result;
   
   for(size_t index = 0; index < str.size(); ++index) {
       if(str[index] == ')') {
           if(ops.empty()) throw bad_expression();
           char op = ops.top();
           ops.pop();
           result << op << ' ';
       } else if (isOperator(str[index])) {
           ops.push(str[index]);
       } else if (isdigit(str[index])) {
           size_t offset;
           T value = std::stoi(str.substr(index), &offset);
           index += offset - 1;
           result << value << ' ';
       }
   }

   return result.str();
}

int main() {
    cout << "Quelle expression voulez-vous convertir ? \n";
    string expression;
    getline(cin, expression);

    cout << "En RPN : " << rpn(expression) << "\n";
}