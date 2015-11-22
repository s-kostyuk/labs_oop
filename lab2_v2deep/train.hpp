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

/*****************************************************************************/

class Train {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Train() = delete;

	Train( const unsigned int _id, const unsigned int _nOfSeats, const unsigned int _currRoute = 0 );

	Train( const Train & ) = delete;
	Train & operator = ( const Train & ) = delete;

	~Train () = default;

	/*-----------------------------------------------------------------*/

	unsigned int GetID();
	unsigned int GetNOfSeats();
	unsigned int GetCurrentRoute();

	/*-----------------------------------------------------------------*/

	void SetNOfSeats( const unsigned int _nOfSeats );
	void SetCurrentRoute( const unsigned int _currRoute );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const unsigned int m_id;
	unsigned int m_nOfSeats;
	unsigned int m_currRoute;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline unsigned int Train::GetID() {
	return m_id;
}

inline unsigned int Train::GetNOfSeats() {
	return m_nOfSeats;
}

inline unsigned int Train::GetCurrentRoute() {
	return m_currRoute;
}

/*****************************************************************************/

inline void Train::SetNOfSeats( const unsigned int _nOfSeats ) {
	m_nOfSeats = _nOfSeats;
}

inline void Train::SetCurrentRoute( const unsigned int _currRoute ) {
	m_currRoute = _currRoute;
}

/*****************************************************************************/

#endif //TRAIN_HPP
