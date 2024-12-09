#include <fstream>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

enum FileType
{
   EMPTY,
   SYSTEM_FILE
};

struct File
{
   int id;
   FileType type;
};

int main()
{
   std::fstream file( "input.txt" );

   std::shared_ptr<File> emptyFile = std::make_shared<File>();
   emptyFile->type = EMPTY;
   std::vector<std::shared_ptr<File>> files;
   std::vector<std::shared_ptr<File>> memory;

   FileType currFileType = SYSTEM_FILE;
   std::string line;
   getline( file, line );
   auto id = 0;
   for( auto c : line )
   {
      auto count = c - '0';
      if( currFileType == EMPTY )
      {
         for( auto i = 0; i < count; i++ )
         {
            memory.push_back( emptyFile );
         }
         currFileType = SYSTEM_FILE;
      }
      else if( currFileType == SYSTEM_FILE )
      {
         std::shared_ptr<File> newFile = std::make_shared<File>();
         newFile->id = id;
         newFile->type = SYSTEM_FILE;

         files.push_back( newFile );

         for( auto i = 0; i < count; i++ )
         {
            memory.push_back( files.back() );
         }

         id++;
         currFileType = EMPTY;
      }
   }

   for( auto i = 0; i < memory.size(); i++ )
   {
      if( memory[ i ]->type == EMPTY )
      {
         for( auto j = memory.size() - 1; j >= i; j-- )
         {
            if( memory[ j ]->type == SYSTEM_FILE )
            {
               std::swap( memory[ i ], memory[ j ] );
               break;
            }
         }
      }
   }

   // cumsum
   long long cumSum = 0;
   for( auto i = 0; i < memory.size(); i++ )
   {
      if( memory[ i ]->type == SYSTEM_FILE )
      {
         cumSum += memory[ i ]->id * i;
      }
   }

   std::cout << cumSum << std::endl;

   return 0;
}