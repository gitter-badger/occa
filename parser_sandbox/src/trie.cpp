#include "trie.hpp"

namespace occa {
  //---[ Node ]-------------------------
  //  ---[ Result ]---------------------
  trieNode_t::result_t::result_t() {}

  trieNode_t::result_t::result_t(const int length_, const int valueIdx_) :
    length(length_),
    valueIdx(valueIdx_) {}
  //  ==================================

  trieNode_t::trieNode_t() :
    valueIdx(-1) {}

  trieNode_t::trieNode_t(const int valueIdx_) :
    valueIdx(valueIdx_) {}

  void trieNode_t::add(const char *c, const int valueIdx_) {
    if (*c == '\0') {
      valueIdx = valueIdx_;
      return;
    }
    trieNode_t &newNode = leaves[*c];
    newNode.add(c + 1, valueIdx_);
  }

  int trieNode_t::nodeCount() const {
    cTrieNodeMapIterator it = leaves.begin();
    int count = (int) leaves.size();
    while (it != leaves.end()) {
      count += it->second.nodeCount();
      ++it;
    }
    return count;
  }

  int trieNode_t::getValueIdx(const char *c) const {
    const int length = (int) strlen(c);
    result_t result = get(c, length);
    return (result.length == length) ? result.valueIdx : -1;
  }

  trieNode_t::result_t trieNode_t::get(const char *c, const int length) const {
    return get(c, 0, length);
  }

  trieNode_t::result_t trieNode_t::get(const char *c, const int cIdx, const int length) const {
    cTrieNodeMapIterator it = leaves.find(c[cIdx]);
    if ((cIdx < length) && (it != leaves.end())) {
      result_t result = it->second.get(c, cIdx + 1, length);
      if (!result.success() && (0 <= valueIdx)) {
        return result_t(cIdx + 1, valueIdx);
      }
      return result;
    }
    return result_t(cIdx, valueIdx);
  }
  //====================================
}
