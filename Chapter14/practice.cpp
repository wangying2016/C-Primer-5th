// 输出两个 Sales_item 的和
cout << item1 + item2;

// 输出两个 Sales_data 的和
print(cout, add(data1, data2));

// 一个非成员运算符函数的等价调用
data1 + data2;              // 普通的表达式
operator+(data1, data2);    // 等价的函数调用

data1 += data2;             // 基于“调用”的表达式
data1.operator+=(data2);    // 对成员运算符函数的等价调用

string s = "world";
string t = s + "!";     // 正确：我们能把一个 const char* 加到一个 string 对象中
string u = "hi" + s;    // 如果 + 是 string 的成员，则产生错误

ostream &operator<<(ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.unites_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

class Sales_data {
friend ostream &operator(ostream&, const Sales_data&);
};

istream &operator>>(istream &is, Sales_data &item)
{
    double price;   // 不需要初始化，因为我们将先读入数据到 price，之后才使用它
    is >> item.bookNo >> item.unites_sold >> price;
    if (is)         // 检查输入是否成功
        item.revenue = item.unites_sold * price;
    else 
        item = Sales_data();    // 输入失败：对象被赋予默认的状态
    return is;
}

// 假设两个对象指向同一本书
Sales_data
operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;           // 把 lhs 的数据成员拷贝给 sum
    sum += rhs;                     // 将 rhs 加到 sum 中
    return sum;
}

bool operatro==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn() &&
           lhs.unites_sold == rhs.unites_sold &&
           lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs == rhs);
}

vector<string> v;
v = {"a", "an", "the"};

class StrVec {
public:
    StrVec &operator=(std::initializer_list<std::string>);
};

StrVec &StrVec::operator=(initializer_list<string> il)
{
    // alloc_n_copy 分配内存空间并从给定范围内拷贝元素
    auto data = alloc_n_copy(il.begin(), il.end());
    // 销毁对象中的元素并释放内存空间
    free();
    // 更新数据成员使其指向新空间
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

// 作为成员的二元运算符：左侧运算对象绑定到隐式的 this 指针
// 假定两个对象表示的是同一本书
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    unites_sold += rhs.unites_sold;
    revenue += rhs.revenue;
    return *this;
}

class StrVec {
public:
    std::string& operator[](std::size_t n) 
        { return elements[n]; }
    const std::string& operator[](std::size_t n) const 
        { return elements[n]; }
private:
    std::string *elements;  // 指向数组首元素的指针
};
// 假设 svec 是一个 StrVec 对象
const StrVec cvec = svec;               // 把 svec 的元素拷贝到 cvec 中
// 如果 svec 中含有元素，对第一个元素运行 string 的 empty 函数
if (svec.size() && svec[0].empty()) {
    svec[0] = "zero";                   // 正确：下标运算符返回 string 的引用
    cvec[0] = "Zip";                    // 错误：对 cvec 取下标返回的是常量引用
}

class StrBlobPtr {
public:
    // 递增和递减运算符
    StrBlobPtr& operator+();            // 前置运算符
    StrBlobPtr& operator--();           
};

