#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <vector>

const std::regex rNUMBER( "-?[\\d]+" );
const std::string FILENAME = "input.txt";

const int WIDTH = 101;
const int HEIGHT = 103;
const int STEPS = 1000000;

struct Point
{
   int x;
   int y;
};

struct Robot
{
   Point position;
   Point velocity;

   void move()
   {
      position.x += velocity.x;
      if( position.x < 0 )
      {
         position.x += WIDTH;
      }
      position.x = position.x % WIDTH;

      position.y += velocity.y;
      if( position.y < 0 )
      {
         position.y += HEIGHT;
      }
      position.y = position.y % HEIGHT;
   }
};

long long calculateSafetyFactor( const std::vector<Robot> &robots )
{
   auto countQ1 = 0;
   auto countQ2 = 0;
   auto countQ3 = 0;
   auto countQ4 = 0;
   for( const auto &robot : robots )
   {
      if( robot.position.x == WIDTH / 2 || robot.position.y == HEIGHT / 2 )
      {
         continue;
      }

      if( robot.position.x < WIDTH / 2 && robot.position.y < HEIGHT / 2 )
      {
         countQ1++;
      }
      else if( robot.position.x >= WIDTH / 2 && robot.position.y < HEIGHT / 2 )
      {
         countQ2++;
      }
      else if( robot.position.x < WIDTH / 2 && robot.position.y >= HEIGHT / 2 )
      {
         countQ3++;
      }
      else if( robot.position.x >= WIDTH / 2 && robot.position.y >= HEIGHT / 2 )
      {
         countQ4++;
      }
   }

   return countQ1 * countQ2 * countQ3 * countQ4;
}

int main()
{
   std::fstream file( FILENAME );

   std::vector<Robot> robots;

   std::string line;
   while( getline( file, line ) )
   {
      std::sregex_iterator it( line.begin(), line.end(), rNUMBER );
      Robot robot;
      robot.position.x = std::stoi( it->str() );
      it++;
      robot.position.y = std::stoi( it->str() );
      it++;
      robot.velocity.x = std::stoi( it->str() );
      it++;
      robot.velocity.y = std::stoi( it->str() );

      robots.push_back( robot );
   }

   for( int i = 0; i < STEPS; i++ )
   {
      for( auto &robot : robots )
      {
         robot.move();
      }

      bool doPrint = false;
      int maxCount = 0;

      auto consecutivesCount = 0;
      for( const auto &robot : robots )
      {
         for( const auto &robot2 : robots )
         {
            if( abs( robot.position.x - robot2.position.x ) == 1 && robot.position.y == robot2.position.y )
            {
               consecutivesCount++;
            }
         }
      }

      if( consecutivesCount >= 200 )
      {
         doPrint = true;
      }

      if( ( i + 1 ) % 1000 == 0 )
      {
         std::cout << "Step " << i + 1 << std::endl;
      }

      // maybe its not optimal way to print, but I print only when I find some promising result
      if( doPrint )
      {
         std::cout << consecutivesCount << " consecutives found at step " << i + 1 << std::endl;

         for( auto i = 0; i < HEIGHT; i++ )
         {
            for( auto j = 0; j < WIDTH; j++ )
            {
               auto found = false;
               for( const auto &robot : robots )
               {
                  if( robot.position.x == j && robot.position.y == i )
                  {
                     found = true;
                     break;
                  }
               }

               if( found )
               {
                  std::cout << "#";
               }
               else
               {
                  std::cout << ".";
               }
            }
            std::cout << std::endl;
         }
      }
   }

   return 0;
}