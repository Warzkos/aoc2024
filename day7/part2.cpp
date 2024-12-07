#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

std::string toTernary( int n )
{
   std::string r;
   while( n != 0 )
   {
      switch( n % 3 )
      {
      case 0:
         r = "0" + r;
         break;
      case 1:
         r = "1" + r;
         break;
      case 2:
         r = "2" + r;
         break;
      }
      n /= 3;
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
      for( int k = 0; k < std::pow( 3, number[ i ].size() - 1 ); k++ )
      {
         auto binStr = toTernary( k );
         binStr.insert( 0, number[ i ].size() - binStr.size() - 1, '0' );

         long long tmpAnswer = number[ i ][ 0 ];
         for( int j = 1; j < number[ i ].size(); j++ )
         {
            switch( binStr[ j - 1 ] )
            {
            case '0':
               tmpAnswer += number[ i ][ j ];
               break;
            case '1':
               tmpAnswer *= number[ i ][ j ];
               break;
            case '2':
               auto s1 = std::to_string( tmpAnswer );
               auto s2 = std::to_string( number[ i ][ j ] );
               tmpAnswer = std::stoll( s1 + s2 );
               break;
            }
         }

         if( tmpAnswer == answer[ i ] )
         {
            result += tmpAnswer;
            break;
         }
      }
      std::cout << "Progress: " << i + 1 << "/" << answer.size() << std::endl;
   }

   std::cout << result << std::endl;

   return 0;
}