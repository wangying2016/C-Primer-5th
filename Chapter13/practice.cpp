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

// �ȼ��ںϳɿ�����ֵ�����
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
    NoCopy() = default; // ʹ�úϳɵ�Ĭ�Ϲ��캯��
    NoCopy(const NoCopy&) = delete;               // ��ֹ����
    NoCopy &operator=(const NoCopy&) = delete;    // ��ֹ��ֵ
    ~NoCopy() = default;// ʹ�úϳɵ���������
};

// �û����Զ�������͵Ķ��󣬵����޷���������
class PrivateCopy {
    PrivateCopy(const PrivateCopy&);
    PrivateCopy& operator=(const PriavteCopy&);
public:
    PrivateCopy() = default;
    ~PrivateCopy();
};

// ��ֵ�汾�� HasPtr
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) { }
    // �� ps ָ��� string��ÿ�� HasPtr �������Լ��Ŀ���
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
    // ���캯�������µ� string ���µļ�����������������Ϊ 1
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    // �������캯�����������������ݳ�Ա��������������
    HasPtr(const HasPtr &p):
        ps(p.ps), i(p.i), use(p.use) { ++*use; }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use; // ������¼�ж��ٸ������� *ps �ĳ�Ա
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