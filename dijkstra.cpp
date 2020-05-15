
#include <iostream>
#include <string>

using namespace std;

class bad_expression { };



#include <stack>

template<typename T = int>
T compute(char op, T left, T right) {
   switch(op) {
      case '+':
         return left + right;
      case '-':
         return left - right;
      case '/':
         return left / right;
      case '*':
         return left * right;
      case '%':
         return left % right;
   }
   throw bad_expression();
}

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
T evalue(std::string str) {
   std::stack<char> ops;
   std::stack<T>    values;
   
   for(size_t index = 0; index < str.size(); ++index) {
       if(str[index] == ')') {
           if(values.size() < 2 or ops.empty()) throw bad_expression();
           T right = values.top();
           values.pop();
           T left = values.top();
           values.pop();
           char op = ops.top();
           ops.pop();
           values.push(compute(op, left, right));
       } else if (isOperator(str[index])) {
           ops.push(str[index]);
       } else if (isdigit(str[index])) {
           size_t offset;
           T value = std::stoi(str.substr(index), &offset);
           index += offset - 1;
           values.push(value);
       }
   }

   if(values.size() != 1 or !ops.empty()) throw bad_expression();
   return values.top();
}

int main() {

    cout << "Quelle expression voulez-vous évaluer ? \n";
    string expression;
    getline(cin, expression);

    try {
        cout << expression << " = " << evalue(expression) << "\n";
    } catch( bad_expression ) {
        cout << "Bad expression \n";
    }
}