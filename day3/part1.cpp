#include <fstream>
#include <iostream>
#include <regex>

int main()
{
   std::fstream file( "input.txt" );

   std::regex pattern( "mul\\([0-9]+,[0-9]+\\)" );
   std::regex patternNum( "[0-9]+" );

   int result = 0;

   std::string line;
   while( getline( file, line ) )
   {
      for( auto it = std::sregex_iterator( line.begin(), line.end(), pattern ); it != std::sregex_iterator(); it++ )
      {
         std::string matchStr = (*it).str();

         int mul = 1;
         for( auto num = std::sregex_iterator( matchStr.begin(), matchStr.end(), patternNum ); num != std::sregex_iterator(); num++ )
         {
            mul *= std::stoi( (*num).str() );
         }

         result += mul;
      }
   }

   std::cout << result << std::endl;

   return 0;
}