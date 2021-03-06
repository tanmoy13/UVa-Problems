#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
#define SIZE 51000


int parent[SIZE][17],depth[SIZE];
vector<int> out[SIZE],cost[SIZE];

int pcost[SIZE][17];

void dfs(int x,int p,int cc){

    //printf("saon %d %d %d\n",x,p,cc);

    parent[x][0] = p;
    //printf("shaon %d %d %d\n",x,p,parent[x][0]);

    depth[x]=depth[p]+1;
    pcost[x][0]=cc;



    for (int i=1;i<17;++i){
        parent[x][i]=parent[ parent[x][i-1] ][i-1];
        pcost[x][i]=max( pcost[x][i-1], pcost[ parent[x][i-1] ][i-1] );
    }


    for (int i=0;i<out[x].size();++i){
        int y=out[x][i];
        if ( y!= p ){
            //printf("going %d %d %d\n",x,y,cost[x][i]);
            dfs(y,x,cost[x][i]);
        }
    }
}

int modifiedlca(int x,int y){
    int ans=INT_MIN;
    if ( depth[x]>depth[y] ){
        swap(x,y);
    }
    for (int i=0;i<17;++i){
        if( ( ( depth[y]-depth[x] )>>i )&1){
            ans=max( ans, pcost[y][i] );
            y=parent[y][i];
        }
    }
    if ( x==y ){
        //printf("shaon %d %d\n",x,ans);
        return ans;
    }
    for(int i=16;i>=0;--i)
        if(parent[x][i]!=parent[y][i] ){
            ans=max( ans, pcost[x][i] );
            ans=max( ans, pcost[y][i] );

            x=parent[x][i];
            y=parent[y][i];

        }

    return max(ans,max( pcost[x][0],pcost[y][0]) );
}


struct lists {
    int start;
    int end;
    int distance;
} a [100000+ 10];

int pp [SIZE];
int component[SIZE];
int vertex;
int edges;

bool cmp (lists p, lists q)
{
    if ( p.distance < q.distance ) return true;
    return false;
}

int parentOf (int n)
{
    if ( n == pp [n] ) return n;
    return pp [n] = parentOf (pp [n]);
}
const int maxBufSize = 6000000;

struct Input
{
	int bufSize, bufEnd, bufPos;
	char buffer[maxBufSize];
	void grabBuffer() {
		bufSize = (maxBufSize); bufPos = 0;
		bufEnd = fread(buffer, sizeof (char), bufSize, stdin);
		buffer[bufEnd] = '\0';
	}
	bool bufEof() {return bufPos == bufEnd;}
	int getChar() {return buffer[bufPos++];}
	void skipWS() {
		while ((buffer[bufPos] == '\n' ||
			buffer[bufPos] == ' ' || buffer[bufPos] == '\t'))
			bufPos++;
	}
	int rInt() {
		int n = 0, x; skipWS();
		bool neg=false;
		if (  ( x = getChar() )=='-'  ){
            neg=true;
            x=getChar();
		}

		for (; x <= '9' && x >= '0'; x = getChar())
			n = (n << 3) + (n << 1) + (x - '0');
        if ( neg )return -n;
        else return n;
	}
	inline bool isWhiteSpace(char x) {
		return x == ' ' || x == '\n' || x == '\t';
	}
	char rChar() {skipWS(); return getChar();}
}input;

int main(){

    freopen("in.txt","r",stdin);
    input.grabBuffer();
    bool on=false;
    while( !input.bufEof() ){

        if (  on )printf("\n");
        on=true;

        vertex=input.rInt();
        edges=input.rInt();
        //printf("shaon\n");
        for (int i=0;i<edges;++i){
            a[i].start=input.rInt();
            a[i].end=input.rInt();
            a[i].distance=input.rInt();
            //printf("shaon2\n");
        }
        //printf("end\n");
        sort (a, a + edges , cmp);


        for (int i=0;i<=vertex;++i){
            out[i].clear();
            cost[i].clear();
        }

        for (int i=0;i<=vertex; ++i ){
            pp [i] = i;
            component[i]=1;
        }


        int selectedEdges = vertex - 1;
        for ( int i = 0; i < edges && selectedEdges; i++ ) {
            int p = parentOf (a [i].start);
            int q = parentOf (a [i].end);

            if ( p != q ) {
                if (component[p]>component[q])swap(p,q);

                component[q]+=component[p];
                pp [p] = q;
                selectedEdges--;

                out[ a [i].start ].push_back(  a [i].end );
                cost[ a[i].start ].push_back( a[i].distance );

                out[ a [i].end ].push_back(  a [i].start );
                cost[ a[i].end ].push_back( a[i].distance );
                //printf("edge %d %d\n",a [i].start,a [i].end);

            }
        }

        dfs(1,0,0);
        //printf("cost %d %d\n",parent[4][16],pcost[4][16]);
        int qq,u,v;
        qq=input.rInt();
        while(qq--){
            u=input.rInt();
            v=input.rInt();
            printf("%d\n",modifiedlca(u,v) );
        }

    }
    return 0;

}
