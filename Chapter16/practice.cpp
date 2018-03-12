// �������ֵ��ȣ����� 0����� v1 С���� -1����� v2 С���� 1
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

// ʵ������ int compare(const int&, const int&);
cout << compare(1, 0) << endl; // T Ϊ int
// ʵ������ int compare(const vector<int>&, const vector<int>&);
vector<int> vec1{1, 2, 3}, vec2{4, 5, 6};
cout << compare(vec1, vec2) << endl;    // T Ϊ vector<int>

// ��ȷ�� �������ͺͲ���������ͬ
template <typename T> T foo(T* p)
{
    T tmp = *p;
    // ...
    return tmp;
}

// ��ȷ����ģ������б��У�typename �� class û��ʲô��ͬ
template <typename T, class U> calc (const T&, const U&);

template<unsigned N, unsigned M>
int compare(const char (&p1)][N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

// ��ȷ��inline ˵��������ģ������б�֮��
template <typename T> inline T min(const T&, const T&);

template <typename T> class Blob {
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // ���캯��
    Blob();
    Blob(std::initializer_list<T> il);
    // Blob �е�Ԫ����Ŀ
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // ��Ӻ�ɾ��Ԫ��
    void push_back(const T &t) { data->push_back(t); }
    // �ƶ��汾
    void push_bacK(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    // Ԫ�ط���
    T& back();
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
    // �� data[i] ��Ч�����׳� msg
    void check(size_type i, const std::string &msg) const;
};

// �� Blob<int>
Blob<int> ia;
// �� 5 ��Ԫ�ص� Blob<int>
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
    // ��� i ̫��check ���׳��쳣����ֹ����һ�������ڵ�Ԫ��
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

// ���ã�����/�ݼ����󵫷���ԭֵ
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    // �˴������飻����ǰ�õ���ʱ����м��
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

// ǰ���������� Blob ��������Ԫ����Ҫ��
template <typename> class BlobPtr;
template <typename> class Blob;     // �����==�еĲ�������Ҫ��
template <typename T>
    bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> class Blob {
    // ÿ�� Blob ʵ��������Ȩ����������ͬ����ʵ������ BlobPtr ����������
    friend class BlobPtr<T>;
    friend bool operator==<T>
            (const Blob<T>&, const Blob<T>&);
};

// ǰ���������ٽ�ģ���һ���ض�ʵ������Ϊ��ԪʱҪ�õ�
template <typename T> class Pal;
class C {
    // ���� C ʵ������ pal �� C ��һ����Ԫ
    friend class Pla<C>;
    // Pal2 ������ʵ������ C ����Ԫ
    template <typename T> friend class Pal2;
};
template <typename T> class C2 {
    // C2 ��ÿ��ʵ������ͬʵ������ Pal ����Ϊ��Ԫ
    friend class Pal<T>;
    // Pal2 ������ʵ������ C2 ��ÿ��ʵ������Ԫ
    template <typename X> friend class Pal2;
    // Pal3 ��һ����ģ���࣬���� C2 ����ʵ������Ԫ
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

// ���岢��ʼ�� ctr
template <typename T>
size_t Foo<T>::ctr = 0;

template <typename Foo> Foo calc(const Foo& a, const Foo& b)
{
    // tmp ������������ͷ�������һ��
    Foo tmp = a;
    // ...
    // �������ͺͲ�������һ��
    return tmp;
}

typedef double A;
template <typename A, typename B> void f(A a, B b)
{
    A tmp = a;
}

// ������������ compare �� Blob
template <typename T> int compare(const T&, const T&);
template <typename T> class Blob;
// 3 �� calc ��ָ����ͬ�ĺ���ģ��
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

// compare ��һ��Ĭ��ģ��ʵ�� less<T> ��һ��Ĭ�Ϻ���ʵ�� F()
template <typename T, typename F = less<T>>
int compare(const T &v1, const T &v2, F f = F())
{
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}

// T Ĭ��Ϊ int
template <class T = int> class Numbers {
public:
    Numbers(T v = 0): val(v) { }
private:
    T val;
};
Numbers<long double> lots_of_precision;
// ��<>��ʾ����ϣ��ʹ��Ĭ������
Numbers<> average_precision;

// ���������࣬�Ը���ָ��ִ�� delete
class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr): os(s) { }
    // ���κκ���ģ����ͬ��T �������ɱ������ƶ�
    template <typename T> void operator()(T *p) const 
        { os << "deleting unique_ptr" << std::endl; delete p; }
private:
    std::ostream &os;
};

template <typename T> class Blob {
    template <typename It> Blob(It b, It e);
    // ...
};

template <typename T>       // ������Ͳ���
template <typename It>      // ���캯�������Ͳ���
    Blob<T>::Blob(It b, It e):
    data(std::make_shared<std::vector>>(b, e)) { }

// ʵ���������붨��
extern template class Blob<string>;         // ����
template int compare(const int&, const int&);   // ����

// ʵ�����Ϳ��Բ�ͬ�����������
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

// �������޷��ƶ� T1����δ�����ں��������б���
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);

