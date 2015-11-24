//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

#ifndef ROUTE_HPP
#define ROUTE_HPP

/*****************************************************************************/

#include "train_sched_item.hpp"

#include <vector>
#include <memory>

/*****************************************************************************/

class Route {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	class ItemIterator;
	class ItemIteratorReverse;

	Route() = delete;

	Route( const int _id );

	Route( const Route & ) = delete;
	Route & operator = ( const Route & ) = delete;

	~ Route() = default;

	/*-----------------------------------------------------------------*/

	ItemIterator begin();
	ItemIterator end();

	ItemIteratorReverse rbegin();
	ItemIteratorReverse rend();

	/*-----------------------------------------------------------------*/

	typedef std::unique_ptr< TrainSchedItem > UniqueRouteItem;

	void AddItem( UniqueRouteItem _it );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const int m_id;
	std::vector< UniqueRouteItem > m_items;

	/*-----------------------------------------------------------------*/

	void CheckItem( UniqueRouteItem & _i );

	/*-----------------------------------------------------------------*/

};

// TODO: Может переместить в отдельный файл?

/*****************************************************************************/

class Route::ItemIterator {

	/*-----------------------------------------------------------------*/

	typedef std::vector< UniqueRouteItem >::const_iterator BaseIterator;

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	explicit ItemIterator ( BaseIterator _baseIt )
			: m_baseIt( _baseIt ) {}

	const TrainSchedItem * operator * () const;

	bool operator == ( ItemIterator _i ) const;

	bool operator != ( ItemIterator _i ) const;

	ItemIterator & operator ++ ();

	ItemIterator   operator ++ ( int );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	BaseIterator m_baseIt;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

// TODO: Буквально copy-paste, если сравнивать с итератором выше

class Route::ItemIteratorReverse {

	/*-----------------------------------------------------------------*/

	typedef std::vector< UniqueRouteItem >::const_reverse_iterator BaseIterator;

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	explicit ItemIteratorReverse ( BaseIterator _baseIt )
			: m_baseIt( _baseIt ) {}

	const TrainSchedItem * operator * () const;

	bool operator == ( ItemIteratorReverse _i ) const;

	bool operator != ( ItemIteratorReverse _i ) const;

	ItemIteratorReverse & operator ++ ();

	ItemIteratorReverse   operator ++ ( int );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	BaseIterator m_baseIt;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline Route::ItemIterator Route::begin() {
	return Route::ItemIterator( m_items.begin() );
}

inline Route::ItemIterator Route::end() {
	return Route::ItemIterator( m_items.end() );
}

/*****************************************************************************/

inline Route::ItemIteratorReverse Route::rbegin() {
	return Route::ItemIteratorReverse( m_items.rbegin() );
}

inline Route::ItemIteratorReverse Route::rend() {
	return Route::ItemIteratorReverse( m_items.rend() );
}

/*****************************************************************************/

#endif //ROUTE_HPP
