#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int diagonalMatches( std::vector<std::vector<char>> puzzle, int rowNum, int colNum, std::string pattern )
{
   int matches = 0;

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( rowNum + i >= puzzle.size() || colNum + i >= puzzle[ rowNum ].size() )
      {
         break;
      }

      if( puzzle[ rowNum + i ][ colNum + i ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( rowNum + i >= puzzle.size() || colNum - i < 0 )
      {
         break;
      }

      if( puzzle[ rowNum + i ][ colNum - i ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( rowNum - i < 0 || colNum + i >= puzzle[ rowNum ].size() )
      {
         break;
      }

      if( puzzle[ rowNum - i ][ colNum + i ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( rowNum - i < 0 || colNum - i < 0 )
      {
         break;
      }

      if( puzzle[ rowNum - i ][ colNum - i ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   return matches;
}

int horizontalMatches( std::vector<std::vector<char>> puzzle, int rowNum, int colNum, std::string pattern )
{
   int matches = 0;

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( colNum + i >= puzzle[ rowNum ].size() )
      {
         break;
      }

      if( puzzle[ rowNum ][ colNum + i ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( rowNum + i >= puzzle.size() )
      {
         break;
      }

      if( puzzle[ rowNum + i ][ colNum ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( colNum - i < 0 )
      {
         break;
      }

      if( puzzle[ rowNum ][ colNum - i ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   for( auto i = 0; i < pattern.size(); i++ )
   {
      if( rowNum - i < 0 )
      {
         break;
      }

      if( puzzle[ rowNum - i ][ colNum ] != pattern[ i ] )
      {
         break;
      }

      if( i == pattern.size() - 1 )
      {
         matches++;
         break;
      }
   }

   return matches;
}

int main()
{
   std::fstream file( "input.txt" );

   std::string pattern = "XMAS";
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
         result += diagonalMatches( puzzle, rowNum, colNum, pattern );
         result += horizontalMatches( puzzle, rowNum, colNum, pattern );
      }
   }

   std::cout << result << std::endl;

   return 0;
}