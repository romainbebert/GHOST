#pragma once

#include <vector>
#include <algorithm>

#include <ghost/constraint.hpp>
#include <ghost/variable.hpp>

using namespace std;
using namespace ghost;

class QAPConstraint : public Constraint<Variable>
{
  int _size;
  int _X;
  vector< vector<int> > _matrix_distances;
  vector< vector<int> > _matrix_flows;
  
  double required_cost() const override;

public:
  QAPConstraint( vector< Variable > *variables,
		 int size,
		 int X,
		 vector< vector<int> > &md,
		 vector< vector<int> > &mf );
};
