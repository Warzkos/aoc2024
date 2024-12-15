#include <fstream>
#include <iostream>
#include <vector>

const std::string FILENAME = "input.txt";

enum FieldType
{
   EMPTY,
   BOX_OPEN,
   BOX_CLOSE,
   BORDER
};

enum Instruction
{
   UP,
   DOWN,
   LEFT,
   RIGHT
};

std::vector<std::vector<FieldType>> map;
std::vector<Instruction> instructions;

struct Robot
{
   int x;
   int y;

   bool isMovePossible( int coorX, int coorY, Instruction dir )
   {
      switch( map[ coorY ][ coorX ] )
      {
      case EMPTY:
         return true;
      case BORDER:
         return false;
      case BOX_OPEN:
         switch( dir )
         {
         case DOWN:
            if( isMovePossible( coorX, coorY + 1, dir ) && isMovePossible( coorX + 1, coorY + 1, dir ) )
            {
               return true;
            }
            break;
         case UP:
            if( isMovePossible( coorX, coorY - 1, dir ) && isMovePossible( coorX + 1, coorY - 1, dir ) )
            {
               return true;
            }
            break;
         case RIGHT:
            if( isMovePossible( coorX + 1, coorY, dir ) )
            {
               return true;
            }
            break;
         case LEFT:
            if( isMovePossible( coorX - 1, coorY, dir ) )
            {
               return true;
            }
            break;
         }
         break;
      case BOX_CLOSE:
         switch( dir )
         {
         case DOWN:
            if( isMovePossible( coorX, coorY + 1, dir ) && isMovePossible( coorX - 1, coorY + 1, dir ) )
            {
               return true;
            }
            break;
         case UP:
            if( isMovePossible( coorX, coorY - 1, dir ) && isMovePossible( coorX - 1, coorY - 1, dir ) )
            {
               return true;
            }
            break;
         case RIGHT:
            if( isMovePossible( coorX + 1, coorY, dir ) )
            {
               return true;
            }
            break;
         case LEFT:
            if( isMovePossible( coorX - 1, coorY, dir ) )
            {
               return true;
            }
            break;
         }
         break;
      }
      return false;
   }

   void moveBox( int coorX, int coorY, Instruction dir )
   {
      switch( map[ coorY ][ coorX ] )
      {
      case BOX_OPEN:
         switch( dir )
         {
         case DOWN:
            if( map[ coorY + 1 ][ coorX ] == BOX_OPEN )
            {
               moveBox( coorX, coorY + 1, dir );
               moveBox( coorX + 1, coorY + 1, dir );
               map[ coorY + 1 ][ coorX ] = EMPTY;
               map[ coorY + 1 ][ coorX + 1 ] = EMPTY;
            }
            else if( map[ coorY + 1 ][ coorX ] == BOX_CLOSE )
            {
               moveBox( coorX, coorY + 1, dir );
               moveBox( coorX - 1, coorY + 1, dir );
               map[ coorY + 1 ][ coorX ] = EMPTY;
               map[ coorY + 1 ][ coorX - 1 ] = EMPTY;
            }
            map[ coorY + 1 ][ coorX ] = BOX_OPEN;
            break;
         case UP:
            if( map[ coorY - 1 ][ coorX ] == BOX_OPEN )
            {
               moveBox( coorX, coorY - 1, dir );
               moveBox( coorX + 1, coorY - 1, dir );
               map[ coorY - 1 ][ coorX ] = EMPTY;
               map[ coorY - 1 ][ coorX + 1 ] = EMPTY;
            }
            else if( map[ coorY - 1 ][ coorX ] == BOX_CLOSE )
            {
               moveBox( coorX, coorY - 1, dir );
               moveBox( coorX - 1, coorY - 1, dir );
               map[ coorY - 1 ][ coorX ] = EMPTY;
               map[ coorY - 1 ][ coorX - 1 ] = EMPTY;
            }
            map[ coorY - 1 ][ coorX ] = BOX_OPEN;
            break;
         case RIGHT:
            if( map[ coorY ][ coorX + 1 ] == BOX_OPEN || map[ coorY ][ coorX + 1 ] == BOX_CLOSE )
            {
               moveBox( coorX + 1, coorY, dir );
            }
            map[ coorY ][ coorX + 1 ] = BOX_OPEN;
            break;
         case LEFT:
            if( map[ coorY ][ coorX - 1 ] == BOX_OPEN || map[ coorY ][ coorX - 1 ] == BOX_CLOSE )
            {
               moveBox( coorX - 1, coorY, dir );
            }
            map[ coorY ][ coorX - 1 ] = BOX_OPEN;
            break;
         }
         break;
      case BOX_CLOSE:
         switch( dir )
         {
         case DOWN:
            if( map[ coorY + 1 ][ coorX ] == BOX_OPEN )
            {
               moveBox( coorX, coorY + 1, dir );
               moveBox( coorX + 1, coorY + 1, dir );
               map[ coorY + 1 ][ coorX ] = EMPTY;
               map[ coorY + 1 ][ coorX + 1 ] = EMPTY;
            }
            else if( map[ coorY + 1 ][ coorX ] == BOX_CLOSE )
            {
               moveBox( coorX, coorY + 1, dir );
               moveBox( coorX - 1, coorY + 1, dir );
               map[ coorY + 1 ][ coorX ] = EMPTY;
               map[ coorY + 1 ][ coorX - 1 ] = EMPTY;
            }
            map[ coorY + 1 ][ coorX ] = BOX_CLOSE;
            break;
         case UP:
            if( map[ coorY - 1 ][ coorX ] == BOX_OPEN )
            {
               moveBox( coorX, coorY - 1, dir );
               moveBox( coorX + 1, coorY - 1, dir );
               map[ coorY - 1 ][ coorX ] = EMPTY;
               map[ coorY - 1 ][ coorX + 1 ] = EMPTY;
            }
            else if( map[ coorY - 1 ][ coorX ] == BOX_CLOSE )
            {
               moveBox( coorX, coorY - 1, dir );
               moveBox( coorX - 1, coorY - 1, dir );
               map[ coorY - 1 ][ coorX ] = EMPTY;
               map[ coorY - 1 ][ coorX - 1 ] = EMPTY;
            }
            map[ coorY - 1 ][ coorX ] = BOX_CLOSE;
            break;
         case RIGHT:
            if( map[ coorY ][ coorX + 1 ] == BOX_OPEN || map[ coorY ][ coorX + 1 ] == BOX_CLOSE )
            {
               moveBox( coorX + 1, coorY, dir );
            }
            map[ coorY ][ coorX + 1 ] = BOX_CLOSE;
            break;
         case LEFT:
            if( map[ coorY ][ coorX - 1 ] == BOX_OPEN || map[ coorY ][ coorX - 1 ] == BOX_CLOSE )
            {
               moveBox( coorX - 1, coorY, dir );
            }
            map[ coorY ][ coorX - 1 ] = BOX_CLOSE;
            break;
         }
      }
   }

