/* 
 * Use Trie(prefix tree) to store strings.
 * Supports addition and deletion.
 */
#include <iostream>
#include <cstring>

using namespace std;

struct node            // Contents of every node in the tree
{
    node* child[26];
    bool isleaf;
};

node* make_new_node()   // For initialsing a node with default values
{                       // Similar to a constructor in a class
    node* temp=new node();
    temp->isleaf=false;
    
    for(int i=0;i<26;i++)
        temp->child[i]=NULL;
    return temp;
}

void insert(node* head,string s)        // Insert a string in a trie
{
    node *cur=head;
    for(int i=0;i<s.length();i++)
    {
        if(cur->child[s[i]-'a']==NULL)
            cur->child[s[i]-'a']=make_new_node();
        cur=cur->child[s[i]-'a'];
    }
    cur->isleaf=true;                   // Mark newly inserted string as leaf
}

bool ispresent(node* head,string s)     // Returns true if "s" is present in trie else returns false
{   
    if(head==NULL)
        return false;
    node *cur=head;
    for(int i=0;i<s.length();i++)
    {
        cur=cur->child[s[i]-'a'];
        if(cur==NULL)
            return false;
    }
    return cur->isleaf;
}

bool has_no_child(node *cur)           // Returns true if a node has no child
{                                      // else returns false
    for(int i=0;i<26;i++)
        if(cur->child[i])
            return false;
    return true;
}

node* delete_node(node*cur,string s,int level)  // Delete a node from a trie
{
    if(!cur)
        return NULL;
    if(level==s.length())               // Base case
    {
        if(cur->isleaf)
            cur->isleaf=false;
        if(has_no_child(cur))
        {
            free(cur);
            cur=NULL;
        }
        return cur;
    }
    cur->child[s[level]-'a']=delete_node(cur->child[s[level]-'a'],s,level+1);
    if(has_no_child(cur) && !cur->isleaf)   // If node has no child after deleting rest of the part 
    {
        free(cur);
        cur=NULL;
    }
    return cur;
}
/*
 * Another code to delete a string 
 */ 
//bool delete_node(node *cur,string s,int level)
//{
//    if(cur)
//    {
//        if(level==s.length())
//        {
//            if(cur->isleaf)
//            {
//                cur->isleaf=false;
//                if(has_no_child(cur))
//                    return true;
//                return false;
//            }
//        }
//        else
//        {
//            if(delete_node(cur->child[s[level]-'a'],s,level+1))
//            {
//                free(cur->child[s[level]-'a']);
//                cur->child[s[level]-'a']=NULL;
//                return (!cur->isleaf && has_no_child(cur));
//            }
//        }
//    }
//    return false;
//}

int main()
{
    node *head=make_new_node();
    insert(head,"hello");
    insert(head,"hell");
    insert(head,"human");
    insert(head,"humans");
    insert(head,"hoomans");
    cout<<ispresent(head,"hello")+ispresent(head,"hoomans");
    cout<<endl;
    cout<<ispresent(head,"humans");
    delete_node(head,"humans",0);
    cout<<endl<<ispresent(head,"human")<<endl;
    return 0;
}
