#include "CharacterParser.h"
#include "experimental/filesystem"
#include <algorithm>

namespace config
{
    const std::string directory = "../freebies-game/Assets/characters/";
    const std::vector<std::string> extensions = {".png"};
}

void CharacterParser::Parse()
{
    parse(config::directory, 0);
    std::sort(charactersKeys.begin(), charactersKeys.end());
}

void CharacterParser::parse(const std::string &directory, int depthLevel)
{
    namespace fs = std::experimental::filesystem;

    static std::string key;
    static std::string animId;

    for(const auto& entry : fs::directory_iterator(directory))
    {
        if(depthLevel == 0)
        {
            key = entry.path().stem();
        }
        else if(depthLevel == 1)
        {
            animId = entry.path().stem();
        }
        else if(depthLevel == 2)
        {
            if(fs::is_regular_file(entry))
            {
                auto iter = std::find(config::extensions.begin(),
                                      config::extensions.end(),
                                      entry.path().extension().string());
                if(iter != config::extensions.end())
                {
                    charactersKeys.push_back({{key, animId, entry.path().string()}});
                }
                else
                {
                    throw std::runtime_error(std::string("Finding regular file with non supported extension: "
                                                         + entry.path().extension().string()));
                }
            }
            else
            {
                throw std::runtime_error(std::string("Reaching depth 3, but find entry that is not regular file!")
                                         + "in directory: "
                                         + config::directory);
            }
        }
        else
        {
            throw std::runtime_error("Parsing character directory: "
                                     + config::directory
                                     + ", that depth is more than: 3");
        }

        if(fs::is_directory(entry))
        {
            parse(entry.path(), (depthLevel + 1));
        }
    }

}