   void move( Instruction dir )
   {
      auto tempX = x;
      auto tempY = y;
      switch( dir )
      {
      case UP:
         tempY--;
         break;
      case DOWN:
         tempY++;
         break;
      case LEFT:
         tempX--;
         break;
      case RIGHT:
         tempX++;
         break;
      }

      if( isMovePossible( tempX, tempY, dir ) )
      {
         x = tempX;
         y = tempY;

         switch( dir )
         {
         case UP:
         case DOWN:
            switch( map[ tempY ][ tempX ] )
            {
            case BOX_OPEN:
               moveBox( tempX, tempY, dir );
               moveBox( tempX + 1, tempY, dir );
               map[ tempY ][ tempX ] = EMPTY;
               map[ tempY ][ tempX + 1 ] = EMPTY;
               break;
            case BOX_CLOSE:
               moveBox( tempX, tempY, dir );
               moveBox( tempX - 1, tempY, dir );
               map[ tempY ][ tempX ] = EMPTY;
               map[ tempY ][ tempX - 1 ] = EMPTY;
               break;
            }
            break;
         case LEFT:
         case RIGHT:
            moveBox( tempX, tempY, dir );
            map[ tempY ][ tempX ] = EMPTY;
            break;
         }
      }
   }

   // for debug purposes
   void printMap()
   {
      for( auto i = 0; i < map.size(); i++ )
      {
         for( auto j = 0; j < map[ i ].size(); j++ )
         {
            if( x == j && y == i )
            {
               std::cout << "@";
            }
            else
            {
               switch( map[ i ][ j ] )
               {
               case EMPTY:
                  std::cout << ".";
                  break;
               case BOX_OPEN:
                  std::cout << "[";
                  break;
               case BOX_CLOSE:
                  std::cout << "]";
                  break;
               case BORDER:
                  std::cout << "#";
                  break;
               }
            }
         }
         std::cout << std::endl;
      }
      std::cout << std::endl;
   }
};

int main()
{
   std::fstream file( FILENAME );

   Robot specimen;
   std::string line;
   // parse map
   while( getline( file, line ) )
   {
      if( line.size() == 0 )
      {
         break;
      }

      std::vector<FieldType> row;
      for( const auto &c : line )
      {
         switch( c )
         {
         case '@':
            specimen.x = row.size();
            specimen.y = map.size();
         case '.':
            row.push_back( EMPTY );
            row.push_back( EMPTY );
            break;
         case '#':
            row.push_back( BORDER );
            row.push_back( BORDER );
            break;
         case 'O':
            row.push_back( BOX_OPEN );
            row.push_back( BOX_CLOSE );
            break;
         default:
            break;
         }
      }

      map.push_back( row );
   }

   // parse instructions
   while( getline( file, line ) )
   {
      for( const auto &c : line )
      {
         switch( c )
         {
         case '^':
            instructions.push_back( UP );
            break;
         case 'v':
            instructions.push_back( DOWN );
            break;
         case '<':
            instructions.push_back( LEFT );
            break;
         case '>':
            instructions.push_back( RIGHT );
            break;
         default:
            break;
         }
      }
   }

   for( const auto &instruction : instructions )
   {
      specimen.move( instruction );
      // specimen.printMap();
   }

   long long result = 0;
   for( auto i = 0; i < map.size(); i++ )
   {
      for( auto j = 0; j < map[ i ].size(); j++ )
      {
         if( map[ i ][ j ] == BOX_OPEN )
         {
            result += i * 100 + j;
         }
      }
   }

   std::cout << "Result: " << result << std::endl;

   return 0;
}