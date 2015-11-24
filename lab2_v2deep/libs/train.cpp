//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

#include "train.hpp"
#include "messages.hpp"

#include <stdexcept>

/*****************************************************************************/

Train::Train( const int _id, const int _nOfSeats, RoutePtr _currRoute )
		: m_id( _id ), m_nOfSeats( _nOfSeats ), m_currRoute( _currRoute )
{
	if( m_id < 0 )
		throw std::logic_error( Messages::NegativeID );

	if( m_nOfSeats < 0 )
		throw std::logic_error( Messages::NegativeNumberOfSeats );
}

/*****************************************************************************/