// T1 ����ʾָ���ģ�T2 �� T3 �ǴӺ���ʵ�������ƶ϶�����
auto val3 = sum<long long>(i, lng); // long long sum(int, long)

// β�÷������������ڲ����б�֮��������������
template <typename It>
auto fcn(It beg, It end) -> decytype(*beg)
{
    // ��������
    return *beg; // ����������һ��Ԫ�ص�����
}

remove_reference<decltype(*beg)>::type

// Ϊ������ģ������ĳ�Ա�������� typename
template <typename It>
auto fcn2(It beg, It end) ->
    typename remove_reference<decltype(*beg)>::type
{
    // ��������
    return *beg;    // ����������һ��Ԫ�صĿ���
}

template <typename T> int compare(const T&, const T&);
// pf1 ָ��ʵ�� int compare(const int&, const int &)
int (*pf1)(const int&, const int&) = compare;

// ��ȷ����ʾָ��ʵ�����ĸ� compare �汾
func(compare<int>);     // ���� compare(const int&, const int&)

template <typename T> void f1(T&);  // ʵ�α�����һ����ֵ

template <typename T> void f2(const T&);    // ���Խ���һ����ֵ
// f2 �еĲ����� const &; ʵ���е� const ���޹ص�
// ��ÿ�������У�f2 �ĺ������������ƶ�Ϊ const int&

template <typename T> void f3(T&&);

template <typename T> void f(T&&);          // �󶨵��� const ��ֵ
template <typename T> void f(const T&);     // ��ֵ�� const ��ֵ

// �ڷ������ͺ�����ת����ҲҪ�õ� typename
// remove_reference 
template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
    return static_cast<typename remove_reference<T>::type&&>(t);
}

// ����һ���ɵ��ö�����������������ģ��
// �ԡ���ת���Ĳ������ø����Ŀɵ��ö���
// flip1 ��һ����������ʵ�֣����� const �����ö�ʧ��
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

// ��ӡ�κ����ǲ��ܴ��������
template <typename T> string debug_rep(const T &t)
{
    ostringstream ret;
    ret << t;   // ʹ�� T ������������ӡ t ��һ����ʾ��ʽ
    return ret.str(); // ���� ret �󶨵� string ��һ������
}

// ��ӡָ���ֵ�����ָ��ָ��Ķ���
// ע�⣺�˺����������� char*
template <typename T> string debug_rep(T *p)
{
    ostreamstream ret;
    ret << "pointer:" << p;     // ��ӡָ�뱾���ֵ
    if (p)
        ret << " " << debug_rep(*p);    // ��ӡ p ָ���ֵ
    else 
        ret << " null pointer";     // ��ָ�� p Ϊ��
    return ret.str();           // ���� ret �󶨵� string ��һ������
}

// ��ӡ˫���Ű�Χ�� string
string debug_rep(const string &s)
{
    return '"' + '"';
}

string s("hi");
cout << debug_rep(s) << endl;

// ���ַ�ָ��ת��Ϊ string�������� string �汾�� debug_reg
string debug_rep(char *p)
{
    return debug_rep(string(p));
}
string debug_rep(const char *p)
{
    return debug_rep(string(p));
}