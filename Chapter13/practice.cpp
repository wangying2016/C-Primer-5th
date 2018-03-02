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

class Message {
    friend class Folder;
public:
    // folders ����ʽ��ʼ��Ϊ�ռ���
    explicit Message(const std::string &str = ""):
        contents(str) { }
    // �������Ƴ�Ա����������ָ�� Message ��ָ��
    Message(const Message&);            // �������캯��
    Message& operator=(const Message&); // ������ֵ�����
    ~Message();                         // ��������
    // �Ӹ��� Folder ���������/ɾ���� Message
    void save(Folder&);
    void remove(Folder&);
private:
    std::string contents;       // ʵ����Ϣ�ı�
    std::set<Folder*> folders;  // ������ Message �� Folder
    // �������캯����������ֵ�����������������ʹ�õĹ��ߺ���
    void add_to_Folders(const Message&);
    // �� folders �е�ÿ�� Folder ��ɾ���� Message
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

// ���� Message ��ӵ�ָ�� m �� Folder ��
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

// �Ӷ�Ӧ�� Folder ��ɾ���� Message
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
    // ͨ����ɾ��ָ���ٲ��������������Ը�ֵ���
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_toFolders(rhs);
    return *this;
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap; 
    // ��ÿ����Ϣ��ָ�������ԭ�������� Folder ��ɾ��
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    // ���� contents �� Folder ָ�� set
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    // ��ÿ�� Message ��ָ����ӵ����ģ��£�Folder ��
    for (auto f : lhs.folders)
        f->addMsg(&lhs)
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}
