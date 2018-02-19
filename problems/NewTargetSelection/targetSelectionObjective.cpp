/*
 * GHOST (General meta-Heuristic Optimization Solving Tool) is a C++ library 
 * designed to help developers to model and implement optimization problem 
 * solving. 
 * GHOST is a meta-heuristic solver aiming to solve any kind of combinatorial 
 * and optimization real-time problems represented by a CSP/COP. 
 * GHOST has been first developped to help making AI for the RTS game
 * StarCraft: Brood war, but can be used for any kind of applications where 
 * solving combinatorial and optimization problems within some tenth of 
 * milliseconds is needed. It is a generalization of the Wall-in project.
 * Please visit https://github.com/richoux/GHOST for further information.
 * 
 * Copyright (C) 2014-2016 Florian Richoux
 *
 * This file is part of GHOST.
 * GHOST is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as published 
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * GHOST is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with GHOST. If not, see http://www.gnu.org/licenses/.
 */


#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdlib>

#include "targetSelectionObjective.hpp"

using namespace std;
using namespace ghost;

/****************************/
/* TargetSelectionObjective */
/****************************/

TargetSelectionObjective::TargetSelectionObjective( const string &name ) : Objective<Variable>( name ) { }

/*************/
/* MaxDamage */
/*************/

MaxDamage::MaxDamage() : TargetSelectionObjective("MaxDamage") {}

double MaxDamage::required_cost( vector<Variable> *variables, vector<Unit> allies, vecotr<UnitEnemy enemies>) {
	double damages =0;
	vector<double> hits;

	for(int i = 0; i < variables->size(); ++i){
		currVar = variables->at(i);
		if(currVar.getValue() != -1) {
			currUnit = allies.at(i);
			hits = currUnit.computeDamage(currVar.getValue() ,enemies);
			for_each( begin(hits), end(hits), [&](double d){ damages +=d; });
		}
	}

	return -damage;
}

/***********/
/* MaxKill */
/***********/

MaxKill::MaxKill() : TargetSelectionObjective("MaxKill") {}

double MaxKill::required_cost( vector<Variable> *variables, vector<Unit> allies, vecotr<UnitEnemy enemies>) {
	vector<double> hits;
	vector<UnitEnemy> copyEnemies(*enemies);

	for(int i = 0; i < variables->size(); ++i){
		currVar = variables->at(i);
		currUnit = allies.at(i);
		if(currVar.getValue() != -1) {
			hits = currUnit.computeDamage(currVar.getValue() ,enemies);
			for( int i = 0; i < allies.size(); ++i )
				copyEnemies[i].data.hp -= hits[i];
		}
	}

	return -count_if(begin(copyEnemies), end(copyEnemies), [](UnitEnemy &u){ return u.isDead(); } );
}