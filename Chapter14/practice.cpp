// ������� Sales_item �ĺ�
cout << item1 + item2;

// ������� Sales_data �ĺ�
print(cout, add(data1, data2));

// һ���ǳ�Ա����������ĵȼ۵���
data1 + data2;              // ��ͨ�ı��ʽ
operator+(data1, data2);    // �ȼ۵ĺ�������

data1 += data2;             // ���ڡ����á��ı��ʽ
data1.operator+=(data2);    // �Գ�Ա����������ĵȼ۵���

string s = "world";
string t = s + "!";     // ��ȷ�������ܰ�һ�� const char* �ӵ�һ�� string ������
string u = "hi" + s;    // ��� + �� string �ĳ�Ա�����������

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
    double price;   // ����Ҫ��ʼ������Ϊ���ǽ��ȶ������ݵ� price��֮���ʹ����
    is >> item.bookNo >> item.unites_sold >> price;
    if (is)         // ��������Ƿ�ɹ�
        item.revenue = item.unites_sold * price;
    else 
        item = Sales_data();    // ����ʧ�ܣ����󱻸���Ĭ�ϵ�״̬
    return is;
}

// ������������ָ��ͬһ����
Sales_data
operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;           // �� lhs �����ݳ�Ա������ sum
    sum += rhs;                     // �� rhs �ӵ� sum ��
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
    // alloc_n_copy �����ڴ�ռ䲢�Ӹ�����Χ�ڿ���Ԫ��
    auto data = alloc_n_copy(il.begin(), il.end());
    // ���ٶ����е�Ԫ�ز��ͷ��ڴ�ռ�
    free();
    // �������ݳ�Աʹ��ָ���¿ռ�
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

// ��Ϊ��Ա�Ķ�Ԫ�����������������󶨵���ʽ�� this ָ��
// �ٶ����������ʾ����ͬһ����
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
    std::string *elements;  // ָ��������Ԫ�ص�ָ��
};
// ���� svec ��һ�� StrVec ����
const StrVec cvec = svec;               // �� svec ��Ԫ�ؿ����� cvec ��
// ��� svec �к���Ԫ�أ��Ե�һ��Ԫ������ string �� empty ����
if (svec.size() && svec[0].empty()) {
    svec[0] = "zero";                   // ��ȷ���±���������� string ������
    cvec[0] = "Zip";                    // ���󣺶� cvec ȡ�±귵�ص��ǳ�������
}

class StrBlobPtr {
public:
    // �����͵ݼ������
    StrBlobPtr& operator+();            // ǰ�������
    StrBlobPtr& operator--();           
};

