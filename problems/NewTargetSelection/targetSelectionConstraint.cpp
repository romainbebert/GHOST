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
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

#include "targetSelectionConstraint.hpp"

using namespace std;
using namespace ghost;

// targetSelectionConstraint::targetSelectionConstraint(const vector<Variable> *variables, vector<Unit> allies, vector<UnitEnemy> enemies) 
// 	: Constraint<Variable>(variables), allies(allies) {}

// double targetSelectionConstraint::required_cost(Variable &currentUnit, 
// 												const std::vector<int> &newTarget,
// 												shared_ptr< Objective<Variable> > objective) 
// {
// 	double conflicts = 0.;
// 	for(int i = 0; i < variables->size(); ++i) {
//		Variable currVar = variables->get(i);
// 		Unit currUnit = allies.get(i);
// 		// A unit u is badly assigned to a target t iif:
// 	    // 1. u can shoot
// 	    // 2. u has at least one living reachable target in its range
// 	    // 3. t is the dummy target (-1) or t in unreachable from u or t is dead
// 		if( currUnit.canShoot() && !currUnit.getLivingEnemiesInRange(enemies).empty() 
// 			&& ( currVar.getValue() == -1 || !enemies.get(currVar.getValue()).isInRangeAndAlive(currUnit) ) ) 
// 		{
// 			++conflicts;
// 		}
		//If no enemies in range and variable isn't set to -1
// 		if( currUnit.getEnemiesInRange(enemies).empty() && currVar.getValue() != -1 ) 
// 			++conflicts;
// 	}

// 	return conflicts;
// }

targetSelectionConstraint::targetSelectionConstraint(const Variable *variable, Unit unit, vector<UnitEnemy> enemies) 
	: Constraint<Variable>(variable), allies(unit), enemies(enemies) {}

double targetSelectionConstraint::required_cost(Variable &currentUnit, 
												const std::vector<int> &newTarget,
												shared_ptr< Objective<Variable> > objective) 
{
	double conflicts = 0.;
	// A unit u is badly assigned to a target t iif:
    // 1. u can shoot
    // 2. u has at least one living reachable target in its range
    // 3. t is the dummy target (-1) or t in unreachable from u or t is dead
	if( unit.canShoot() && !unit.getLivingEnemiesInRange(enemies).empty() 
		&& ( variable.getValue() == -1 || !enemies.get(variable.getValue()).isInRangeAndAlive(currUnit) ) ) 
	{
		++conflicts;
	}
	//If no enemies in range and variable isn't set to -1
	if( unit.getEnemiesInRange(enemies).empty() && variable.getValue() != -1 ) 
		++conflicts;
	}

	return conflicts;
}