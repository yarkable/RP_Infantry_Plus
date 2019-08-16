#ifndef __DAHUA_INFRA_CSTRING_H__
#define __DAHUA_INFRA_CSTRING_H__

#include <stddef.h> /// for size_t
#include <Infra/Defs.h>

namespace Dahua{
namespace Infra{

/// 字符串操作类
class INFRA_API CString
{
public:
	/// 字符串尾索引
	static const size_t npos;
	
	/// 默认构造函数
	CString();
		
	/// 构造函数
	/// \param str 拷贝构造提供的CString
	CString( CString const& str );
		
	/// 构造函数
	/// \param str 被构造的原始字符串
	/// \param pos 第一个构造字符在原字符串中的偏移位置
	/// \param len 构造字符串长度
	CString( CString const& str, size_t pos, size_t len );
		
	/// 构造函数
	/// \param s 构造字符串
	CString( const char* s );

	/// 构造函数
	/// \param s 被构造字符串
	/// \param n 构造字符串长度
	CString( const char* s, size_t n );
		
	/// 构造函数
	/// \param c 构造元字符
	/// \param n 构造元字符的数量
	CString( char c, size_t n );
		
	/// 析构函数
	~CString();
		
	/// 赋值构造函数
	/// \param str 赋值字符串
	CString& operator=( CString const& str );
		
	/// 赋值构造函数
	/// \param str 赋值字符串
	CString& operator=( const char* str );
		
	/// 赋值构造函数
	/// \param c 使用字符构造长度为1的字符串
	CString& operator=( char c );
		
	/// 获取字符串长度
	size_t size() const;
		
	/// 获取字符串长度
	size_t length() const;
		
	/// 重置字符串长度
	/// \param n 重置后字符串长度
	void resize( size_t n );
		
	/// 使用指定字符重置字符串长度
	/// \param c 指定字符串
	/// \param n 重置后字符串长度
	void resize( char c, size_t n );
		
	/// 返回字符串占用内存大小
	size_t capacity() const;
		
	/// 设置字符串的存储长度
	/// \param n 字符存储长度
	void reserve( size_t n );
		
	/// 清除字符串数据
	void clear();
		
	/// 判断字符串是为空
	bool empty() const;
		
	/// 获取字符串中指定索引字符
	/// \param pos 索引值
	char const& operator[]( size_t pos ) const;
		
	/// 获取字符串中指定索引字符
	/// \param pos 索引值
	char& operator[]( size_t pos );
		
	/// 获取字符串中指定索引字符
	/// \param n 索引值
	char const& at( size_t n ) const;
		
	/// 获取字符串中指定索引字符
	/// \param n 索引值
	char& at( size_t n );
		
	/// 重载自加操作符
	/// \param str 被追加字符串
	CString& operator+=( CString const& str );
		
	/// 重载自加操作符
	/// \param str 被追加字符串
	CString& operator+=( const char* str );
		
	/// 重载自加操作符
	/// \param c 被追加字符
	CString& operator+=( const char c );
		
	/// 追加字符串
	/// \param str 追加的字符串
	CString& append( CString const& str );
		
	/// 追加指定长度字符串
	/// \param str 追加的字符串
	/// \param pos 追加字符串的偏移量
	/// \param n 追加字符长度
	CString& append( CString const& str, size_t pos, size_t n );
		
	/// 追加指定长度的字符串
	/// \param s 追加字符串地址
	/// \param n 追加字符串长度
	CString& append( const char* s, size_t n );
		
	/// 追加指定字符串
	/// \param s 追加字符串地址
	CString& append( const char* s );
		
	/// 增加自定字符
	/// \param c 追加字符
	void push_back( const char c );
		
	/// 将其他字符串分配给自身
	/// \param str 分配字符串
	CString& assign( CString const& str );
		
	/// \指定长度字符串分配
	/// \param str 原始待分配字符串
	/// \param pos 分配字符串偏移量
	/// \param n 分配字符串长度
	CString& assign( CString const& str, size_t pos, size_t n );
		
	/// 使用字符串地址分配字符串
	/// \param s 字符串地址
	/// \param n 字符长度
	CString& assign( const char* s, size_t n );
		
	/// 从指定地址分配字符串
	/// \param s 分配字符串地址
	CString& assign( const char* s );
		
	/// 在指定位置插入指定字符串
	/// \param pos 插入位置偏移量
	/// \param str 插入字符串
	CString& insert( size_t pos, CString const& str );
		
	/// 在指定位置插入指定长度的字符串
	/// \param pos 插入位置偏移量
	/// \param str 原插入字符串
	/// \param pos 插入字符串基于原插入字符串的偏移量
	/// \param n 插入字符串的长度
	CString& insert( size_t pos1, CString const& str, 
		size_t pos2, size_t n );
		