// ǰ�ð汾�����ص���/�ݼ����������
StrBlobPtr& StrBlobPtr::operator++()
{
    // ��� curr �Ѿ�ָ����������β��λ�ã����޷�������
    check(curr, "increment past end of StrBlobPtr");
    // �� curr �ڵ�ǰ״̬����ǰ�ƶ�һ��Ԫ��
    ++curr;
    return *this;
}
StrBlobPtr& StrBlobPtr::operator--()
{
    // ��� curr ��0��������ݼ���������һ����Ч�±�
    --curr;         // �� curr �ڵ�ǰ״̬������ƶ�һ��Ԫ��
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

class StrBlobPtr {
public:
    // �����͵ݼ������
    StrBlobPtr operator++(int);         // ���������
    StrBlobPtr operator--(int);
};

// ���ð汾������/�ݼ������ֵ���Ƿ���ԭֵ
StrBlobPtr StrBlobPtr::operator++(int)
{
    // �˴���������Ч�ԣ�����ǰ�õ�������ʱ����Ҫ���
    StrBlobPtr ret = *this;     // ��¼��ǰ��ֵ
    ++*this;                    // ��ǰ�ƶ�һ��Ԫ�أ�ǰ��++��Ҫ����������Ч��
    return ret;                 // ����֮ǰ��¼��״̬
}
StrBlobPtr StrBlobPtr::operator--(int)
{
    // �˴���������Ч�ԣ�����ǰ�õݼ�����ʱ����Ҫ���
    StrBlobPtr ret = *this;     // ��¼��ǰ��ֵ
    --*this;                    // ����ƶ�һ��Ԫ�أ�ǰ��--��Ҫ���ݼ�����Ч��
    return ret;                 // ����֮ǰ��¼��״̬
}

class StrBlobPtr {
public:
    // �����͵ݼ������
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
};

// ǰ�ð汾�����ص���/�ݼ����������
StrBlobPtr& StrBlobPtr::operator++()
{
    // ��� curr �Ѿ�ָ����������β��λ�ã����޷�������
    check(curr, "increment past end of StrBlobPtr");
    ++curr;         // �� curr �ڵ�ǰ״̬����ǰ�ƶ�һ��Ԫ��
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
    // ��� curr ��0��������ݼ���������һ����Ч�±�
    --curr;         // �� curr �ڵ�ǰ״̬������ƶ�һ��Ԫ��
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

class StrBlobPtr {
public:
    // �����͵ݼ������
    StrBlobPtr operator++(int);         // ���������
    StrBlobPtr operator--(int);
};

// ���ð汾������/�ݼ������ֵ���Ƿ���ԭֵ
StrBlobPtr StrBlobPtr::operator++(int)
{
    // �˴���������Ч�ԣ�����ǰ�õ�������ʱ����Ҫ���
    StrBlobPtr ret = *this; // ��¼��ǰ��ֵ
    ++*this;                // ��ǰ�ƶ�һ��Ԫ�أ�ǰ��++��Ҫ����������Ч��
    return ret;             // ����֮ǰ��¼��״̬
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    // �˴���������Ч�ԣ�����ǰ�õݼ�����ʱ����Ҫ���
    StrBlobPtr ret = *this;         // ��¼��ǰ��ֵ
    --*this;                        // ����ƶ�һ��Ԫ�أ�ǰ��--��Ҫ���ݼ�����Ч��
    return ret;                     // ����֮ǰ��¼��״̬
}

StrBlobPtr p(a1);                   // p ָ�� a1 �е� vector
p.operator++(0);                    // ���ú��ð汾�� operator++
p.operator++();                     // ����ǰ�ð汾�� operator++

class StrBlobPtr {
public:
    std::string& operator*() const
    { auto p = check(curr, "decrement past end"); 
    return (*p)[curr]; }
    std::string* operator->() const
    {
        // ��ʵ�ʹ���ί�и������������
        return & this->operator*();
    }
};

StrBlob a1 = {"hi", "bye", "now"};
StrBlobPtr p(a1);                   // p ָ�� a1 �е� vector
*p = "okay";                        // �� a1 ����Ԫ�ظ�ֵ
cout << p->size() << endl;          // ��ӡ 4������ a1 ��Ԫ�صĴ�С
cout << (*p).size() << endl;        // �ȼ��� p->size()

struct absInt {
    int operator()(int val) const {
        return val < 0 ? -val : val;
    }
};

int i = -42;
absInt absObj;          // ���к������÷��Ķ���
int ui = absObj(i);     // �� i ���ݸ� absObj.operator()

class PrintString {
public:
    PrintString(ostream &o = cout, char c = ' '):
        os(o), sep(c) { }
    void operator()(const string &s) const { os << s << sep; }
private:
    ostream &os;       // ����д���Ŀ����
    char sep;          // ���ڽ���ͬ����������ַ�
};

PrintString printer;            // ʹ��Ĭ��ֵ����ӡ�� cout
printer(s);                     // �� cout �д�ӡ s�������һ���ո�
PrintString errors(cerr, '\n');
errors(s);                      // �� cerr �д�ӡ s�������һ�����з�

for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));

// ���ݵ��ʵĳ��ȶ���������򣬶��ڳ�����ͬ�ĵ��ʰ�����ĸ��˳������
stable_sort(words.begin(), words.end(),
            [](const string &a, const string &b)
              { return a.size() < b.size(); });

// ��õ�һ��ָ����������Ԫ�صĵ���������Ԫ������ size() is >= sz
auto wc = find_if(words.begin(), words.end(),
                  [sz](const string &a)
                        { return a.size() >= sz; });

// ����һ����ʱ�ĺ�����������ִ������ string ����� > �Ƚ�����
sort(svec.begin(), svec.end(), greater<string>());

vector<string *> nameTable;         // ָ��� vector
// ����nameTable �е�ָ��˴�֮��û�й�ϵ������ < ������δ�������Ϊ
sort(nameTable.begin(), nameTable.end(),
     [](string *a, string *b){ return a < b; });
// ��ȷ����׼��涨ָ��� less �Ƕ������õ�
sort(nameTable.begin(), nameTable.end(), less<string*>());

