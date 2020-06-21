// LANG : C++ 
// maker : Marc LeBlanc
// 2020.6.21

#include <bits/stdc++.h>
#define int long long 
using namespace std ;
const int MAX = 1e6 + 1 ;
int a[ MAX ] , N , M ;
int st[ MAX ][ 21 ] ;

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

inline int Query( int l , int r ){
    int k = log2( r - l + 1 ) ;
    return max( st[ l ][ k ] , st[ r - ( 1 << k ) + 1 ][ k ] ) ;
}

signed main(){
    N = read() , M = read() ;
    for( int i = 1 ; i <= N ; i ++ ){
        a[ i ] = read() ;
        st[ i ][ 0 ] = a[ i ] ;
    }
    for( int j = 1 ; j <= 21 ; j ++ ){
        for( int i = 1 ; i + ( 1 << j ) - 1 <= N ; i ++ ){
            st[ i ][ j ] = max( st[ i ][ j - 1 ] , st[ i + ( 1 << ( j - 1 ) ) ][ j - 1 ] ) ;
        }
    }
    while( M -- ){
        int l , r ;
        l = read() , r = read() ; 
        printf( "%d\n" , Query( l , r ) ) ;
    }
    return 0 ;
}
