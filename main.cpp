#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#include<stdio.h>
#include <cstdlib>
#include <stdlib.h>
class DFA
{
public:
    int states;
    int currentstate;
    std::vector<int> finalstates;
    std::vector<std::vector<int>> transition;

    DFA()
    {
        currentstate=0;
        states=0;
        finalstates=vector<int>();
        transition=vector<vector<int>>();
    }
    void reset()
    {
        currentstate=0;
    }
};
void print(DFA* d)
{
    cout<<"DFA :"<<endl;
    cout<<"No of States : "<<d->states<<endl;
    cout<<"States\t0\t1"<<endl;
    for(int i=0; i<d->states; i++)
    {
        cout<<i<<"\t"<<d->transition[i][0]<<"\t"<<d->transition[i][1]<<endl;
    }
    cout<<"Final States : ";
    for(int i:d->finalstates)
    cout<<i<<" ";
    cout<<endl;
}
bool check_DFA(DFA d,string s)
{
    int state=0;
    for(char i:s)
    {
        if(i=='a'||i=='0')
        state=d.transition[state][0];
        else
        state=d.transition[state][1];
        if(state==-1)
        return false;
    }
    if(count(d.finalstates.begin(),d.finalstates.end(),state))
    return true;
    return false;
}
class NFA
{
public:
    int states;
    vector<int> finalstates;
    vector<vector<vector<int>>> transition;

    NFA(int n)
    {
    states = n;
    finalstates = vector<int>();
    transition = vector<vector<vector<int>>>(states, vector<vector<int>>(2, vector<int>()));
    }

};

NFA initialize_NFA()
{
    int b;
    cout << "Enter Number of States: ";
    cin >> b;
    NFA a(b);
    cout << "Enter Final States :";
    int t;
    cin >> t;
    while (t != -1)
    {
        a.finalstates.push_back(t);
        cin >> t;
    }
    for (int i = 0; i < a.states; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << "Enter Transition From State " << i << " in input " << j << " : ";
            int s;
            cin >> s;
            while (s != -1)
            {
                a.transition[i][j].push_back(s);
                cin >> s;
            }
        }
    }
    return a;
}

