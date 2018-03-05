class Quote {
public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
};

// Bulk_quote 继承了 Quote
class Bulk_quote : public Quote {
public:
    double net_price(std::size_t) const override;
};

// 计算并打印销售给定数量的某种书籍所得的费用
double print_total(ostream &os,
                   const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

class Quote {
public:
    Quote() = default; 
    Quote(const std::string &book, double sales_price): 
                        bookNo(book), price(sales_price) { }
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const
                { return n * price; }
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &, double, std::size_t, double);
    double net_price(std::size_t) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

Bulk_quote(const std::string &book, double p,
           std::size_t qty, double disc) :
           Quote(book, p), min_qty(qty), discount(disc) { }

// 如果达到了购买书籍的某个最低限量值，就可以享受折扣价格了
double Bulk_quote::net_price(size_t cnt) const 
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else 
        return cnt * price;
}

class Base {
public:
    static void statmem();
};

class Derived : public Base {
    void f(const Derived&);
};

void Derived::f(const Derived &derived_obj)
{
    Base::statmem();
    Derived::statmem();
    derived_obj.statmem();
    statmem();
}

class NoDerived final { }
class Base { }
class Last final : Base { }

// 强行调用基类重定义的函数版本而不管 baseP 的动态类型到底是什么
double undiscounted = baseP->Quote::net_price(42);

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
               std::size_t qty, double disc):
               Quote(book, price),
               quantity(qty), discount(disc) { }
    double net_price(std::size_t) const = 0;
protected:
    std::size_t quantity = 0;
    double discount = 0;
};

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double price,
               std::size_t qty, double disc):
               Disc_quote(book, price, qty, disc) { }
    // 覆盖基类中的函数版本以实现一种新的折扣策略
    double net_price(std::size_t) const override;
};

class Base {
protected:
    int prot_mem;
};
class Sneaky : public Base {
    friend void clobber(Sneaky&);   // 能访问 Sneaky::prot_mem
    friend void clobber(Base&);     // 不能访问 Base::prot_mem
    int j;
};

class Base {
public:
    void pub_mem();
protected:
    int prot_mem;
private:
    char priv_mem;
};
struct Pub_Derv : public Base {
    // 正确：派生类能访问 protected 成员
    int f() { return prot_mem; }
    // 错误：private 成员对于派生类来说是不可访问的
    char g() { return priv_mem; }
};
struct Priv_Derv : private Base {
    // private 不影响派生类的访问权限
    int f1() const { return prot_mem; }
};

class Base {
public:
    std::size_t size() const { return n; }
protected:
    std::size_t n;
};
class Derived : private Base {
public:
    using Base::size;
protected:
    using Base::n;
};

class Base { }
// 默认 public 继承
struct D1 : Base { }
// 默认 private 继承
class D2 : Base { }

class Quote {
public:
    // 如果我们删除的是一个指向派生类对象的基类指针，则需要虚析构函数
    virtual ~Quote() = default;         // 动态绑定析构函数
};

Quote *itemP = new Quote;       // 静态类型与动态类型一致
delete itemP;                   // 调用 Quote 的析构函数
itemP = new Bulk_quote;         // 静态类型与动态类型不一致
delete itemP;                   // 调用 Bulk_quote 的析构函数

class Quote {
public:
    Quote() = default;          // 对成员依次进行默认初始化
    Quote(const Quote&) = default; // 对成员依次拷贝
    Quote(Quote&&) = default;   // 对成员依次拷贝 
    Quote& operator=(const Quote&) = default;   // 拷贝赋值
    Quote& operator=(Quote&&) = default;    // 移动赋值
    virtual ~Quote() = default; // 虚析构函数
};

class Base { };
class D : public Base {
public:
    // 拷贝基类成员
    D(const D& d) : Base(d) {}
    // 移动基类成员
    D(D&& d) : Base(std::move(d)) {}
};

D &D::operator=(const D &rhs)
{
    Base::operator=(rhs);
    return *this;
}

class D : public Base {
public:
    // Base::~Base 被自动调用运行
    ~D() {} 
};

class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote; // 继承 Disc_quote 的构造函数
    double net_price(std::size_t) const;
};

vector<sharted_ptr<Quote>> basket;
basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
basket.push_back(
    make_shared<Bulk_quote>>("0-201-54848-8", 50, 10, .25));
cout << basket.back()->net_price(15) << endl;

class Basket {
public:
    // Basket 使用合成的默认构造函数和拷贝控制成员
    void add_item(const std::shared_ptr<Quote> &sale)
        { items.insert(sale); }
    // 打印每本书的总价和购物篮中所有书的总价
    double total_receipt(std::ostream&) const;
private:
    // 该函数用于比较 shared_ptr, multiset 成员会用到它
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
    { return lhs->isbn() < rhs->isbn(); }
    // multiset 保存多个报价，按照 compare 成员排序
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*>
                    items{compare};
};

double Basket::total_receipt(ostream &os) const
{
    // 保存实时计算出的价格
    double sum = 0.0;
    // iter 指向 ISBN 相同的一批元素中的第一个
    // upper_bound 返回一个迭代器，该迭代器指向这批元素的尾后位置
    for (auto iter = items.cbegin();
              iter != items.cend();
              iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }       
    // 打印最终的价格
    os << "Total Sale: " << sum << endl;
    return sum;
}

