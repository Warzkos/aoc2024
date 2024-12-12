#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::vector<char>> map;

struct Point
{
   int x;
   int y;
};

struct Field
{
   char type;
   std::vector<Point> points;

   int calculateArea() { return points.size(); }

   int calculateNeighbours( Point p )
   {
      int count = 0;

      if( p.x > 0 && map[ p.y ][ p.x - 1 ] == type )
      {
         count++;
      }
      if( p.x < map[ p.y ].size() - 1 && map[ p.y ][ p.x + 1 ] == type )
      {
         count++;
      }
      if( p.y > 0 && map[ p.y - 1 ][ p.x ] == type )
      {
         count++;
      }
      if( p.y < map.size() - 1 && map[ p.y + 1 ][ p.x ] == type )
      {
         count++;
      }

      return count;
   }

   int calculatePerimeter()
   {
      int perimiter = 0;
      for( const auto &p : points )
      {
         perimiter += 4 - calculateNeighbours( p );
      }
      return perimiter;
   }
};

std::vector<Point> getNeighbours( Point p, char type )
{
   std::vector<Point> neighbours;

   if( p.x > 0 && map[ p.y ][ p.x - 1 ] == type )
   {
      neighbours.push_back( { p.x - 1, p.y } );
   }
   if( p.x < map[ p.y ].size() - 1 && map[ p.y ][ p.x + 1 ] == type )
   {
      neighbours.push_back( { p.x + 1, p.y } );
   }
   if( p.y > 0 && map[ p.y - 1 ][ p.x ] == type )
   {
      neighbours.push_back( { p.x, p.y - 1 } );
   }
   if( p.y < map.size() - 1 && map[ p.y + 1 ][ p.x ] == type )
   {
      neighbours.push_back( { p.x, p.y + 1 } );
   }

   return neighbours;
}

int main()
{
   std::fstream file( "input.txt" );

   std::string line;
   while( getline( file, line ) )
   {
      std::vector<char> row;
      for( auto c : line )
      {
         row.push_back( c );
      }
      map.push_back( row );
   }

   std::vector<Field> fields;
   std::vector<std::vector<bool>> visited( map.size(), std::vector<bool>( map[ 0 ].size(), false ) );

   for( int y = 0; y < map.size(); y++ )
   {
      for( int x = 0; x < map[ y ].size(); x++ )
      {
         Field newField;

         if( visited[ y ][ x ] )
         {
            continue;
         }

         visited[ y ][ x ] = true;

         newField.type = map[ y ][ x ];
         newField.points.push_back( { x, y } );

         std::vector<Point> toVisit = getNeighbours( { x, y }, newField.type );
         while( !toVisit.empty() )
         {
            Point p = toVisit.back();
            toVisit.pop_back();

            if( visited[ p.y ][ p.x ] )
            {
               continue;
            }

            visited[ p.y ][ p.x ] = true;

            newField.points.push_back( p );

            std::vector<Point> neighbours = getNeighbours( p, newField.type );
            for( const auto &n : neighbours )
            {
               toVisit.push_back( n );
            }
         }

         fields.push_back( newField );
      }
   }

   int result = 0;
   for( auto f : fields )
   {
      result += f.calculateArea() * f.calculatePerimeter();
   }

   std::cout << "Result: " << result << std::endl;

   return 0;
}
