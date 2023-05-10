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
};


#endif