//! we are going to implement Conway's GoL in a beautiful simple language called ISO C.
//! however, instead of jumping into coding it in "vanilla" C, we begin by defining a 
//! bunch of handy typedefs, idiomatic expressions and abbreviations which have no direct
//! relation to the task at hand, but serve two very important generic purposes:

//! 1. they will make our code much more compact without impacting readability and clarity,
//     because we are going to use these conventions without exceptions. Uniformity is key
//     to readable, compact and bug-free code. Less typing, less bugs!

//! 2. they will allow us to completely escape a whole galaxy of deadly traps associated
//     with implicit declaration of imperative loops, most importantly `for(;;){}`,
//     and even more so its nested variants for(;;){for(;;){}}.

//! and this is how:

//! arthur way                  arthur whitney is a guy who taught us to write C this way
typedef char   C;               //!<  C is signed byte, i.e [-128..127], occupies 8 bits
typedef char*  S;               //!<  S is string - a mnemory pointer to a sequence of signed bytes.
typedef int    I;               //!<  I is 32-bit signed integer, occupies 4 bytes.
typedef short  H;               //!<  I is 16-bit signed integer, occupies 2 bytes.
typedef long   J;               //!<  J is 64-bit signed intgeger, occupoes 8 bytes.
typedef float  E;               //!<  E is a single-precision floating point number, 4 bytes.
typedef double F;               //!<  F is a double-precision floating point number, 8 bytes.
typedef void   V;               //!<  V is return type of a function that returns no value.

typedef unsigned long long UJ;  //!<  UJ is *unsigned* 64-bit signed intgeger
typedef unsigned int   UI;      //!<  UI is same for I
typedef unsigned short UH;      //!<  UH same for H
typedef unsigned char  G;       //!<  G same for C

#define ZG static G             //!< `static` prefix depends on the usage context, we'll revisit that.
#define ZI static I
#define ZE static E

#define O printf                //!< O(fmt,args..) is simply a shoutcut for "output", less type than printf
#define R return                //!< same for return
#define nl() O("\n");           //!< shortcut for newline

//! easy math
#define ABS(x) (((x)>0)?(x):-(x))             //!< absulute value of x
#define IN(l,x,r) ((l)<=(x)&&(x)<=(r))        //!< true if x is between l and r, inclusive

//! no stinking loops
#define W(a...)  while(({a;}))                      //!< no more need to type while anymore
#define N(n,a...) {UI _n=(n),i=-1;W(++i<_n){a;}}    //!< no more need to type for(i=0;i<n;++i){a...}
#define Nj(n,a...) {UI _n=(n),j=-1;W(++j<_n){a;}}   //!< no more need to type for(j=0;j<n;++i){a...}

//! fail fast
#define P(x,y...) {if(x)R(y);}                      //!< panic aka predicate - typically used to check 
                                                    //!< argument values of a function and return early 
                                                    //!< if something looks bad.

//! now that we have an even simpler C, let's implement game of life on small embedded computer.

//:~
