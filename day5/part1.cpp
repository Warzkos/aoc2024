#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int main()
{
   std::fstream file( "input.txt" );

   struct rule
   {
      int before;
      int after;
   };
   std::vector<rule> rules;
   std::vector<std::vector<int>> book;

   int result = 0;

   std::regex number( "[\\d]+" );

   std::string line;
   while( getline( file, line ) )
   {
      if( line.size() == 0 )
      {
         break;
      }
      auto it = std::sregex_iterator( line.begin(), line.end(), number );
      rules.push_back( { std::stoi( it->str() ), std::stoi( ( ++it )->str() ) } );
   }

   while( getline( file, line ) )
   {
      std::vector<int> page;
      for( auto it = std::sregex_iterator( line.begin(), line.end(), number ); it != std::sregex_iterator(); it++ )
      {
         page.push_back( std::stoi( it->str() ) );
      }
      book.push_back( page );
   }

   for( auto page : book )
   {
      bool valid = true;
      for( auto i = 0; i < page.size(); i++ )
      {
         for( auto j = 0; j < i; j++ )
         {
            for( auto rule : rules )
            {
               if( rule.before == page[ i ] )
               {
                  if( rule.after == page[ j ] )
                  {
                     valid = false;
                     break;
                  }
               }
            }
            if( !valid )
            {
               break;
            }
         }
         if( !valid )
         {
            break;
         }

         for( auto j = i + 1; j < page.size(); j++ )
         {
            for( auto rule : rules )
            {
               if( rule.after == page[ i ] )
               {
                  if( rule.before == page[ j ] )
                  {
                     valid = false;
                     break;
                  }
               }
            }
            if( !valid )
            {
               break;
            }
         }
         if( !valid )
         {
            break;
         }
      }

      if( valid )
      {
         result += page[ page.size() / 2 ];
      }
   }

   std::cout << result << std::endl;

   return 0;
}