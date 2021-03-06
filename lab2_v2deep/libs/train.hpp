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

typedef const Route * ConstRoutePtr;

/*****************************************************************************/

class Train {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Train() = delete;

	Train( const int _id, const int _nOfSeats, ConstRoutePtr _currRoute = nullptr );

	Train( const Train & ) = delete;
	Train & operator = ( const Train & ) = delete;

	~Train () = default;

	/*-----------------------------------------------------------------*/

	int           GetID()           const;
	int           GetNOfSeats()     const;
	ConstRoutePtr GetCurrentRoute() const;

	/*-----------------------------------------------------------------*/

	void SetNOfSeats( const int _nOfSeats );
	void SetCurrentRoute( ConstRoutePtr const _currRoute );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const int     m_id;
	int           m_nOfSeats;
	ConstRoutePtr m_currRoute;

	/*-----------------------------------------------------------------*/

	void CheckNOfSeats( const int _n );

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline int Train::GetID() const {
	return m_id;
}

inline int Train::GetNOfSeats() const {
	return m_nOfSeats;
}

inline ConstRoutePtr Train::GetCurrentRoute() const {
	return m_currRoute;
}

/*****************************************************************************/

inline void Train::SetNOfSeats( const int _nOfSeats ) {
	CheckNOfSeats( _nOfSeats );

	m_nOfSeats = _nOfSeats;
}

inline void Train::SetCurrentRoute( ConstRoutePtr const _currRoute ) {
	m_currRoute = _currRoute;
}

/*****************************************************************************/

#endif //TRAIN_HPP
