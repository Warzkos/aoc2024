#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int main()
{
   std::fstream file( "input.txt" );

   std::vector<std::vector<char>> puzzle;

   int result = 0;

   std::string line;
   while( getline( file, line ) )
   {
      std::vector<char> row;
      for( auto it = line.begin(); it != line.end(); it++ )
      {
         row.push_back( *it );
      }
      puzzle.push_back( row );
   }

   for( auto rowNum = 0; rowNum < puzzle.size(); rowNum++ )
   {
      for( auto colNum = 0; colNum < puzzle[ rowNum ].size(); colNum++ )
      {
         if( puzzle[ rowNum ][ colNum ] == 'A' )
         {
            auto matchCnt = 0;
            if( colNum + 1 < puzzle[ rowNum ].size() && rowNum - 1 >= 0 )
            {
               if( colNum - 1 >= 0 && rowNum + 1 < puzzle.size() )
               {
                  if( puzzle[ rowNum - 1 ][ colNum + 1 ] + puzzle[ rowNum + 1 ][ colNum - 1 ] == 'S' + 'M' )
                  {
                     matchCnt++;
                  }
               }
            }

            if( colNum + 1 < puzzle[ rowNum ].size() && rowNum + 1 < puzzle.size() )
            {
               if( colNum - 1 >= 0 && rowNum - 1 >= 0 )
               {
                  if( puzzle[ rowNum + 1 ][ colNum + 1 ] + puzzle[ rowNum - 1 ][ colNum - 1 ] == 'S' + 'M' )
                  {
                     matchCnt++;
                  }
               }
            }

            // oops mistakenly counted also horizontal and vertical matches ;)

            // if( colNum + 1 < puzzle[ rowNum ].size() && colNum - 1 >= 0 )
            // {
            //    if( puzzle[ rowNum ][ colNum + 1 ] + puzzle[ rowNum ][ colNum - 1 ] == 'A' + 'M' )
            //    {
            //       matchCnt++;
            //    }
            // }

            // if( rowNum + 1 < puzzle.size() && rowNum - 1 >= 0 )
            // {
            //    if( puzzle[ rowNum + 1 ][ colNum ] + puzzle[ rowNum - 1 ][ colNum ] == 'A' + 'M' )
            //    {
            //       matchCnt++;
            //    }
            // }

            if( matchCnt > 1 )
            {
               result++;
            }
         }
      }
   }

   std::cout << result << std::endl;

   return 0;
}