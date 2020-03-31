#pragma once
#include <exception>
#include <string>
#include <sstream>

#include <iostream>

#include "utils.cpp"

//std::string Utility::to_string( const void *ptr );

template <typename U>
using  CompareFunction = bool	(*)(const U & lhs, const U & rhs);


//template <typename T>
using T = int;
class LinkedList_t
{
	struct Node;
	//	static inline const std::string name{"LinkedList_t"};

public:

	void	push_front( const T& data )
	{
		Node *newNode = new Node{ data };

		newNode->next = m_head;

		if ( m_head )
			m_head->prev = newNode;

		m_head = newNode;

		if ( !m_tail )
			m_tail = m_head;
	}

	void	push_back( const T& data )
	{
		Node *newNode = new Node{ data };

		newNode->prev = m_tail;

		if ( m_tail )
			m_tail->next = newNode;

		m_tail = newNode;

		if ( !m_head )
			m_head = m_tail;
	}

	void	pop_front()
	{
		if ( !m_head )
			return;

		Node *oldHead = m_head;

		m_head = m_head->next;

		if ( m_head )/* move trailing node up*/
		{
			m_head->prev = nullptr;
		}
		else/* empty list */
		{
			m_tail = m_head = nullptr;
		}

		delete oldHead;
	}

	void	pop_back()
	{
		if ( !m_tail )
			return;

		Node *oldTail = m_tail;

		m_tail = m_tail->prev;

		if ( m_tail )/* move trailing node up*/
		{
			m_tail->next = nullptr;
		}
		else/* empty list */
		{
			m_tail = m_head = nullptr;
		}

		delete oldTail;
	}

	/*void	insert_before( const iterator& it, const T& value ) */
	/*void	insert_after( const iterator& it, const T& value ) */

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
			throw std::out_of_range( "LinkedList::back() : list is empty." );
	}


	/* void	remove( iterator& it ) */


	void	sort( CompareFunction<T> );

	Node *find( const T& val )
	{
		Node *stepper;

		for ( stepper = m_head; stepper != nullptr; stepper = stepper->next )
		{
			if ( stepper->data == val )
				break;
		}

		return stepper;
	}

	/*	iterator	begin() */
	/*	iterator	end()	*/
	/*	iterator	cbegin(); */
	/*	iterator	cend();	  */


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

	void clear()
	{
		for ( Node *mover = m_head; mover != nullptr; )
		{
			Node *delNode = mover;
			mover = mover->next;

			delete delNode;
		}

		m_head = m_tail = nullptr;

	}

	~LinkedList_t()
	{
		clear();
	}

	std::string	debug_dump_internals() const
	{
		std::stringstream ss;
		ss
			<< "current size: " << size() << "\n"
			<< "    Node  *m_head : " << Utility::to_string( m_head ) << "\n"
			<< "    Node  *m_tail : " << Utility::to_string( m_tail ) << "\n";
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


private:
	struct Node
	{
		Node( const T& t ) : data( t ) { ; }
		T	data;
		Node	*prev = nullptr;
		Node	*next = nullptr;
	};

	Node	*m_head = nullptr;
	Node	*m_tail = nullptr;
};









