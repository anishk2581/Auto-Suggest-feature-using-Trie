#include <bits/stdc++.h>
using namespace std;
struct Trienode
{
    Trienode *child[26];
    bool isend;
    Trienode()  //constructor
    {
        isend=false;
        for(int i=0;i<26;i++)
        child[i]=NULL;
    }
};
bool isempty(Trienode *root);
bool search(const string key,Trienode *root)
{
    Trienode *curr=root;
    for(int i=0;i<key.length();i++)
    {
        int index=key[i]-'a';
        if(curr->child[index]==NULL)
        return false;
        curr=curr->child[index];
    }
    return curr->isend;
}
void insert(const string key,Trienode *root)
{
    Trienode *curr=root;
    for(int i=0;i<key.length();i++)
    {
        int index=key[i]-'a';
        if(curr->child[index]==NULL)
        curr->child[index]=new Trienode();
        curr=curr->child[index];
    }
    curr->isend=true;
}
Trienode *delkey(Trienode *root,string key,int i)//i=0 initially
{
    if(root==NULL)
    return NULL;
    if(i==key.length())
    {
        root->isend=false;
        if(isempty(root)==true)
        {
            delete root;
            root=NULL;
        }
        return root;
    }
    int index=key[i]-'a';
    root->child[index]=delkey(root->child[index],key,i+1);
    if(isempty(root)&&root->isend==false)
    {
        delete root;
        root=NULL;
    }
    return root;
}
bool isempty(Trienode *root)
{
    for(int i=0;i<26;i++)
    if(root->child[i]!=NULL)
    return false;
    return true;
}
void suggestionrec(Trienode *root,string prefix)
{
    if(root->isend)
    cout<<prefix<<endl;
    if(isempty(root))
    return;
    for(int i=0;i<26;i++)
    {
        if(root->child[i])
        {
            prefix.push_back(97+i);
            suggestionrec(root->child[i],prefix);
            prefix.pop_back();
        }
    }
}
int autosuggest(Trienode *root,const string s)
{
    Trienode *curr=root;
    for(int i=0;i<s.length();i++)
    {
        int index=s[i]-'a';
        if(!curr->child[index])
        return 0;
        curr=curr->child[index];
    }
    bool isword=(curr->isend==true);
    bool islast=isempty(curr);
    if(isword&&islast)
    {
        cout<<s<<endl;
        return 1;
    }
    if(!islast)
    {
    string prefix=s;
    suggestionrec(curr,prefix);
    return 1;
    }
}
int main()
{
   Trienode *root=new Trienode();
    insert("he",root);
    insert("hel",root); 
    insert("hell",root); 
    insert("hello",root); 
    insert("helloworld",root);
    insert("h",root); 
    insert("helps",root); 
    insert("helping",root); 
    int res=autosuggest(root, "hell");
    if(res==0)
    cout<<"No string found with this prefix"<<endl;
}

