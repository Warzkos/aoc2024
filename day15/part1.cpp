#include <fstream>
#include <iostream>
#include <vector>

const std::string FILENAME = "input.txt";

enum FieldType
{
   EMPTY,
   BOX,
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

   bool nextMovePossible( int coorX, int coorY, Instruction dir )
   {
      switch( map[ coorY ][ coorX ] )
      {
      case EMPTY:
         return true;
      case BORDER:
         return false;
      case BOX:
         switch( dir )
         {
         case UP:
            return nextMovePossible( coorX, coorY - 1, dir );
         case DOWN:
            return nextMovePossible( coorX, coorY + 1, dir );
         case LEFT:
            return nextMovePossible( coorX - 1, coorY, dir );
         case RIGHT:
            return nextMovePossible( coorX + 1, coorY, dir );
         }
      default:
         return false;
      }
   }

   void moveBox( int coorX, int coorY, Instruction dir )
   {
      switch( map[ coorY ][ coorX ] )
      {
      case BOX:
         switch( dir )
         {
         case UP:
            moveBox( coorX, coorY - 1, dir );
            break;
         case DOWN:
            moveBox( coorX, coorY + 1, dir );
            break;
         case LEFT:
            moveBox( coorX - 1, coorY, dir );
            break;
         case RIGHT:
            moveBox( coorX + 1, coorY, dir );
            break;
         }
         break;
      case EMPTY:
         map[ coorY ][ coorX ] = BOX;
         break;
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

      if( nextMovePossible( tempX, tempY, dir ) )
      {
         x = tempX;
         y = tempY;

         if( map[ tempY ][ tempX ] == BOX )
         {
            moveBox( tempX, tempY, dir );
            map[ tempY ][ tempX ] = EMPTY;
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
               case BOX:
                  std::cout << "O";
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
            break;
         case '#':
            row.push_back( BORDER );
            break;
         case 'O':
            row.push_back( BOX );
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

   specimen.printMap();
   long long result = 0;
   for( auto i = 0; i < map.size(); i++ )
   {
      for( auto j = 0; j < map[ i ].size(); j++ )
      {
         if( map[ i ][ j ] == BOX )
         {
            result += i * 100 + j;
         }
      }
   }

   std::cout << "Result: " << result << std::endl;

   return 0;
}