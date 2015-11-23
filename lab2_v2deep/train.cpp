//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

#include "train.hpp"
#include "messages.hpp"

#include <stdexcept>

/*****************************************************************************/

Train::Train( const unsigned int _id, const unsigned int _nOfSeats, const unsigned int _currRoute )
		: m_id( _id ), m_nOfSeats( _nOfSeats ), m_currRoute( _currRoute )
{ }

/*****************************************************************************/
