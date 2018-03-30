
#include <vector>
#include <map>
#include <memory>
#include <ghost/objective.hpp>

#include "QAPObjective.hpp"


using namespace std;
using namespace ghost;


	double QAPObjective::required_cost(vector<Variable> *variables) const {
		double sum = 0.;
		for( int i = 0 ; i < size ; ++i )
		  for( int j = i + 1 ; j < size ; ++j )
		    sum += ( dist_matrix[ variables->at(i).get_value() ][ variables->at(j).get_value() ] * flux_matrix[i][j] );
		#if DEBUG
  		//cout << "Objective value : " << sum << endl;
  		#endif
  		return sum;
	}

	QAPObjective::QAPObjective( string name, int size,
	 vector< vector<int> > &dist_matrix,
	 vector< vector<int> > &flux_matrix ) 
	: Objective<Variable>(name), size(size), dist_matrix(dist_matrix), flux_matrix(flux_matrix) { }
