#ifndef __MODELS_WORD__
#define __MODELS_WORD__

#include <string>

class Word
{
private:
    uint64_t id_;
    std::string word_;
    uint32_t level_;
    uint64_t makerId_;

public:
    Word() { id_ = 0; };
    Word(uint64_t id) : id_(id) {};
    Word(const std::string& word, uint32_t level, uint64_t makerId) : word_(word), level_(level), makerId_(makerId) {};

    uint64_t GetId() const { return id_; };
    void SetId(uint64_t id) { id_ = id; };

    std::string GetWord() const { return word_; };
    void SetWord(const std::string& word) { word_ = word; };

    uint32_t GetLevel() const { return level_; };
    void SetLevel(uint32_t level) { level_ = level; };

    uint64_t GetMakerId() const { return makerId_; };
    void SetMakerId(uint64_t makerId) { makerId_ = makerId; };

    void FromString(const std::string& str)
    {
        std::string::size_type pos = str.find('\t');
        id_ = std::stoull(str.substr(0, pos));
        std::string::size_type pos2 = str.find('\t', pos + 1);
        word_ = str.substr(pos + 1, pos2 - pos - 1);
        std::string::size_type pos3 = str.find('\t', pos2 + 1);
        level_ = std::stoi(str.substr(pos2 + 1, pos3 - pos2 - 1));
        makerId_ = std::stoull(str.substr(pos3 + 1));
    };
    std::string ToString() const { return std::to_string(id_) + "\t" + word_ + "\t" + std::to_string(level_) + "\t" + std::to_string(makerId_); };
};


#endif