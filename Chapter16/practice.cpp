// 如果两个值相等，返回 0，如果 v1 小返回 -1，如果 v2 小返回 1
int compare(const string &v1, const string &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
int compare(const double &v1, const double &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

// 实例化出 int compare(const int&, const int&);
cout << compare(1, 0) << endl; // T 为 int
// 实例化出 int compare(const vector<int>&, const vector<int>&);
vector<int> vec1{1, 2, 3}, vec2{4, 5, 6};
cout << compare(vec1, vec2) << endl;    // T 为 vector<int>

// 正确： 返回类型和参数类型相同
template <typename T> T foo(T* p)
{
    T tmp = *p;
    // ...
    return tmp;
}

// 正确：在模板参数列表中，typename 和 class 没有什么不同
template <typename T, class U> calc (const T&, const U&);

template<unsigned N, unsigned M>
int compare(const char (&p1)][N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

// 正确：inline 说明符跟在模板参数列表之后
template <typename T> inline T min(const T&, const T&);

template <typename T> class Blob {
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // 构造函数
    Blob();
    Blob(std::initializer_list<T> il);
    // Blob 中的元素数目
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const T &t) { data->push_back(t); }
    // 移动版本
    void push_bacK(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    // 元素访问
    T& back();
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
    // 若 data[i] 无效，则抛出 msg
    void check(size_type i, const std::string &msg) const;
};

// 空 Blob<int>
Blob<int> ia;
// 有 5 个元素的 Blob<int>
Blob<int> ia2 = {0, 1, 2, 3, 4}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}
template <typename T>
T& Blob<T>::operator[](size_type i)
{
    // 如果 i 太大，check 会抛出异常，阻止访问一个不存在的元素
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T> void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()) { }

template <typename T>
Blob<T>::Blob(std::initailizer_list<T> il):
                data(std::make_shared<std::vector<T>>(il)) { }
Blob<string> articles = {"a", "an", "the"};

// 后置：递增/递减对象但返回原值
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    // 此处无须检查；调用前置递增时会进行检查
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

// 前置声明，在 Blob 中声明友元所需要的
template <typename> class BlobPtr;
template <typename> class Blob;     // 运算符==中的参数所需要的
template <typename T>
    bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> class Blob {
    // 每个 Blob 实例将访问权限授予用相同类型实例化的 BlobPtr 和相等运算符
    friend class BlobPtr<T>;
    friend bool operator==<T>
            (const Blob<T>&, const Blob<T>&);
};

// 前置声明，再将模板的一个特定实例声明为友元时要用到
template <typename T> class Pal;
class C {
    // 用类 C 实例化的 pal 是 C 的一个友元
    friend class Pla<C>;
    // Pal2 的所有实例都是 C 的友元
    template <typename T> friend class Pal2;
};
template <typename T> class C2 {
    // C2 的每个实例将相同实例化的 Pal 声明为友元
    friend class Pal<T>;
    // Pal2 的所有实例都是 C2 的每个实例的友元
    template <typename X> friend class Pal2;
    // Pal3 是一个非模板类，它是 C2 所有实例的友元
    friend class Pal3;
};

template<typename T> using twin = pair<T, T>;
twin<string> authors;

template <typename T> class Foo {
public:
    static std::size_t count() { return ctr; };
private:
    static std::size_t ctr;
};

// 定义并初始化 ctr
template <typename T>
size_t Foo<T>::ctr = 0;

template <typename Foo> Foo calc(const Foo& a, const Foo& b)
{
    // tmp 的类型与参数和返回类型一样
    Foo tmp = a;
    // ...
    // 返回类型和参数类型一样
    return tmp;
}

typedef double A;
template <typename A, typename B> void f(A a, B b)
{
    A tmp = a;
}

// 声明但不定义 compare 和 Blob
template <typename T> int compare(const T&, const T&);
template <typename T> class Blob;
// 3 个 calc 都指向相同的函数模板
template <typename T> T calc(const T&, const T&);
template <typename U> U calc(const U&, const U&);
template <typename Type>
Type calc(const Type& a, const Type& b) { }

template <typename T>
typename T::value_type top(const T& c)
{
    if (!c.empty())
        return c.back();
    else 
        return typename T::value_type();
}

// compare 有一个默认模板实参 less<T> 和一个默认函数实参 F()
template <typename T, typename F = less<T>>
int compare(const T &v1, const T &v2, F f = F())
{
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}

// T 默认为 int
template <class T = int> class Numbers {
public:
    Numbers(T v = 0): val(v) { }
private:
    T val;
};
Numbers<long double> lots_of_precision;
// 空<>表示我们希望使用默认类型
Numbers<> average_precision;

// 函数对象类，对给定指针执行 delete
class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr): os(s) { }
    // 与任何函数模板相同，T 的类型由编译器推断
    template <typename T> void operator()(T *p) const 
        { os << "deleting unique_ptr" << std::endl; delete p; }
private:
    std::ostream &os;
};

