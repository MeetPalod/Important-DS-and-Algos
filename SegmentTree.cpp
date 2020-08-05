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
