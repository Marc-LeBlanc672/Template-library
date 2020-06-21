// LANG : C++ 
// maker : Marc LeBlanc
// 2020.6.21

#include <bits/stdc++.h>
#define int unsigned long long 

using namespace std ;

const int MaxM = 5e6 + 1 ;
const int MaxN = 1e5 + 1 ;
const int INF = 1e99 ;
int N , M , S , cnt ;
int vis[ MaxN ] , dis[ MaxN ] , head[ MaxM ] ;
struct Edge{
	int u , v , dis ;
}edge[ MaxM ] ;

inline int read(){
	int f = 1 , x = 0 ;
	char c = getchar() ;
	while( c < '0' || c > '9' ){
		if( c == '-' ){
			f = -1 ;
		}
		c = getchar() ;
	}
	while( c <= '9' && c >= '0' ){
		x = ( x << 1 ) + ( x << 3 ) + ( c ^ 48 ) ;
		c = getchar() ;
	}
	return f * x ;
}

inline void add_edge( int u , int v , int dis ){
    edge[ ++ cnt ].dis = dis ;
    edge[ cnt ].u = v ;
    edge[ cnt ].v = head[ u ] ;
    head[ u ] = cnt ;
}

inline void Build(){
	N = read() , M = read() , S = read() ;
	for( int i = 1 ; i <= M ; i ++ ){
		int u , v , dis ;
		u = read() , v = read() , dis = read() ;
		add_edge( u , v , dis ) ;
	}
}


inline void Initialization(){
    for( int i = 1 ; i <= N ; i ++ ){
    	dis[ i ] = INF ;
    	vis[ i ] = 0 ;
	}
	dis[ S ] = 0 ;
	 
}

inline void Spfa(){
	queue< int > Q ;
	Initialization() ;
	Q.push( S ) , vis[ S ] = 1 ;
	
	while( ! Q.empty() ){
		int u = Q.front() ;
		Q.pop() ;
		vis[ u ] = 0 ;
		for( int i = head[ u ] ; i ; i = edge[ i ].v ) {
			int v = edge[ i ].u ;
			if( dis[ v ] > dis[ u ] + edge[ i ].dis ) {
				dis[ v ] = dis[ u ] + edge[ i ].dis ;
				if( vis[ v ] == 0 ){
					vis[ v ] = 1 ;
					Q.push( v ) ;
				}
			}
		}
	}
}

signed main(){
	Build() ;
	Spfa() ;
	for( int i = 1 ; i <= N ; i ++ ){
		printf( "%lld " , dis[ i ] ) ;
	}
	return 0 ;
}

