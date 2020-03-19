#pragma once
#include <exception>
#include <string>
#include <sstream>

std::string to_string( const void *ptr )
{
	char buff[20] = { 0 };

	if( ptr )
		std::snprintf( buff, 20, "0x%p", ptr );
	else
		std::snprintf( buff, 20, "nullptr" );

	return std::string( buff );
}


template <typename U>
using  CompareFunction = bool	(*)(const U & lhs, const U & rhs);


template <typename T>
class LinkedList
{
	class Node;
public:
	class iterator
	{
	public:
		iterator();
		~iterator();

		T&	operator*() const { return m_node->data; }
		iterator&	operator=( const iterator& rhs );

		iterator&	operator++();
		iterator&	operator--();

		iterator&	operator++( int );
		iterator&	operator--( int );

		bool	operator == ( const iterator& rhs )	const;
		bool	operator != ( const iterator& rhs )	const;
		bool	operator < ( const iterator& rhs )	const;
		bool	operator > ( const iterator& rhs )	const;

//	private:
		iterator( Node *node ) : m_node( node ) { ; }
		Node	*m_node = nullptr;
		bool	m_isValid = false;
		bool	m_isDereferenceable = false;
	};

	void	push_front( const T& data )
	{
		Node *newNode = new Node( data );
		newNode->next = m_head;
		m_head = newNode;

		if ( !m_tail )
			m_tail = newNode;

		//		++m_size
	}
	void	push_back( const T& data )
	{
		Node *newNode = new Node( data );

		newNode->prev = m_tail;

		if ( m_tail )
		{
			m_tail->next = newNode;
		}

		m_tail = newNode;

		if ( !m_head )
			m_head = newNode;
	}

	void	pop_front()
	{
		if ( !m_head ) return;

		auto delNode = m_head;

		m_head = m_head->next;

		delete delNode;

		if ( m_head )
			m_head->prev = nullptr;
		else
			m_tail = nullptr;

	}
	void	pop_back()
	{
		if ( !m_tail ) return;

		auto delNode = m_tail;

		m_tail = m_tail->prev;

		delete delNode;

		if ( m_tail )
			m_tail->next = nullptr;
		else
			m_head = nullptr;
	}


	void	insert_before( const iterator&, const T& value );
	void	insert_after( const iterator&, const T& value );

	//	T&	front();
	//	T&	back();
	T&	front()	const
	{
		if ( m_head )
			return m_head->data;
		else
			throw std::out_of_range( "LinkedList::front() : list is empty." );
	}

	T&	back()	const
	{
		if ( m_tail )
			return m_tail->data;
		else
			throw std::out_of_range( "LinkedList::front() : list is empty." );
	}


	void	remove( const iterator& );

	void	sort( CompareFunction<T> );

	iterator	find( const T& );

	iterator	begin()
	{
		iterator it( m_head );

		if ( m_head )
		{
			it.m_isValid = true;
			it.m_isDereferenceable = true;
		}
	}
	iterator	end();

	iterator	cbegin();
	iterator	cend();


	size_t	size() const
	{
		size_t size = 0;
		auto p = m_head;
		while ( p )
		{
			++size;
			p = p->next;
		}
		return size;
	}

	//	bool	empty() const;


//private:
	struct Node
	{
		Node( const T& t ) : data( t ) { ; }
		T	data;
		Node	*prev = nullptr;
		Node	*next = nullptr;
	};

	
	std::string	debug_dump_internals() const
	{
		std::stringstream ss;
		ss
		<< "current size: " << size() << "\n"
		<< "    Node  *m_head : " << to_string(m_head) << "\n"
		<< "    Node  *m_tail : " << to_string(m_tail) << "\n";
		return ss.str();
	}

	std::string debug_dump_values()
	{
		std::stringstream ss;

		ss << "{ ";

		auto p = m_head;

		while ( p )
		{
			ss << p->data << ", ";
			p = p->next;
		}

		ss << "}";

		return ss.str();
	}

	Node	*m_head = nullptr;
	Node	*m_tail = nullptr;

};

