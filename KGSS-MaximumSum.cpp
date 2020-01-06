#include<bits/stdc++.h>
#define ll long long 
using namespace std;
struct Node
{
    int mx,smx;
};
void buildTree(int arr[],Node tree[],int node,int st,int ed)
{
    if(st==ed)
    {
        tree[node].mx=arr[st];
        tree[node].smx=INT_MIN;
        return;
    }
    int mid=(st+ed)/2;
    buildTree(arr,tree,2*node,st,mid);
    buildTree(arr,tree,2*node+1,mid+1,ed);

    Node le=tree[2*node];
    Node re=tree[2*node+1];

    tree[node].mx=max(le.mx,re.mx);
    tree[node].smx=min(max(le.mx,re.smx),max(re.mx,le.smx));
}
void update(int arr[],Node tree[],int st,int ed,int node,int idx,int value)
{
    if(st==ed)
    {
        arr[idx]=value;
        tree[node].mx=value;
        return ;
    }
    int mid=(st+ed)/2;
    if(idx>mid)
    {
        update(arr,tree,mid+1,ed,2*node+1,idx,value);
    }
    else
    {
        update(arr,tree,st,mid,2*node,idx,value);
    }
    Node le=tree[2*node];
    Node re=tree[2*node+1];
    tree[node].mx=max(le.mx,re.mx);
    tree[node].smx=min(max(le.mx,re.smx),max(re.mx,le.smx));
    
}
Node query(Node tree[],int st,int ed,int node,int left,int right)
{
    Node cur;
    cur.smx=cur.mx=INT_MIN;
    if(st>right || ed<left)
    {
        return cur;
    }
    if(st>=left && ed<=right)
    {
        return tree[node];
    }
    int mid=(st+ed)/2;
    Node le=query(tree,st,mid,2*node,left,right);
    Node re=query(tree,mid+1,ed,2*node+1,left,right);
    cur.mx=max(le.mx,re.mx);
    cur.smx=min(max(le.mx,re.smx),max(re.mx,le.smx));

    return cur;
}
int main()
{
    int n;
    cin>>n;

    int arr[n];
    for(int i=0;i<n;i++)
    cin>>arr[i];

    Node tree[3*n];
    buildTree(arr,tree,1,0,n-1);
    int q;
    cin>>q;
    char c;
    int left,right;
    while(q--)
    {
        cin>>c>>left>>right;
        if(c=='Q')
        {
            left--;
            right--;
            Node x=query(tree,0,n-1,1,left,right);
            cout<<x.mx+x.smx<<endl;
        }
        else
        {
            left--;
            update(arr,tree,0,n-1,1,left,right);
        }
        
    }

    return 0;
}