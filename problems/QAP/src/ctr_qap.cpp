#include "ctr_qap.hpp"

double QAPConstraint::required_cost() const
{
  int sum = 0;
  for( int i = 0 ; i < _size ; ++i )
    for( int j = i + 1 ; j < _size ; ++j )
      sum += ( _matrix_distances[ variables->at(i).get_value() ][ variables->at(j).get_value() ] * _matrix_flows[i][j] );
  
  std::max( 0, sum - _X );
}

QAPConstraint::QAPConstraint( vector< Variable > *variables,
			      int size,
			      int X,
			      vector< vector<int> > &md,
			      vector< vector<int> > &mf )
  : Constraint<Variable>	( variables ),
  _size				( size ),
  _X				( X ),
  _matrix_distances		( md ),
  _matrix_flows			( mf )
{ }
