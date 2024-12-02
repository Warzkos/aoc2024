// just bruteforce answer

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool isSafe( std::vector<int> report )
{
   bool isIncreasing = report[ 0 ] < report[ 1 ];
   int prevVal = report[ 0 ];

   for( auto i = 1; i < report.size(); i++ )
   {
      if( ( report[ i ] <= prevVal && isIncreasing ) || ( report[ i ] >= prevVal && !isIncreasing ) )
      {
         return false;
      }
      if( std::abs( report[ i ] - prevVal ) > 3 )
      {
         return false;
      }

      prevVal = report[ i ];
   }

   return true;
}

bool isSafeBruteForce( std::vector<int> report )
{
   bool safe = false;

   for( auto i = 0; i < report.size(); i++ )
   {
      std::vector<int> temp = report;
      temp.erase( temp.begin() + i );

      if( isSafe( temp ) )
      {
         safe = true;
         break;
      }
   }

   return safe;
}

int main()
{
   int safeCnt = 0;
   std::fstream file( "input.txt" );

   std::string line;
   while( getline( file, line ) )
   {
      std::stringstream ss( line );
      std::vector<int> report;

      int value;
      while( ss >> value )
      {
         report.push_back( value );
      }

      if( isSafeBruteForce( report ) )
      {
         safeCnt++;
      }
   }

   std::cout << safeCnt << std::endl;

   return 0;
}