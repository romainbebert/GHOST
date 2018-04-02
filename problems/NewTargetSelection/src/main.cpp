#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "unit.hpp"
#include "targetSelectionConstraint.hpp"
#include "targetSelectionObjective.hpp"
#include "unitMap.hpp"

#include <ghost/variable.hpp>
#include <ghost/solver.hpp>

using namespace ghost;
using namespace std;

int main(int argc, char **argv) {
	int sat = 20;
	int opt = 30;
	if( argc > 1 )
		sat = stoi(argv[1]);
	if( argc > 2 )
		opt = stoi(argv[2]);

	vector<int> domain(15);
	iota(domain.begin(),domain.end(), -1);
	vector<Variable> variables {
		Variable("Terran_Marine","Terran_Marine",domain,-1),
		Variable("Terran_Marine","Terran_Marine",domain,-1),
		Variable("Terran_Marine","Terran_Marine",domain,-1),
		Variable("Terran_Marine","Terran_Marine",domain,-1),
		Variable("Terran_Marine","Terran_Marine",domain,-1),
		Variable("Terran_Goliath","Terran_Goliath",domain,-1),
		Variable("Terran_Vulture","Terran_Vulture",domain,-1),
		Variable("Terran_Vulture","Terran_Vulture",domain,-1),
		Variable("Terran_Goliath","Terran_Goliath",domain,-1),
		Variable("Terran_Siege_Tank_Tank_Mode","Terran_Siege_Tank_Tank_Mode",domain,-1),
		Variable("Terran_Gost","Terran_Gost",domain,-1),
		Variable("Terran_Gost","Terran_Gost",domain,-1),
		Variable("Terran_Siege_Tank_Tank_Mode","Terran_Siege_Tank_Tank_Mode",domain,-1),
		Variable("Terran_Siege_Tank_Siege_Mode","Terran_Siege_Tank_Siege_Mode",domain,-1)
	};

	// Define Units
  vector< Unit > units {
    Unit( unitOf["Terran_Marine"], {30, 30} ), // 0
      Unit( unitOf["Terran_Marine"], {50, 30} ), // 1
      Unit( unitOf["Terran_Marine"], {70, 30} ), // 2
      Unit( unitOf["Terran_Marine"], {90, 30} ), // 3
      Unit( unitOf["Terran_Marine"], {110, 30} ), // 4
      Unit( unitOf["Terran_Goliath"], {10, 65} ), // 5
      Unit( unitOf["Terran_Vulture"], {50, 65} ), // 6
      Unit( unitOf["Terran_Vulture"], {90, 65} ), // 7
      Unit( unitOf["Terran_Goliath"], {130, 65} ), // 8
      Unit( unitOf["Terran_Siege_Tank_Tank_Mode"], {10, 102} ), // 9
      Unit( unitOf["Terran_Ghost"], {65, 102} ), // 10
      Unit( unitOf["Terran_Ghost"], {75, 102} ), // 11
      Unit( unitOf["Terran_Siege_Tank_Tank_Mode"], {130, 102} ), // 12
      Unit( unitOf["Terran_Siege_Tank_Siege_Mode"], {70, 139} ) // 13
  };
  // Define enemies, mirror to our units
  vector< UnitEnemy > enemies;
  for( int i = 0 ; i < units.size() ; ++i )
    enemies.emplace_back( UnitEnemy( units.at(i).getData(), { units.at(i).getX(), -units.at(i).getY() } ) );

	vector<TargetSelectionConstraint> constraints;
	for(int i = 0; i < 12; ++i) {
		//TargetSelectionConstraint constraint(v, units[i], enemies);
		constraints.push_back({&variables, units[i], enemies});
	}
	
	MaxDamage mdobj(units, enemies);

	Solver<Variable, TargetSelectionConstraint> solver(variables, constraints,make_shared<MaxDamage>(mdobj));

	double finalCost;
	vector<int> finalSolution;
	
	solver.solve(finalCost, finalSolution, sat, opt);

	cout << "final cost = "<< finalCost << " | solution : ";
    for (int& e : finalSolution)
        cout << e << " ";
    cout << endl;

    return 0;
}

