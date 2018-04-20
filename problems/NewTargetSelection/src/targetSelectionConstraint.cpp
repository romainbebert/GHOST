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


TargetSelectionConstraint::TargetSelectionConstraint( vector<Variable>* variables, Unit &currUnit, vector<UnitEnemy> &enemies, int index) 
	: Constraint(variables), currUnit(currUnit), enemies(enemies), index(index) {}

double TargetSelectionConstraint::required_cost() const
{
	double conflicts = 0.;
	// A unit u is badly assigned to a target t iif:
    // 1. u can shoot
    // 2. u has at least one living reachable target in its range
    // 3. t is the dummy target (-1) or t in unreachable from u or t is dead
	if( currUnit.canShoot() && !currUnit.getLivingEnemiesInRange(enemies).empty() 
		&& ( variables->at(index).get_value() == -1 || !enemies.at(variables->at(index).get_value()).isInRangeAndAlive(currUnit) ) ) 
	{
		++conflicts;
	}
	//If no enemies in range and variable isn't set to -1
	if( currUnit.getLivingEnemiesInRange(enemies).empty() && variables->at(index).get_value() != -1 ) 
		++conflicts;

	return conflicts;
}