	/// 在指定位置插入指定字符串
	/// \param pos 插入位置偏移量
	/// \param s 插入字符串地址
	/// \param n 插入字符串长度
	CString& insert( size_t pos, const char* s, size_t n );
		
	/// 在指定位置插入指定字符串
	/// \param pos 插入位置偏移量
	/// \param s 插入字符串地址
	CString& insert( size_t pos, const char* s );
		
	/// 在指定位置插入n个指定元字符
	/// \param pos 插入位置偏移量
	/// \param c 元字符
	/// \param n 元字符数量
	CString& insert( size_t pos, char c, size_t n );
		
	/// 在指定位置插入元字符
	/// \param pos 插入位置偏移量
	/// \param c 元字符
	CString& insert( size_t pos, char c );
		
	/// 在指定位置删除n个字符
	/// \param pos 删除起始位置偏移量
	/// \param n 删除字符数量
	CString& erase( size_t pos, size_t n );
		
	/// 将指定位置的n个字符替换为另一字符串
	/// \param pos 替换位置的偏移量
	/// \param n 替换字符数量
	/// \param str 替换字符串
	CString& replace( size_t pos, size_t n, CString const& str );
		
	/// 将指定位置的n个字符替换为另一字符串
	/// \param pos1 替换位置的偏移量
	/// \param n1 替换字符数量
	/// \param str 用于替换的原始字符串
	/// \param pos2 替换字符串在str中的偏移量
	CString& replace( size_t pos1, size_t n, 
		CString const& str, size_t pos2 );
			
	/// 将指定位置的n个字符替换为另一字符串
	/// \param pos1 替换位置的偏移量
	/// \param n1 替换字符数量
	/// \param s 替换字符串地址
	CString& replace( size_t pos1, size_t n1, const char* s );
		
	/// 从指定位置拷贝n个字符串到指定地址
	/// \param s[ out ] 接收字符串地址
	/// \param n[ int ] 拷贝字符串长度
	/// \param pos[ int ] 拷贝起始位置偏移量
	size_t copy( char* s, size_t n, size_t pos = 0 ) const;
		
	/// 交换两个字符串
	/// \param other 被交换字符串
	void swap( CString& other );
		
	/// 获取字符串的起始指针
	const char* c_str() const;
		
	/// 获取字符串的起始指针
	const char* data() const;
		
	/// 查找指定字符串
	/// \param str 查询字符串
	/// \param pos 查询起始位置的偏移量
	/// \return 查询成功，返回字符串所在位置，查询失败返回npos
	size_t find( CString const& str, size_t pos = 0 ) const;
		
	/// 查找指定字符串
	/// \param s 查询字符串地址
	/// \param pos 查询起始位置的偏移量
	/// \param n 指定查询串的长度
	/// \return 查询成功，返回字符串所在位置，查询失败返回npos
	size_t find( const char* s, size_t pos, size_t n ) const;
		
	/// 查找指定字符串
	/// \param s 查询字符串地址
	/// \param pos 查询起始位置的偏移量
	/// \return 查询成功，返回字符串所在位置，查询失败返回npos
	size_t find( const char* s, size_t pos = 0 ) const;
		
	/// 查询指定字符
	/// \param s 查询字符
	/// \param pos 查询起始位置的偏移量
	/// \查询成功，返回字符串所在位置，查询失败返回npos
	size_t find( char c, size_t pos = 0 ) const;
		
	/// 反向查询指定字符串
	/// \param str 查询字符串
	/// \param pos 查询起始位置的偏移量
	/// \return 查询成功，返回字符串所在位置，查询失败返回npos
	size_t rfind( CString const& str, size_t pos = npos ) const;
		
	/// 反向查找指定字符串
	/// \param s 查询字符串地址
	/// \param pos 查询起始位置的偏移量
	/// \param n 指定查询串的长度
	/// \return 查询成功，返回字符串所在位置，查询失败返回npos
	size_t rfind( const char* s, size_t pos, size_t n ) const;
		
	/// 反向查找指定字符串
	/// \param s 查询字符串地址
	/// \param pos 查询起始位置的偏移量
	/// \return 查询成功，返回字符串所在位置，查询失败返回npos
	size_t rfind( const char* s, size_t pos = npos ) const;
		
	/// 反向查询指定字符
	/// \param s 查询字符
	/// \param pos 查询起始位置的偏移量
	/// \查询成功，返回字符串所在位置，查询失败返回npos
	size_t rfind( char c, size_t pos = npos ) const;
		
	/// 查询第一个匹配指定字符串的位置
	/// \param str 匹配字符串
	/// \param pos 开始匹配偏移量
	size_t find_first_of( CString const& str, size_t pos = 0 ) const;
		
	/// 查询第一个匹配指定字符串的位置
	/// \param s 匹配字符串地址
	/// \param pos 开始匹配偏移量
	/// \param n 指定匹配字符串长度
	size_t find_first_of( const char* s, size_t pos, size_t n ) const;
		
