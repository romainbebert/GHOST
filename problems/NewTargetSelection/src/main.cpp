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

vector<int> getLivingEnemiesInRange( const UnitEnemy &u, const vector<Unit> &vec )
{
  vector<int> inRange;

  for( int j = 0 ; j < vec.size() ; ++j )
    if( u.isInRangeAndAlive( vec[j] ) )
      inRange.push_back( j );
      
  return inRange;
}

int getLowestHPUnit( const vector<int> &inRange, const vector<Unit> &vec )
{
  double minHP = std::numeric_limits<double>::max();
  vector<int> ties;
  
  for( int i = 0 ; i < inRange.size() ; ++i )
    if( vec[i].getHP() == minHP )
      ties.push_back( i );
    else if( vec[i].getHP() < minHP )
    {
      ties.clear();
      ties.push_back( i );
      minHP = vec[i].getHP();
    }
    return rand() % ties.size();
  //return random.get_random_number( ties.size() );
}

int getLowestHPRatioUnit( const vector<int> &inRange, const vector<Unit> &vec )
{
  double minHP = std::numeric_limits<double>::max();
  double ratio;
  vector<int> ties;
  
  for( int i = 0 ; i < inRange.size() ; ++i )
    if( ( ratio = vec[i].getHP() / vec[i].getInitialHP() ) == minHP )
      ties.push_back( i );
    else if( ratio < minHP )
    {
      ties.clear();
      ties.push_back( i );
      minHP = ratio;
    }

    return rand() % ties.size();
  //return random.get_random_number( ties.size() );
}

