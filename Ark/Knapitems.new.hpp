/* ***************************************************

    Mark Sattolo (msattolo@sympatico.ca)
   -----------------------------------------------
     $Source: c:\prog\cvslocal/KnapsackNewCpp/src/node.hpp,v $
     $Revision: #1 $
     $Date: 2010/10/23 $

*************************************************** */

#ifndef MHS_KNAPSACKNEWCPP_KNAPITEMS_HPP
#define MHS_KNAPSACKNEWCPP_KNAPITEMS_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std ;

namespace mhs_knapsacknewcpp_items
{

// store and manipulate the (attributes of the) items
// which are to be placed in the knapsack
class Knapitem
{
 protected:

     string	_name   ;
     int	  _level  ; // in the state space tree
     int	  _profit ;
     int	  _weight ;
     float	_pwr    ; // profit to weight ratio
     float	_bound  ; // i.e. potential max profit of each node

 public:

		 // default Constructor
     Knapitem( string s, int l=0 )
     {
       _name.assign( s ) ;
       _level  = l ;
       _profit = _weight = 0 ;
       _pwr    = _bound  = 0.0 ;
     };

     // usual Constructor
     Knapitem( string s, int p, int w, int l=0, float b=0.0 )
     {
       _name.assign( s );
       _level  = l ;
       _profit = p ;
       _weight = w ;
       _pwr    = (w > 0) ? (static_cast<float>(p)/static_cast<float>(w)) : 0.0 ;
       _bound  = b ;
     };

     // Accessor & Mutator functions

     string  name() const { return _name ; };
     void    name( string s ) { _name.assign( s ); };
     void    addname( string s ) { _name.append( s ); };

     int     level() const { return _level ; };
     void    level( int l ) { _level = l ; };

     int     profit() const { return _profit ; };
     void    profit( int p ) { _profit = p ; };

     int     weight() const { return _weight ; };
     void    weight( int w ) { _weight = w ; };

     float   pwr() const { return _pwr ; };
     void    pwr( float r ) { _pwr = r ; };

     float   bound() const { return _bound ; };
     void    bound( float b ) { _bound = b ; };

     // operator modification
     Knapitem operator=( Knapitem k )
     {
       _name   = k.name()  ;
       _level  = k.level() ;
       _profit = k.profit() ;
       _weight = k.weight() ;
       _pwr    = k.pwr() ;
       _bound  = k.bound() ;

       return *this ;
     };

     // debug
     void display( ostream &strm ) const
     {
       strm << setw(25) << _name << ": lev " << setw(3) << _level ;
       strm << " ; prof " << setw(6) << _profit ;
       strm << " ; wt " << setw(5) << _weight ;
       strm.setf( ios_base::fixed, ios_base::floatfield );
       strm << setprecision(3) << " ; bnd " << setw(9) << _bound ;
       strm << " ; pwr " << setw(7) << _pwr << endl ;
     };

     // FUNCTIONS TO ENABLE less<Knapitem>
     friend bool operator< ( const Knapitem&, const Knapitem& );
     friend bool operator== ( const Knapitem&, const Knapitem& );

};// class Knapitem


/*
	PRIORITY QUEUE FUNCTIONS
	- priority queue used to store the state space tree in bestFirstSearch()
*/

// typedefs for STL type 'priority_queue'
// - see "The C++ Standard Template Library", by Plauger et al., p.455
typedef allocator<Knapitem> knapPqAlloc ;
typedef less<Knapitem> knapPqPredicate ;
typedef vector<Knapitem, knapPqAlloc> knapPqSequence ;
typedef priority_queue<Knapitem, knapPqSequence, knapPqPredicate> knapPqContainer ;
knapPqContainer::container_type *p_cont = (knapPqSequence*)0 ;
knapPqContainer::value_type *p_val = (Knapitem*)0 ;
knapPqContainer::size_type *p_size = (size_t*)0 ;


// function objects for ordering the priority_queues
bool operator< ( const Knapitem& k1, const Knapitem& k2 )
{
  if( k1.bound() < k2.bound() )
    return true ;

  return false ;
}

bool operator== ( const Knapitem& k1, const Knapitem k2 )
{
  return( k1.bound() == k2.bound() );
}


// FIXME: CAN'T GET THIS ONE TO WORK !
struct order_bound
{
  bool operator()( Knapitem a, Knapitem b ) const
  {
    return( a.bound() < b.bound() );
  }
};

// displayPq()
void displayPq( knapPqContainer pq, ostream &strm )
{
  strm << endl << "top of Pq:" << endl ;
  pq.top().display( strm );

  // ??displayVector( reinterpret_cast< vector<Knapitem&> >( pq ) );
}

/*
	VECTOR FUNCTIONS
  - vector used to store the Knapitem items, sort them and display them
*/

// typedef for vector
typedef vector<Knapitem> knapVector ;

// function object for ordering the vector
struct order_pwr
{
  bool operator()( Knapitem a, Knapitem b ) const
  {
    return( a.pwr() > b.pwr() ); // descending order
  }
};

// debug
void displayVector( knapVector v, ostream &strm )
{
  int i=1 ;
  knapVector::iterator vit = v.begin();

  strm << endl << "Vector Elements:" << endl ;
  while( vit != v.end() )
  {
    strm << " #" << i << " " ;
    (*vit).display( strm );

    vit++ ;
    i++ ;
  }
  //strm << endl ;
}

}// namespace mhs_knapsacknewcpp_items

#endif // MHS_KNAPSACKNEWCPP_KNAPITEMS_HPP
