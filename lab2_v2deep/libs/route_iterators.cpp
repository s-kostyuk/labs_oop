//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 24.11.15.
//

/*****************************************************************************/

#include "route.hpp"

/*****************************************************************************/

Route::ItemIterator & Route::ItemIterator::operator ++() {
	++ m_baseIt;

	return * this;
}

Route::ItemIterator Route::ItemIterator::operator ++( int ) {
	ItemIterator copy = *this;

	++ m_baseIt;

	return copy;
}

bool Route::ItemIterator::operator !=( ItemIterator _i ) const {
	return m_baseIt != _i.m_baseIt;
}

bool Route::ItemIterator::operator ==( ItemIterator _i ) const {
	return m_baseIt == _i.m_baseIt;
}

const TrainSchedItem * Route::ItemIterator::operator * () const {
	return ( *m_baseIt ).get();
}

/*****************************************************************************/

Route::ItemIteratorReverse & Route::ItemIteratorReverse::operator ++ () {
	++ m_baseIt;

	return * this;
}

Route::ItemIteratorReverse   Route::ItemIteratorReverse::operator ++ ( int ) {
	ItemIteratorReverse copy = *this;

	++ m_baseIt;

	return copy;
}

bool Route::ItemIteratorReverse::operator != ( ItemIteratorReverse _i ) const {
	return m_baseIt != _i.m_baseIt;
}

bool Route::ItemIteratorReverse::operator == ( ItemIteratorReverse _i ) const {
	return m_baseIt == _i.m_baseIt;
}

const TrainSchedItem * Route::ItemIteratorReverse::operator * () const {
	return ( *m_baseIt ).get();
}

/*****************************************************************************/