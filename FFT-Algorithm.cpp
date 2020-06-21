// LANG : C++
// maker : Marc LeBlanc
// 2020.6.21

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std ;
const int MAX = 1e7 + 1 ; 
int M , N , limit = 1 ;

const double pai = acos( -1.0 ) ;
struct complex{
	double Real , Virtual_Part ;
	complex( double x = 0 , double y = 0 ){ Real = x , Virtual_Part = y ; }
}a[ MAX ] , b[ MAX ] ;

inline int read(){
	char c = getchar () ;
	int x = 0 ; 
	int f = 1 ;
	while( c < '0' || c > '9' ){
		if( c == '-' ){
			f = -1 ;
		}
		c = getchar () ;
	}
	while( c <= '9' && c >= '0' ){
		x = ( x << 3 ) + ( x << 1 ) + ( c - '0' ) ;
		c = getchar () ;
	}
	return f * x ;
}

complex operator + ( complex a , complex b ){ return complex ( a.Real + b.Real , a.Virtual_Part + b.Virtual_Part ) ; }
complex operator - ( complex a , complex b ){ return complex ( a.Real - b.Real , a.Virtual_Part - b.Virtual_Part ) ; } 
complex operator * ( complex a , complex b ){ return complex ( a.Real * b.Real - a.Virtual_Part * b.Virtual_Part , a.Real * b.Virtual_Part + a.Virtual_Part * b.Real ) ; }
int L , R[ MAX ] ;

inline void FFT_Algorithm( complex *s , int type ){
	for( register int i = 0 ; i < limit ; i ++ ){
		if( i < R[ i ] ){
			swap( s[ i ] , s[ R[ i ] ] ) ;
		}
	}
	for( register int middle = 1 ; middle < limit ; middle <<= 1 ){
		complex Plural( cos( pai / middle ) , type * sin( pai / middle ) ) ;
		for( register int r = middle << 1 , j = 0 ; j < limit ; j += r ){
			complex temple( 1 , 0 ) ;
			for( register int k = 0 ; k < middle ; k ++ , temple = temple * Plural ) {
				complex x = s[ j + k ] ;
				complex y = temple * s[ j + middle + k ] ;
				s[ j + k ] = x + y ;
				s[ j + middle + k ] = x - y ;
			}
		}
	}
}


int main(){
	N = read() , M = read() ;
	for( register int i = 0 ; i <= N ; i ++ ){
		a[ i ].Real = read() ;
	}
	
	for( register int i = 0 ; i <= M ; i ++ ){
		b[ i ].Real = read() ;
	}
	
	while( limit <= M + N ){ // 2 ;
		limit <<= 1 ;
		L ++ ;
	}
	for( register int i = 0 ; i < limit ; i ++ ){
		R[ i ] = ( R[ i >> 1 ] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	}
	FFT_Algorithm( a , 1 ) ; // FFT ;
	FFT_Algorithm( b , 1 ) ;

	for( register int i = 0 ; i <= limit ; i ++ ){
		a[ i ] = a[ i ] * b[ i ] ;
	}
	FFT_Algorithm( a , -1 ) ; // IFFT ;
	
	for( register int i = 0 ; i <= N + M ; i ++ ){
		printf( "%d " , ( int )( a[ i ].Real / limit + 0.5 ) ) ;
	}
	return 0 ;
}
