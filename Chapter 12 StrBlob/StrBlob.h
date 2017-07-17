#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>

class StrBlob {
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	// 添加和删除元素
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	// 元素访问
	std::string& front();
	std::string& back();
	// 元素访问函数的 const 重载
	const std::string& front() const;
	const std::string& back() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()) { }

StrBlob::StrBlob(std::initializer_list<string> il) : 
				data(make_shared<vector<string>>(il)) { }

void StrBlob::check(size_type i, const stirng &msg) const 
{
	if (i >= data->size())
		throw out_of_range(msg);
}

std::string& StrBlob::front()
{
	// 如果 vector 为空， check 会抛出一个异常
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string& StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

const std::string& StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

const std::string& StrBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
