#pragma once
#include <exception>
#include <string>
#include <sstream>

#include "utils.cpp"

//std::string Utility::to_string( const void *ptr );

template <typename U>
using  CompareFunction = bool	(*)(const U & lhs, const U & rhs);


template <typename T>
class LinkedList_t
{
	class Node;
//	static inline const std::string name{"LinkedList_t"};

public:
	class iterator
	{
	public:
		iterator();
		iterator( const iterator& it ) { *this = it; }
		~iterator();

		T&	operator*() const
		{
			if ( !m_isValid || !m_isDereferenceable )
				throw std::logic_error{ "LinkedList_t::iterator : iterator not dereferenceable" };

			return m_node->data;
		}
		iterator&	operator=( const iterator& rhs )
		{
			m_parent = rhs.m_parent;
			m_node = rhs.m_node;
			m_isValid = rhs.m_isValid;
			m_isDereferenceable = rhs.m_isDereferenceable;
			m_afterEnd = rhs.m_afterEnd;

			return *this;
		}

		iterator&	operator++()
		{
			if ( !m_node || !m_isValid )/* validity should not involve a nullptr check*/
				throw std::out_of_range{ "LinkedList_t::iterator : iterator invalid" };

			if ( !m_node->next )
				throw std::out_of_range{ "LinkedList_t::iterator : cannot increment past end of list" };

			m_node = m_node->next;

			return *this;
		}

		iterator&	operator--()
		{
			if ( !m_node || !m_isValid )
				throw std::out_of_range{ "iterator : iterator invalid" };

			if ( !m_node->prev )
				throw std::out_of_range{ "iterator : cannot decrement past start of list" };

			m_node = m_node->prev;

			return *this;
		}

		iterator	operator++( int )
		{
			auto it = *this;
			operator++();
			return it;
		}

		iterator	operator--( int )
		{
			auto it = *this;
			operator--();
			return it;
		}


		bool	operator == ( const iterator& rhs )	const;
		bool	operator != ( const iterator& rhs )	const;
		bool	operator < ( const iterator& rhs )	const;
		bool	operator > ( const iterator& rhs )	const;

//	private:
		iterator(const LinkedList<T>& parentList, Node *node ) : m_parent{&parentList}, m_node( node ) { ; }
		const LinkedList<T>	*m_parent;/*are there any actual instances where the iterator should be invalidated?*/
		Node	*m_node = nullptr;
		bool	m_isValid = false;
		bool	m_isDereferenceable = false;
		bool	m_afterEnd = false;
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
		iterator it{ m_head };

		if ( m_head )
		{
			it.m_isValid = true;
			it.m_isDereferenceable = true;
		}
		return it;
	}

	iterator	end()
	{
		iterator it{ m_tail };
		it.m_afterEnd = true;

		if ( m_tail )
		{
			it.m_isValid = true;
			it.m_isDereferenceable = false;
		}
		return it;
	}


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
		<< "    Node  *m_head : " << Utility::to_string(m_head) << "\n"
		<< "    Node  *m_tail : " << Utility::to_string(m_tail) << "\n";
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









