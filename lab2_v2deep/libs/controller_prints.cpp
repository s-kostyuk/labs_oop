//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.11.15.
//

/*****************************************************************************/

#include "controller.hpp"

#include <algorithm>
#include <map>

/*****************************************************************************/

const Controller::RoutesContainer::const_iterator
Controller::findTwoStationsInRoutes(
		const StationsContainer::iterator & _1st,
		const StationsContainer::iterator & _2nd,
		const RoutesContainer::const_iterator & _startRoute
) const
{
	return std::find_if(
			_startRoute,
			m_allRoutes.end(),
			[ & ] ( const auto & _sp ) {
				return _sp.second->HasStation( **_1st ) && _sp.second->HasStation( **_2nd );
			}
	);
}

/*****************************************************************************/

// распечатать 5 станций по убыванию, принимающих наиболее количество маршрутов
// (название станции, количество маршрутов, проходящих через станцию);
void Controller::printBusiestStations( std::ostream & _o, const long _nOfStations ) {
	typedef long Counter;

	// Контейнер для хранения информации о найденых станциях
	std::multimap< Counter, StationName > resultStations;

	// Переменная-счетчик, хранит количество маршрутов, в которых найдена текущая станция
	Counter nOfRoutes = 0;

	// TODO: Рассмотреть for_each вместо цикла
	// Цикл. Обходит станции, считает к-во маршрутов, в которых станция встретилась
	for( auto it = m_allStations.begin(); it != m_allStations.end(); ++it ) {
		nOfRoutes = std::count_if(
				m_allRoutes.begin(),
		        m_allRoutes.end(),
		        [ & ] ( const auto & _sp ) {
			        return _sp.second->HasStation( **it );
		        }
		);

		// После подсчета вставляем собранную информацию в контейнер
		resultStations.insert( std::pair< Counter, StationName >( nOfRoutes, (*it)->GetName() ) );
	}

	// Обходим собранную информацию в обратном порядке
	auto it = resultStations.rbegin();

	// Останавливаемся, когда дойдем до конца контейнера или распечатаем _nOfStations станций
	for( int i = 0; i < _nOfStations && it != resultStations.rend(); ++i, ++it )
		_o << "\n" << it->second << "\t" << it->first;
}

/*****************************************************************************/

// распечатать 5 маршрутов с самым долгим временем в пути по убыванию (номер маршрута,
// начальная и конечная станции, длительность в пути);
void Controller::printSlowestRoutes( std::ostream & _o, const long _nOfRoutes ) {
	// TODO: Ниже в этой функции творится какой-то нечитаемый ад

	// Информация об отдельном маршруте - номер маршрута, начальная и конечная станции (их имена)
	typedef std::tuple< RouteID, const StationName &, const StationName & > RouteInfo;

	// Контейнер для хранения найденной информации
	std::multimap< TimeHM::TimeDiff, RouteInfo > routeList;

	// TODO: Рассмотреть for_each вместо цикла

	// Обходим маршруты, извлекаем их длительность и другую информацию (см. RouteInfo)
	for( auto it = m_allRoutes.begin(); it != m_allRoutes.end(); ++it ) {
		// Извлекаем указатели на первую и последнюю станцию маршрута
		auto outermostStations = it->second->GetOutermostStations();

		routeList.insert(
				std::make_pair (
						it->second->GetDuration(),
						RouteInfo{
								it->first,
								outermostStations.first->GetName(),
								outermostStations.second->GetName()
						}
				)
		);
	}

	auto it = routeList.rbegin();

	// Останавливаемся, когда дойдем до конца контейнера или распечатаем _nOfStations маршрутов
	for( int i = 0; i < _nOfRoutes && it != routeList.rend(); ++i, ++it )
		_o << "\n"
			<< std::get< 0 >(it->second) << "\t" // номер маршрута
			<< std::get< 1 >(it->second) << "\t" // начальная станция
			<< std::get< 2 >(it->second) << "\t" // конечная станция
			<< it->first; // время в пути

	// Maybe FIXME: (в версии TimeHM на 26-е ноября продолжительность считается в минутах)
}