class Quote {
public:
    // 该虚函数返回当前对象的一份动态分配的拷贝
    virtual Quote* clone() const & { return new Quote(*this); }
    virtual Quote* clone() &&
                        { return new Quote(std::move(*this)); }
};
class Bulk_quote : public Quote {
    Bulk_quote* clone() const & { return new Bulk_quote(*this); }
    Bulk_quote* clone() &&
                    { return new Bulk_quote(std::move(*this)); }
};
class Basket {
public:
    // 拷贝给定的对象
    void add_item(const Quote& sale)        
        { items.insert(std::shared_ptr<Quote>(sale.clone()); }
    void add_item(Quote&& sale)
        { items.insert(
            std::shared_ptr<Quote>(std::move(sale).clone())); }
};

// 这是一个抽象基类，具体的查询类型从中派生，所有成员都是 private 的
class Query_base {
    friend class Query;
protected:
    // 用于 eval 函数
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    // eval 返回当前 Query 匹配的 QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep 是表示查询的一个 string
    virtual std::string rep() const = 0;
};

// 这是一个管理 Query_base 继承体系的接口类
class Query {
    // 这些运算符需要访问接受 shared_ptr 的构造函数，而该函数是私有的
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);
public:
    // 构建一个新的 WordQuery
    Query(const std::string&);
    // 接口函数：调用对应的 Query_base 操作
    QueryResult eval(const TextQuery &t) const
                            { return q->eval(t); }
    std::string rep() const { return q->rep(); }
private:
    Query(std::shared_ptr<Query_base> query) : q(query) { }
    std::shared_ptr<Query_base> q;
};

std::ostream &
operator<<(std::ostream &os, const Query &query)
{
    // Query::rep 通过它的 Query_base 指针对 rep() 进行了虚调用
    return os << query.rep();
}

class WordQuery: public Query_base {
    // Query 使用 WordQuery 构造函数
    friend class Query;     
    WordQuery(const std::string &s): query_word(s) { }
    // 具体的类：WordQuery 将定义所有继承而来的纯虚函数
    QueryResult eval(const TextQuery &t) const 
                    { return t.query(query_word); }
    std::string rep() const { return query_word; }
    // 要查找的单词
    std::string query_word
};

inline 
Query::Query(const std::string &s): q(new WordQuery(s)) { }

class NotQuery: public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) { }
    // 具体的类：NotQuery 将定义所有继承而来的纯虚函数
    std::string rep() const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery&) const;
    Query query;
};
inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base)(new NotQuery(operand));
}

class BinaryQuery: public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
        lhs(l), rhs(r), opSym(s) { }
    // 抽象类：BinaryQuery 不定义 eval
    std::string rep() const { return "(" + lhs.rep() + " "
                                         + opSym + " "
                                         + rhs.rep() + ")"; }
    // 左侧和右侧运算对象                                         
    Query lhs, rhs;
    // 运算符的名字
    std::string opSym;
};

class AndQuery: public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right):
                    BinaryQuery(left, right, "&") { }
    // 具体的类：AndQuery 继承了 rep 并且定义了其他纯虚函数
    QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right):
                    BinaryQuery(left, right, "|") { }
    QueryResult eval(cosnt TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult 
OrQuery::eval(const TextQuery& text) const 
{
    // 通过 Query 成员 lhs 和 rhs 进行的虚调用
    // 调用 eval 返回每个运算对象的 QueryResult
    auto right =  rhs.eval(text), left = lhs.eval(text);
    // 将左侧运算对象的行号拷贝到结果 set 中
    auto ret_lines =
        make_shared<set<line_no>>(left.begin(), left.end());
    // 插入右侧运算对象所得的行号
    ret_liens->insert(right.begin(), right.end());
    // 返回一个新的 QueryResult，它表示 lhs 和 rhs 的并集
    return QueryResult(rep(), ret_lines, left.get_file());
}

// 返回运算对象查询结果 set 的交集
QueryResult
AndQuery::eval(const TextQuery& text) cosnt
{
    // 通过 Query 运算对象进行的虚调用，以获得运算对象的查询结果 set
    auto left = lhs.eval(text), right = rhs.eval(text);
    // 保存 left 和 right 交集的 set
    auto ret_lines = make_shared<set<line_no>>();
    // 将两个范围的交集写入一个目的迭代器中
    // 本次调用的目的迭代器向 ret 添加元素
    set_intersection(left.begin(), left.end(),
                     right.begin(), right.end(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

// 返回运算对象的结果 set 中不存在的行
QueryResult
NotQuery::eval(const TextQuery& text) const 
{
    // 通过 Query 运算对象对 eval 进行虚调用
    auto result = query.eval(text);
    // 开始时结果 set 为空
    auto ret_lines = make_shared<set<line_no>>();
    // 我们必须在运算对象出现的所有行中进行迭代
    auto beg = result.begin(), end = result.end();
    // 对于输入文件的每一行，如果改行不再 result 当中，则将其添加到 ret_lines
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        // 如果我们还没有处理完 result 的所有行
        // 检查当前行是否存在
        if (beg == end || *beg != n)
            ret_lines->insert(n);       // 如果不在 result 当中，添加这一行
        else if (beg != end)
            ++beg;                      // 否则继续获取 result 的下一行
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}
