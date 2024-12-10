#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

struct trailPoint
{
   int x;
   int y;
   int currentHeight;
   int beginX;
   int beginY;
};

std::vector<trailPoint> getNextPoints( const std::vector<std::vector<int>> &map, trailPoint currentPoint )
{
   std::vector<trailPoint> nextPoints;

   if( currentPoint.y - 1 >= 0 )
   {
      if( map[ currentPoint.x ][ currentPoint.y - 1 ] == currentPoint.currentHeight + 1 )
      {
         nextPoints.push_back( { currentPoint.x, currentPoint.y - 1, currentPoint.currentHeight + 1, currentPoint.beginX, currentPoint.beginY } );
      }
   }

   if( currentPoint.y + 1 < map.size() )
   {
      if( map[ currentPoint.x ][ currentPoint.y + 1 ] == currentPoint.currentHeight + 1 )
      {
         nextPoints.push_back( { currentPoint.x, currentPoint.y + 1, currentPoint.currentHeight + 1, currentPoint.beginX, currentPoint.beginY } );
      }
   }

   if( currentPoint.x - 1 >= 0 )
   {
      if( map[ currentPoint.x - 1 ][ currentPoint.y ] == currentPoint.currentHeight + 1 )
      {
         nextPoints.push_back( { currentPoint.x - 1, currentPoint.y, currentPoint.currentHeight + 1, currentPoint.beginX, currentPoint.beginY } );
      }
   }

   if( currentPoint.x + 1 < map[ currentPoint.y ].size() )
   {
      if( map[ currentPoint.x + 1 ][ currentPoint.y ] == currentPoint.currentHeight + 1 )
      {
         nextPoints.push_back( { currentPoint.x + 1, currentPoint.y, currentPoint.currentHeight + 1, currentPoint.beginX, currentPoint.beginY } );
      }
   }

   return nextPoints;
}

int main()
{
   std::fstream file( "input.txt" );

   std::vector<std::vector<int>> map;

   std::deque<trailPoint> trailPoints;

   std::string line;
   while( getline( file, line ) )
   {
      std::vector<int> mapRow;
      for( auto c : line )
      {
         if( c == '0' )
         {
            trailPoint newTrailPoint;
            newTrailPoint.x = map.size();
            newTrailPoint.y = mapRow.size();
            newTrailPoint.currentHeight = 0;
            newTrailPoint.beginX = newTrailPoint.x;
            newTrailPoint.beginY = newTrailPoint.y;
            trailPoints.push_back( newTrailPoint );
         }

         mapRow.push_back( c - '0' );
      }
      map.push_back( mapRow );
   }

   int trailsComplete = 0;
   std::vector<trailPoint> reachableSummits;

   while( trailPoints.size() > 0 )
   {

      std::vector<trailPoint> nextTrailPoints = getNextPoints( map, trailPoints.front() );

      if( nextTrailPoints.size() > 0 )
      {
         for( auto nextTrailPoint : nextTrailPoints )
         {
            if( nextTrailPoint.currentHeight == 9 )
            {
               bool visited = false;
               for( auto summit : reachableSummits )
               {
                  if( summit.x == nextTrailPoint.x && summit.y == nextTrailPoint.y && summit.beginX == nextTrailPoint.beginX &&
                      summit.beginY == nextTrailPoint.beginY )
                  {
                     visited = true;
                     break;
                  }
               }

               if( !visited )
               {
                  trailsComplete++;
                  reachableSummits.push_back( nextTrailPoint );
               }
               else
               {
                  continue;
               }
            }
            else
            {
               trailPoints.push_back( nextTrailPoint );
            }
         }
      }
      trailPoints.pop_front();
   }

   std::cout << trailsComplete << std::endl;

   return 0;
}