
// 
https://github.com/gsimsekfb/lang-ref

// Next:
  - Java  

// Next later:
  es2018: http://2ality.com/2017/02/ecmascript-2018.html
    https://babeljs.io/learn-es2015/    
    https://github.com/lukehoban/es6features
    
// Sources
    . C++ 11/14/17
        https://github.com/AnthonyCalandra/modern-cpp-features

    . ES2017    
        http://exploringjs.com/es2016-es2017/pt_es2017.html    

//// -------------------------------------- C++ ---------------------------------------------
{

Lang:            C++    
First appeared:  1985
Designed by:     Bjarne Stroustrup
Paradigm:        Multi-paradigm: procedural, functional, object-oriented, generic[1]

----
    
C++20 (major)
  // -- Big four
  Concepts          ( Def: template<typename T> concept Sortable = requires(T t) {...};                    
                      Use: sort(Sortable& auto s);                                                         )
  Modules           ( Optionally no header file, all in one file. Use: import foo; Foo::f();               
                      Def module (foo.cppm): export module foo; namespace Foo { export f() {..} }          ) 
  Coroutines        ( A func is coroutine if one used: co_await, co_yield, co_return                       )
  Ranges            ( vector v { 1, 3, 1 }; ranges::sort(v);                                               
                      or -> auto v2 = v | views::filter( [](){..} ) | views::reverse | views::drop(2)      )
                                                                                                           
  // -- Other Features                                                                                     
  using enum        ( 1. enum class E {x,y}; switch(val) { using enum E; case x: case y: }
                      2. struct Foo { using enum E; } / Foo f; f.x; or Foo::x; // OK, names E::x           )
  Designated init.  ( struct Person { int age; int x; } ; Person alex { .age = 42, .x = 2 }                )
  Init-statement    ( for (auto vec = getVec(); auto e : vec ) {...} )                                     
       range-for                                                                                           
  std::format       ( cout << format("Name:{0}, Surname: {1}", name, surname)                              )       
  std::erase()      ( erase(vec, 1); instead of vec.erase(remove(vec.begin(), vec.end(), 2), vec.end())    )
  std::erase_if()   ( erase_if(v, [](int e) { return e == 2; });                                           )
  std::span         ( read(span<int> buffer) instead of -> read(int* buffer, size_t buffer_size)           
                      lite-weight abstraction of contiguous data -> span<int,42> arr                       )
  operator<=>       ( a <=> b is >0 if a>b, <0 if a<b, 0 if a==b                                           
                      operator<=>(const F&) = default; // request ( ==, !=, <, >, <=, >= ) ops )           
  bit ops           ( global funcs rotl() /*rotate left*/, rotr(), countl_zero() etc..                     )
  calendar & tz     ( std::year, month, day. e.g. date1 { 2020y, September, 15d }                          )
  constinit         ( Force compile time constant initialization                                           
                      constinit const int x { <static-init> } // compile err in case of dynamic init..     )
  consteval         ( Force produce constant at compile time, like constexpr but compile time eval forced  
                      consteval int sq(int x){..}; int a { 42 }; const res { sq(a) } // compile error      )
  [=, this]         ( C++20: [=] wont implicitly capture this, [=, this] must be used to capture this      )
  Templated lambdas ( [] <typename T> (T t) { ... }                                                        )
  [[likely]]        ( Hints for compilers to optimize certain branches                                     )
  [[unlikely]]        switch(val){ [[likely]] case 1: ...; [[unlikely]] case 2: ...; // same for if        )    
  source_location   ( void log(..) { cout << src_loc.file_name() << ':' << src_loc.line() ... }            )                        
  Feature Testing   ( __cpp_coroutines, __cpp_ranges ...                                                   )
          Macros
    
  // -- Concurrency
  std::jthread      ( doWork() { jthread job { [](){...} }; } /* auto join&cancel request in dtor */       )
  atomic smart ptrs ( class concurrent_stack { ... atomic<shared_ptr<T>> head; }                           )
  std::latch        ( a thread coordination point, threads block till given # of thrds reach latch point   )
  std::barrier      ( thread coordination with phases, threads block till given # of threads reach barrier )
  Semaphores        ( std::counting_semaphore: allows more than one concurrent access, 
                      std::binary_semaphore  : alias for std::counting_semaphore with LeastMaxValue = 1    )  
                                          
  *Ref:
    C++20: An (Almost) Complete Overview - Marc Gregoire - CppCon 2020
    https://www.youtube.com/watch?v=FRkJCvHWdwQ&t=110s
    https://www.reddit.com/r/cpp/comments/au0c4x/201902_kona_iso_c_committee_trip_report_c20/
    https://en.wikipedia.org/wiki/C%2B%2B20

C++17 (medium)
  // -- Major Features
  Parallel STL        ( permit parallel/unseq/vectorel execution: sort(std::par, vec.begin(), vec.end())   )
      algorithms
  Filesystem library  ( std::filesystem::path, directory iterators, files ops: copy/move, create, symlinks )
                                    
  // -- Other Features                       
  Structured Binding  ( const auto [a,b,c] = array/struct/pair/tuple e.g. for(auto& [key,val] : map)) {..} )    
        (decomposers)  
  Nested namespaces   ( e.g., namespace X::Y { ... } instead of namespace X { namespace Y { ... }}         )    
  string_view         ( string_view substr(string_view sv){..} 'instead of' string substr(string const& s) 
                       * non-owning view of original string; ptr to the internal buffer and the length     )
  std::optional       ( optional<int> try_parse_int(std::string str)  // return an int or no value         )
  std::variant        ( Type safe unions -> std::variant<int, float, std::string> var                      )
  std::any            ( Use any if list of types are unknown, otherwise use variant. Replaces void*        )
  inline static       ( class Foo { inline static const int COUNT = 100; } in .h instead of in .h & .cpp   )
  Init-statement      ( if (auto val = GetValue(); condition(val)) {...}                                   )
       if/switch
  if constexpr        ( The static/compile time-if for C++!, if constexpr(cond) { ... }                    )
  constexpr lambda    ( Compile-time lambdas, e.g. constexpr auto add = [] (int x, int y)..                )
  Template argument   ( std::pair pp(10, 3.14) - instead of - std::pair<int,double> pp(10, 3.14)           )
          deduction
  UTF-8 Character     ( Euro sign: U+20AC - HEX, 4 bytes                                                   )
         Literals
  std::byte           ( Neither an integer nor a character, just data                                      )
  New algorithms      ( for_each_n, reduce, transform_reduce, exclusive_scan..                             )
  Searchers           ( boyer_moore_searcher, boyer_moore_horspool_searcher w/ std::search                 )
                                    
  // -- Removed             
  auto_ptr
  register
  throw()             ( noexcept instead of -> void fooThrowsInt(int a) throw(int) {..}                    ) 
      
  *Ref: 
    http://www.bfilipek.com/2017/11/cpp17summary.html
    https://stackoverflow.com/questions/38060436/what-are-the-new-features-in-c17
    https://github.com/AnthonyCalandra/modern-cpp-features#c171411
    https://en.wikipedia.org/wiki/C%2B%2B17     

C++14 (minor)
  // -- Features
  Auto return type  ( for functions & lambdas: auto f() { return 42; } // return type deduced as int   )
  Generic lambdas   ( auto saveEvent = [](auto const& event) { ... }                                   )
  Extended capture  ( auto timer = [val = system_clock::now()] { ... }                                 )
        in lambdas                                                                                    
  decltype(auto)    ( auto for generic (template) code, to perfectly forward a return type             )
  Binary literals   ( auto a3 = 0b101010;  // ... binary                                               )
  Time literals     ( auto msec = 42ms;    // millisecond                                              )
  String literals   ( auto strA = "42"s;   // std::string                                              )
  [[deprecated]]    ( [[ deprecated ]] void f() { ... }                                                )
  Digit separators  ( auto million = 1'000'000                                                         )
                                                                                                      
  // -- Concurrency                                                                                   
  shared_timed_mutex( std::shared_timed_mutex: protect shared data being accessed by multiple threads  )
  std::shared_lock  ( general-purpose shared mutex ownership wrapper                                   )
     
  *Ref: https://isocpp.org/wiki/faq/cpp14-language

C++11 (major)
  // -- Major Features
  Multithreading     ( memory model and official support for multithreaded programming                 )
  Concurrency Supp.  ( std::thread, std::async, std::future, std::mutex, std::condition_variable etc.. )                                                
  Move semantics     ( perf boost when used correctly instead of copy, e.g. newStr = std::move(str)    )
  
  // -- Other Features
  Smart pointers     ( unique_ptr, shared_ptr, weak_ptr                                                )    
  auto               ( automatic type deduction: e.g. auto x = Foo(..)                                 )
  nullptr            ( std::nullptr object instead of usage null or 0                                  )
  Range for loop     ( for(auto const& name : names) {...}                                             )        
  Initializer lists  ( std::vector<std::string> vec { "a", "b", "cd" }                                 )
  constexpr          ( Do things at compile time (not forced), constexpr int sq(int x) { return x^2; } )
  Uniform init.      ( Foo f {'a', 43}, uniform type initialization that works on any object           )    
  using              ( using MyInt = int - instead of - typedef int MyInt                              )
  default            ( SomeType() = default; // Request compiler generated default constructor         )    
  delete             ( NonCopyable(const NonCopyable&) = delete; // Forbid copy construction           )   
  override           ( class Base { virtual void f1() } , class Der : Base { void f1() override; }
                       class method identifier to make sure that base method is overridden             )
  final              ( final classes not extendable and class methods not be overridden                )
  Typed enums        ( class enum instead of enum                                                      )           
  Lambdas            ( [&captured_var](int e){return e*e}                                              )
  non-member begin() ( begin(myVector)                                                                 )
             & end()  
  static_assert      ( assertion check at compile-time                                                 )  
                     ( static_assert(Size < 3, "Size is too small")                                    )
  Type traits        ( static_assert(std::is_integral<T1>::value, "Type T1 must be integral")          )
  Variadic templates ( templates can take variable numbers of template parameters                      
                       template<typename T, typename... Args>                                          )
  New string literals( supports three Unicode encodings: UTF-8, UTF-16, and UTF-32                     )
  long long int      ( have no fewer than 64 bits. Solves 32-bit/64-bit problems of C++03 long int     )
  Attributes         ( [[ noreturn ]] void f() { throw "error"; }, syntax for compiler/tool extensions )
  std::map & set     ( unordered_set, unordered_multiset, unordered_map, unordered_multimap            )
  Regular expressions( new library, header <regex>: std::regex, std::regex_search etc...               )
  Random numbers     ( A number of standard distributions and three base generator engine algorithms   )
  
  // -- Deprecated
  std::auto_ptr      ( use std::unique_ptr instead                                                     )
      
  *Ref: https://en.wikipedia.org/wiki/C%2B%2B11
        https://www.codeproject.com/Articles/570638/Ten-Cplusplus-Features-Every-Cplusplus-Developer

C++03 (TC, bug fixes only)  
C++98 (Major)       
and before
  // 
  decltype          ( int x = 0; -> decltype(x) y = 0; // y: int                                       )
  explicit          ( forbid implicit ctor conversion: explicit A(int); Ex: A a = 12; // compile error )
  virtual           ( dynamic binding happens virtual function is called ref or ptr to base-class      )
  Virtual dtor      ( force derived dtor to be called when base ptr to a derived object is deleted     )
  Pure virtual func ( Base: int price() const = 0  // force derived class to implement this func       )
  Abstract class    ( A class containing at least one pure virtual function                            )
  Func ptrs         ( int (*f1)(int, int); f1(3,4);                                                    )
  const member func ( void Foo::getVal() const                                                         )
  extern            ( forward declare & use global var: aa.cpp: extern int global_x;
                      Define only once in another source file: bb.cpp: int global_x = 42               )
  #ifdef #ifndef    ( #ifndef XX / #define XX / #endif                                                 )
  char char* char[] ( char str1[] = "Hello"; char* str2 = "Hello"; char* str3 = new char[28]{'a','b'}; ) 
  dynamic_cast<>    ( Safely convert ptrs and refs to classes up, down, and sideway inherit. hierarchy 
                      Base* base = new Derived; if(Derived* d = dynamic_cast<Derived*>(base) {..}      )
  static_cast<>     ( Convert between types using a combination of implicit and user-def conversions   
                      int x = static_cast<int>(3.14); // x: 3                                          )
  const_cast<>      ( remove the const-ness from ref/ptr that refer to something that is not const     
                      int i = 3; const int& ri = i; const_cast<int&>(ri) = 4; // OK: modifies i        )
  reinterpret_cast  ( convert types by reinterpreting underlying bit pattern                           )
  switch/case       ( switch (ch) { case 'a': .. break; case 'b': ... break; default: ... break; }     )  
  Local static obj  ( int count() { static int cnt=0; return ++cnt; }; // cnt destroyed at program exit)
  Overloaded Func   ( return value is not part of function signature                                   )
  Default Argument  ( void f1(int x, int y=0)                                                          )
  inline funcs      ( a.h: inline get() {return 43} / b.h: inline get() {return 8}                     
                      1. Each translation unit can (and must) supply its own copy of the func's def.                    
                      2. Request compiler to replace each func. call with func body at compile time    )
  static funcs      ( functions not be visible or shared outside of the translation unit               )
  const member func ( void getX() const { return _x } 
                      Const obj and ref or ptr to const objects, may call only const member func       ) 
  struct            ( only difference between struct/class is the default access level public/private  )        
  mutable           ( class Foo { mutable int cnt=0; }  // modify cnt even inside a const member func  ) 
  Delegating Ctors  ( Sales_data(string s) : Sales_data() {...};                                       )
  Aggregate Class   ( All members public, no ctors, no in-class initializers, no base class, virt. func
                      struct Data { int val; string str; }                                             )
  emplace_back      ( vec.emplace_back("Alex", 35) instead of vec.push_back(Person("Alex", 25))        )  
  mutable lambda    ( [i]() mutable {return ++i; } // w/o mutable compile error: i read-only           )  
  protected         ( allow derived class members to access while banning access to class users        )
  Exceptions in dtor( Dtors should never have exceptions, o/w terminates or yields undefined behavior  )  
  throw             ( try{ } catch (){  throw // re-throw  }                                           )  
  catch(...)        ( try{ } catch (...) // catch all exceptions {  }                                  )
  noexcept          ( f() noexcept; /*won't throw*/ - f() noexcept(true);  // won't throw  
                      f();          /*might throw*/ - f() noexcept(false); // might throw              )
  copy ctor         ( Foo(Foo const& other): x(other.x), ptr(new int(*other.ptr)) {}                   ) 
  copy-assign. op.  ( A& operator=(A const& rhs){ x = rhs.x;  ptr = new int(*rhs.ptr); return *this; } )
  move ctor         ( A(A&& rhs): x(rhs.x), ptr(new string(*rhs.ptr)) {rhs.x = 0; rhs.ptr = nullptr;}  )
  move assign. op.  ( A& operator=(A&& rhs){ if (this != &rhs){ x = rhs.x; *ptr = *rhs.ptr;  
                                             rhs.age = 0; rhs.pstr = nullptr; } return *this; }        )
                                            
  // Rarely used / Not to use        
  macros            ( Do not use macros - #define square(X) X*X - Use: square(2)                       )   
  placement new     ( ptr2 = new(ptr)Foo(); // construct new Foo at address "ptr"                      )       
  Friend func       ( allow another function to access its nonpublic members 
                      class F{ friend x(F&) /*x not class member*/ {return _x} } / main.cpp: getX(foo) )
  Friend class      ( allow another class members to access nonpublic members this class
                      class Screen {  friend class Window_mgr; ... }                                   )
  volatile          ( volatile int x = 100; // To compiler: x can be changed by outside of program     )

  // Debug
  set_terminate     ( stack trace for an uncaught exception                                            )
  typeid / RTTI     ( Use for debugging purposes - typeid(foo.name())                                  )  
  __FUNCTION__      ( local static defined by the compiler that holds the functions name               )
  __FILE__          ( string  - name of the file                                                       )
  __LINE__          ( integer - current line number                                                    )
  __TIME__          ( string  - time the file was compiled                                             )
  __DATE__          ( string  - date the file was compiled                                             )

  // Misc
  Archive libs      (.a, .a, .lib: for static linking ...                                              )
  Dynamic libs      (.so, .dylib, .dll: for dynamic linking                                            )

}





//// -------------------------------------- Python ---------------------------------------------
{

Lang:           Python    
First appeared: 1991
Designed by:    Guido van Rossum 
Paradigm:       Multi-paradigm: functional, imperative, object-oriented, structured, reflective
Typing:         Duck, dynamic, gradual
----
    
  Dictionaries   ( d = { 'x':3, 'y': 'str' } // unique keys                           
                   use: d['x'] /*x:3*/ , d['g'] = 42, for k, v in d.items(): ..       )
  Sets           ( s = {1,1,2} // s:1,2 // unique, heterogeneous, im-mutable elems    )
  Tuples         ( t = 1, 'a', 3   // heterogeneous, im-mutable elems, fixed size     )
  Lists          ( l = [3, 'b', 5] // heterogeneous, mutable elems                    )
  Arrays         ( arr = [3, 5, 1] // homogeneous, mutable elems, fixed size          )
  Strings        ( s = 'str'       // homogeneous, im-mutable elems, same as "str"    )
                                                                                      
  Functions      ( def add(x, y): return x + y )                                      )
  Lambdas        ( def increment(n):  return lambda x: x + n )                        )
  Standard params( def f(arg): // use: f(2) or f(arg=2)                               )
  Positional prms( def f(arg, /): // use: f(2) only                                   )
  Keyword params ( def f(*, arg): // use: f(arg=2) only                               )
  Mixed params   ( def f(pos1, pos2, /, pos_or_kwd, *, kwd1, kwd2): ...               )
  pass           ( Do nothing. use: while True: pass /*Busy-wait*/ , class Foo: pass  )
  """ """        ( Func documentation: def f():  """ Do nothing, but document it """  )
  ** unpack args ( d = {"y": 22, "x": 11} , f(**d) , def f(x, y=0, z=0): ...          )
  Variadic funcs ( def j(*args, sep="/"): return sep.join(args), j("a", "b") // 'a/b' )
  global         ( global x   // use global/module x                                  )
  nonlocal       ( nonlocal y // use variable from outer scope                        )
                                                                                      
  Classes        (class Foo:  // Use: f = Foo(3.0, -4.5)                              
                    def __init__(self, x, y):                                         
                      self.x = x   # instance variable unique to each instance                   
                    counter = 0    # class variable shared by all instances           )
  Inheritance    ( class Fish(Animal): ...                                            )
  Multi. Inher.  ( class DerivedClass(Base1, Base2, Base3):                           )
                                                                                      
  if else        ( if b > a: ... elif a == b: ... else: ...                           )
  for in         ( for i in iterable: ..., use: for i in range(3): /*i: 0,1,2*/       )
  for in else    ( for x in seq: if x==5: /*found*/, break, else: /*Failed to find*/  )
  No switch/case ( N/A                                                                )
  Ternary Op.    ( result = x if a > b else y)                                        )
  Exceptions     ( try: x = 10/2, except ValueError: .. , except: raise,              
                                  else:    // execute if no except raised in try      
                                  finally: // always execute                          )
  range()        ( range(3) /*0,1,2*/ , range(0,5,2) /*0,2,4*/                        )
  Slice Notation ( arr[x:y] /*items x to y-1*/, arr[x:] // from x till end            
                   arr[:y] /*begin till y-1*/, a[:] // copy of all items              
                   arr[x:y:step] // x through not past y, by step                     )
                                                                                      
  // Modules                                                                          
  import         ( 'import os' instead of 'from os import *'                            
                   This will prevent os.open() shadowing the built-in open() function )
  import as      ( import cv2 as cv                                                   )
  dir(os)        ( list of all module functions                                       )
  for in dir()   ( ex: list all 'event's in OpenCV module                             
                   events = [e for e in dir(cv) if 'EVENT' in e]                      
                   events = [e for e in dir(cv) if 'event' in e.lower()]              )
  help(os)       ( manual page                                                        )
  from import    ( from math import add, multiply                                     )
  from import *  ( from math import *  // bad practice                                )
  from import as ( from math import multiply as mult                                  )
  import x.y     ( import sound.effects.echo                                          )
  from x.y import z ( from sound.effects import echo                                  )
  Intra-package  ( from . import echo                                                 
    References     from .. import formats                                             
                   from ..filters import equalizer                                    )                                                                                      
  __init__.py    ( sound/  // Top-level package                                       
                      __init__.py          // Initialize the sound package            )

  // Debug 
  sys.argv[1]   ( 42 -> python main.py 42                                             )
  print(f'..')  ( print(f'xx: {xx}')  // same as print("xx: ", xx)                            
                  print(f'aa: {aa:-5}, bb: {bb:2.2%}')  // aa: 42572, bb: 88.00%      
                  aa = 42_572, bb = 88/100                                            )        
  dir(sys)      ( list of names a module or a file defines                            
        or dir()                                                                      )
  dir(builtins) ( list the names of built-in functions and variables                  )
  __name__      ( module name, ex: print("inside module:", __name__ )                 )
  Comments      ( # this is a comment in python                                       
                  No multi line comment support                                       )
  logging       ( import logging, logging.debug('...')  // also: info, warn, err, cri )
  sys.path      ( one of the Module Search Paths                                      )
  sys.exit()    ( terminate a script                                                  )

  // Misc
  python -c "code" ( python -c "import keras; print(keras.__version__)"               )
  __annotations__  ( Function Annotations, use: f.__annotations__                     )
  json             ( import json,  j='{ "x":3}' , y=json.loads(j) , y["x"] // 3       
                    // parse j, y is a Python dictionary, y: { "x":3 }                )
  42_572           ( same as 42572                                                    )
                                                                                      
  // Async                                                                            )
  ...todo          ( import threading, ...                                            )
                                                                                      )
  // Quirks                                                                           )
  Variable Scope   ( for x in range(10): ... / print(x) // x lives after for scope    )
                                                                                      
  // pip / Package Man.                                                               
  pip show tensorflow         // package info                                         )
  pip install pyinstaller     // install                                              )
  pip install tensorflow -U   // upgrade                                              )
  python -m site --user-site  // local packages path                                  )
    e.g. C:\Users\<user>\AppData\Roaming\Python\Python37\site-packages                )
  
}






                
//// -------------------------------------- Javascript ---------------------------------------------
{
Lang:           JavaScript
First appeared: 1995
Designed by:    Brendan Eich
Paradigm:       High-level, dynamic, weakly typed, prototype-based, multi-paradigm, and 
                interpreted programming language.    

---

ES2020 (ES11)
  Dynamic Import          ( let module = prompt("Enter module");  import(module).then(...)       )
  Promise.allSettled      ( Promise.allSettled([promise_1, promise_2]).then() => { ... }         
                            // Resolved promise will return obj with status & value props,       
                            // while rejected ones will have status and reason.                  )
  Top Level Await         ( const response = await fetch(url)                                    )
  Class static Methods    ( class Foo { static staticMethod() {...} }                            )
  Nullish Coalescing      ( x = y ?? 42 // x is 42 if y is null or undefined                     
            Operator ??                                                                          )
  Optional Chaining       ( Obj: x.y?.z -- Array: arr?.[1] -- Func: f1?.()                       )
  BigInt                  ( BigInt(Number.MAX_SAFE_INTEGER+1)                                    
                            For numbers larger than 2^53-1 (Number.MAX_SAFE_INTEGER)             )
  globalThis              ( Browser: window == globalThis -- node.js: global == globalThis       )
  String.matchAll         ( re = /(Mister )\w+/g;  matches = str.matchAll(re);                   )
      
  * Ref:
  https://www.telerik.com/blogs/latest-features-javascript-ecmascript-2020
  https://javascript.info/modules-dynamic-imports
  https://dev.to/olivierloverde/es2020-summary-of-new-features-examples-2260

ES2019 (ES10)
  flat() & flatMap()        ( arr = ['a', 'b', ['c']]; flattened = arr.flat(); // ["a","b","c"]  )
  Object.entries()          ( obj = {a: 1, b: 2};  Object.entries(obj) // [["a", 1], ["b", 2]]   
        .fromEntries()                                                                           )
  trimStart() and trimEnd() ( str = "   string   ";  str.trimStart() // "string   "              )
  Description property      ( let sym = Symbol('foo');  sym.description; // foo                   
      for Symbol objs                                                                            )
  Optional catch binding    ( try {..} catch {/*catch without catching the value thrown*/}       )

  * Ref:
    https://blog.logrocket.com/5-es2019-features-you-can-use-today/
    https://2ality.com/2018/02/ecmascript-2019.html
  
ES2018 (ES9)                                                                                       
  Asynchronous Iteration ( for await (let e of elems) {...}                                      )
  Promise.finally()      ( .finally(() => {...}                                                  )
  Rest/Spread for objs   ( function restParam({ a, ...x }) and const { a, ...x } = myObject      )
  Reg. Exp. Improvements ()
  
    * Ref:
        https://www.sitepoint.com/es2018-whats-new/   
                  
ES2017 (ES8)
  // -- Major Features
  Async Functions        ( async function asyncFunc() { const res = await otherAsyncFunc().. }   
      async & await                                                                              )
  Shared Memory & Atomics( SharedArrayBuffer, Atomics.store(), Atomics.load() ...)               )
  
  // -- Others
  Object.entries()       ( for(const [key,val] of Object.entries(obj)) {...}                    
        .values()          for(const val of Object.values(obj)) {...}                            )
  String.padStart()      ( 'x'.padStart(5, 'ab') /*'ababx' */ ,                                  
        .padEnd()          'x'.padEnd(5, 'ab') //'xabab'                                         )
  Object.getOwnProp..()  ( Object.getOwnPropertyDescriptors(obj)                                 )
  Trailing commas        ( let arr = [12, 13, 14,]                                               )
  
  * Ref:
      http://exploringjs.com/es2016-es2017/index.html                   
    
ES2016 (ES7)
  Array.includes()      ( ['a', 'b', 'c'].includes('a') // true                                  )
  Exponentiation op. ** ( x**y produces the same result as Math.pow(x, y)                        )

  *Ref:
      http://exploringjs.com/es2016-es2017/index.html
    
ES2015 (ES6)
  // -- Major Features
  Classes               ( classes instead of constructor functions, e.g. class Person {...}      )
  Derived classes       ( class Employee extends Person {...}                                    )
  Promises              ( function f1() { return new Promise((resolve, reject) => {..}) }        )
  Modules               ( import React, { Component } from 'react'; export const COUNT = 44,     
                          export function square(x) {...}, import { xx, yy } from 'lib';         )
  Error class           ( subclassing Error class instead of custom error constructors           )
  Map                   ( Maps instead of objects, e.g. let myMap = new Map(),                   
                          arbitrary values for keys & values, not just strings                   )
                          
  // -- Others                                                                                 
  const/let             ( const/let (block-scoped) instead of var (function-scoped)              )
  Arrow functions       ( x => x * x instead of function(x) { return x * x }                     )
  for...of              ( for (const e of array) {...}                                           )
  Computed Properties   ( const key = 'age'; const obj = {[key]: 10}; // obj: {'age', 10}        )
  Object Short Notation ( const name = 'Alex'; const obj = { name }; // obj: { name: 'Alex' }    )
  Object Concise Method ( f = { f1(){return 5} } /*bef. es6*/: f = { f1: function(){return 10} } )
  String interpolation  ( console.log(`(${x}, ${y})`) instead of console.log('('+x+', '+y+')')   )
  Multi-line strings    ( e.g. `1st_Line 2nd_Line etc..` )                                       )
  Destructing arrays    ( const [, year, month, day] = arr    // skip arr[0] )                   )
  Destructing objects   ( const {name, age} = person )                                           )
  Default parameters    ( function foo(a, b = 1) )                                               )
  Rest parameters       ( Use ...args instead of arguments (arguments) e.g. function(x, ...args) )
  Spread operator '...' ( arr1.push(...arr2)                                                     )
  Method definitions    ( const myFuncs = { f1() {...}, f2() {...} }                             )
  New Array methods     ( e.g. arr.findIndex(x => Number.isNaN(x)), Array.from(),fill() etc..    )
  New string methods    ( str.startsWith(), endsWith(), includes(), repeat() ...                 )
                                                                                                    
  *Ref:                                                                                             
      http://exploringjs.com/es6/ch_core-features.html                                              
      https://github.com/lukehoban/es6features
}
