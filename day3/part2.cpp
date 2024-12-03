#include <fstream>
#include <iostream>
#include <regex>

int main()
{
   std::fstream file( "input.txt" );

   std::regex pattern( "mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don\\'t\\(\\)" );
   std::regex patternNum( "[0-9]+" );
   bool enabled = true;

   int result = 0;

   std::string line;
   while( getline( file, line ) )
   {
      for( auto it = std::sregex_iterator( line.begin(), line.end(), pattern ); it != std::sregex_iterator(); it++ )
      {
         std::string matchStr = ( *it ).str();

         if( matchStr == "do()" )
         {
            enabled = true;
         }
         else if( matchStr == "don't()" )
         {
            enabled = false;
         }
         else
         {
            int mul = 1;
            for( auto itNum = std::sregex_iterator( matchStr.begin(), matchStr.end(), patternNum ); itNum != std::sregex_iterator();
                 itNum++ )
            {
               mul *= std::stoi( ( *itNum ).str() );
            }

            if( enabled )
            {
               result += mul;
            }
         }
      }
   }

   std::cout << result << std::endl;

   return 0;
}