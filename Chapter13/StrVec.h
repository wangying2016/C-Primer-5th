// 类 vector 类内存分配策略的简化实现
class StrVec {
public:
    StrVec(): // allocator 成员进行默认初始化
        elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec&);              // 拷贝构造函数
    StrVec(StrVec&&) noexcept;          // 移动构造函数
    StrVec &operator=(const StrVec&);   // 拷贝赋值运算符
    StrVec &operator=(StrVec &&) noexcept; // 移动赋值运算符
    ~StrVec();                          // 析构函数
    void push_back(const std::string&); // 拷贝元素
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    // ...
private:
    Static std::allocator<std::string> alloc;  // 分配元素
    // 被添加元素的函数所使用
    void chk_n_alloc()
        { if (size() == capacity()) reallocate(); }
    // 工具函数，被拷贝构造函数、赋值运算符和析构函数所使用
    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);
    void free();            // 销毁元素并释放内存
    void reallocate();      // 获得更多内存并拷贝已有元素
    std::string *elements;  // 指向数组首元素的指针
    std::string *first_free;// 指向数组第一个空闲元素的指针
    std::string *cap;       // 指向数组尾后位置的指针
};

void StrVec::push_back(const string& s)
{
    chk_n_alloc();  // 确保有空间容纳新元素
    // 在 first_free 指向的元素中构造 s 的副本
    alloc.construct(frist_free++, s);
}

part<string*, string*>
StrVec::alloc_n_copy(const string *b, const string *e)
{
    // 分配空间保存给定范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个 pair，该 pair 由 data 和 uninitialzed_copy 的返回值构成
    return {data, uninitialzed_copy(b, e, data)};
}

void StrVec::free()
{
    // 不能传递给 deallocate 一个空指针，如果 elements 为 0，函数什么也不做
    if (elemetns) {
        // 逆序销毁旧元素
        for (auto p = first_free; p != elements; /* 空 */)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s)
{
    // 调用 alloc_n_copy 分配空间以容纳与 s 中一样多的元素
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() 
{
    free();
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    // 调用 alloc_n_copy 分配内存，大小与 rhs 中元素占用空间一样多
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    // 将数据从旧内存移动到新内存
    auto dest = newdata;        // 指向新数组中下一个空闲元素
    auto elem = elements;       // 指向旧数组下一个元素
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free(); // 一旦我们移动玩元素就释放旧内存空间
    // 更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

StrVec::StrVec(StrVec &&s) noexcept // 移动操作不应抛出任何异常
    // 成员初始化器接管 s 中的资源
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    // 令 s 进入这样的状态 -- 对其运行析构函数是安全的
    s.elements = s.first_free = s.cap = nullptr;
}

// 使用移动迭代器
StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    // 直接检测自赋值
    if (this != &rhs) {
        free();                 // 释放已有元素
        elements = rhs.elements;// 从 rhs 接管资源
        frist_free = rhs.first_free;
        cap = rhs.cap;
        // 将 rhs 置于可析构状态
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::reallocate()
{
    // 分配两倍于当前规模的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    // 移动元素
    auto last = uninitialized_copy(make_move_iterator(begin()),
                                   make_move_iterator(end()),
                                   first);
    // 释放旧空间
    free();
    // 更新指针
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}
