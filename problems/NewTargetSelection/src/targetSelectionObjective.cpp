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

TargetSelectionObjective::TargetSelectionObjective(  string name,  vector<Variable> vecVariables,  vector<Unit> allies,  vector<UnitEnemy> enemies ) 
													: Objective<Variable>(name), vecVariables(vecVariables), allies(allies), enemies(enemies)  { }

/*************/
/* MaxDamage */
/*************/

MaxDamage::MaxDamage( vector<Variable> vecVariables,  vector<Unit> allies,  vector<UnitEnemy> enemies) 
					: TargetSelectionObjective("MaxDamage", vecVariables, allies, enemies) {}

double MaxDamage::required_cost() {
	double damages =0;
	vector<double> hits;

	for(int i = 0; i < vecVariables.size(); ++i){
		Variable currVar = vecVariables.at(i);
		if(currVar.get_value() != -1) {
			Unit currUnit = allies.at(i);
			hits = currUnit.computeDamage(&enemies);
			for_each( begin(hits), end(hits), [&](double d){ damages +=d; });
		}
	}

	return -damages;
}

/***********/
/* MaxKill */
/***********/

MaxKill::MaxKill( vector<Variable> vecVariables,  vector<Unit> allies,  vector<UnitEnemy> enemies) 
				: TargetSelectionObjective("MaxKill", vecVariables, allies, enemies) {}

double MaxKill::required_cost() {
	vector<double> hits;
	vector<UnitEnemy> copyEnemies(enemies);

	for(int i = 0; i < vecVariables.size(); ++i){
		Variable currVar = vecVariables.at(i);
		Unit currUnit = allies.at(i);
		if(currVar.get_value() != -1) {
			hits = currUnit.computeDamage(&enemies);
			for( int i = 0; i < allies.size(); ++i )
				copyEnemies[i].data.hp -= hits[i];
		}
	}

	return -count_if(begin(copyEnemies), end(copyEnemies), [](UnitEnemy &u){ return u.isDead(); } );
}