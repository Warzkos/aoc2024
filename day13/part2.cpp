#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

struct Axis
{
   long long x;
   long long y;
};

bool isSolved( Axis spins, Axis button1, Axis button2, Axis prize )
{
   return button1.x * spins.x + button2.x * spins.y == prize.x && button1.y * spins.x + button2.y * spins.y == prize.y;
}

Axis solveEquation( Axis button1, Axis button2, Axis prize )
{
   long long det = button1.x * button2.y - button1.y * button2.x;
   long long detX = prize.x * button2.y - prize.y * button2.x;
   long long detY = button1.x * prize.y - button1.y * prize.x;

   return { detX / det, detY / det };
}

int main()
{
   std::fstream file( "input.txt" );
   std::regex number( "[\\d]+" );
   long long result = 0;

   std::string line;
   while( getline( file, line ) )
   {
      // button 1
      Axis button1;
      auto it = std::sregex_iterator( line.begin(), line.end(), number );
      button1.x = std::stoll( it->str() );
      it++;
      button1.y = std::stoll( it->str() );

      // button 2
      getline( file, line );
      Axis button2;
      it = std::sregex_iterator( line.begin(), line.end(), number );
      button2.x = std::stoll( it->str() );
      it++;
      button2.y = std::stoll( it->str() );

      // prize
      getline( file, line );
      Axis prize;
      it = std::sregex_iterator( line.begin(), line.end(), number );
      prize.x = std::stoll( it->str() ) + 10000000000000;
      it++;
      prize.y = std::stoll( it->str() ) + 10000000000000;

      auto spins = solveEquation( button1, button2, prize );

      if( isSolved( spins, button1, button2, prize ) )
      {
         result += spins.x * 3 + spins.y;
      }

      // get empty line
      getline( file, line );
   }

   std::cout << "Result: " << result << std::endl;

   return 0;
}
