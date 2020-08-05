// FOR SUM QUERY
#include <bits/stdc++.h> 
using namespace std; 

const int N = 100000; 
int n; // array size 
int tree[2 * N]; 

void build( int arr[]) 
{ 
	for (int i=0; i<n; i++)	 
		tree[n+i] = arr[i]; 	
	for (int i = n - 1; i > 0; --i)	 
		tree[i] = tree[i<<1] + tree[i<<1 | 1];	 
} 

void updateTreeNode(int p, int value) 
{ 
	tree[p+n] = value; 
	p = p+n; 
	for (int i=p; i > 1; i >>= 1) 
		tree[i>>1] = tree[i] + tree[i^1]; 
} 

int query(int l, int r) 
{ 
	int res = 0; 
	
	// loop to find the sum in the range 
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
	{ 
		if (l&1) 
			res += tree[l++]; 
	
		if (r&1) 
			res += tree[--r]; 
	} 
	
	return res; 
} 

int main() 
{ 
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; 
	n = sizeof(a)/sizeof(a[0]); 
	build(a); 
	cout << query(1, 3)<<endl; 
	updateTreeNode(2, 1); 
	cout << query(1, 3)<<endl; 

	return 0; 
} 

////////////////////////////////////////////////////////////////////
// FOR MIN RANGE QUERY

#include "bits/stdc++.h"
#define MODULO 1000000007
#define endl '\n'
#define m(a) ((a)%MODULO)
#define s(a) scanf("%d", &a)
#define sl(a) scanf("%lld", &a)
#define p(a) printf("%d\n", a)
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

class SegmentTree {
	private:
		int tree[4 * 100000];
		int * arr;

	public:
		SegmentTree(int * array);
		void build(int l, int r, int p);
		int rmq(int l, int r, int x, int y, int p);
};

SegmentTree::SegmentTree(int * array){
	arr = array;
}

