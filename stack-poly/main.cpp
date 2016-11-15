//
//  main.cpp
//  stack-poly
//
//  Created by Jiang Zhenfei on 2016/11/14.
//  Copyright © 2016年 姜震飞. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#define max 20
//栈数据结构定义
using namespace std;
typedef int ElemType;
typedef struct {
    ElemType elements[max];
    int top;
}STACK;
typedef struct {
    float elements[max];
    int top;
}fSTACK;

void MakeNull(STACK &S)
{
    S.top = -1;
}
void MakeNull(fSTACK &S)
{
    S.top = -1;
}
bool IsEmpty(STACK &S)
{
    if (S.top < 0) {
        return true;
    }
    else
        return false;
}
bool IsEmpty(fSTACK &S)
{
    if (S.top < 0) {
        return true;
    }
    else
        return false;
}

ElemType GetTop(STACK &S)
{
    if (IsEmpty(S)) {
        return NULL;
    }
    else
        return S.elements[S.top];
}
float GetTop(fSTACK &S)
{
    if (IsEmpty(S)) {
        return NULL;
    }
    else
        return S.elements[S.top];
}
bool Pop(STACK &S,ElemType &elem)
{
    if (IsEmpty(S)) {
        return false;
    }
    else
    {
        elem = S.elements[S.top];
        S.top -= 1;
    }
    return true;
}
bool Pop(fSTACK &S,float &elem)
{
    if (IsEmpty(S)) {
        return false;
    }
    else
    {
        elem = S.elements[S.top];
        S.top -= 1;
    }
    return true;
}
bool Push(STACK &S,ElemType elem)
{
    if (S.top == max - 1) {
        return false;
    }
    else{
        S.top += 1;
        S.elements[S.top] = elem;
        return true;
    }
}
bool Push(fSTACK &S,float elem)
{
    if (S.top == max - 1) {
        return false;
    }
    else{
        S.top += 1;
        S.elements[S.top] = elem;
        return true;
    }
}
void ViewStack(STACK &S)
{
    int i;
    cout <<"-----THE STACK-----"<<endl;
    if (IsEmpty(S)) {
        cout << "NULL\n";
    }
    else{
        for (i = S.top; i >-1; i--) {
            //cout <<i<<" "<<S.elements[i]<<endl;
            printf("%d %c\n",i,S.elements[i]);
        }
    }
}
void ViewStack(fSTACK &S)
{
    int i;
    cout <<"-----THE STACK-----"<<endl;
    if (IsEmpty(S)) {
        cout << "NULL\n";
    }
    else{
        for (i = S.top; i >-1; i--) {
            //cout <<i<<" "<<S.elements[i]<<endl;
            printf("%d %f\n",i,S.elements[i]);
        }
    }
}
char Precede(char op1,char op2){
    //判断op1和op2优先级的高低，返回'>','<','='
    switch(op1){
        case '+':
            switch(op2){
                case '*':
                case '/':
                case '(':
                case '@':
                    return '<';
                    break;
                default:
                    return '>';
                    break;
            }
            break;
        case '-':
            switch(op2){
                case '*':
                case '/':
                case '(':
                case '@':
                    return '<';
                    break;
                default:
                    return '>';
                    break;
            }
            break;
        case '*':
            switch(op2){
                case '(':
                case '@':
                    return '<';
                    break;
                default:
                    return '>';
                    break;
            }
            break;
        case '/':
            switch(op2){
                case '(':
                case '@':
                    return '<';
                    break;
                default:
                    return '>';
                    break;
            }
            break;
        case '(':
            switch(op2){
                case ')':
                    return '=';
                    break;
                default:
                    return '<';
                    break;
            }
            break;
        case ')':
            switch(op2){
                case '@':
                    return '<';
                    break;
                default:
                    return '>';
                    break;
            }
            break;
        case '#':
            switch(op2){
                case '#':
                    return '=';
                    break;
                default:
                    return '<';
                    break;
            }
            break;
        default:
            return '<';
            break;
    }
}

