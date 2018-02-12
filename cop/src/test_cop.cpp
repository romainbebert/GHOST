
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <string>

#include <ghost/constraint.hpp>
#include <ghost/objective.hpp>
#include <ghost/solver.hpp>
#include <ghost/domain.hpp>

using namespace ghost;
using namespace std;


class MyConstraint : public Constraint<Variable>
{
  double required_cost() const override
  {
    return 0.;
    /*return all_off(	variables.begin()+1, variables.end(), 
    				[&](const Variable & r) {
    			   		return r.getValue() != variables.front().getValue();
    			   	});
    */

  }

public:
  MyConstraint() = default;
  
  MyConstraint( vector< Variable > *variables )
    : Constraint( variables ) {}

  Variable& get_var( int index ) const { return (*variables)[index]; }
};



template <typename TypeVariable>
class MyObjective : public Objective<TypeVariable> {

	private :
		double required_cost(vector<TypeVariable> *variables) const {
			vector<int> preferred = {3,4,7,11,18};
			int tot = 0;

			for (int i = 0; i < 5; ++i) {
				tot += abs((*variables)[i].get_value() - preferred[i]);
			}

			return tot;
		}

	public:
		MyObjective(const string& name) : Objective<TypeVariable>(name) {}

};

int main() {

	vector<int> list = {1,2,5,7,13,21};

	//Domain list = Domain(skis);

	vector<Variable> vars = { Variable("3","3", list), Variable("4","4", list), 
						 Variable("7","7", list), Variable("11","11", list),
						 Variable("18","18", list) } ;


	vector<MyConstraint> ctr;
	ctr.push_back({&vars});

	MyObjective<Variable> obj("littlest differences");

	//Solver<Variable,MyConstraint> solver(&vars, &list, ctr, obj);
	Solver<Variable,MyConstraint> solver(vars, ctr, make_shared<MyObjective<Variable>>(obj));

	double finalCost;
	vector<int> finalSolution;

	solver.solve(finalCost, finalSolution,10);

	cout << "final cost = "<< finalCost << " | solution : ";
    for (int& e : finalSolution)
        cout << e << " ";
    cout << endl;

    return 0;

}