bool check_NFA(NFA a, string s)
{
    queue<int> q;
    q.push(0);
    int i = 0;
    while (i < s.size())
    {
        int queueSize = q.size();
        while (queueSize--)
        {
            int state = q.front();
            q.pop();
            for (int j : a.transition[state][s[i] - '0'])
                q.push(j);
        }
        i++;
    }
    while (!q.empty())
    {
        if (count(a.finalstates.begin(), a.finalstates.end(), q.front()))
            return true;
        q.pop();
    }
    return false;
}
void print_NFA(NFA n)
{
    cout<< "NFA :"<<endl;
    cout << "No of States : " << n.states << endl;
    cout << "States\t0\t1" << endl;
    for (int i = 0; i < n.states; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < 2; j++)
        {
            cout << "{";
            for (int k = 0; k < n.transition[i][j].size(); k++)
            {
                cout << n.transition[i][j][k];
                if (k < n.transition[i][j].size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "}";
            if (j < 1)
            {
                cout << "\t";
            }
        }
        cout << endl;
    }
    cout << "Final States : ";
    for (int i : n.finalstates)
        cout << i << " ";
    cout << endl;
}
string convstring(set<int>&s)
{
    string ret="";
    for(int i:s)
    ret+=to_string(i)+".";
    return ret;
}
bool existfinal(set<int>&temp,vector<int>&arr)
{
    for(auto &i: temp)
    {
        if(count(arr.begin(),arr.end(),i))
        return true;
    }
    return false;
}
DFA nfatodfa(NFA a)
{
    DFA d;
    unordered_map<string,int>m;
    m["0."]=d.states;
    d.states++;
    d.transition.push_back(vector<int>(2,-1));
    queue<set<int>>q;
    q.push({0});
    while(!q.empty())
    {
        set<int>s=q.front();
        int h=m[convstring(s)];
        q.pop();
        for(int j=0; j<2; j++)
        {
            set<int>temp;
            for (const auto& elem: s) {
                for(int m: a.transition[elem][j])
                {
                if(m!=-1)
                temp.insert(m);
                }
            }
            if(temp.empty())
            continue;
            string p=convstring(temp);
            if(!m.count(p))
            {
                m[p]=d.states;
                d.transition[h][j]=d.states;
                d.states++;
                q.push(temp);
                d.transition.push_back(vector<int>(2,-1));
                if(existfinal(temp,a.finalstates))
                d.finalstates.push_back(d.states-1);
            }
            else
            {
            d.transition[h][j]=m[p];
            }
        }   
    }
    return d;
}
class NFAe {
public:
    int states;
    std::vector<int> finalstates;
    std::vector<std::vector<std::vector<int>>> transition;

    NFAe(int n)
    {
    states = n;
    finalstates = vector<int>();
    transition = vector<vector<vector<int>>>(states, vector<vector<int>>(3, vector<int>()));
    }   

};

NFAe initialize_NFAe()
{
    int b;
    cout << "Enter Number of States: ";
    cin >> b;
    NFAe a(b);
    cout << "Enter Final States :";
    int t;
    cin >> t;
    while (t != -1)
    {
        a.finalstates.push_back(t);
        cin >> t;
    }
    for (int i = 0; i < a.states; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << "Enter Transition From State " << i << " in input " << j << " : ";
            int s;
            cin >> s;
            while (s != -1)
            {
                a.transition[i][j].push_back(s);
                cin >> s;
            }
        }
        cout << "Enter Transition From State " << i << " in input ε : ";
        int s;
        cin >> s;
        while (s != -1)
        {
            a.transition[i][2].push_back(s);
            cin >> s;
        }
    }
    return a;
}
void print_NFAe(NFAe n)
{
    cout<<" NFA with e transition "<<endl;
    cout << "No of States : " << n.states << endl;
    cout << "States\t0\t1" << endl;
    for (int i = 0; i < n.states; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < 3; j++)
        {
            cout << "{";
            for (int k = 0; k < n.transition[i][j].size(); k++)
            {
                cout << n.transition[i][j][k];
                if (k < n.transition[i][j].size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "}";
            if (j < 2)
            {
                cout << "\t";
            }
        }
        cout << endl;
    }
    cout << "Final States : ";
    for (int i : n.finalstates)
        cout << i << " ";
    cout << endl;
}
void dfs(int i,vector<unordered_set<int>>&e_closure,vector<vector<vector<int>>>&transition,int& visited)
{
    if((visited>>i & 1))
    return ;
    e_closure[i].insert(i);
    visited=visited|(1<<i);
    for(int j: transition[i][2])
    {
        if(!(visited>>j & 1))
        dfs(j,e_closure,transition,visited);
        for(int k:e_closure[j])
        e_closure[i].insert(k);
    }
}
NFA convNFA(NFAe ne)
{
    NFA n(ne.states);
    vector<unordered_set<int>>e_closure(ne.states,unordered_set<int>());
    int visited=0;
    for(int i=0; i<ne.states; i++)
    dfs(i,e_closure,ne.transition,visited);
    for(int i=0; i<ne.states; i++)
    {
        for(int j=0; j<2; j++)
        {
            set<int>s;
            for(auto& k: e_closure[i])
            {
                for(int m:ne.transition[k][j])
                {
                    for(auto& h: e_closure[m])
                    {
                    s.insert(h);
                    }
                }
            }
            for(auto &k : s)
            n.transition[i][j].push_back(k); 
        }
    }
    for(int i:ne.finalstates)
    for(int j:e_closure[i])
    n.finalstates.push_back(j);
    return n;
}
string infixtopostfix(string s)
{
    stack<char>st;
    string postfix="";
    for(char i:s)
    {
        if(i=='('|| i=='*'|| i=='|'||i=='.')
        st.push(i);
        else if(i=='a')
        postfix+="0";
        else if(i=='b')
        postfix+="1";
        else if(i==')')
        {
            while(st.top()!='(')
            {
                postfix+=st.top();
                st.pop();
            }
            st.pop();
        }
    }
    while(!st.empty())
    {
        postfix+=st.top();
        st.pop();
    }
    return postfix;
}
NFAe postfixtoNFAe(string s)
{
        stack<NFAe>st;
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]=='0')
            {
                NFAe n(2);
                n.transition[0][0].push_back(1);
                n.finalstates.push_back(1);
                st.push(n);
            }
            else if(s[i]=='1')
            {
                NFAe n(2);
                n.transition[0][1].push_back(1);
                n.finalstates.push_back(1);
                st.push(n);
            }
            else if(s[i]=='.')
            {
                NFAe n2=st.top();
                st.pop();
                NFAe n1=st.top();
                st.pop();
                NFAe n3(n1.states+n2.states);
                for(int j=0; j<n1.states; j++)
                {
                    for(int p=0; p<3; p++)
                    {
                    for(int k:n1.transition[j][p])
                    {
                        n3.transition[j][p].push_back(k);
                    }}
                }
                for(int j=0; j<n2.states; j++)
                {
                    for(int p=0; p<3; p++)
                    {
                    for(int k:n2.transition[j][p])
                    {
                        n3.transition[j+n1.states][p].push_back(k+n1.states);
                    }
                    }
                }
                for(int j:n2.finalstates)
                n3.finalstates.push_back(j+n1.states);
                for(int j:n1.finalstates)
                {
                    n3.transition[j][2].push_back(n1.states);
                }
                st.push(n3);
            }
            else if(s[i]=='*')
            {
                NFAe n1=st.top();
                st.pop();
                for(int j:n1.finalstates)
                {
                    n1.transition[j][2].push_back(0);
                    n1.transition[0][2].push_back(j);
                }
                st.push(n1);
            }
            else if(s[i]=='|')
            {
                NFAe n2=st.top();
                st.pop();
                NFAe n1=st.top();
                st.pop();
                NFAe n3(n1.states+n2.states+2);
                for(int j=0; j<n1.states; j++)
                {
                    for(int p=0; p<3; p++)
                    {
                    for(int k:n1.transition[j][p])
                    {
                        n3.transition[j+1][p].push_back(k+1);
                    }
                    }
                }
                for(int j=0; j<n2.states; j++)
                {
                    for(int p=0; p<3; p++)
                    {
                    for(int k:n2.transition[j][p])
                    {
                        n3.transition[j+n1.states+1][p].push_back(k+n1.states+1);
                    }
                    }
                }
                for(int j:n1.finalstates)
                n3.transition[j+1][2].push_back(n1.states+n2.states+1);
                for(int j:n2.finalstates)
                n3.transition[j+1+n1.states][2].push_back(n1.states+n2.states+1);
                n3.finalstates.push_back(n1.states+n2.states+1);
                n3.transition[0][2].push_back(1);
                n3.transition[0][2].push_back(n1.states+1);
                st.push(n3);
            }
            else
            {
                cout<<"Errror";
            }
        }
        return st.top();

}
string adddot(string s)
{
    string answer="";
    for(int i=0; i<s.size(); i++)
    {
        if(s[i]==')' && ((i+1)<s.size()) && s[i+1]=='(')
        {
            answer+=')';
            answer+='.';
        }
        else
        answer+=s[i];
    }
    return answer;
}
string removespace(string s)
{
    string answer="";
    for(char i:s)
    if(i!=' ')
    answer+=i;
    return answer;
}
DFA regextoDFA(string s_infix)
{
    s_infix=adddot(removespace(s_infix));
    string s_postfix=infixtopostfix(s_infix);
    NFAe ne=postfixtoNFAe(s_postfix);
    NFA n=convNFA(ne);
    DFA d=nfatodfa(n);
    return d;
}
bool checkstate(DFA ds)
{
    if(count(ds.finalstates.begin(),ds.finalstates.end(),ds.currentstate))
    return true;
    else
    return false;
}
void nextstate(DFA& ds,char c)
{
    if(ds.currentstate!=-1)
    ds.currentstate=ds.transition[ds.currentstate][c-'a'];
}
bool iteratetillmatch(int& index,string &in, vector<DFA>&input)
{
    int finished=0;
    int startindex=index;
    int size=in.size();
    int dfasize=input.size();
    vector<int>matched(dfasize,-2);
    for(int i=0; i<dfasize; i++)
    input[i].reset();
    for(int i=0; i<dfasize; i++)
    {
        if(checkstate(input[i]))
        matched[i]=-1;
    }
    while(index<size)
    {
        for(int i=0; i<dfasize; i++)
        nextstate(input[i],in[index]);
        for(int i=0; i<dfasize; i++)
        {
            if(input[i].currentstate==-1)
            finished=finished|(1<<i);
        }
        if(finished==((1<<dfasize)-1))
        break;
        for(int i=0; i<dfasize; i++)
        {
        if(checkstate(input[i]))
        matched[i]=index;
        }
        index++;
    }  
    int maxdfa=0;
    for(int i=0; i<dfasize; i++)
    {
        if(matched[i]>matched[maxdfa])
        maxdfa=i;
    }
    if(matched[maxdfa]==-2)
    cout<<"<"<<in.substr(startindex,index-startindex)<<",0>";
    else if(matched[maxdfa]==-1)
    cout<<"<,0>";
    else
    {
    cout<<"<"<<in.substr(startindex,matched[maxdfa]-startindex+1)<<","<<maxdfa+1<<">";
    index=matched[maxdfa]+1;
    }
    if(index!=size)
        return true;
    else
        return false;
}
int main()
{
    // string in="";
    // cout<<"Enter a string to check : ";
    // cin>> in;
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Unable to open the file.\n";
        return 0; 
    }
    string in;
    getline(inputFile,in);
    vector<DFA>input;
    // string s;
    // cout<<"Enter Regex Pattern :";
    // cin>>s;
    // while(s!="exit")
    // {
    // DFA d=regextoDFA(s);
    // print(&d);
    // input.push_back(d);
    // cout<<"Enter Regex Pattern :";
    // cin>>s;
    // }
    string s;
    while(getline(inputFile,s))
    {
        DFA d=regextoDFA(s);
        input.push_back(d);
    }
    inputFile.close();
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the file.\n";
        return 1;
    }
    streambuf* coutbuf = std::cout.rdbuf();
    cout.rdbuf(outputFile.rdbuf());
    int index=0;
    while(iteratetillmatch(index,in,input));
    cout.rdbuf(coutbuf);
    outputFile.close();
    return 0;
}  