#include <iostream> 
#include <string>
#include <vector>

int main() {
    std::vector<std::string> brothers{"Groucho", "Harpo", "Chico"};
    for (std::string const& brother : brothers) {
        std::cout << "Hello " << brother << "!\n";
    }
}