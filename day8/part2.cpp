#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

class Antenna
{
 public:
   Antenna( int x, int y, char frequency )
   {
      this->x = x;
      this->y = y;
      this->frequency = frequency;
   }

   std::tuple<int, int> calculateDistance( Antenna other ) { return std::make_tuple( other.x - x, other.y - y ); }

   char getFrequency() { return frequency; }
   int getX() { return x; }
   int getY() { return y; }

   bool operator==( Antenna other ) { return x == other.x && y == other.y && frequency == other.frequency; }

 protected:
   int x;
   int y;
   char frequency;
};

int main()
{
   std::fstream file( "input.txt" );
   int count = 0;

   std::vector<std::vector<bool>> antinodes;
   std::vector<Antenna> antennas;

   std::string line;
   auto x = 0;
   while( getline( file, line ) )
   {
      std::vector<bool> row;
      for( auto y = 0; y < line.size(); y++ )
      {
         row.push_back( false );

         if( line[ y ] != '.' )
         {
            row[ y ] = true;
            antennas.push_back( Antenna( x, y, line[ y ] ) );
         }
      }
      antinodes.push_back( row );
      x++;
   }

   for( auto curAntenna : antennas )
   {
      for( auto otherAntenna : antennas )
      {
         if( otherAntenna.getFrequency() == curAntenna.getFrequency() && !( curAntenna == otherAntenna ) )
         {
            auto distanceVec = curAntenna.calculateDistance( otherAntenna );
            auto distanceVecX = std::get<0>( distanceVec ) * 2;
            auto distanceVecY = std::get<1>( distanceVec ) * 2;

            auto antinodeX = curAntenna.getX() + distanceVecX;
            auto antinodeY = curAntenna.getY() + distanceVecY;

            while( true )
            {
               if( antinodeX >= 0 && antinodeX < antinodes.size() && antinodeY >= 0 && antinodeY < antinodes[ 0 ].size() )
               {
                  antinodes[ antinodeX ][ antinodeY ] = true;
               }
               else
               {
                  break;
               }

               antinodeX += distanceVecX / 2;
               antinodeY += distanceVecY / 2;
            }
         }
      }
   }

   for( auto row : antinodes )
   {
      for( auto antinode : row )
      {
         if( antinode )
         {
            count++;
         }
      }
   }

   std::cout << count << std::endl;

   return 0;
}