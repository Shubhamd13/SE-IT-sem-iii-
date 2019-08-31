
#include<iostream>
#include<string.h>
#include<map>
#include<math.h>
using namespace std;
//-------------Stack as ADT-----------------------
//---using link list
template <class T>
struct Node{
    T var;
    struct Node *next;
};
template<class T>
class Stack{
    Node<T> *start;
    public:
    //ctor----------
    Stack():start(NULL){};
    void push(T );
    T pop();
    T top();
};
template<class T>
void Stack<T>::push(T a){
    Node<T> *temp;
    temp=start;
    start= new Node<T>;
    start->var=a;
    start->next=temp;
}
template<class T>
T Stack<T>::pop(){
    if(start== NULL ){return 0;}
    Node<T> *temp;
    T t;
    temp=start;
    t=start->var;
    start=start->next;
    delete temp;
    return t;
}
template<class T>
T Stack<T>::top(){
    if(start==NULL){return 0;}
    return start->var;
}
//---------------------------------------------------
bool isOperator(char t){
    switch(t)
    {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return true;
    default:
        return false;
    }
}
bool precedence(char a,char b)
{
    if(a==0)return false;
    if( a == '^' && b == '^' )return false;
    map <char,int> prcd;
    prcd['(']=0;
    prcd['-']=1;
    prcd['+']=2;
    prcd['*']=3;
    prcd['/']=4;
    prcd['^']=5;
    return (prcd[a]>=prcd[b]);
}
void  toPostfix(char expression[],char strin[])
{
    char c;
    int l=0;
    Stack<char> operators;
    int len=strlen(expression);
    for(int i=0;i<len;i++)
    {
        c=expression[i];
        if(!isOperator(c)){
            //-----------operand----------
            strin[l]=c;
            ++l;
        }else{
            //--------operator---------
            if(c == '(')
            {
                operators.push(c);
            }else if (c == ')'){
                while(operators.top()!='(')
                {
                    strin[l]=operators.pop();
                    ++l;
                }
                operators.pop();//pop opening braces
            }else{
                while(precedence(operators.top(),c))
                {
                    strin[l]=operators.pop();
                    ++l;
                }
                operators.push(c);
            }
        }
    }
     while(operators.top()!=0)
        {
                        strin[l]=operators.pop();
                        ++l;
        }
        strin[l]='\0';
}
void  toPrefix(char expression[],char prefix[])
{
    int len;
    char *temp;
    temp=strrev(expression);
    len=strlen(temp);
    for(int i=0;i<len;i++)
    {
        if(temp[i]=='(')
        {
            temp[i]=')';
        }else if(temp[i]==')')
        {
            temp[i]='(';
        }
    }
    toPostfix(temp,prefix);
    prefix=strrev(prefix);
}
map<char, int> getVals(char postfix[])
{
    int val,len=strlen(postfix);
    map<char,int> operands;
    for(int i=0;i<len;i++)
    {
        if(!isOperator(postfix[i])) //is operand
        {
            if(operands.find(postfix[i])==operands.end())// take value
            {
                cout<<"Enter value of "<<postfix[i]<<"=";
                cin>>val;
                operands.insert(pair<char,int>(postfix[i],val));
            }
        }
    }
    return operands;
}
void evalPostfix(char postfix[])
{
    map<char,int> operands=getVals(postfix);
    //-----------------temp-----------
    map<char,int>::iterator it;
    for(it=operands.begin();it!=operands.end();++it)
    {
        cout<<it->first<<"\t"<<it->second<<endl;
    }
    //----------temp------------
    Stack<float> values;
    int len=strlen(postfix);
    float val1,val2;
    for(int i=0;i<len;i++)
    {
        if(!isOperator(postfix[i]))//push operand to stack
        {
            values.push(operands[postfix[i]]);
        }else{
           val1=values.pop();
           val2=values.pop();
           switch(postfix[i])
           {
            case'+':
                values.push(val1+val2);
            break;
            case'-':
                values.push(val2-val1);
            break;
            case'*':
                  values.push(val1*val2);
            break;
            case'/':
                   values.push(val2/val1);
            break;
               case'^':
                   values.push(pow(val2,val1));
            break;
           }
        }
    }
    cout<<"Result is :"<<fixed<<values.pop()<<endl;
}
void evalPrefix(char prefix[])
{
    map<char,int> operands=getVals(prefix);
    //-----------------temp-----------
    map<char,int>::iterator it;
    for(it=operands.begin();it!=operands.end();++it)
    {
        cout<<it->first<<"\t"<<it->second<<endl;
    }
    //----------temp------------
    Stack<float> values;
    int len=strlen(prefix);
    float val1,val2;
    for(int i=len-1;i>=0;i--)
    {
        if(!isOperator(prefix[i]))//operand
        {
            values.push(operands[prefix[i]]);
        }else{
            val1=values.pop();
            val2=values.pop();
           switch(prefix[i])
           {
            case'+':
                values.push(val1+val2);
            break;
            case'-':
                values.push(val1-val2);
            break;
            case'*':
                  values.push(val1*val2);
            break;
            case'/':
                   values.push(val1/val2);
            break;
               case'^':
                   values.push(pow(val1,val2));
            break;
           }
        }
    }
    cout<<"Result is :"<<fixed<<values.pop()<<endl;
}
//------------------main----------------
int main(){
    char expression[100],postfix[100],prefix[100];
    cout<<"Enter infix expression : ";
    cin>>expression;
    toPostfix(expression,postfix);
    cout<<"Postfix expression is : "<<postfix<<endl;
    toPrefix(expression,prefix);
    cout<<"Prefix expression is : "<<prefix<<endl;
    //--------Evaluation----------------
    cout<<"---------Evaluating postfix---------"<<endl;
    evalPostfix(postfix);
    cout<<"---------Evaluating prefix---------"<<endl;
    evalPrefix(prefix);
}
