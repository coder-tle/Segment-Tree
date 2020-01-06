#include<bits/stdc++.h>
#define ll long long
using namespace std;
void buildTree(int arr[],int tree[],int st,int ed,int node)
{
    if(st==ed)
    {
        tree[node]=arr[st];
        return;
    }
    int mid=(st+ed)/2;

    buildTree(arr,tree,st,mid,2*node);
    buildTree(arr,tree,mid+1,ed,2*node+1);

    tree[node]=tree[2*node]+tree[2*node+1];

}
void updateTree(int arr[],int tree[],int st,int ed,int node,int idx,int value)
{
    if(st==ed)
    {
        arr[idx]=value;
        tree[node]=value;
        return;
    }

    int mid=(st+ed)/2;
    if(idx>mid)
    {
        updateTree(arr,tree,mid+1,ed,2*node+1,idx,value);
    }
    else
    {
        updateTree(arr,tree,st,mid,2*node,idx,value);
    }
    tree[node]=tree[2*node]+tree[2*node+1];
    
}
int query(int tree[],int st,int ed,int node,int left,int right)
{
    //completely outside
    if(st>right || ed<left)
    {
        return 0;
    }
   
    //completely inside
    if(st>=left && ed<=right)
    {
        return tree[node];
    }

    //partially inside and partially outside

    int mid=(st+ed)/2;
    int ans1=query(tree,st,mid,2*node,left,right);
    int ans2=query(tree,mid+1,ed,2*node+1,left,right);

    return ans1+ans2;
      
}
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    
    int tree[2*n];
    buildTree(arr,tree,0,n-1,1);

    return 0;
}