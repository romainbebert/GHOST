

#pragma once

#include <vector>
#include <map>
#include <memory>
#include <ghost/objective.hpp>

using namespace std;
using namespace ghost;

class QAPObjective : public Objective<Variable> {

	double required_cost(vector<Variable> *variables) const override;

	private:
		int size;
		vector< vector<int> > dist_matrix;
		vector< vector<int> > flux_matrix;

	public:
		QAPObjective( string name, int size,
		 vector< vector<int> > &dist_matrix,
		 vector< vector<int> > &flux_matrix );

};