#include<bits/stdc++.h>
#define ll long long
using namespace std;
//Question- get minimum
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
void updateSegmentLazy(int tree[],int lazy[],int low,int high,int startR,int endR,int currPos,int inc)
{
    if(low > high)
    {
        return;
    }

    //check if pending updates of current node
    if(lazy[currPos]!=0)
    {
        tree[currPos]+=lazy[currPos];

        // tell child nodes
        if(low!=high)
        {
            lazy[2*currPos]+=lazy[currPos];
            lazy[2*currPos+1]+=lazy[currPos];
        }
        lazy[currPos]=0;
    }

    // NO overlap
    if(startR>high || endR < low)
    {
        return ;
    }

    // complete overlap
    if(startR <=low && high <=endR)
    {
        tree[currPos]+=inc;
        if(low!=high)
        {
            lazy[2*currPos]+=inc;
            lazy[2*currPos+1]+=inc;
        }
        return ;
    }
     // partial overlap
    int mid=(low+high)/2;
    updateSegmentLazy(tree,lazy,low,mid,startR,endR,2*currPos,inc);
    updateSegmentLazy(tree,lazy,mid+1,high,startR,endR,2*currPos+1,inc);
    
    tree[currPos]=min(tree[2*currPos],tree[2*currPos+1]);
}   
int query(int tree[],int lazy[],int st,int ed,int left,int right,int node)
{
    if(st > ed)
    {
        return INT_MAX;
    }
        
    if(st >right || ed < left)
    {
        return INT_MAX;
    }

    if(lazy[node]!=0)
    {
        tree[node]+=lazy[node];
        if(st!=ed)
        {
            lazy[2*node]+=lazy[node];
            lazy[2*node+1]+=lazy[node];
        }
        lazy[node]=0;
    }

    //completely inside
    if(st>=left && ed<=right)
    {
        return tree[node];
    }

    // partial overlap
    int mid=(st+ed)/2;
    int leftAns=query(tree,lazy,st,mid,left,right,2*node);
    int rightAns=query(tree,lazy,mid+1,ed,left,right,2*node+1);

    int ans=min(leftAns,rightAns);
    return ans;

}
int main()
{
    int n=4;
    int arr[5]={1,3,-2,4};
    int tree[20]={0},lazy[20]={0};

    buildTree(arr,tree,0,3,1);

    updateSegmentLazy(tree,lazy,0,3,0,3,1,3);
    updateSegmentLazy(tree,lazy,0,3,0,1,1,2);
  
    for(int i=1;i<15;i++)
    cout<<tree[i]<<" ";
    cout<<endl;
    for(int i=1;i<15;i++)
    cout<<lazy[i]<<" ";
    cout<<endl;

    cout<<query(tree,lazy,0,3,3,3,1)<<endl;
    return 0;
}