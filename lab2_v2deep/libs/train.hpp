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

	Train( const int _id, const int _nOfSeats, RoutePtr const _currRoute = nullptr );

	Train( const Train & ) = delete;
	Train & operator = ( const Train & ) = delete;

	~Train () = default;

	/*-----------------------------------------------------------------*/

	int GetID() const;
	int GetNOfSeats() const;
	RoutePtr GetCurrentRoute() const;

	/*-----------------------------------------------------------------*/

	void SetNOfSeats( const int _nOfSeats );
	void SetCurrentRoute( RoutePtr const _currRoute );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const int m_id;
	int m_nOfSeats;
	RoutePtr     m_currRoute;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline int Train::GetID() const {
	return m_id;
}

inline int Train::GetNOfSeats() const {
	return m_nOfSeats;
}

inline RoutePtr Train::GetCurrentRoute() const {
	return m_currRoute;
}

/*****************************************************************************/

inline void Train::SetNOfSeats( const int _nOfSeats ) {
	m_nOfSeats = _nOfSeats;
}

inline void Train::SetCurrentRoute( RoutePtr const _currRoute ) {
	m_currRoute = _currRoute;
}

/*****************************************************************************/

#endif //TRAIN_HPP
