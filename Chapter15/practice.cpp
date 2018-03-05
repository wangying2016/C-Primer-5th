class Quote {
public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
};

// Bulk_quote �̳��� Quote
class Bulk_quote : public Quote {
public:
    double net_price(std::size_t) const override;
};

// ���㲢��ӡ���۸���������ĳ���鼮���õķ���
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

// ����ﵽ�˹����鼮��ĳ���������ֵ���Ϳ��������ۿۼ۸���
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

// ǿ�е��û����ض���ĺ����汾������ baseP �Ķ�̬���͵�����ʲô
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
    // ���ǻ����еĺ����汾��ʵ��һ���µ��ۿ۲���
    double net_price(std::size_t) const override;
};

class Base {
protected:
    int prot_mem;
};
class Sneaky : public Base {
    friend void clobber(Sneaky&);   // �ܷ��� Sneaky::prot_mem
    friend void clobber(Base&);     // ���ܷ��� Base::prot_mem
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
    // ��ȷ���������ܷ��� protected ��Ա
    int f() { return prot_mem; }
    // ����private ��Ա������������˵�ǲ��ɷ��ʵ�
    char g() { return priv_mem; }
};
struct Priv_Derv : private Base {
    // private ��Ӱ��������ķ���Ȩ��
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
// Ĭ�� public �̳�
struct D1 : Base { }
// Ĭ�� private �̳�
class D2 : Base { }

class Quote {
public:
    // �������ɾ������һ��ָ�����������Ļ���ָ�룬����Ҫ����������
    virtual ~Quote() = default;         // ��̬����������
};

Quote *itemP = new Quote;       // ��̬�����붯̬����һ��
delete itemP;                   // ���� Quote ����������
itemP = new Bulk_quote;         // ��̬�����붯̬���Ͳ�һ��
delete itemP;                   // ���� Bulk_quote ����������

class Quote {
public:
    Quote() = default;          // �Գ�Ա���ν���Ĭ�ϳ�ʼ��
    Quote(const Quote&) = default; // �Գ�Ա���ο���
    Quote(Quote&&) = default;   // �Գ�Ա���ο��� 
    Quote& operator=(const Quote&) = default;   // ������ֵ
    Quote& operator=(Quote&&) = default;    // �ƶ���ֵ
    virtual ~Quote() = default; // ����������
};

class Base { };
class D : public Base {
public:
    // ���������Ա
    D(const D& d) : Base(d) {}
    // �ƶ������Ա
    D(D&& d) : Base(std::move(d)) {}
};

D &D::operator=(const D &rhs)
{
    Base::operator=(rhs);
    return *this;
}

class D : public Base {
public:
    // Base::~Base ���Զ���������
    ~D() {} 
};

class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote; // �̳� Disc_quote �Ĺ��캯��
    double net_price(std::size_t) const;
};

vector<sharted_ptr<Quote>> basket;
basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
basket.push_back(
    make_shared<Bulk_quote>>("0-201-54848-8", 50, 10, .25));
cout << basket.back()->net_price(15) << endl;

class Basket {
public:
    // Basket ʹ�úϳɵ�Ĭ�Ϲ��캯���Ϳ������Ƴ�Ա
    void add_item(const std::shared_ptr<Quote> &sale)
        { items.insert(sale); }
    // ��ӡÿ������ܼۺ͹���������������ܼ�
    double total_receipt(std::ostream&) const;
private:
    // �ú������ڱȽ� shared_ptr, multiset ��Ա���õ���
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
    { return lhs->isbn() < rhs->isbn(); }
    // multiset ���������ۣ����� compare ��Ա����
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*>
                    items{compare};
};

double Basket::total_receipt(ostream &os) const
{
    // ����ʵʱ������ļ۸�
    double sum = 0.0;
    // iter ָ�� ISBN ��ͬ��һ��Ԫ���еĵ�һ��
    // upper_bound ����һ�����������õ�����ָ������Ԫ�ص�β��λ��
    for (auto iter = items.cbegin();
              iter != items.cend();
              iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }       
    // ��ӡ���յļ۸�
    os << "Total Sale: " << sum << endl;
    return sum;
}

