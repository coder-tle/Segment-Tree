#include<bits/stdc++.h>
using namespace std;
void update(int tree[],int lazy[] ,int low,int high ,int startR,int endR,int currPos)
{
    if(low>high)
        return;
    
    int total=high-low+1;
    if(lazy[currPos]!=0)
    {
        tree[currPos]=total-tree[currPos];
        
        if(low!=high)
        {
            lazy[2*currPos]^=1;
            lazy[2*currPos+1]^=1;
        }
        
        lazy[currPos]=0;
    }
    if(startR > high || endR < low)
        return;
    
    if(startR <=low && high<=endR)
    {
        tree[currPos]=total-tree[currPos];
        
        if(low!=high)
        {
            lazy[2*currPos]^=1;
            lazy[2*currPos+1]^=1;
        }
        
        return;
    }
    int mid=(low+high)/2;
    update(tree,lazy,low,mid,startR,endR,2*currPos);
    update(tree,lazy,mid+1,high,startR,endR,2*currPos+1);
    tree[currPos]=tree[2*currPos]+tree[2*currPos+1];
}
int query(int tree[],int lazy[],int st,int ed,int left,int right,int node)
{
    if(st > ed)
    {
        return 0;
    }
        
    if(st >right || ed < left)
    {
        return 0;
    }
    int total=ed-st+1;
    if(lazy[node]!=0)
    {
        tree[node]=total-tree[node];
        if(st!=ed)
        {
            lazy[2*node]^=lazy[node];
            lazy[2*node+1]^=lazy[node];
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

    int ans=(leftAns+rightAns);
    return ans;

}
int main()
{
    int n,q;
    cin>>n>>q;
    // tails= 0 , heads= 1

    int tree[4*n]={0},lazy[4*n]={0};
    while(q--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if(a==0)
        {
            update(tree,lazy,0,n-1,b,c,1);
        }
        else
        {
            cout<<query(tree,lazy,0,n-1,b,c,1)<<endl;
        }
        
    }

    return 0;
}