	/// 查询第一个匹配指定字符串的位置
	/// \param s 匹配字符串地址
	/// \param pos 开始匹配偏移量
	size_t find_first_of( const char* s, size_t pos = 0 ) const;
		
	/// 查询第一个匹配指定字符的位置
	/// \param c 匹配字符
	/// \param pos 开始匹配偏移量
	size_t find_first_of( char c, size_t pos = 0 ) const;
		
	/// 从后向前查询，查找第一个匹配到指定字符串的位置
	/// \param str 匹配字符串
	/// \param pos 开始匹配偏移量
	size_t find_last_of( CString const& str, size_t pos = 0 ) const;
		
	/// 从后向前查询，查找第一个匹配到指定字符串的位置
	/// \param s 匹配字符串地址
	/// \param pos 开始匹配偏移量
	/// \param n 指定匹配字符串长度
	size_t find_last_of( const char* s, size_t pos, size_t n ) const;
		
	/// 从后向前查询，查找第一个匹配到指定字符串的位置
	/// \param s 匹配字符串地址
	/// \param pos 开始匹配偏移量
	size_t find_last_of( const char* s, size_t pos = 0 ) const;
		
	/// 从后向前查询，查询第一个匹配指定字符的位置
	/// \param c 匹配字符
	/// \param pos 开始匹配偏移量
	size_t find_last_of( char c, size_t pos = 0 ) const;
		
	/// 在原字符串上截取子字符串
	/// \param pos 子字符串其实位置偏移量
	/// \param n 子字符串长度
	CString substr( size_t pos = 0, size_t n = npos ) const;
		
	/// 比较两个字符串是否相等
	/// \param str 比较字符串
	int compare( CString const& str ) const;
		
	/// 比较两个字符串是否相等
	/// \param pos1 被比较字符串的起始偏移量
	/// \param n1 指定被比较字符串长度
	/// \param str 比较字符串
	int compare( size_t pos1, size_t n1, CString const& str ) const;
		
	/// 比较两个字符串是否相等
	/// \param pos1 被比较字符串的起始偏移量
	/// \param n1 指定被比较字符串长度
	/// \param s 比较字符串地址
	int compare( size_t pos1, size_t n1, const char* s ) const;
		
	/// 比较两个字符串是否相等
	/// \param pos1 被比较字符串的起始偏移量
	/// \param n1 指定被比较字符串长度
	/// \param s 比较字符串地址
	/// \param n2 比较长度
	int compare( size_t pos1, size_t n1, const char* s, size_t n2 ) const;
		
	/// 比较两个字符串是否相等
	/// \param pos1 被比较字符串的起始偏移量
	/// \param n1 指定被比较字符串长度
	/// \param str 比较字符串
	/// \param pos2 比较字符串的起始偏移量
	/// \param n2 指定比较字符串长度
	int compare( size_t pos1, size_t n1, CString const& str, 
		size_t pos2 ) const;
		
	/// 比较两个字符串是否相等
	/// \param s 比较字符串地址
	int compare( const char* s ) const;
		
	/// 重载 + 操作符
	/// \param b 加字符串
	CString operator + ( CString const& other ) const;
		
	/// 重载 + 操作符
	/// \param b 加字符串
	CString operator + ( const char* other ) const;

	/// 重载 == 操作符
	/// \param b 比较字符串
	bool operator == ( CString const& other ) const;
		
	/// 重载 == 操作符
	/// \param b 比较字符串地址
	bool operator == ( const char* other ) const;

	/// 重载 != 操作符
	/// \param b 比较字符串地址
	bool operator != ( CString const& other ) const;
		
	/// 重载 != 操作符
	/// \param b 比较字符串地址
	bool operator != ( const char* other ) const;

	/// 重载 < 操作符
	/// \param b 比较字符串地址
	bool operator < ( CString const& other ) const;
		
	/// 重载 < 操作符
	/// \param b 比较字符串地址
	bool operator < ( const char* other ) const;

	/// 重载 <= 操作符
	/// \param b 比较字符串地址
	bool operator <= ( CString const& other ) const;
		
	/// 重载 <= 操作符
	/// \param b 比较字符串地址
	bool operator <= ( const char* other ) const;

	/// 重载 > 操作符
	/// \param b 比较字符串地址
	bool operator > ( CString const& other ) const;
		
	/// 重载 > 操作符
	/// \param b 比较字符串地址
	bool operator > ( const char* other ) const;

	/// 重载 >= 操作符
	/// \param b 比较字符串地址
	bool operator >= ( CString const& other ) const;
		
	/// 重载 >= 操作符
	/// \param b 比较字符串地址
	bool operator >= ( const char* other ) const;

private:
	struct Internal;
	Internal* m_internal;
};

} /// namespace Infra
} /// namespace Dahua

#endif /// __DAHUA_INFRA_CSTRING_H__