/*****************************************************************************/


/*****************************************************************************/

// распечатать все пары станций, связанных более чем двумя маршрутами;
void Controller::printMultipleConnectedStations( std::ostream & _o ) {
	typedef std::pair< const StationName &, const StationName & > NamePair;

	std::vector< NamePair > resultStations;

	RoutesContainer::const_iterator rIt;

	// Перебор первых элементов пары
	for( auto sIt = m_allStations.begin(); sIt != m_allStations.end(); ++sIt ) {
		// Перебор остальных станций
		for( auto sIt2 = sIt; sIt2 != m_allStations.end(); ++sIt2 ) {

			// TODO: Много копипасты

			// Получаем итератор на маршрут, содержащий обе станции одновременно
			auto rIt = findTwoStationsInRoutes( sIt, sIt2, m_allRoutes.begin() );

			// Если такой маршрут не встретился - идем к след. станции в паре
			if( rIt == m_allRoutes.end() )
				continue;

			// Иначе продолжаем поиски среди оставшихся маршрутов
			rIt = findTwoStationsInRoutes( sIt, sIt2, rIt );

			// Если такой маршрут не встретился - идем к след. станции в паре
			if( rIt == m_allRoutes.end() )
				continue;

			// Иначе продолжаем поиски среди оставшихся маршрутов
			rIt = findTwoStationsInRoutes( sIt, sIt2, rIt );

			// Если мы найдем третий маршрут с такой парой станций - сохраняем пару
			if( rIt != m_allRoutes.end() ) {
				resultStations.push_back(
						std::make_pair (
								sIt->get()->GetName(),
								sIt2->get()->GetName()
						)
				);
			}

		} // Конец внутреннего цикла

	} // Конец внешнего цикла

	// Печатаем
	std::for_each(
			resultStations.begin(),
			resultStations.end(),
	        [ & ] ( const NamePair & _pair ) {
		        _o << _pair.first << "\t" << _pair.second;
	        }
	);
}

/*****************************************************************************/

// распечатать станции, которые не связаны ни одним из маршрутов;
void Controller::printNonConnectedStations( std::ostream & _o ) {
	/* FIXME: Переписать, устранить дупликацию инициализации контейнера, циклов,
	 * печати результатов с printMultipleConnectedStations
	 */

	typedef std::pair< const StationName &, const StationName & > NamePair;

	std::vector< NamePair > resultStations;

	RoutesContainer::const_iterator rIt;

	// Перебор первых элементов пары
	for( auto sIt = m_allStations.begin(); sIt != m_allStations.end(); ++sIt ) {
		// Перебор остальных станций
		for( auto sIt2 = sIt; sIt2 != m_allStations.end(); ++sIt2 ) {

			// TODO: Много копипасты

			// Получаем итератор на маршрут, содержащий обе станции одновременно
			auto rIt = findTwoStationsInRoutes( sIt, sIt2, m_allRoutes.begin() );

			// Если такой маршрут не встретился - запоминаем пару
			if( rIt == m_allRoutes.end() )
				resultStations.push_back(
						std::make_pair (
								sIt->get()->GetName(),
								sIt2->get()->GetName()
						)
				);

		} // Конец внутреннего цикла

	} // Конец внешнего цикла

	// Печатаем
	std::for_each(
			resultStations.begin(),
			resultStations.end(),
			[ & ] ( const NamePair & _pair ) {
				_o << _pair.first << "\t" << _pair.second;
			}
	);
}

/*****************************************************************************/

// распечатать станции, у которых в некоторое время суток не хватит свободных перронов для
// приема всех запланированных маршрутов;
void Controller::printOverloadedStations( std::ostream & _o ) {
	//FIXME
}

/*****************************************************************************/