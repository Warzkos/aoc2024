#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <unordered_set>
#include <vector>

class Node
{
   std::vector<std::shared_ptr<Node>> children;
   std::string name;

 public:
   Node( std::string n ) : name( n ) {};
   void addChild( std::shared_ptr<Node> child ) { children.push_back( child ); };
   std::string getName() const { return name; };
   std::vector<std::shared_ptr<Node>> getChildren() { return children; };

   struct KeyEqual
   {
      bool operator()( const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs ) const
      {
         return lhs->getName() == rhs->getName();
      }
   };

   struct Hash
   {
      size_t operator()( const std::shared_ptr<Node> &n ) const { return std::hash<std::string>()( n->getName() ); }
   };
};

// got to figure out a smarter way to check if path is distinct
bool pathExists( const std::vector<std::vector<std::string>> &paths, const std::vector<std::string> &path )
{
   for( const auto &p : paths )
   {
      std::unordered_set<std::string> pathSet( p.begin(), p.end() );
      int matches = 0;
      for( const auto &n : path )
      {
         if( pathSet.find( n ) != pathSet.end() )
         {
            matches++;
         }
      }
      if( matches == 3 )
      {
         return true;
      }
   }

   return false;
}

const std::string FILENAME = "input.txt";

int main()
{
   std::fstream file( FILENAME );

   std::unordered_set<std::shared_ptr<Node>, Node::Hash, Node::KeyEqual> nodes;
   std::string line;
   while( getline( file, line ) )
   {
      std::string parent = line.substr( 0, line.find( '-' ) );
      std::string child = line.substr( line.find( '-' ) + 1 );

      std::shared_ptr<Node> thisNode = std::make_shared<Node>( parent );
      std::shared_ptr<Node> otherNode = std::make_shared<Node>( child );

      auto thisNodeIt = nodes.find( thisNode );
      auto otherNodeIt = nodes.find( otherNode );

      if( thisNodeIt == nodes.end() )
      {
         if( otherNodeIt == nodes.end() )
         {
            thisNode->addChild( otherNode );
            nodes.insert( thisNode );
            otherNode->addChild( thisNode );
            nodes.insert( otherNode );
         }
         else
         {
            thisNode->addChild( *otherNodeIt );
            nodes.insert( thisNode );
            ( *otherNodeIt )->addChild( thisNode );
         }
      }
      else
      {
         if( otherNodeIt == nodes.end() )
         {
            otherNode->addChild( *thisNodeIt );
            ( *thisNodeIt )->addChild( otherNode );
            nodes.insert( otherNode );
         }
         else
         {
            ( *thisNodeIt )->addChild( *otherNodeIt );
            ( *otherNodeIt )->addChild( *thisNodeIt );
         }
      }
   }

   std::vector<std::vector<std::string>> distinctPaths;
   for( const auto &node : nodes )
   {
      for( const auto &child : node->getChildren() ) // 1
      {
         for( const auto &grandChild : child->getChildren() ) // 2
         {
            for( const auto &grandGrandChild : grandChild->getChildren() ) // 3
            {
               if( grandGrandChild->getName() == node->getName() )
               {
                  std::vector<std::string> path;
                  path.push_back( node->getName() );
                  path.push_back( child->getName() );
                  path.push_back( grandChild->getName() );

                  if( !pathExists( distinctPaths, path ) )
                  {
                     distinctPaths.push_back( path );
                  }
               }
            }
         }
      }
   }

   auto countT = 0;
   for( const auto &path : distinctPaths )
   {
      for( const auto &node : path )
      {
         if( node[ 0 ] == 't' )
         {
            countT++;
            break;
         }
      }
   }

   std::cout << "Paths that contain 't': " << countT << std::endl;

   return 0;
}