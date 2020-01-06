#include<bits/stdc++.h>
#define ll long long 
using namespace std;
struct Node{
ll mxSum,sum,preffixSum,suffixSum;
};
void buildTree(ll arr[],Node tree[],int st,int ed,int node)
{
    if(st==ed)
    {
        tree[node].mxSum=arr[st];
        tree[node].sum=arr[st];
        tree[node].preffixSum=arr[st];
        tree[node].suffixSum=arr[st];
        return;
    }

    int mid=(st+ed)/2;

    buildTree(arr,tree,st,mid,2*node);
    buildTree(arr,tree,mid+1,ed,2*node+1);

    tree[node].sum=tree[2*node].sum+tree[2*node+1].sum;
    tree[node].preffixSum=max(tree[2*node].preffixSum,tree[2*node].sum+tree[2*node+1].preffixSum);
    tree[node].suffixSum=max(tree[2*node+1].suffixSum,tree[2*node+1].sum+tree[2*node].suffixSum);
    
    ll mx=max(tree[2*node].mxSum,tree[2*node+1].mxSum);
    mx=max(mx,tree[2*node].sum+tree[2*node+1].preffixSum);
    mx=max(mx,tree[2*node+1].sum+tree[2*node].suffixSum);
    mx=max(mx,tree[2*node].suffixSum+tree[2*node+1].preffixSum);
    mx=max(mx,tree[2*node].sum+tree[2*node+1].sum);
    tree[node].mxSum=mx;
}

Node query(Node tree[],int st,int ed,int node,int left,int right)
{
    Node cur;
    cur.mxSum=- 1e14;
    cur.preffixSum= - 1e14;
    cur.sum= -1e14;
    cur.suffixSum=-1e14;

    //completely outside
    if(st>right || ed<left)
    {
        return cur;
    }

    //completely inside
    if(st>=left && ed<=right)
    {
        return tree[node];
    }

    //partially inside and partially outside
    int mid=(st+ed)/2;

    Node leftNode=query(tree,st,mid,2*node,left,right);
    Node rightNode=query(tree,mid+1,ed,2*node+1,left,right);

    cur.sum=leftNode.sum+rightNode.sum;
    cur.preffixSum=max(leftNode.preffixSum , leftNode.sum+rightNode.preffixSum);
    cur.suffixSum=max(rightNode.suffixSum , rightNode.sum + leftNode.suffixSum );

    ll mx=max(leftNode.mxSum,rightNode.mxSum);
    mx=max(mx,leftNode.sum+rightNode.preffixSum);
    mx=max(mx,rightNode.sum+leftNode.suffixSum);
    mx=max(mx,leftNode.suffixSum+rightNode.preffixSum);
    mx=max(mx,leftNode.sum+rightNode.sum);
    cur.mxSum=mx;
    return cur;
}
int main()
{
    int n;
    cin>>n;

    ll arr[n];
    Node tree[4*n],res;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    buildTree(arr,tree,0,n-1,1);
    int q;
    cin>>q;
    int l,r;
    while(q--)
    {
        cin>>l>>r;
        l--;r--;
        res=query(tree,0,n-1,1,l,r);
        cout<<res.mxSum<<endl;
    }
    return 0;
}