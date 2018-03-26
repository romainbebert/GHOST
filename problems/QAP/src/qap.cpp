#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <ghost/solver.hpp>
#include "ctr_qap.hpp"

using namespace std;

// from https://stackoverflow.com/a/236803/2007142
template<typename Out>
void split( const string &s, char delim, Out result )
{
  stringstream ss(s);
  string item;
  while( getline( ss, item, delim ) )
    *(result++) = item;
}

// from https://stackoverflow.com/a/236803/2007142
vector<string> split( const string &s, char delim )
{
  vector<string> elems;
  split( s, delim, back_inserter( elems ) );
  return elems;
}

// from https://stackoverflow.com/a/39309182/2007142
void remove_multiple_spaces( string &s )
{
  string::iterator new_end = 
    unique( s.begin(), s.end(),
	   [](char lhs, char rhs){ return (lhs == rhs) && (lhs == ' '); } );
  s.erase( new_end, s.end() );

  // remove first character if it is a space
  if( s[0] == ' ' )
    s.erase( s.begin() );
}

#if DEBUG
void print_matrix( const vector< vector<int> > &vec )
{
  for( const auto& line : vec )
  {
    for( const auto& number : line )
      cout << number << " ";
    cout << "\n";
  }
  cout << "\n";
}
#endif

void process_input( char* arg,
		    int &size,
		    int &X,
		    vector< vector<int> > &md,
		    vector< vector<int> > &mf )
{
  string line;
  ifstream file( arg );

  if( file.is_open() )
  {
    // get instance size
    getline( file, line );
    size = stoi( line );

    // create empty matrices
    md.resize( size );
    for( int i = 0 ; i < size ; ++i )
      md[i].resize( size );

    mf.resize( size );
    for( int i = 0 ; i < size ; ++i )
      mf[i].resize( size );

    // get value X
    getline( file, line );
    X = stoi( line );

    // eat empty line
    getline( file, line );

#if DEBUG
    cout << "Size: " << size << "\n"
	 << "X: " << X << "\n";
#endif
    
    // fill up matrix_distances
    for( int i = 0 ; i < size ; ++i )
    {
      getline( file, line );
      remove_multiple_spaces( line );
      auto vec_strings = split( line, ' ' );

      for( int j = 0 ; j < size ; ++j )
	md[i][j] = stoi( vec_strings[j] );
    }

    // eat empty line
    getline( file, line );
      
    // fill up matrix_flows
    for( int i = 0 ; i < size ; ++i )
    {
      getline( file, line );
      remove_multiple_spaces( line );
      auto vec_strings = split( line, ' ' );

      for( int j = 0 ; j < size ; ++j )
	mf[i][j] = stoi( vec_strings[j] );
    }

#if DEBUG
    print_matrix( md );
    print_matrix( mf );
#endif
    
    file.close();
  }
  else cout << "Unable to open file";
}

int main( int argc, char* argv[] )
{
  if( argc != 2 )
  {
    cout << "Usage: " << argv[0] << " <file>";
    return EXIT_FAILURE;
  }

  int size;
  int X;
  vector< vector<int> > matrix_distances;
  vector< vector<int> > matrix_flows;

  process_input( argv[1], size, X, matrix_distances, matrix_flows );

  vector<Variable> variables;
  for( int i = 0 ; i < size ; ++i )
    variables.emplace_back( ""+i, ""+i, size, 1 );
  QAPConstraint constraint( &variables, size, X, matrix_distances, matrix_flows );

  vector< QAPConstraint > constraints { constraint };
  
  Solver<Variable, QAPConstraint> solver( variables, constraints, true );

  double cost = 0.;
  vector<int> solution( size, 0 );
    
  solver.solve( cost, solution, 10 );

  if( cost == 0. )
  {
    for( const auto &v : solution )
      cout << v << " ";
    cout << "\n";
  }
  else
    cout << "Solution not found.\n";  
  
  return EXIT_SUCCESS;
}
