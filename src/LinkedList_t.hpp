#pragma once


template <typename U>
using  CompareFunction = bool	(*comp)( const U& lhs, const U& rhs );


template <typename T>
class LinkedList
{
public:
	class iterator
	{
	public:
		iterator();
		~iterator();

		T&	operator*() const;
		iterator&	operator=( const iterator& rhs );

		iterator&	operator++();
		iterator&	operator--();

		iterator&	operator++(int);
		iterator&	operator--(int);

		bool	operator == ( const iterator& rhs)	const;
		bool	operator != ( const iterator& rhs)	const;
		bool	operator < (  const iterator& rhs)	const;
		bool	operator > (  const iterator& rhs)	const;

	private:
		Node	*m_node;
		bool	m_isValid;
		bool	m_isDereferenceable;
	};

	void	push_front( const T& );
	void	push_back( const T& );

	void	insert_before( const iterator&, const T& value );
	void	insert_after(  const iterator&, const T& value );

//	T&	front();
//	T&	back();
	const T&	front()	const ;
	const T&	back()	const ;

	void	pop_front();
	void	pop_back();

	void	remove( const iterator& );

	void	sort( CompareFunction<T> );

	iterator	find( const T& );

	iterator	begin();
	iterator	end();

	iterator	cbegin();
	iterator	cend();


	size_t	size() const;
//	bool	empty() const;


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

