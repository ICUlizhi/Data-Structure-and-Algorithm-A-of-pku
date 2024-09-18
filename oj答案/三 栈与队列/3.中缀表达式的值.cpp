#include <bits/stdc++.h>
using namespace std;

// 获取运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 计算两个数的运算结果
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// 中缀表达式转后缀表达式
string infixToPostfix(string expression) {
    stack<char> ops;
    string output = "";

    for (int i = 0; i < expression.length(); i++) {
        // 如果是数字，处理多位数字的情况
        if (isdigit(expression[i])) {
            string num = "";
            while (i < expression.length() && isdigit(expression[i])) {
                num += expression[i];
                i++;
            }
            output += num + " ";  // 将完整的数字添加到输出
            i--;  // 调整索引，确保不会跳过下一个非数字字符
        }
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                output += ops.top();
                output += " ";  // 运算符之间加空格分隔
                ops.pop();
            }
            ops.pop(); // 弹出 '('
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                output += ops.top();
                output += " ";  // 运算符之间加空格分隔
                ops.pop();
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.empty()) {
        output += ops.top();
        output += " ";  // 运算符之间加空格分隔
        ops.pop();
    }

    return output;
}

// 计算后缀表达式的值
int evaluatePostfix(string postfix) {
    stack<int> values;
    istringstream tokens(postfix);
    string token;
    
    while (tokens >> token) {
        if (isdigit(token[0])) {
            // 如果是数字，转为整数并压入堆栈
            values.push(stoi(token));
        } else {
            // 如果是运算符，弹出两个操作数进行计算
            int val2 = values.top(); values.pop();
            int val1 = values.top(); values.pop();
            int result = applyOp(val1, val2, token[0]);
            values.push(result);
        }
    }

    return values.top();
}

int main() {
    int N;
    cin >> N;  // 测试数据的组数
    cin.ignore();  // 忽略换行符
    while (N--) {
        string expression;
        getline(cin, expression);  // 输入一行中缀表达式
        string postfix = infixToPostfix(expression);  // 转换为后缀表达式
        int result = evaluatePostfix(postfix);  // 计算后缀表达式的值
        cout << result << endl;  // 输出结果
    }
    return 0;
}
