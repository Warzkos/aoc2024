#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

struct rule
{
   int before;
   int after;
};

int fixPageAndYieldMiddle( std::vector<int> page, std::vector<struct rule> rules )
{
   while( true )
   {
      bool changed = false;

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
                     page[ i ] = rule.after;
                     page[ j ] = rule.before;
                     changed = true;
                     break;
                  }
               }
            }
            if( changed )
            {
               break;
            }
         }
         if( changed )
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
                     page[ i ] = rule.before;
                     page[ j ] = rule.after;
                     changed = true;
                     break;
                  }
               }
            }
            if( changed )
            {
               break;
            }
         }
         if( changed )
         {
            break;
         }
      }

      if( !changed )
      {
         break;
      }
   }
   return page[ page.size() / 2 ];
}

int main()
{
   std::fstream file( "input.txt" );

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

      if( !valid )
      {
         result += fixPageAndYieldMiddle( page, rules );
      }
   }

   std::cout << result << std::endl;

   return 0;
}