// ��ͨ����
int add(int i, int j) { return i + j; }
// lambda, �����һ��δ�����ĺ���������
auto mod = [](int i, int j) { return i % j; }
// ����������
struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
};
// ������yunsuanfu9������ָ���ӳ���ϵ�����к����������� int������һ�� int
map<string, int(*)(int, int)> binops;

// ��ȷ��add ��һ��ָ����ȷ���ͺ�����ָ��
binops.insert({"+", add});          // {"+", add} ��һ�� pair

binops.insert({"%", mod});          // ����mod ����һ������ָ��

function<int(int, int)>

function<int(int, int)> f1 = add;       // ����ָ��
function<int(int, int)> f2 = divide();  // ����ָ��Ķ���
function<int(int, int)> f3 = [](int i, int j)   // lambda
                             { return i * j; };
cout << f1(4, 2) << endl;
cout << f2(4, 2) << endl;
cout << f3(4, 2) << endl;

// �о��˿ɵ��ö������Ԫ�������Ӧ��ϵ�ı��
// ���пɵ��ö��󶼱���������� int������һ�� int
// ���е�Ԫ�ؿ����Ǻ���ָ�롢����������� lambda
map<string, function<int(int, int)>> binops;

map<string, function<int(int, int)>> binops = {
    {"+", add},                                 // ����ָ��
    {"-", std::minus<int>()},                   // ��׼�⺯������
    {"/", divide()},                            // �û�����ĺ�������
    {"*", [](int i, int j){ return i * j; }};   // δ������ lambda
    {"%", mod} };                               // �����˵� lambda ����

binops["+"](10, 5);                             // ���� add(10, 5)
binops["-"](10, 5);                             // ���� minus<int> ����ĵ��������
binops["/"](10, 5);                             // ʹ�� divide ����ĵ��������
binops["*"](10, 5);                             // ���� lambda ��������
binops["%"](10, 5);                             // ���� lambda ��������

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
si = 4;     // ���Ƚ� 4 ��ʽת���� SmallInt��Ȼ����� SmallInt::operator==
si + 3;     // ���Ƚ� si ��ʽ��ת���� int��Ȼ��ִ�������ļӷ�

class SmallInt {
public:
    // �����������Զ�ִ����һ����ת��
    explicit operator int() const { return val; }
};

// ��ò�Ҫ��������֮�乹����ͬ������ת��
struct B;
struct A {
    A() = default;
    A(const B&);            // ��һ�� B ת���� A
    // �������ݳ�Ա
};
struct B {
    operator A() const;     // Ҳ�ǰ�һ�� B ת���� A
    // �������ݳ�Ա
};
A f(const A&);
B b;
A a = f(b);     // �����Դ��󣺺����� f(B::operator A()) 
                // ���� f(A::A(const B&))��

struct A {
    A(int = 0);     // ��ò�Ҫ��������ת��Դ�����������͵�����ת��
    A(double);
    operator int() const;   // ��ò�Ҫ��������ת���������������͵�����ת��
    operator double() const;
};
void f2(long double);
A a;
f2(a);      // �����Դ��󣺺����� f(A::operator int())
            // ���� f(A::operator double())��
long lg;
A a2(lg);   // �����Դ��󣺺����� A::A(int) ���� A::A(double)��

short s = 42;
// �� short ������ int ���ڰ� short ת���� double
A a3(s);    // ʹ�� A::A(int)

struct C {
    C(int);
    // ������Ա
};
struct D {
    D(int);
};
void mainip(const C&);
void mianip(const D&);
mainip(10);     // �����Դ��󣺺����� mainip(C(10)) ���� mainip(D(10))

struct E {
    E(double);
    // ������Ա
};
void mainip2(const C&);
void mainip2(const E&);
// �����Դ���������ͬ���û����������ת���������ڴ˴�
mainip2(10);        // ������ mainip2(C(10)) ���� mainip2(E(double(10)))

class SmallInt {
    friend 
    SmallInt operator+(const SmallInt&, const SmallInt&);
public:
    SmallInt(int = 0);                      // ת��ԴΪ int ������ת��
    operator int() const { return val; }    // ת��Ŀ��Ϊ int ������ת��
private:
    std::size_t val;
};

SmallInt s1, s2;
SmallInt s3 = s1 + s2;  // ʹ�����ص� operator+
int i = s3 + 0;         // �����Դ���