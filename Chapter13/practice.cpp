// Copy constructor.
class Foo {
public:
    Foo();              // default constructor
    Foo(const Foo&);    // copy constructor
    // ...
};

class Sales_data {
public:
    Sales_data(const Sales_data&);
private:
    std::string bookNo;
    int unites_sold = 0;
    double revenue = 0.0;
};

Sales_data::Sales_data(const Sales_data &orig):
    bookNo(orig.bookNo),
    unites_sold(orig.unites_sold),
    revenue(orig.revenue)
    { }


Sales_data trans, accum;
trans = accum; 

// Copy-assigment operator
class Foo {
public:
    Foo(const Foo&);
    Foo& operator=(const Foo&);
    // ...
};

// 等价于合成拷贝赋值运算符
Sales_data&
Sales_data::operator=(const Sales_data &rhs)
{
    bookNo = rhs.bookNo;
    unites_sold = rhs.unites_sold;
    revenue = rhs.revenue;
    return *this;
}

// Destructor.
class Foo {
public:
    ~Foo();
    // ...
};

{ 
    Sales_data *p = new Sales_data;
    auto p2 = make_shared<Sales_data>();
    Sales_data item(*p);
    vector<Sales_data> vec;
    vec.push_back(*p2);
    delete p;
}

class Sales_data {
public:
    ~Sales_data() { }
};

class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const Sales_data&) = default;
    Sales_data& operator=(const Sales_data&);
    ~Sales_data() = default;
};
Sales_data& Sales_data::operator=(const Sales_data&) = default;

struct NoCopy {
    NoCopy() = default; // 使用合成的默认构造函数
    NoCopy(const NoCopy&) = delete;               // 阻止拷贝
    NoCopy &operator=(const NoCopy&) = delete;    // 阻止赋值
    ~NoCopy() = default;// 使用合成的析构函数
};

// 用户可以定义此类型的对象，但是无法拷贝它们
class PrivateCopy {
    PrivateCopy(const PrivateCopy&);
    PrivateCopy& operator=(const PriavteCopy&);
public:
    PrivateCopy() = default;
    ~PrivateCopy();
};

// 类值版本的 HasPtr
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) { }
    // 对 ps 指向的 string，每个 HasPtr 对象都有自己的拷贝
    HasPtr(const HasPtr &p):
        ps(new std::string(*p.ps)), i(p.i) { }
    HasPtr& operator=(const HasPtr &);
    ~HasPtr() { delete ps; }
private:
    std::string *ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}

class HasPtr {
public:
    // 构造函数分配新的 string 和新的计数器，将计数器置为 1
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
    HasPtr(const HasPtr &p):
        ps(p.ps), i(p.i), use(p.use) { ++*use; }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use; // 用来记录有多少个对象共享 *ps 的成员
};

HasPtr::~HasPtr()
{
    if (--*use == 0) {
        delete ps;
        delete use;
    }
}

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    ++*rhs.use;
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
};

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

HasPtr& HasPtr::operator=(HasPtr rhs)
{
    swap(*this, rhs);
    return *this;
}