void SegmentTree::build(int l, int r, int p){
	if (l == r){
		tree[p] = arr[l];
	} else {
		int mid = (l+r)/2;
		build(l, mid, 2*p);
		build(mid+1, r, 2*p+1);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
}

int SegmentTree::rmq(int l, int r, int x, int y, int p){
	int mid;
	if (l > y || r < x){ // out of boundary
		return MODULO;
	} else if (l <= x && r >= y){ // l..r oversizes the boundary
		return tree[p];
	} else {
		mid = (x+y)/2;
		return min(rmq(l, r, x, mid, p*2), rmq(l, r, mid+1, y, p*2+1));
	}
}


int main(){
	int t, i, n, q, l, r;
	s(n);
	int arr[n];

	for (i=0; i<n; i++) 
		s(arr[i]);

	SegmentTree myt(arr);
	myt.build(0, n-1, 1);

	s(q);

	for (i=0; i<q; i++){
		scanf("%d %d", &l, &r);
		p(myt.rmq(l, r, 0, n-1, 1));
	}

	return 0;
}





/////////////////////////////////////////////////////
//LAZY PROPOGATION
lementation:
// C++ program to showLazy propagation in Segment Tree - Sum of range
#include<bits/stdc++.h>
using namespace std;
#define MAX 100010
int tree[MAX], lazy[MAX];
vector<int> ar;
/* Function to display elements of the Segment Tree and
   the Lazy tree level by level. */
void showSegTree(int n)
{
  int i, j, h = ceil(log2(n));
  cout<<"Segment Tree:"<<endl;
  for(i=0 ; i<=h ; ++i)
  {
    for(j=0 ; j<pow(2, i) ; ++j)
      cout<<tree[int(pow(2, i)-1 + j)]<<' ';
    cout<<endl;
  }
  cout<<"Lazy Tree:"<<endl;
  for(i=0 ; i<=h ; ++i)
  {
    for(j=0 ; j<pow(2, i) ; ++j)
      cout<<lazy[int(pow(2, i)-1 + j)]<<' ';
    cout<<endl;
  }
}
/* Function to construct the Segment Tree recursively.
   At each node, if it is not the leaf, two children are
   processed further. Otherwise, the leaf is assigned an
   array alement. strt and end are range in the array,
   idx is the index used in the segment tree */
int constSegTree(int strt, int end, int idx)
{
  // Initialize all lazy tree nodes with 0
  lazy[idx] = 0;
  // Saves tree[idx] = ar[strt] and then returns tree[idx]
  if(strt == end)
    return tree[idx] = ar[strt];
  int mid = (strt + end) / 2;
  return tree[idx] = constSegTree(strt, mid, 2*idx+1) +
            constSegTree(mid+1, end, 2*idx+2);
}
void constSegTree(int n)
{
  constSegTree(0, n-1, 0);
}
/* Function to get the sum of elements of array in the
   range [strt..end]. l & r are the range of current node.
   indx is the index of node in segment tree */
int getSum(int strt, int end, int l, int r, int idx)
{
  // If there's pending update, update the node first
  if(lazy[idx] != 0)
  {
    // Add the pending update to the current node
    // [l..r] contains l-r+1 nodes
    tree[idx] += (r-l+1)*lazy[idx];
    // If the node has children, postpone the updates
    // to the children by adding to the their lazy nodes
    if(l != r)
    {
      lazy[2*idx+1] += lazy[idx];
      lazy[2*idx+2] += lazy[idx];
    }
    // Reset the lazy node of current node
    lazy[idx] = 0;
  }
  // If completly outside the range, don't care
  if(end < l || r < strt || l > r)
    return 0;
  
  // If node is entirely within the range, return the node value
  if(strt <= l && r <= end)
    return tree[idx];
  
  // Enter its children and process further
  int mid = (l + r) / 2;
  return getSum(strt, end, l, mid, 2*idx+1) +
      getSum(strt, end, mid+1, r, 2*idx+2);
}
int getSum(int n, int strt, int end)
{
  return getSum(strt, end, 0, n-1, 0);
}
/* Function to update a particular node of the array in
   Segment Tree. pos is the desired index in the array.
   val is the value to be added */
void updtSegTree(int strt, int end, int val, int l, int r, int idx)
{
  // If there's pending update, update the node first
  if(lazy[idx] != 0)
  {
    // Add the pending update to the current node
    // [l..r] contains l-r+1 nodes
    tree[idx] += (r-l+1)*lazy[idx];
    // If the node has children, postpone the updates
    // to the children by adding to the their lazy nodes
    if(l != r)
    {
      lazy[2*idx+1] += lazy[idx];
      lazy[2*idx+2] += lazy[idx];
    }
    // Reset the lazy node of current node
    lazy[idx] = 0;
  }
  // If completly outside the range, don't care
  if(end < l || r < strt || l > r)
    return;
  // If node is entirely within the range
  if(strt <= l && r <= end)
  {
    // Update the current node in Segment tree
    tree[idx] += (r-l+1)*val;
    // If the node has children, postpone the updates
    // of the children by adding to the their lazy nodes
    if(l != r)
    {
      lazy[2*idx+1] += val;
      lazy[2*idx+2] += val;
    }
  }
  else
  {
    // Enter its children and process further
    int mid = (l + r) / 2;
    updtSegTree(strt, end, val, l, mid, 2*idx+1);
    updtSegTree(strt, end, val, mid+1, r, 2*idx+2);
    // Recalculate the itermediate nodes after updation
    tree[idx] = tree[2*idx+1] + tree[2*idx+2];  
  }
}
void updtSegTree(int n, int strt, int end, int val)
{
  updtSegTree(strt, end, val, 0, n-1, 0);
}
int main()
{
  int n = 7;
  ar = {18, 17, 1, 19, 15, 11, 20};
  constSegTree(n);
  cout<<"n = 7, ar = {18, 17, 1, 19, 15, 11, 20}"<<endl;
  showSegTree(n);
  
  updtSegTree(n, 0, 4, 2);
  
  cout<<"\nupdtSegTree(n, 0, 4, 2):"<<endl;
  showSegTree(n);
  cout<<"\nSum of ar[1..4] = "<<getSum(n, 1, 4)<<endl;
  showSegTree(n);
    return 0;
}
