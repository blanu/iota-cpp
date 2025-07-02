//
// Created by Dr. Brandon Wiley on 3/10/25.
//

#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <unordered_map>
#include <unordered_set>

#include "../../storage/storage.h"

template <>
struct std::hash<std::vector<Storage>>
{
  std::size_t operator()(const std::vector<Storage>& vec) const noexcept
  {
    std::size_t hashValue = vec.size();
    for (const auto& item : vec)
    {
      hashValue ^= std::hash<Storage>()(item) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
    }
    return hashValue;
  }
};

class Log
{
  public:
    static void initialize();

    // Monads
    static Storage makeTable(const Storage& i);
    static Storage copyTable(const Storage& i);
    static Storage freeTable(const Storage& i);
    static Storage flatten(const Storage& i);

    // Dyads
    static Storage insert(const Storage& i, const Storage& x);
    static Storage remove(const Storage& i, const Storage& x);
    static Storage iunion(const Storage& i, const Storage& x);
    static Storage project(const Storage& i, const Storage& x);
    static Storage difference(const Storage& i, const Storage& x);
    static Storage rename(const Storage& i, const Storage& x);
    static Storage crossProduct(const Storage& i, const Storage& x);
    static Storage restrict(const Storage& i, const Storage& x);
    static Storage intersection(const Storage& i, const Storage& x);

  private:
    class Table
    {
      public:
        static int nextId;
        static Storage nextIdStorage();

        explicit Table(const mixed& names);

        // Copy constructor
        explicit Table(const Table *x);

        // Header
        std::unordered_map<Storage, int> nameSet;
        std::vector<Storage> nameOrder;
        int rowSize;

        std::vector<mixed> columns = {};
        std::unordered_map<mixed, int> rows;

        int columnSize = 0;

        static Storage makeReference(int id);
    };

    static std::unordered_map<int, Table*> tables;

    static Table *findTable(const Storage& i);
};

#endif //RELATION_H
