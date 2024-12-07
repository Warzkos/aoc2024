#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

std::string toBinary( int n )
{
   std::string r;
   while( n != 0 )
   {
      r = ( n % 2 == 0 ? "0" : "1" ) + r;
      n /= 2;
   }
   return r;
}

int main()
{
   std::fstream file( "input.txt" );

   std::regex numberPattern( "[\\d]+" );

   std::vector<long long> answer;
   std::vector<std::vector<int>> number;

   std::string line;
   while( getline( file, line ) )
   {
      auto it = std::sregex_iterator( line.begin(), line.end(), numberPattern );

      answer.push_back( std::stoll( it->str() ) );
      it++;

      std::vector<int> tmp;
      while( it != std::sregex_iterator() )
      {
         tmp.push_back( std::stoi( it->str() ) );
         it++;
      }

      number.push_back( tmp );
   }

   long long result = 0;

   for( int i = 0; i < answer.size(); i++ )
   {
      for( int k = 0; k < std::pow( 2, number[ i ].size() - 1 ); k++ )
      {
         auto binStr = toBinary( k );
         binStr.insert( 0, number[ i ].size() - binStr.size() - 1, '0' );

         long long tmpAnswer = number[ i ][ 0 ];
         for( int j = 1; j < number[ i ].size(); j++ )
         {
            if( binStr[ j - 1 ] == '1' )
            {
               tmpAnswer *= number[ i ][ j ];
            }
            else
            {
               tmpAnswer += number[ i ][ j ];
            }
         }

         if( tmpAnswer == answer[ i ] )
         {
            result += tmpAnswer;
            break;
         }
      }
   }

   std::cout << result << std::endl;

   return 0;
}