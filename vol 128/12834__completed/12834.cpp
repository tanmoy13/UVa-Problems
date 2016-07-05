#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

typedef long long LL;

#define PB push_back
#define FRO freopen("in.txt","r",stdin);

#define CLR(arr) memset( (arr),0,sizeof(arr) );
#define NEG(arr) memset( (arr),-1,sizeof(arr) );

#define X first
#define Y second

#define MP make_pair

#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)


typedef pair<int,int> pint;
typedef map<int,int> mint;

#define SIZE 1000010

int A[SIZE],B[SIZE],C[SIZE];

int main(){

    int kase;
    scanf("%d",&kase);

    for (int kk=1;kase--;++kk){
        int n,k;
        scanf("%d %d",&n,&k);
        for (int i=0;i<n;++i){
            scanf("%d",&A[i]);
        }
        for (int i=0;i<n;++i){
            scanf("%d",&B[i]);
        }
        for (int i=0;i<n;++i){
            C[i] = B[i]-A[i];
        }
        sort( C,C+n );
        LL ans = 0;
        for (int i=0;i<n;++i){
            if ( C[i] >0 ){
                ans += C[i];
            }else if( i>=k ){
                ans += C[i];
            }
        }
        if ( ans <= 0 ){
            printf("Case %d: No Profit\n",kk);
        }else{
            printf("Case %d: %lld\n",kk,ans);
        }
    }


    return 0;
}
