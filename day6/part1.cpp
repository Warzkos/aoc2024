#include <fstream>
#include <iostream>
#include <vector>

enum field
{
   EMPTY,
   WALL
};

enum direction
{
   UP,
   RIGHT,
   DOWN,
   LEFT
};

struct position
{
   int x;
   int y;
};

struct guardian
{
   position pos;
   direction dir;

   void turnRight()
   {
      switch( dir )
      {
      case UP:
         dir = RIGHT;
         break;
      case RIGHT:
         dir = DOWN;
         break;
      case DOWN:
         dir = LEFT;
         break;
      case LEFT:
         dir = UP;
         break;
      }
   }

   position seek()
   {
      switch( dir )
      {
      case UP:
         return { pos.x - 1, pos.y };
         break;
      case RIGHT:
         return { pos.x, pos.y + 1 };
         break;
      case DOWN:
         return { pos.x + 1, pos.y };
         break;
      case LEFT:
         return { pos.x, pos.y - 1 };
         break;
      }
   }

   void move() { pos = seek(); }
};

int main()
{
   std::fstream file( "input.txt" );

   std::vector<std::vector<field>> map;
   std::vector<std::vector<bool>> visited;
   guardian guardian;
   std::string line;

   int x = 0;
   while( getline( file, line ) )
   {
      std::vector<field> row;
      std::vector<bool> visitedRow;
      int y = 0;
      for( auto it = line.begin(); it != line.end(); it++ )
      {
         if( *it == '.' )
         {
            row.push_back( EMPTY );
            visitedRow.push_back( false );
         }
         else if( *it == '#' )
         {
            row.push_back( WALL );
            visitedRow.push_back( false );
         }
         else if( *it == '^' )
         {
            row.push_back( EMPTY );
            visitedRow.push_back( true );
            guardian.pos.x = x;
            guardian.pos.y = y;
            guardian.dir = UP;
         }

         y++;
      }

      x++;
      map.push_back( row );
      visited.push_back( visitedRow );
   }

   while( true )
   {
      position next = guardian.seek();

      if( next.x < 0 || next.x >= map.size() || next.y < 0 || next.y >= map[ 0 ].size() )
      {
         break;
      }

      if( map[ next.x ][ next.y ] == EMPTY )
      {
         guardian.move();
         visited[ guardian.pos.x ][ guardian.pos.y ] = true;
      }
      else
      {
         guardian.turnRight();
      }
   }

   int count = 0;
   for( auto row : visited )
   {
      for( auto pos : row )
      {
         if( pos )
         {
            count++;
         }
      }
   }

   std::cout << count << std::endl;

   return 0;
}