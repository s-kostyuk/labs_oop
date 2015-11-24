//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

#ifndef TRAIN_SCHED_ITEM_HPP
#define TRAIN_SCHED_ITEM_HPP

/*****************************************************************************/

#include "time_hm.hpp"

/*****************************************************************************/

class Station;

/*****************************************************************************/

class TrainSchedItem {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	TrainSchedItem() = delete;

	TrainSchedItem(
			const Station & _arriveStation,
			const TimeHM  & _arriveTime,
			const TimeHM  & _departureTime
	);

	~ TrainSchedItem() = default;

	/*-----------------------------------------------------------------*/

	const Station & GetArriveStation() const;
	const TimeHM    GetArriveTime   () const;
	const TimeHM    GetDepartTime   () const;

	/*-----------------------------------------------------------------*/

	bool operator == ( const TrainSchedItem & _item ) const;
	bool operator  < ( const TrainSchedItem & _item ) const;

	/*-----------------------------------------------------------------*/

	static bool IsOverlaps(
			const TrainSchedItem & _item1,
			const TrainSchedItem & _item2
	);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const Station & m_arriveStation;
	const TimeHM    m_arriveTime;
	const TimeHM    m_departureTime;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline const Station &
TrainSchedItem::GetArriveStation() const {
	return m_arriveStation;
}

inline const TimeHM
TrainSchedItem::GetArriveTime() const {
	return m_arriveTime;
}

inline const TimeHM
TrainSchedItem::GetDepartTime() const {
	return m_departureTime;
}

/*****************************************************************************/

#endif //TRAIN_SCHED_ITEM_HPP
