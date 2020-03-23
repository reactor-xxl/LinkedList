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
		iterator( Node *node = nullptr ) : m_node{ node }
		{
			if ( m_node )
			{
				m_isValid = true;
				m_isDereferenceable = true;
			}
		}

		iterator( const iterator& it ) { *this = it; }
		~iterator(){ ; }	

		bool is_valid() const { return m_isValid; }


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

#pragma message ("validity should not involve a nullptr check")

		iterator&	operator++()
		{
			if ( !m_node || !m_isValid )/* validity should not involve a nullptr check*/
				throw std::out_of_range{ "LinkedList_t::iterator : iterator invalid" };

			if ( m_afterEnd )
				throw std::out_of_range{ "LinkedList_t::iterator : cannot increment past end of list" };

			if ( m_node->next )
			{
				m_node = m_node->next;
			}
			else
			{
				m_afterEnd = true;
				m_isDereferenceable = false;
			}

			return *this;
		}

		iterator&	operator--()
		{
			if ( !m_node || !m_isValid )
				throw std::out_of_range{ "iterator : iterator invalid" };

			if ( !m_node->prev )
				throw std::out_of_range{ "iterator : cannot decrement past start of list" };

			if ( !m_afterEnd )
			{
				m_node = m_node->prev;
			}

			m_afterEnd = false;
			m_isDereferenceable = true;

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


		bool	operator == ( const iterator& rhs )	const
		{
			if( m_parent != rhs.m_parent) return false;

			if( m_node != rhs.m_node) return false;

			if( m_isValid != rhs.m_isValid) return false;

			if( m_isDereferenceable != rhs.m_isDereferenceable) return false;

			if( m_afterEnd != rhs.m_afterEnd) return false;

			return true;
		}

		bool	operator != ( const iterator& rhs )	const
		{
			return !operator==( rhs );
		}

		bool	operator < ( const iterator& rhs )	const;
		bool	operator > ( const iterator& rhs )	const;

//	private:
		iterator(const LinkedList_t<T>& parentList, Node *node ) : m_parent{&parentList}, m_node( node ) { ; }
		const LinkedList_t<T>	*m_parent = { nullptr };
#pragma message( "const LinkedList_t<T>	*m_parent <-- are there any actual instances\n" \
		"where the iterator should be invalidated by the parent?")
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


	void	insert_before( const iterator& it, const T& value )
	{
		if( !it.is_valid() )
			throw std::out_of_range{ "LinkedList_t::iterator : iterator invalid" };

		auto node = it.m_node;
		Node *newNode = new Node{ value };

		newNode->prev = node->prev;
		newNode->next = node;
		node->prev = newNode;
	}

	void	insert_after( const iterator& it, const T& value )
	{
		if( !it.is_valid() )
			throw std::out_of_range{ "LinkedList_t::iterator : iterator invalid" };

		auto node = it.m_node;
		Node *newNode = new Node{ value };

		newNode->next = node->next;
		newNode->prev = node;
		node->next = newNode;
	}

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


	void	remove( iterator& it )
	{
		if( !it.is_valid() )
			throw std::out_of_range{ "LinkedList_t::iterator : iterator invalid" };

		auto prevNode = it.m_node->prev;
		auto nextNode = it.m_node->next;

		if ( prevNode )
			prevNode->next = nextNode;
	
		if ( nextNode )
			nextNode->prev = prevNode;

		delete it.m_node;
		it.m_isDereferenceable = false;
	}

	void	sort( CompareFunction<T> );

	iterator	find( const T& val )
	{
		iterator it;

		for ( it = begin(); it != end(); ++it )
		{
			if ( *it == val )
				break;
		}

		return it;
	}

	iterator	begin()
	{
		return iterator { m_head };
	}

	iterator	end()
	{
		iterator it{ m_tail };

		it.m_afterEnd = true;
		it.m_isDereferenceable = false;

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