int main(int argc, char **argv) {
	int experimentSize = 1;
	int sat = 50;
	int opt = 150;
	if( argc > 1 )
		experimentSize = stoi(argv[1]);
	if( argc > 2 )
		sat = stoi(argv[2]);
	if( argc > 3 )
		opt = stoi(argv[3]);

	vector<int> domain(15);
	iota(domain.begin(),domain.end(), -1);
	/*vector<Variable> vecVariables[14] = {	
		{Variable("Terran_Marine","Terran_Marine",domain,-1)},
		{Variable("Terran_Marine","Terran_Marine",domain,-1)},
		{Variable("Terran_Marine","Terran_Marine",domain,-1)},
		{Variable("Terran_Marine","Terran_Marine",domain,-1)},
		{Variable("Terran_Marine","Terran_Marine",domain,-1)},
		{Variable("Terran_Goliath","Terran_Goliath",domain,-1)},
		{Variable("Terran_Vulture","Terran_Vulture",domain,-1)},
		{Variable("Terran_Vulture","Terran_Vulture",domain,-1)},
		{Variable("Terran_Goliath","Terran_Goliath",domain,-1)},
		{Variable("Terran_Siege_Tank_Tank_Mode","Terran_Siege_Tank_Tank_Mode",domain,-1)},
		{Variable("Terran_Gost","Terran_Gost",domain,-1)},
		{Variable("Terran_Gost","Terran_Gost",domain,-1)},
		{Variable("Terran_Siege_Tank_Tank_Mode","Terran_Siege_Tank_Tank_Mode",domain,-1)},
		{Variable("Terran_Siege_Tank_Siege_Mode","Terran_Siege_Tank_Siege_Mode",domain,-1)}
	};*/

	for( int k = 0; k < experimentSize; ++k ) 
	{
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

	vector< shared_ptr<Constraint> > constraints;
	for(int i = 0; i < 12; ++i) {
		//TargetSelectionConstraint constraint(v, units[i], enemies);
		constraints.emplace_back(make_shared<TargetSelectionConstraint>(&(variables), units[i], enemies, i));
	}
	
	Solver solver(variables, constraints,make_shared<MaxDamage>(units, enemies));

double finalCost;
vector<int> finalSolution;

vector<int> inRange;

int numUnits = units.size();
int numEnemy = enemies.size();
vector<int> aimedUnits(numUnits, -1);

int deadUnits;
int deadEnemy;

double totalDamages;
double totalDamagesEnemy;

int tour = 1;

vector<UnitEnemy> copyEnemies( enemies );

//Do TS turns until someone loses
do {
	//First we verify if no unit can shoot, to avoid useless calls to solve
	if( none_of( begin(units), end(units), [&](Unit &u){return !u.isDead() && u.canShoot() && !u.getLivingEnemiesInRange(enemies).empty(); } )
	&& none_of( begin(enemies), end(enemies), [&](UnitEnemy &e){return !e.isDead() && e.canShoot() && !getLivingEnemiesInRange(e, units).empty(); } ) ) 
	{
    for_each( begin(units), end(units), [](Unit &u){u.oneStep();} );
    for_each( begin(enemies), end(enemies), [](UnitEnemy &e){e.oneStep();} );
    continue;
	}

	solver.solve( finalCost, finalSolution, sat, opt);

	cout << endl << endl << "Turn : " << tour << endl << "Solution found : " << endl;
	for (int e : finalSolution)
		std::cout << e << " ";

 	tour++;
	totalDamages = 0.;
	totalDamagesEnemy = 0.;

	#ifndef NDEBUG
		cout << endl << ":::: My turn ::::" << endl;
	#endif

	for(int i = 0; i < enemies.size(); ++i)
		copyEnemies[i].data.hp = enemies[i].data.hp;

	for(int i = 0; i < variables.size(); ++i)
		if(!units.at(i).isDead()) {
			//If canShoot && not assigned to -1, do damages
			if( units.at(i).canShoot() && variables.at(i).get_value() != -1)
				totalDamages += units.at(i).doDamage( copyEnemies, variables.at(i).get_value());
			//if NOT, make step
			else {
				#ifndef NDEBUG 
	  			cout << units.at(i).getFullName() << ":" << i << " HP=" << units.at(i).getHP() << ", wait=" << units.at(i).canShootIn() << " (value="<< variables.at(i).get_value() <<")" << endl;
				#endif
	  			if( !units.at(i).canShoot() )
	  				units.at(i).oneStep();
			}
		}

		std::cout << "Total Damage : " << totalDamages << endl;


	#ifndef NDEBUG
		cout << "@@@@ Enemy's turn @@@@" << endl;
	#endif

	fill(aimedUnits.begin(), aimedUnits.end(), -1);

	//Choosing targets for each enemies
	for( int i = 0; i < enemies.size(); ++i )
		if( !enemies.at(i).isDead() && enemies.at(i).canShoot() ) {
			inRange = getLivingEnemiesInRange(enemies.at(i), units);

			if(!inRange.empty()) {
				/* Random shot
				aimedUnits[i] = inRange[ rand() % inRange.size() ];
				/*/
				aimedUnits[i] = inRange[ getLowestHPRatioUnit(inRange, units) ];
				//*/
			}
		}

	//Info printing and decrement cooldowns
	for(int i = 0; i < enemies.size(); ++i) {
		if( !enemies[i].isDead() ) {
			if( enemies[i].canShoot() ) {
				if( aimedUnits[i] != -1 )
					totalDamagesEnemy += enemies.at(i).doDamageAgainst( aimedUnits[i], units, i );
				#ifndef NDEBUG
				else
	    		cout << enemies[i].data.name << "@" << i << " HP=" << enemies[i].data.hp << ", wait=" << enemies[i].data.canShootIn << endl;	    
				#endif
	    } else {
	    	#ifndef NDEBUG
	  			cout << enemies[i].data.name << "@" << i << " HP=" << enemies[i].data.hp << ", wait=" << enemies[i].data.canShootIn << endl;
				#endif
	  		if( !enemies.at(i).canShoot() )
	  			enemies.at(i).oneStep();
	    }
		}
	}

	for(int i = 0; i < enemies.size(); ++i) 
		enemies.at(i).data.hp = copyEnemies.at(i).data.hp;

	deadUnits = count_if( begin(units), end(units), [](Unit &u){return u.isDead();});
	deadEnemy = count_if( begin(enemies), end(enemies), [](UnitEnemy &e){return e.isDead();});

	#ifndef NDEBUG 
		cout << "XXXX Turn's over XXXX" << endl
				 << "Total damages from you : " << totalDamages << endl
				 << "Total damages from the enemy : " << totalDamagesEnemy << endl 
				 << "Number of dead units : " << deadUnits << endl
				 << "Number of dead enemies : " << deadEnemy << endl;
		//cout << "Press enter for next turn" << endl;
		//cin.get();
	#endif
} while( deadUnits < numUnits && deadEnemy < numEnemy && tour < 150);

double total_hp = 0.;

if( count_if( begin(enemies), end(enemies), [&](UnitEnemy &e){ return e.isDead(); }) == numEnemy
	&& count_if( begin(units), end(units), [&](Unit &u){ return u.isDead(); }) < numUnits )
{
	for(const auto &u : units )
		if( !u.isDead() ) 
			total_hp += u.getHP();

		cout << endl << endl 
				 << "Winner: You!" << endl 
				 << "Diff : " << deadEnemy - deadUnits << endl 
				 << "HP : " << total_hp << endl;

		#ifndef NDEBUG
			for( int i = 0; i < units.size(); ++i)
	      cout << units.at(i).getFullName() << ":" << i << " " << units.at(i).getHP() << " HP left" << endl;
	  #endif
	} else if( count_if( begin(enemies), end(enemies), [&](UnitEnemy &e){ return e.isDead(); }) < numEnemy
	&& count_if( begin(units), end(units), [&](Unit &u){ return u.isDead(); }) == numUnits )
	{ 
		for(const auto &u : enemies )
			if( !u.isDead() ) 
				total_hp += u.data.hp;

		cout << endl << "--------------------------------------------------------" << endl << endl
				 << "Winner: The enemy..." << endl 
				 << "Diff : " << deadEnemy - deadUnits << endl 
				 << "HP : " << total_hp << endl;

		#ifndef NDEBUG
			for( int i = 0; i < enemies.size(); ++i)
	      cout << enemies.at(i).data.name << "@" << i << " " << enemies.at(i).data.hp << " HP left" << endl;
	  #endif
	} else {
		cout << endl << "Draw!" << endl;
	}
}
}


