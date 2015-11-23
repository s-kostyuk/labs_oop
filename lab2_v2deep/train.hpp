//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

#ifndef TRAIN_HPP
#define TRAIN_HPP

/*****************************************************************************/

#include <memory>

/*****************************************************************************/

class Route;

typedef const Route * RoutePtr;

/*****************************************************************************/

class Train {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Train() = delete;

	Train( const unsigned int _id, const unsigned int _nOfSeats, RoutePtr const _currRoute = nullptr );

	Train( const Train & ) = delete;
	Train & operator = ( const Train & ) = delete;

	~Train () = default;

	/*-----------------------------------------------------------------*/

	unsigned int GetID() const;
	unsigned int GetNOfSeats() const;
	RoutePtr     GetCurrentRoute() const;

	/*-----------------------------------------------------------------*/

	void SetNOfSeats( const unsigned int _nOfSeats );
	void SetCurrentRoute( RoutePtr const _currRoute );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const unsigned int m_id;
	unsigned int m_nOfSeats;
	RoutePtr     m_currRoute;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline unsigned int Train::GetID() const {
	return m_id;
}

inline unsigned int Train::GetNOfSeats() const {
	return m_nOfSeats;
}

inline RoutePtr Train::GetCurrentRoute() const {
	return m_currRoute;
}

/*****************************************************************************/

inline void Train::SetNOfSeats( const unsigned int _nOfSeats ) {
	m_nOfSeats = _nOfSeats;
}

inline void Train::SetCurrentRoute( RoutePtr const _currRoute ) {
	m_currRoute = _currRoute;
}

/*****************************************************************************/

#endif //TRAIN_HPP