class Quote {
public:
    // ���麯�����ص�ǰ�����һ�ݶ�̬����Ŀ���
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
    // ���������Ķ���
    void add_item(const Quote& sale)        
        { items.insert(std::shared_ptr<Quote>(sale.clone()); }
    void add_item(Quote&& sale)
        { items.insert(
            std::shared_ptr<Quote>(std::move(sale).clone())); }
};

// ����һ��������࣬����Ĳ�ѯ���ʹ������������г�Ա���� private ��
class Query_base {
    friend class Query;
protected:
    // ���� eval ����
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    // eval ���ص�ǰ Query ƥ��� QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep �Ǳ�ʾ��ѯ��һ�� string
    virtual std::string rep() const = 0;
};

// ����һ������ Query_base �̳���ϵ�Ľӿ���
class Query {
    // ��Щ�������Ҫ���ʽ��� shared_ptr �Ĺ��캯�������ú�����˽�е�
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);
public:
    // ����һ���µ� WordQuery
    Query(const std::string&);
    // �ӿں��������ö�Ӧ�� Query_base ����
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
    // Query::rep ͨ������ Query_base ָ��� rep() �����������
    return os << query.rep();
}

class WordQuery: public Query_base {
    // Query ʹ�� WordQuery ���캯��
    friend class Query;     
    WordQuery(const std::string &s): query_word(s) { }
    // ������ࣺWordQuery ���������м̳ж����Ĵ��麯��
    QueryResult eval(const TextQuery &t) const 
                    { return t.query(query_word); }
    std::string rep() const { return query_word; }
    // Ҫ���ҵĵ���
    std::string query_word
};

inline 
Query::Query(const std::string &s): q(new WordQuery(s)) { }

class NotQuery: public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) { }
    // ������ࣺNotQuery ���������м̳ж����Ĵ��麯��
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
    // �����ࣺBinaryQuery ������ eval
    std::string rep() const { return "(" + lhs.rep() + " "
                                         + opSym + " "
                                         + rhs.rep() + ")"; }
    // �����Ҳ��������                                         
    Query lhs, rhs;
    // �����������
    std::string opSym;
};

class AndQuery: public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right):
                    BinaryQuery(left, right, "&") { }
    // ������ࣺAndQuery �̳��� rep ���Ҷ������������麯��
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
    // ͨ�� Query ��Ա lhs �� rhs ���е������
    // ���� eval ����ÿ���������� QueryResult
    auto right =  rhs.eval(text), left = lhs.eval(text);
    // ��������������кſ�������� set ��
    auto ret_lines =
        make_shared<set<line_no>>(left.begin(), left.end());
    // �����Ҳ�����������õ��к�
    ret_liens->insert(right.begin(), right.end());
    // ����һ���µ� QueryResult������ʾ lhs �� rhs �Ĳ���
    return QueryResult(rep(), ret_lines, left.get_file());
}

// ������������ѯ��� set �Ľ���
QueryResult
AndQuery::eval(const TextQuery& text) cosnt
{
    // ͨ�� Query ���������е�����ã��Ի���������Ĳ�ѯ��� set
    auto left = lhs.eval(text), right = rhs.eval(text);
    // ���� left �� right ������ set
    auto ret_lines = make_shared<set<line_no>>();
    // ��������Χ�Ľ���д��һ��Ŀ�ĵ�������
    // ���ε��õ�Ŀ�ĵ������� ret ���Ԫ��
    set_intersection(left.begin(), left.end(),
                     right.begin(), right.end(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

// �����������Ľ�� set �в����ڵ���
QueryResult
NotQuery::eval(const TextQuery& text) const 
{
    // ͨ�� Query �������� eval ���������
    auto result = query.eval(text);
    // ��ʼʱ��� set Ϊ��
    auto ret_lines = make_shared<set<line_no>>();
    // ���Ǳ��������������ֵ��������н��е���
    auto beg = result.begin(), end = result.end();
    // ���������ļ���ÿһ�У�������в��� result ���У�������ӵ� ret_lines
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        // ������ǻ�û�д����� result ��������
        // ��鵱ǰ���Ƿ����
        if (beg == end || *beg != n)
            ret_lines->insert(n);       // ������� result ���У������һ��
        else if (beg != end)
            ++beg;                      // ���������ȡ result ����һ��
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}