// 前置版本：返回递增/递减对象的引用
StrBlobPtr& StrBlobPtr::operator++()
{
    // 如果 curr 已经指向了容器的尾后位置，则无法递增它
    check(curr, "increment past end of StrBlobPtr");
    // 将 curr 在当前状态下向前移动一个元素
    ++curr;
    return *this;
}
StrBlobPtr& StrBlobPtr::operator--()
{
    // 如果 curr 是0，则继续递减它将产生一个无效下标
    --curr;         // 将 curr 在当前状态下向后移动一个元素
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

class StrBlobPtr {
public:
    // 递增和递减运算符
    StrBlobPtr operator++(int);         // 后置运算符
    StrBlobPtr operator--(int);
};

// 后置版本：递增/递减对象的值但是返回原值
StrBlobPtr StrBlobPtr::operator++(int)
{
    // 此处无须检查有效性，调用前置递增运算时才需要检查
    StrBlobPtr ret = *this;     // 记录当前的值
    ++*this;                    // 向前移动一个元素，前置++需要检查递增的有效性
    return ret;                 // 返回之前记录的状态
}
StrBlobPtr StrBlobPtr::operator--(int)
{
    // 此处无须检查有效性，调用前置递减运算时才需要检查
    StrBlobPtr ret = *this;     // 记录当前的值
    --*this;                    // 向后移动一个元素，前置--需要检查递减的有效性
    return ret;                 // 返回之前记录的状态
}

class StrBlobPtr {
public:
    // 递增和递减运算符
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
};

// 前置版本：返回递增/递减对象的引用
StrBlobPtr& StrBlobPtr::operator++()
{
    // 如果 curr 已经指向了容器的尾后位置，则无法递增它
    check(curr, "increment past end of StrBlobPtr");
    ++curr;         // 将 curr 在当前状态下向前移动一个元素
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
    // 如果 curr 是0，则继续递减它将产生一个无效下标
    --curr;         // 将 curr 在当前状态下向后移动一个元素
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

class StrBlobPtr {
public:
    // 递增和递减运算符
    StrBlobPtr operator++(int);         // 后置运算符
    StrBlobPtr operator--(int);
};

// 后置版本：递增/递减对象的值但是返回原值
StrBlobPtr StrBlobPtr::operator++(int)
{
    // 此处无须检查有效性，调用前置递增运算时才需要检查
    StrBlobPtr ret = *this; // 记录当前的值
    ++*this;                // 向前移动一个元素，前置++需要检查递增的有效性
    return ret;             // 返回之前记录的状态
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    // 此处无须检查有效性，调用前置递减运算时才需要检查
    StrBlobPtr ret = *this;         // 记录当前的值
    --*this;                        // 向后移动一个元素，前置--需要检查递减的有效性
    return ret;                     // 返回之前记录的状态
}

StrBlobPtr p(a1);                   // p 指向 a1 中的 vector
p.operator++(0);                    // 调用后置版本的 operator++
p.operator++();                     // 调用前置版本的 operator++

class StrBlobPtr {
public:
    std::string& operator*() const
    { auto p = check(curr, "decrement past end"); 
    return (*p)[curr]; }
    std::string* operator->() const
    {
        // 将实际工作委托给解引用运算符
        return & this->operator*();
    }
};

StrBlob a1 = {"hi", "bye", "now"};
StrBlobPtr p(a1);                   // p 指向 a1 中的 vector
*p = "okay";                        // 给 a1 的首元素赋值
cout << p->size() << endl;          // 打印 4，这是 a1 首元素的大小
cout << (*p).size() << endl;        // 等价于 p->size()

struct absInt {
    int operator()(int val) const {
        return val < 0 ? -val : val;
    }
};

int i = -42;
absInt absObj;          // 含有函数调用符的对象
int ui = absObj(i);     // 将 i 传递给 absObj.operator()

class PrintString {
public:
    PrintString(ostream &o = cout, char c = ' '):
        os(o), sep(c) { }
    void operator()(const string &s) const { os << s << sep; }
private:
    ostream &os;       // 用于写入的目的流
    char sep;          // 用于将不同输出隔开的字符
};

PrintString printer;            // 使用默认值，打印到 cout
printer(s);                     // 在 cout 中打印 s，后面跟一个空格
PrintString errors(cerr, '\n');
errors(s);                      // 在 cerr 中打印 s，后面跟一个换行符

for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));

// 根据单词的长度对其进行排序，对于长度相同的单词按照字母表顺序排序
stable_sort(words.begin(), words.end(),
            [](const string &a, const string &b)
              { return a.size() < b.size(); });

// 获得第一个指向满足条件元素的迭代器，该元素满足 size() is >= sz
auto wc = find_if(words.begin(), words.end(),
                  [sz](const string &a)
                        { return a.size() >= sz; });

// 传入一个临时的函数对象用于执行两个 string 对象的 > 比较运算
sort(svec.begin(), svec.end(), greater<string>());

vector<string *> nameTable;         // 指针的 vector
// 错误：nameTable 中的指针彼此之间没有关系，所以 < 将产生未定义的行为
sort(nameTable.begin(), nameTable.end(),
     [](string *a, string *b){ return a < b; });
// 正确：标准库规定指针的 less 是定义良好的
sort(nameTable.begin(), nameTable.end(), less<string*>());