template <typename T> class Blob {
    template <typename It> Blob(It b, It e);
    // ...
};

template <typename T>       // 类的类型参数
template <typename It>      // 构造函数的类型参数
    Blob<T>::Blob(It b, It e):
    data(std::make_shared<std::vector>>(b, e)) { }

// 实例化声明与定义
extern template class Blob<string>;         // 声明
template int compare(const int&, const int&);   // 定义

// 实参类型可以不同，但必须兼容
template <typename A, typename B>
int flexibleCompare(const A& v1, const B& v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
long lng;
flexibleCompare(lng, 1024);

template <typename T> 
ostream &print(ostream &os, const T &obj)
{
    return os << obj;
}

// 编译器无法推断 T1，它未出现在函数参数列表中
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);

// T1 是显示指定的，T2 和 T3 是从函数实参类型推断而来的
auto val3 = sum<long long>(i, lng); // long long sum(int, long)

// 尾置返回允许我们在参数列表之后声明返回类型
template <typename It>
auto fcn(It beg, It end) -> decytype(*beg)
{
    // 处理序列
    return *beg; // 返回序列中一个元素的引用
}

remove_reference<decltype(*beg)>::type

// 为了适用模板参数的成员，必须用 typename
template <typename It>
auto fcn2(It beg, It end) ->
    typename remove_reference<decltype(*beg)>::type
{
    // 处理序列
    return *beg;    // 返回序列中一个元素的拷贝
}

template <typename T> int compare(const T&, const T&);
// pf1 指向实例 int compare(const int&, const int &)
int (*pf1)(const int&, const int&) = compare;

// 正确：显示指出实例化哪个 compare 版本
func(compare<int>);     // 传递 compare(const int&, const int&)

template <typename T> void f1(T&);  // 实参必须是一个左值

template <typename T> void f2(const T&);    // 可以接受一个右值
// f2 中的参数是 const &; 实参中的 const 是无关的
// 在每个调用中，f2 的函数参数都被推断为 const int&

template <typename T> void f3(T&&);

template <typename T> void f(T&&);          // 绑定到非 const 右值
template <typename T> void f(const T&);     // 左值和 const 右值

// 在返回类型和类型转换中也要用到 typename
// remove_reference 
template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
    return static_cast<typename remove_reference<T>::type&&>(t);
}

// 接受一个可调用对象和另外另个参数的模板
// 对“翻转”的参数调用给定的可调用对象
// flip1 是一个不完整的实现：顶层 const 和引用丢失了
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}

template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(t2, t1);
}

template <typename Type> intermediary(Type &&arg)
{
    finalFcn(std::forward<Type>(arg));
    // ...
}

template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

// 打印任何我们不能处理的类型
template <typename T> string debug_rep(const T &t)
{
    ostringstream ret;
    ret << t;   // 使用 T 的输出运算符打印 t 的一个表示形式
    return ret.str(); // 返回 ret 绑定的 string 的一个副本
}

// 打印指针的值，后跟指针指向的对象
// 注意：此函数不能用于 char*
template <typename T> string debug_rep(T *p)
{
    ostreamstream ret;
    ret << "pointer:" << p;     // 打印指针本身的值
    if (p)
        ret << " " << debug_rep(*p);    // 打印 p 指向的值
    else 
        ret << " null pointer";     // 或指出 p 为空
    return ret.str();           // 返回 ret 绑定的 string 的一个副本
}

// 打印双引号包围的 string
string debug_rep(const string &s)
{
    return '"' + '"';
}

string s("hi");
cout << debug_rep(s) << endl;

