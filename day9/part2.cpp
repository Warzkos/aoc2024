#include <fstream>
#include <iostream>
#include <memory>
#include <ranges>
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
   int beginIdx;
   int length;
};

int main()
{
   std::fstream file( "testInput.txt" );

   std::shared_ptr<File> emptyFile = std::make_shared<File>();
   emptyFile->type = EMPTY;
   std::vector<File> files;
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
         File newFile;
         newFile.id = id;
         newFile.type = SYSTEM_FILE;

         files.push_back( newFile );

         for( auto i = 0; i < count; i++ )
         {
            memory.push_back( std::make_shared<File>( files.back() ) );
         }

         files.back().beginIdx = memory.size() - count;
         files.back().length = count;

         id++;
         currFileType = EMPTY;
      }
   }

   for( auto &sysFile : files | std::views::reverse )
   {
      auto consecutiveEmpty = 0;
      for( auto i = 0; i < sysFile.beginIdx; i++ )
      {
         if( memory[ i ]->type == EMPTY )
         {
            consecutiveEmpty++;
         }

         if( consecutiveEmpty >= sysFile.length )
         {
            for( auto j = sysFile.beginIdx; j < sysFile.beginIdx + sysFile.length; j++ )
            {
               std::swap( memory[ i - consecutiveEmpty + 1 ], memory[ j ] );
               i++;
            }

            sysFile.beginIdx = i - consecutiveEmpty - sysFile.length + 1;

            break;
         }

         if( memory[ i ]->type == SYSTEM_FILE )
         {
            consecutiveEmpty = 0;
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