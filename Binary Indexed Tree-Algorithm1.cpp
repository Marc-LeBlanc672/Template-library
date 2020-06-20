#include <bits/stdc++.h>
#define int unsigned long long 
using namespace std ;
const int MAX = 5e5 + 1 ;
int a[ MAX ] , Tree[ MAX ] ;
int N , M ;

inline int read(){
    int x = 0 , f = 1 ;
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

inline int Lowbit( int x ){
    return x & ( - x ) ;
}

inline void modify( int x , int k ){
    for( ; x <= N ; x += Lowbit( x ) ) {
        Tree[ x ] += k ;
    }
}

inline void Build(){
    for( int i = 1 ; i <= N ; i ++ ){
        a[ i ] = read() ;
        //Tree[ i ] = a[ i ] ;
        modify( i , a[ i ] ) ;
    }
}

inline int query( int x ){
    int ans = 0 ;
    for( ; x ; x -= Lowbit( x ) ) {
        ans = ans + Tree[ x ] ;
    }
    return ans ;
}

inline int Union( int x , int y ){
    return query( y ) - query( x - 1 ) ;
}

signed main(){
    N = read() , M = read() ;
    Build() ;
    while( M -- ){
        int opt ;
        opt = read() ;
        switch( opt ){
            case 1 :{
                int x , k ;
                x = read() , k = read() ;
                modify( x , k ) ;
                break;
            }
            case 2 :{
                int x , y ;
                x = read() , y = read() ;
                printf( "%d\n" , Union( x , y ) ) ;
                break;
            }
        }
    }
    return 0 ;
}
