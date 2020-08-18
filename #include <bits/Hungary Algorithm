#include <bits/stdc++.h>
using namespace std ;
const int MAX = 1e3 ;

int a[ MAX ] , M , N , K , ans , used[ MAX ] , line[ MAX ][ MAX ] ;

inline int read(){
	int x = 0 , f = 1  ;
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

inline bool Hungary( int x ){
	for( int i = 1 ; i <= M ; i ++ ){
		if( used[ i ] == false && line[ x ][ i ] == true ){
			used[ i ] = true ;
			if( a[ i ] == false || Hungary( a[ i ] ) == true ){
				a[ i ] = x ;
				return true ; 
			}
		}
	}
	return false ;
}

inline void scan(){
	N = read() , M = read() , K = read() ;
	for( int i = 1 ; i <= K ; i ++ ){
		int x , y ;
		x = read() , y = read() ;
		line[ x ][ y ] = true ;
	}
}

int main(){
	scan() ;
	for( int i = 1 ; i <= N ; i ++ ){
		memset( a , 0 , sizeof( a ) ) ;
		if( Hungary( i ) == true ){
			ans ++ ;
		}
	}
	printf( "%d\n" , ans ) ;
	return 0 ;
} 
