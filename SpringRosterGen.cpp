#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

class Player
{
public:
    Player() = default;
    std::map<std::string, std::string> attributes;
};

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./roster-gen DYNASTYEXPORT.CSV ROSTERIMPORT.CSV" << std::endl;
        return -1;
    }

    std::ifstream dynasty_roster(argv[1]);

    std::string line;

    // Skip key from export
    std::getline(dynasty_roster, line);

    // Load in attribute lines
    std::getline(dynasty_roster, line);
    std::vector<std::string> attributes;

    std::stringstream att_line(line);
    while (std::getline(att_line, line, ','))
    {
        if (!line.empty())
        {
            attributes.push_back(line);
        }
    }

    attributes.pop_back(); // TODO: Find a better way of stopping this.  Last attribute loaded in is empty, find a way to  not load it in!
    std::cout << attributes.at(148) << std::endl;
    std::cout << attributes.size() << " columns." << std::endl;

    std::vector<Player> player_database;

    while (std::getline(dynasty_roster, line))
    {
        Player entry;
        std::stringstream player_stats(line);
        std::string word;
        
        for (int i = 0; i < attributes.size(); ++i)
        {
            std::getline(player_stats, word, ',');
            entry.attributes.insert({attributes.at(i), word});
        }

        player_database.push_back(entry);
    }

    std::cout << player_database.size() << " players." << std::endl;

    auto& player = player_database.at(0);
    std::cout << player.attributes["PFNA"] << ' ' << player.attributes["PLNA"] << std::endl;

    return 0;
}
