class Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
public:
    Sales_data() = default;
    // Sales_data(const std::string &s) : bookNo(s) { }
    explicit Sales_data(std::string s = " "): bookNo(s) { }
    Sales_data(const std::string &s, unsinged n, double p) :
               bookNo(s), unites_sold(n), revenue(p*n) { }
    explicit Sales_data(std::istream &);
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
private:
    double avg_price() const 
        { return unites_sold ? revenue/unites_sold : 0; }
    std::string bookNo;
    unsigned unites_sold = 0;
    double revenue = 0.0;
};

Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Saleds_data&);

std::string Sales_data::isbn(const Sales_data *const this)
{ return this->isbn; }

double Sales_data::avg_price() const {
    if (unites_sold) 
        return revenue/unites_sold;
    else 
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data &rhs) 
{
    unites_sold += rhs.unites_sold;
    revenue += rhs.revenue;
    return *this;
}

istream &read(istream &is, Sales_data &item) 
{
    double price = 0;
    is >> item.bookNo >> item.unites_sold >> price;
    item.revenue = price * item.unites_sold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item) 
{
    os << item.isbn() << " " << item.unites_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) 
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

Sales_data::Sales_data(std::istream &is)
{
    read(is, *this);
}

class Screen {
    // friend class Window_mgr;
    friend void Window_mgr::clear(ScreenIndex);
public:
    // typedef std::string::size_type pos;
    using pos = std::string::size_type;
    Screen() = default;
    Screen(pos ht, pos wd, char c) : height(ht), width(wd),
    contens(ht * wd, c) { }
    char get() const 
        { return contents[cursor]; }
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);
    void some_member() const;
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os)
                { do_display(os); return *this; }
    const Screen &display(std::ostream &os) const
                { do_display(os); return *this; }
private:
    void do_display(std::ostream &os) const { os << contents; }
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_ctr;
};

inline
Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}

void Screen::some_member() const
{
    ++access_ctr;
}

class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
    ScreenIndex addScreen(const Screen&);
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex
Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}

class Link_screen {
    Screen window;
    Link_screen *next;
    Link_screen *prev;
};

struct X {
    friend void f();
    X() { f(); }
    void g();
    void h();
};

// wrong: f was not declared.
void X::g() { return f(); }
void f();
// right: f was declared.
void X::h() { return f(); }

typedef double Money;
string bal;
class Account {
public:
    Money balance() { return bal; }
private:
    Money bal;
};

class ConstRef {
public:
    ConstRef(int ii);
private:
    int i;
    const int ci;
    int &ri;
};

ConstRef::ConstRef(int ii): i(ii), ci(ii), ri(i) { }

class X {
    int i;
    int j;
public:
    // Undefined: i will be initialized before j.
    X(int val): j(val), i(j) { }
};

// delegating constructor
class Sales_data {
public:
    Sales_data(std::string s, unsigned cnt, double price):
            bookNo(s), unites_sold(cnt), revenue(cnt*price) { }
    Sales_data(): Sales_data("", 0, 0) { }
    Sales_data(std::string s): Sales_data(s, 0, 0) { }
    Sales_data(std::istream &is): Sales_data() 
                                        { read(is, *this); }  
};

struct Data {
    int ival;
    string s;
};

Data val1 = { 0, "Anna" };

class Debug {
public:
    constexpr Debug(bool b = true): hw(b), io(b), other(b) { }
    constexpr Debug(bool h, bool i, bool o):
                        hw(h), io(i), other(o) { }
    constexpr bool any() { return hw || io || other; }
    void set_io(bool b) { io = b; }
    void set_hw(bool b) { hw = b; }
    void set_other(bool b) { hw = b; }
private:
    bool hw;
    bool io;
    bool other;
};

constexpr Debug io_sub(false, true, false);
if (io_sub.any()) 
    cerr << "print appropriate error messages" << endl;
constexpr Debug prod(false);
if (prod.any())
    cerr << "print an error messsage" << endl;

class Account {
public:
    void calculate() { amount += amount * interstRate; }
    static double rate() { return interstRate; }
    static void rate(double);
private:
    std::string owner;
    double amount;
    static double interstRate;
    static double initRate();
    static constexpr int period = 30;
    double daily_tbl[period];
};

void Account::rate(double newRate)
{
    interstRate = newRate;
}

double Account::interstRate = initRate();

class Screen {
public:
    Screen& clear(char = bkground);
private:
    static const char bkground;
};