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

class Message {
    friend class Folder;
public:
    // folders 被隐式初始化为空集合
    explicit Message(const std::string &str = ""):
        contents(str) { }
    // 拷贝控制成员，用来管理指向本 Message 的指针
    Message(const Message&);            // 拷贝构造函数
    Message& operator=(const Message&); // 拷贝赋值运算符
    ~Message();                         // 析构函数
    // 从给定 Folder 集合中添加/删除本 Message
    void save(Folder&);
    void remove(Folder&);
private:
    std::string contents;       // 实际消息文本
    std::set<Folder*> folders;  // 包含本 Message 的 Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    void add_to_Folders(const Message&);
    // 从 folders 中的每个 Folder 中删除本 Message
    void remove_from_Folders();
};

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.remMsg(this);
}

// 将本 Message 添加到指向 m 的 Folder 中
void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}

Message::Message(const Message &m):
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}

// 从对应的 Folder 中删除本 Message
void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
}

Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
    // 通过先删除指针再插入它们来处理自赋值情况
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_toFolders(rhs);
    return *this;
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap; 
    // 将每个消息的指针从它（原来）所在 Folder 中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    // 交换 contents 和 Folder 指针 set
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    // 将每个 Message 的指针添加到它的（新）Folder 中
    for (auto f : lhs.folders)
        f->addMsg(&lhs)
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}