//convert infix expression to postfix
string convert(string expr,STACK &S)
{
    int i = 0,j = 0,flag = 0;
    string result = "";
    int now,e,last = '#';
    do
    {
        now = expr.at(i);
        i++;
        //to judge whether the '-' represents negtive or minus
        if (now == '-')
        {
            if (last != ')' &&(!(last >='0' && last <= '9'))) {
                now = ' ';
                result += '@';
            }
            //repalce '-' with '@',which represents negtive operation
            else
                result += ' ';
        }
        if (now == '#') {
            flag++;
        }
        
        else if ((now >='0' && now <= '9')||(now >= 'a'&&now <= 'z')||(now >= 'A'&&now <= 'Z')||'.'== now) {
            result += now;
        }
        else if (now == ' ')
            continue;
        else if (now == ')')
        {
            //pop until '('
            while (S.elements[S.top] != '(') {
                Pop(S, e);
                //cout << e;
                ViewStack(S);
                result += e;
            }
        }
        else
        {
            result +=' ';
            if (S.top == -1) {
                Push(S, now);
                ViewStack(S);
            }
            else
            {
                if ('(' == S.elements[S.top]) {
                    Push(S, now);
                    ViewStack(S);
                }
                else if ('<' == Precede(S.elements[S.top], now))
                {
                    Push(S, now);
                    ViewStack(S);
                }
                else
                {
                    //pop until a lower priority one
                    while ('<' != Precede(S.elements[S.top], now)) {
                        Pop(S, e);
                        ViewStack(S);
                        //cout << e;
                        result += e;
                    }
                    //then push tmp to Stack S
                    Push(S, now);
                    ViewStack(S);
                }
            }
        }
        last = now;
    }while (flag != 2);
    for (j = S.top; j >= 0; j--) {
        Pop(S, e);
        if (e!= '(' &&e != ')')
            //cout << e;
            result += e;
    }
    return result;
}

float Calculate(string expr,fSTACK &S)
{
    char now,last = '#';
    int i = 0,flag = 0;
    string floatnum = "";
    float num,opnd1,opnd2,tr,result;
    stringstream stream;
    do {
        now = expr.at(i);
        i++;
        if (now == '#') {
            flag ++;
        }
        else if ((now >= '0'&&now <= '9')||now == '.')
        {//读取1个浮点数
            if (last == '@') {
                floatnum += '-';
            }
            floatnum += now;
        }
        else
        {
            if (floatnum != "") {
                stream << floatnum;
                stream >> num;
                Push(S, num);
                ViewStack(S);//view the stack
                stream.clear();//necessary if you dont want to make you program shit!!!
                floatnum = "";
            }
            //starting calculate and then push'em back to stack
            if (now == '+') {
                Pop(S, opnd1);
                Pop(S, opnd2);
                tr = opnd1 + opnd2;
                Push(S, tr);
                ViewStack(S);
            }
            else if (now == '-') {
                Pop(S, opnd1);
                Pop(S, opnd2);
                tr = opnd2 - opnd1;
                Push(S, tr);
                ViewStack(S);
            }
            else if (now == '*') {
                Pop(S, opnd1);
                Pop(S, opnd2);
                tr = opnd1 * opnd2;
                Push(S, tr);
                ViewStack(S);
            }
            else if (now == '/') {
                Pop(S, opnd1);
                Pop(S, opnd2);
                tr = opnd2 / opnd1;//attention!!!!!!!!!!!
                Push(S, tr);
                ViewStack(S);
            }
        }
        last = now;
    } while (flag != 2);//two #,stop
    Pop(S, result);
    return result;
}
float Variable()
{
    float result;
    
    return result;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    //cout << "Hello, World!\n";
    ifstream in("input.txt");
    string expression,postfix;
    int line = 0;
    float result;
    STACK S;
    fSTACK fS;
    MakeNull(S);
    MakeNull(fS);
    if (in.fail()) {
        cout << "could not find input.txt"<<endl;
        return  1;
    }
    while (getline(in,expression)) {
        cout << ++line <<":"<<expression<<endl;
    }
    postfix = convert(expression,S);
    ViewStack(S);
    postfix = '#' +postfix +'#';
    cout << "the postfix is:"<<postfix<<endl;
    result = Calculate(postfix, fS);
    cout <<"the calculate result is:"<<result<<endl;
    return 0;
}
