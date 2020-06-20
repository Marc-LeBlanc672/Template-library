// LANG : C++ 
// maker : Marc LeBlanc
// 2020.6.20

#include <cstdio>
#include <algorithm>
using namespace std ;

const int MAXN = 1e6 + 1 ;

typedef long long lld ;
lld n , m , MOD ;
lld arry[ MAXN ] ;
struct Edge {  // Numerical is zhe numerical of The Point , Tag_Multiplication is
// the multiplication lazy_tag of the point , Tag_Addition is the addition lazy_tag of the point ;
    lld Numerical , Tag_Multiplication , Tag_Addition ;
}st[ MAXN << 2 ] ; // multiply 4 ;
inline void pushup( int root ){
    st[ root ].Numerical = ( st[ root << 1 ].Numerical + st[ root << 1 | 1 ].Numerical ) % MOD ;
}
inline void BuildTree( int root , int rootL , int rootR ) {
    st[ root ].Tag_Multiplication = 1 ;// the initialization of the lazy_tag ;
    st[ root ].Tag_Addition = 0 ; // Initialization ;
    if ( rootL == rootR ){
        st[ root ].Numerical = arry[ rootL ] ; // and arry[ rootR ] is OK ;
    }
    else {
        lld middle = rootL + rootR >> 1 ;
        BuildTree( root << 1 , rootL , middle ) ;
        BuildTree( root << 1 | 1 , middle + 1 , rootR ) ;
        st[ root ].Numerical =  st[ root << 1 ].Numerical + st[ root << 1 | 1 ].Numerical ;
    }
    st[ root ].Numerical %= MOD ;
    return ; 
}

inline void Initialization ( lld root , lld rootL , lld rootR ) {
    lld middle = rootL + rootR >> 1 ;
    st[ root << 1 ].Numerical = ( st[ root << 1 ].Numerical * st[ root ].Tag_Multiplication + st[ root ].Tag_Addition * ( middle - rootL + 1 ) ) % MOD ;
    st[ root << 1 | 1 ].Numerical = ( st[ root << 1 | 1 ].Numerical * st[ root ].Tag_Multiplication + st[ root ].Tag_Addition * ( rootR - middle ) ) % MOD ;
    return ;
}

inline void update_Add( lld root , lld rootL , lld rootR ){
    st[ root << 1 ].Tag_Addition = ( st[ root << 1 ].Tag_Addition * st[ root ].Tag_Multiplication + st[ root ].Tag_Addition ) % MOD ;
    st[ root << 1 | 1 ].Tag_Addition = ( st[ root << 1 | 1 ].Tag_Addition * st[ root ].Tag_Multiplication + st[ root ].Tag_Addition ) % MOD ;
    st[ root ].Tag_Addition = 0 ;
    return ;
}

inline void update_Mul( lld root , lld rootL , lld rootR ){
    st[ root << 1 ].Tag_Multiplication = ( st[ root << 1 ].Tag_Multiplication * st[ root ].Tag_Multiplication ) % MOD ;
    st[ root << 1 | 1 ].Tag_Multiplication = ( st[ root << 1 | 1 ].Tag_Multiplication * st[ root ].Tag_Multiplication ) % MOD ;
    st[ root ].Tag_Multiplication = 1 ;
    return ;
}

inline void pushdown ( lld root , lld rootL , lld rootR ){
    Initialization( root , rootL , rootR ) ;
    update_Add ( root , rootL , rootR ) ;
    update_Mul ( root , rootL , rootR ) ;
    return ;
}

inline void modify_Mul( lld root , lld rootL , lld rootR , lld mL , lld mR , lld m ){
    if ( mR < rootL || rootR < mL ) {
        return ; // there is no intersection between the two intervals ;
    }
    if( mL <= rootL && rootR <= mR ){
        st[ root ].Numerical = ( st[ root ].Numerical * m ) % MOD ;
        st[ root ].Tag_Multiplication = ( st[ root ].Tag_Multiplication * m ) % MOD ;
        st[ root ].Tag_Addition = ( st[ root ].Tag_Addition * m ) % MOD ;
        return ; 
    }
    pushdown( root , rootL , rootR ) ;
    lld middle = rootL + rootR >> 1 ;
    modify_Mul ( root << 1 , rootL , middle , mL , mR , m ) ;
    modify_Mul ( root << 1 | 1 , middle + 1 , rootR , mL , mR , m ) ;
    pushup( root ) ;
    return ; 
}

inline void modify_Add ( lld root , lld rootL , lld rootR , lld mL , lld mR , lld m ) {
    if ( mR < rootL || rootR < mL ){
        return ;  // there is no intersection between the two intervals ;
    }
    if( mL <= rootL && rootR <= mR ) {
        st[ root ].Tag_Addition = ( st[ root ].Tag_Addition + m ) % MOD ;
        st[ root ].Numerical = ( st[ root ].Numerical + m * ( rootR - rootL + 1 ) ) % MOD ;
        return ;
    }
    pushdown ( root , rootL , rootR ) ;
    lld middle = rootL + rootR >> 1 ;
    modify_Add( root << 1 , rootL , middle , mL , mR , m ) ;
    modify_Add( root << 1 | 1 , middle + 1 , rootR , mL , mR , m ) ;
    pushup( root ) ;
    return ;
}

inline lld query( lld root , lld rootL , lld rootR , lld mL , lld mR ) {
    if ( mR < rootL || rootR < mL ){
        return 0 ;   // there is no intersection between the two intervals ;
    }
    if( mL <= rootL && rootR <= mR ){
        return st[ root ].Numerical ;
    }
    pushdown( root , rootL , rootR ) ;
    lld middle = rootL + rootR >> 1 ;
    lld s = 0 ;
    s += query( root << 1 , rootL , middle , mL , mR ) ;
    s += query( root << 1 | 1 , middle + 1 , rootR , mL , mR ) ;
    return s %= MOD ;
}

int main(){
    scanf( "%lld%lld%lld" , &n , &m , &MOD ) ;
    for ( int i = 1 ; i <= n ; i ++ ){
        scanf( "%lld" , &arry[ i ] ) ;
    }
    BuildTree ( 1 , 1 , n ) ;
    while( m -- ){
        int opt ;
        scanf( "%d" , &opt ) ;
        switch( opt ){
            case 1 : {
                lld x , y , z ;
                scanf( "%lld%lld%lld" , &x , &y , &z ) ;
                modify_Mul( 1 , 1 , n , x , y , z ) ;
                break;
            }
            case 2 : {
                lld x , y , z ;
                scanf( "%lld%lld%lld" , &x , &y , &z ) ;
                modify_Add( 1 , 1 , n , x , y , z ) ;
                break;
            }
            case 3 : {
                lld x , y ;
                scanf( "%lld%lld" , &x , &y ) ;
                printf( "%lld\n" , query( 1 , 1 , n , x , y ) ) ;
                break;
            }
        }
    }
    return 0 ;
}
