/*
 * Segment tree to find max element in a given range in O(log(n))
*/ 
#include <iostream>
#include <time.h>

using namespace std;
int n=9;

/*
 * Build the "Segment Tree" recursively .
 * "low" and "high" are indices of the given array.
 */ 
void build(int arr[],int tree[],int node,int low,int high)
{
    if(low>high)    // Out of Range 
        return ;
        
    if(low==high)   // Only one element(leaf)
    {
        tree[node]=arr[low];
        return;
    }
    
    build(arr,tree,2*node+1,low,(low+high)/2); // Build left tree recursively
    build(arr,tree,2*node+2,(low+high)/2+1,high); // Build right tree recursively
    
    tree[node]=max(tree[2*node+1],tree[2*node+2]);  //Selects maximum of left and right subtree
}

/*
 * Updates the tree by adding value of "value" to each element in the range a...b
 * "low" and "high" are indices of current range of segment tree. 
 */
void update_range(int tree[],int node,int a,int b,int low,int high,int value)
{
    if(low>high|| b<low || a>high) //Out of Bounds
        return;
    if(low==high)  // Only one element
    {
        tree[node]+=value;
        return;
    }
    update_range(tree,2*node+1,a,b,low,(high+low)/2,value);
    update_range(tree,2*node+2,a,b,(high+low)/2+1,high,value);
    
    tree[node]=max(tree[2*node+1],tree[2*node+2]); //Selects Max of left and right subtree.
}

/*
 * Return max. element of a given range(a...b)
 */
int query(int tree[],int node,int a,int b,int low,int high)
{
    if(low>high||low>b||high<a)
        return -1<<31;
    if(low>=a && high<=b)
        return tree[node];
    return max(query(tree,2*node+1,a,b,low,(low+high)/2),query(tree,2*node+2,a,b,(high+low)/2+1,high));
}

void display(int arr[],int len)
{
    //int len=sizeof(arr)/sizeof(arr[0]);//this does not work as arr is converted to a pointer
    for(int i=0;i<len;i++)               //when passed as a parameter to the function.
        cout<<arr[i]<<" ";
    cout<<endl;
}

int main()
{
    int arr[n];
    int tree[3*n];
    srand(time(NULL));
    for(int i=0;i<n;i++)
    arr[i]=rand()%16;
    build(arr,tree,0,0,n-1);
    cout<<query(tree,0,0,n-1,0,n-1);
    cout<<endl;
    display(arr,n);
    update_range(tree,0,2,5,0,n-1,5);
    display(tree,2*n+2);
    cout<<query(tree,0,0,n-1,0,n-1);
    cout<<endl;
    return 0;
}
