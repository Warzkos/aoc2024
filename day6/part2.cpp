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

struct visited
{
   bool visited;
   std::vector<direction> vec;
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
   std::vector<std::vector<visited>> vis;
   guardian guard;
   std::string line;

   int x = 0;
   while( getline( file, line ) )
   {
      std::vector<field> row;
      std::vector<visited> visRow;
      int y = 0;
      for( auto it = line.begin(); it != line.end(); it++ )
      {
         if( *it == '.' )
         {
            row.push_back( EMPTY );
            visRow.push_back( { false, {} } );
         }
         else if( *it == '#' )
         {
            row.push_back( WALL );
            visRow.push_back( { false, {} } );
         }
         else if( *it == '^' )
         {
            row.push_back( EMPTY );
            visRow.push_back( { true, { UP } } );
            guard.pos.x = x;
            guard.pos.y = y;
            guard.dir = UP;
         }

         y++;
      }

      map.push_back( row );
      vis.push_back( visRow );

      x++;
   }

   int count = 0;
   for( auto i = 0; i < map.size(); i++ )
   {
      for( auto j = 0; j < map[ i ].size(); j++ )
      {
         if( map[ i ][ j ] != EMPTY || ( guard.pos.x - 1 == i && guard.pos.y == j ) )
         {
            continue;
         }

         guardian tmpGuard = guard;
         std::vector<std::vector<field>> tmpMap = map;
         std::vector<std::vector<visited>> tmpVis = vis;

         tmpMap[ i ][ j ] = WALL;

         bool loop = false;
         while( true )
         {
            // Check if the next position is out of bounds
            position next = tmpGuard.seek();
            if( next.x < 0 || next.x >= tmpMap.size() || next.y < 0 || next.y >= tmpMap[ 0 ].size() )
            {
               break;
            }

            // Check if the next position has been visited and guardian is moving in the same direction
            if( tmpVis[ next.x ][ next.y ].visited )
            {
               for( auto dir : tmpVis[ next.x ][ next.y ].vec )
               {
                  if( dir == tmpGuard.dir )
                  {
                     loop = true;
                     break;
                  }
               }
               if( loop )
               {
                  break;
               }
            }

            // Check if the next position is empty
            if( tmpMap[ next.x ][ next.y ] == EMPTY )
            {
               tmpGuard.move();
               tmpVis[ tmpGuard.pos.x ][ tmpGuard.pos.y ].visited = true;
               tmpVis[ tmpGuard.pos.x ][ tmpGuard.pos.y ].vec.push_back( tmpGuard.dir );
            }
            else
            {
               tmpGuard.turnRight();
            }
         }

         if( loop )
         {
            count++;
         }
      }
   }

   std::cout << count << std::endl;

   return 0;
}