// 普通函数
int add(int i, int j) { return i + j; }
// lambda, 其产生一个未命名的函数对象类
auto mod = [](int i, int j) { return i % j; }
// 函数对象类
struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
};
// 构建从yunsuanfu9到函数指针的映射关系，其中函数接收两个 int、返回一个 int
map<string, int(*)(int, int)> binops;

// 正确：add 是一个指向正确类型函数的指针
binops.insert({"+", add});          // {"+", add} 是一个 pair

binops.insert({"%", mod});          // 错误：mod 不是一个函数指针

function<int(int, int)>

function<int(int, int)> f1 = add;       // 函数指针
function<int(int, int)> f2 = divide();  // 函数指针的对象
function<int(int, int)> f3 = [](int i, int j)   // lambda
                             { return i * j; };
cout << f1(4, 2) << endl;
cout << f2(4, 2) << endl;
cout << f3(4, 2) << endl;

// 列举了可调用对象与二元运算符对应关系的表格
// 所有可调用对象都必须接受两个 int、返回一个 int
// 其中的元素可以是函数指针、函数对象或者 lambda
map<string, function<int(int, int)>> binops;

map<string, function<int(int, int)>> binops = {
    {"+", add},                                 // 函数指针
    {"-", std::minus<int>()},                   // 标准库函数对象
    {"/", divide()},                            // 用户定义的函数对象
    {"*", [](int i, int j){ return i * j; }};   // 未命名的 lambda
    {"%", mod} };                               // 命名了的 lambda 对象

binops["+"](10, 5);                             // 调用 add(10, 5)
binops["-"](10, 5);                             // 调用 minus<int> 对象的调用运算符
binops["/"](10, 5);                             // 使用 divide 对象的调用运算符
binops["*"](10, 5);                             // 调用 lambda 函数对象
binops["%"](10, 5);                             // 调用 lambda 函数对象

class SmallInt {
public:
    SmallInt(int i = 0): val(i)
    {
        if (i < 0 || i > 255) 
            throw std::out_of_range("Bad SmallInt value");
    }
    operator int() const { return val; }
private:
    std::size_t val;
};

SmallInt si;
si = 4;     // 首先将 4 隐式转换成 SmallInt，然后调用 SmallInt::operator==
si + 3;     // 首先将 si 隐式地转换成 int，然后执行整数的加法

class SmallInt {
public:
    // 编译器不会自动执行这一类型转换
    explicit operator int() const { return val; }
};

// 最好不要在两个雷之间构建相同的类型转换
struct B;
struct A {
    A() = default;
    A(const B&);            // 把一个 B 转换成 A
    // 其他数据成员
};
struct B {
    operator A() const;     // 也是把一个 B 转换成 A
    // 其他数据成员
};
A f(const A&);
B b;
A a = f(b);     // 二义性错误：含义是 f(B::operator A()) 
                // 还是 f(A::A(const B&))？

struct A {
    A(int = 0);     // 最好不要创建两个转换源都是算数类型的类型转换
    A(double);
    operator int() const;   // 最好不要创建两个转换对象都是算数类型的类型转换
    operator double() const;
};
void f2(long double);
A a;
f2(a);      // 二义性错误：含义是 f(A::operator int())
            // 还是 f(A::operator double())？
long lg;
A a2(lg);   // 二义性错误：含义是 A::A(int) 还是 A::A(double)？

short s = 42;
// 把 short 提升到 int 优于把 short 转换成 double
A a3(s);    // 使用 A::A(int)

struct C {
    C(int);
    // 其他成员
};
struct D {
    D(int);
};
void mainip(const C&);
void mianip(const D&);
mainip(10);     // 二义性错误：含义是 mainip(C(10)) 还是 mainip(D(10))

struct E {
    E(double);
    // 其他成员
};
void mainip2(const C&);
void mainip2(const E&);
// 二义性错误：两个不同的用户定义的类型转换都能用在此处
mainip2(10);        // 含义是 mainip2(C(10)) 还是 mainip2(E(double(10)))

class SmallInt {
    friend 
    SmallInt operator+(const SmallInt&, const SmallInt&);
public:
    SmallInt(int = 0);                      // 转换源为 int 的类型转换
    operator int() const { return val; }    // 转换目标为 int 的类型转换
private:
    std::size_t val;
};

SmallInt s1, s2;
SmallInt s3 = s1 + s2;  // 使用重载的 operator+
int i = s3 + 0;         // 二义性错误