// 将字符指针转换为 string，并调用 string 版本的 debug_reg
string debug_rep(char *p)
{
    return debug_rep(string(p));
}
string debug_rep(const char *p)
{
    return debug_rep(string(p));
}

// Args 是一个模板参数包；rest 是一个函数参数包
// Args 表示零个或多个模板类型参数
// rest 表示零个或多个函数参数
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest);

template <typename ... Args>
void g(Args ... args) 
{
    // 类型参数的数目
    cout << sizeof...(Args) << endl;
    // 函数参数的数目
    cout << sizeof...(args) << endl;
}

// 用来终止递归并打印最后一个元素的函数
// 此函数必须在可变参数版本的 print 定义之前声明
template <typename T>
ostream &print(ostream &os, const T &t)
{
    return os << t; // 包中最后一个元素之后不打印分隔符
}
// 包中除了最后一个元素之外的其他元素都会调用这个版本的 print
template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";            // 打印第一个实参
    return print(os, rest...);  // 递归调用，打印其他实参
}

template <typename T, typename... Args>
ostream &
print(ostream &os, const T &t, const Args&... rest) // 扩展 Args
{
    os << t << ", ";
    return print(os, rest...);                      // 扩展 rest
}

// 在 print 调用中对每个实参调用 debug_rep
template <typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
    // print (os, debug_rep(a1), debug_rep(a2), ..., debug_rep(an))
    return print(os, debug_rep(rest)...);
}

class StrVec {
public:
    template <class... Args> void emplace_back(Args&&...);
};

template <class... Args>
inline
void StrVec::emplace_back(Args&&... args)
{
    chk_n_alloc();      // 如果需要的话重新分配 StrVec 内存空间
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

// fun 有零个或多个参数，每个参数都是一个模板参数类型的右值引用
template <typename... Args>
void fun(Args&&... args)    // 将 Args 扩展为一个右值引用的列表
{
    // work 的实参既扩展 Args 又扩展 args
    work(std::forward<Args>(args)...);
}

// 第一个版本；可以比较任意两个类型
template <typename T> int compare(const T&, const T&);
// 第二个版本处理字符串字面常量
template<size_t N, size_t M>
int compare(const char (&)[N], const char (&)[M]);

// compare 的特殊版本，处理字符数组的指针
template <>
int compare(const char* const &p1, const char* const &p2)
{
    return strcmp(p1, p2);
}

// 打开 std 命名空间，以便特例化 std::hash
namespace std {
template <> // 我们正在定义一个特例化版本，模板参数为 Sales_data
struct hash<Sales_data>
{
    // 用来散列一个无序容器的类型必须要定义下列类型
    typedef size_t result_type;
    typedef Sales_data argument_type;   // 默认情况下，此类型需要==
    size_t operator()(const Sales_data& s) const;
    // 我们的类使用合成的拷贝控制成员和默认构造函数
};
size_t
hash<Sales_data>::operator()(const Sales_data& s) const 
{
    return hash<string>()(s.bookNo) ^
           hash<unsigned>()(s.unites_sold) ^
           hash<double>()(s.revenue);
}
} // 关闭 std 命名空间；注意：右花括号之后没有分号

template <class T> class std::hash; // 友元声明所需要的
class Sales_data {
friend class std::hash<Sales_data>;
};

// 原始的、最通用的版本
template <class T> struct remove_reference {
    typedef T type;
};
// 部分特例化版本，将用于左值引用和右值引用
template <class T> struct remove_reference<T&>  // 左值引用
    { typedef T type; };
template <class T> struct remove_reference<T&&> // 右值引用
    { typedef T type; };

int i;
// decltype(42)为 int，使用原始模板
remove_reference<decltype(42)>::type a;
// decltype(i) 为 int&，使用第一个 (T&) 部分特例化版本
remove_reference<decltype(i)>::type b;
// decltype(std::move(i)) 为 int&&，使用第二个（即T&&）部分特例化版本
remove_reference<decltype(std::move(i))>::type c;

template <typename T> struct Foo {
    Foo(const T &t = T()): mem(t) { }
    void Bar() { }
    T mem;
};
template <>                 // 我们正在特例化一个模板
void Foo<int>::Bar()        // 我们正在特例化 Foo<int> 的成员 Bar
{
    // 进行应用于 int 的特例化处理
}