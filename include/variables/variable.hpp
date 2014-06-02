/*
 * GHOST (General meta-Heuristic Optimization Solving Tool) is a C++ library 
 * designed for StarCraft: Brood war. 
 * GHOST is a meta-heuristic solver aiming to solve any kind of combinatorial 
 * and optimization RTS-related problems represented by a CSP. 
 * It is an extension of the project Wall-in.
 * Please visit https://github.com/richoux/GHOST for further information.
 * 
 * Copyright (C) 2014 Florian Richoux
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


#pragma once

#include <algorithm>
#include <iostream>

using namespace std;

namespace ghost
{
  class Variable
  {
  public:
    Variable( string, int = -1 )
    
    virtual bool operator<( const Variable& other ) const = 0;
    
    inline void		setValue( int v )			{ value = v; }
    inline void		shiftValue()				{ ++value; }
    inline int		getValue()			const	{ return value; }
    inline int		getId()				const	{ return id; }
    inline string	getName()			const	{ return name; }
    inline void		swapValue( Variable &other )		{ std::swap(this->value, other.value); }

    virtual friend ostream& operator<<( ostream&, const Variable& );
    
  protected:
    string	name;
    int		id;
    int		value;
    
  private:
    static int numberVariables;
  };
}