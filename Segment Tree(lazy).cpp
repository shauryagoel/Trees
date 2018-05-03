/*
 * Segement tree with lazy propogation to find max element in a given range in O(log(n))
 * It is used when number of updates are very large
 */ 
#include <iostream>
#include <cstring>

using namespace std;
#define mid(a,b) (a+b)/2      
int n=9;

/*
 * Building the segment tree recursively
 */ 
void build(int arr[],int tree[],int node,int low,int high)
{
    if(low>high)
        return;
    if(low==high)
    {
        tree[node]=arr[low];
        return;
    }
    
    build(arr,tree,2*node+1,low,mid(low,high));
    build(arr,tree,2*node+2,mid(low,high)+1,high);
    
    tree[node]=max(tree[2*node+1],tree[2*node+2]);
}

/*
 * Updates segement tree by adding "value" to each node in range i...j
 * Also updates the lazy tree simultaneously
 */ 
void update(int tree[],int node,int lazy[],int low,int high,int i,int j,int value)
{
    /*
     * (It is checked before because it is possible that its(node) parent need
     * its update value(as in the last line of this function))
     */
    if(lazy[node]!=0)                 // If pending updates remaining first update them
    {                                 
        tree[node]+=lazy[node];       // Update the segment tree
        if(low!=high)                 // If this node has two children pass this update to them
        {
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
        }
        lazy[node]=0;                 // Therefore no update remaining in current node
    }
   
    if(low>high || low>j || high<i)    // Out of Bounds
        return;
        
    if(low>=i && high<=j)             // If given range lies completely within bounds
    {
        tree[node]+=value;            // Update the tree by adding "value"
        if(low!=high)                 // If this node has two children pass "value" 
        {                             // to its children in the lazy tree for future updates
            lazy[2*node+1]+=value;
            lazy[2*node+2]+=value;
        }
        return;                       // Dont go any further down the tree 
    }
    update(tree,2*node+1,lazy,low,mid(low,high),i,j,value); // Recursively do this for left subarray and right subarray
    update(tree,2*node+2,lazy,mid(low,high)+1,high,i,j,value);
    
    tree[node]=max(tree[2*node+1],tree[2*node+2]); 
}

/*
 * Finds max element in a given range i..j
 */ 
int query(int tree[],int node,int lazy[],int low,int high,int i,int j)
{
    if(lazy[node]!=0)                 // Same as above 
    {
        tree[node]+=lazy[node];
        if(low!=high)
        {
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
        }
        lazy[node]=0;
    }
    if(low>high || low>j || high<i)   // Out of bounds 
        return -1<<31;
    if(low>=i && high<=j)           // If given range lies completely within bounds Return the current node
        return tree[node];
    
    return max(query(tree,2*node+1,lazy,low,mid(low,high),i,j),query(tree,2*node+2,lazy,mid(low,high)+1,high,i,j));
}

int main()
{
	int arr[n];
    int tree[3*n];
    int lazy[3*n];
    memset(lazy, 0, sizeof lazy);
    srand(time(NULL));
    for(int i=0;i<n;i++)
        arr[i]=rand()%16;
    build(arr,tree,0,0,n-1);
    cout<<query(tree,0,lazy,0,n-1,0,n-1);
    cout<<endl;
    update(tree,0,lazy,2,5,0,n-1,5);
    cout<<query(tree,0,lazy,0,n-1,0,n-1);
    cout<<endl;
	return 0;
}
