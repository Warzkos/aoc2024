#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

struct numCount
{
   long long key;
   long long count;
};

void addToNumbers( std::vector<numCount> &numbers, numCount num )
{
   bool isFound = false;
   for( auto i = 0; i < numbers.size(); i++ )
   {
      if( numbers[ i ].key == num.key )
      {
         numbers[ i ].count += num.count;
         isFound = true;
         break;
      }
   }
   if( !isFound )
   {
      numbers.push_back( num );
   }
}

int main()
{
   std::fstream file( "input.txt" );

   int blinks = 75;
   long long result = 0;

   std::regex number( "[\\d]+" );
   std::vector<numCount> numbers;

   std::string line;
   while( getline( file, line ) )
   {
      for( auto it = std::sregex_iterator( line.begin(), line.end(), number ); it != std::sregex_iterator(); it++ )
      {
         numbers.push_back( { std::stoll( it->str() ), 1 } );
      }
   }

   for( auto i = 0; i < blinks; i++ )
   {
      std::vector<numCount> newNumbers;
      for( auto num : numbers )
      {
         if( num.key == 0 )
         {
            num.key = 1;
            addToNumbers( newNumbers, num );
         }
         else
         {
            std::string numStr = std::to_string( num.key );
            if( numStr.size() % 2 == 0 )
            {
               long long num1 = std::stoll( numStr.substr( 0, numStr.size() / 2 ) );
               addToNumbers( newNumbers, { num1, num.count } );

               long long num2 = std::stoll( numStr.substr( numStr.size() / 2 ) );
               addToNumbers( newNumbers, { num2, num.count } );
            }
            else
            {
               num.key *= 2024;
               addToNumbers( newNumbers, num );
            }
         }
      }
      numbers = newNumbers;
   }

   for( auto num : numbers )
   {
      result += num.count;
   }
   std::cout << result << std::endl;

   return 0;
}