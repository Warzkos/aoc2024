#include <iostream>
#include <vector>
#include <fstream>

int main() {
    std::ifstream file("input.txt");

    struct kv {
        int key;
        int occurances;
    };
    std::vector<kv> vec;

    int val1, val2;
    while( file >> val1 >> val2 )
    {
        vec.push_back( kv{ val1, 0 } );
    }

    file.clear();
    file.seekg(0);

    while( file >> val1 >> val2 )
    {
        for( auto& v : vec )
        {
            if( v.key == val2 )
            {
                v.occurances++;
            }
        }
    }

    auto result = 0;
    for( auto v : vec )
    {
        result += v.key * v.occurances;
    }

    std::cout << result << std::endl;

    return 0;
}