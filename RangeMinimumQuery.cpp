#include<bits/stdc++.h>
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
    
    tree[node]=min(tree[2*node],tree[2*node+1]);
    
}
void update(int arr[],int tree[],int st,int ed,int node,int idx,int value)
{
    if(st==ed)
    {
        arr[idx]=value;
        tree[node]=value;
        return;
    }
    int mid=(st+ed)/2;
    if(idx > mid)
    {
        update(arr,tree,mid+1,ed,2*node+1,idx,value);
    }
    else
    {
        update(arr,tree,st,mid,2*node,idx,value);
    }
    tree[node]=min(tree[2*node],tree[2*node+1]);
}
int query(int arr[],int tree[],int st,int ed,int node,int left,int right)
{
    if(st>right||ed<left)
    {
        return INT_MAX;
    }
    
    if(st>=left && ed<=right)
    {
        return tree[node];
    }
    
    int mid=(st+ed)/2;
    int ans1=query(arr,tree,st,mid,2*node,left,right);
    int ans2=query(arr,tree,mid+1,ed,2*node+1,left,right);
    
    return min(ans1,ans2);
}
int main() {

	// Write your code here
    int n,q;
    cin>>n>>q;
    
    int arr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    
    int tree[4*n];
    
    buildTree(arr,tree,0,n-1,1);
    char c;
    int left,right;
    while(q--)
    {
        cin>>c>>left>>right;
        if(c=='q')
        {
            left--;right--;
            cout<<query(arr,tree,0,n-1,1,left,right)<<endl;
        }
        else
        {
            left--;
            update(arr,tree,0,n-1,1,left,right);
        }
    }
}