#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std ;
const int MAX = 5000010 ;
const double pai = acos( -1.0 ) ;

struct  complex{
	double Real_Part , Inmaginary_Part ;
	complex( double x = 0 , double y = 0 ) {
		Real_Part = x ;
		Inmaginary_Part = y ;
	}
}A[ MAX ] , B[ MAX ] ;

string s1 , s2 ;
int ans[ MAX ] , Rev[ MAX ] , L , limit = 1 ;
int N , headA , headB ;
complex operator + ( complex a , complex b ){
	return complex( a.Real_Part + b.Real_Part , a.Inmaginary_Part + b.Inmaginary_Part ) ;
}
complex operator - ( complex a , complex b ){
	return complex( a.Real_Part - b.Real_Part , a.Inmaginary_Part - b.Inmaginary_Part ) ;
	
}
complex operator * ( complex a , complex b ){
	return complex( a.Real_Part * b.Real_Part - a.Inmaginary_Part * b.Inmaginary_Part , a.Real_Part * b.Inmaginary_Part + a.Inmaginary_Part * b.Real_Part ) ;
	
}

inline int read() {
	int f = 1 , x = 0 ;
	char c = getchar () ;
	while( c < '0' || c > '9' ) {
		if( c == '-' ){
			f = -1 ;
		}
		c = getchar () ;
	}
	while( c >= '0' && c <= '9' ){
		x = ( x << 3 ) + ( x << 1 ) + ( c ^ 48 ) ;
		c = getchar() ;
	}
	return f * x ;
}

inline void FFT( complex *s , double type ){
	for( int i = 0 ; i < limit ; i ++ ){
		if( i < Rev[ i ] ){
			swap( s[ i ] , s[ Rev[ i ] ] ) ;
		}
	}
	for( int i = 1 ; i < limit ; i <<= 1 ){
		complex Plural( cos( pai / i ) , type * sin( pai / i ) ) ;
		for( int j = 0 ; j < limit ; j += ( i << 1 ) ) {
			complex temple( 1 , 0 ) ;
			for( int k = 0 ; k < i ; k ++ , temple = temple * Plural ){
				complex X = s[ k + j ] , Y = temple * s[ k + j + i ] ;
				s[ k + j ] = X + Y ;
				s[ k + j + i ] = X - Y ;
			}
		}
	}
}

int main(){
	//N = read() ;
	ios :: sync_with_stdio( 0 ) ;
	cin >> s1 ;
	cin >> s2 ;
 	int len_a = s1.size() - 1 , len_b = s2.size() - 1 ;
	for( int i = len_a ; i >= 0 ; i -- ){
		A[ headA ++ ].Real_Part = s1[ i ] - 48 ;
	}
	for( int i = len_b ; i >= 0 ; i -- ){
		B[ headB ++ ].Real_Part = s2[ i ] - 48 ;
	}
	limit = 1 , L = 0 ;
	while( limit <= len_a + len_b ){
		limit <<= 1 ;
		L ++ ;
	}
	for( int i = 0 ; i < limit ; i ++ ){
		Rev[ i ] = ( Rev[ i >> 1 ] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	}
	FFT( A , 1 ) ;
	FFT( B , 1 ) ;
	for( int i = 0 ; i <= limit ; i ++ ){
		A[ i ] = A[ i ] * B[ i ] ;
	}
	FFT( A , -1 ) ;
	/////////////////////chenge line : 1 ///////////////
	
	
	memset( ans , 0 , sizeof( ans ) ) ;
	for( int i = 0 ; i <= len_a + len_b + 1 ; i ++ ){
		ans[ i ] = ( int )( A[ i ].Real_Part / limit + 0.5 ) ;
		/*if( ans[ i ] >= 10 ){
			ans[ i + 1 ] += ans[ i ] / 10 ;
			ans[ i ] %= 10 ;
			//limit += ( i == limit ) ;
		}*/
	}
	for( int i = 0 ; i <= len_a + len_b ; i ++ ){
		ans[ i + 1 ] += ans[ i ] / 10 ;
		ans[ i ] %= 10 ;
	}
	/*while( !ans[ limit ] && limit >= 1 ){
		limit -- ;
	}*/
	
	//limit ++ ;
	limit = len_a + len_b + 1 ;
	while( ans[ limit ] ) {
		ans[ limit + 1 ] += ans[ limit ] / 10 ;
		ans[ limit ] %= 10 ;
		limit ++ ;
	}
	/*while( -- limit >= 0 ){
		printf( "%d" , ans[ limit ] ) ;
	}*/
	for( int i = limit - 1 ; i >= 0 ; i -- ){
		printf( "%d" , ans[ i ] ) ;
	}
	return 0 ;
}
