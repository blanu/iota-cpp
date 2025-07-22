//
// Created by Dr. Brandon Wiley on 3/10/25.
//

#include "relation.h"

#include "../effects.h"

#include "../../verbs.h"
#include "../../nouns/error.h"
#include "../../api.h"

#include <storage/word.h>
#include <storage/word_array.h>

#include "../../nouns/noun.h"
#include <storage/mixed_array.h>

std::unordered_map<int, Log::Table*> Log::tables;

int Log::Table::nextId = 1;

Log::Table::Table(const mixed& names)
{
  rowSize = 0;

  for(const Storage& y : names)
  {
    nameSet[y] = rowSize++;
    nameOrder.push_back(y);
  }
}

// Copy constructor
Log::Table::Table(const Table *x)
{
  rowSize = 0;

  for(const auto& name : x->nameOrder)
  {
    nameSet[name] = rowSize++;
    nameOrder.push_back(name);
  }

  for(const auto& [fst, snd] : x->rows)
  {
    // Add new row to rows and columns
    rows[fst] = columnSize;
    for(int columnIndex = 0; columnIndex < rowSize; columnIndex++)
    {
      columns[columnIndex].push_back(fst[columnIndex]);
    }

    columnSize++;
  }
}

Storage Log::Table::nextIdStorage()
{
  return makeReference(nextId);
}

Storage Log::Table::makeReference(const int id)
{
  return Word::make(id, NounType::RESOURCE);
}

Log::Table *Log::findTable(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int ii = std::get<int>(i.i);

    if(tables.find(ii) == tables.end())
    {
      Table* table = tables[ii];
      return table;
    }
  }

  return nullptr;
}

void Log::initialize()
{
  // Effects::registerMonadicEffect();
}

// Monads
// This moves i.i.
Storage Log::makeTable(const Storage& i)
{
  if(std::holds_alternative<mixed>(i.i))
  {
    const mixed mis = std::get<mixed>(i.i);

    // New table
    // This moves i.i.
    const int id = Table::nextId++;
    tables[id] = new Table(mis);
    return Table::makeReference(id);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Log::copyTable(const Storage& i)
{
  const Table *oldTable = findTable(i);
  if(oldTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  Table newTable(oldTable);
  Table* newTablePointer = &newTable;

  const int newId = Table::nextId++;
  tables[newId] = newTablePointer;
  return Table::makeReference(newId);
}

Storage Log::freeTable(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    const int ii = std::get<int>(i.i);

    if(tables.find(ii) == tables.end())
    {
      const Table* table = tables[ii];
      tables.erase(ii);
      delete table;

      return WordArray::nil();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Log::flatten(const Storage& i)
{
  const Table *oldTable = findTable(i);
  if(oldTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  auto results = mixed();
  for(const auto& [fst, snd] : oldTable->rows)
  {
    results.push_back(MixedArray::make(fst));
  }

  return MixedArray::make(results);
}

// Dyads
Storage Log::insert(const Storage& i, const Storage& x)
{
  Table *oldTable = findTable(i);
  if(oldTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  Storage mx = Noun::mix(x);

  const mixed mis = std::get<mixed>(x.i);

  // Check size of new row
  if(static_cast<int>(static_cast<int>(mis.size())) != oldTable->rowSize)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  // Check if the new row is a duplicate
  if(oldTable->rows.find(mis) != oldTable->rows.end())
  {
    // Idempotent
    return i;
  }

  // Add new row to rows and columns
  oldTable->rows[mis] = oldTable->columnSize;
  for(int columnIndex = 0; columnIndex < oldTable->rowSize; columnIndex++)
  {
    oldTable->columns[columnIndex].push_back(mis[columnIndex]);
  }

  oldTable->columnSize++;

  return i;
}

Storage Log::remove(const Storage& i, const Storage& x)
{
  Table *oldTable = findTable(i);
  if(oldTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  const Storage mx = Noun::mix(x);
  const mixed mis = std::get<mixed>(mx.i);

  const auto rowIndex = oldTable->rows.find(mis);
  if(rowIndex == oldTable->rows.end())
  {
    // Idempotent
    return i;
  }

  // Remove selected row from rows and columns
  oldTable->rows.erase(rowIndex);
  for(int columnIndex = 0; columnIndex < static_cast<int>(static_cast<int>(mis.size())); columnIndex++)
  {
    oldTable->columns[columnIndex].erase(oldTable->columns[columnIndex].begin() + rowIndex->second);
  }

  oldTable->columnSize--;

  return i;
}

Storage Log::iunion(const Storage& i, const Storage& x)
{
  Table *iTable = findTable(i);
  if(iTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  const Table *xTable = findTable(x);
  if(xTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(iTable->rowSize != xTable->rowSize)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(iTable->nameSet != xTable->nameSet)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  const auto flattenedNames = mixed(iTable->nameOrder);
  const Storage temp = makeTable(MixedArray::make(flattenedNames));

  for(const auto& [fst, snd] : iTable->rows)
  {
    insert(temp, MixedArray::make(fst));
  }

  for(const auto& [fst, snd] : xTable->rows)
  {
    insert(temp, MixedArray::make(fst));
  }

  return temp;
}

Storage Log::project(const Storage& i, const Storage& x)
{
  using namespace iota;

  Table *iTable = findTable(i);
  if(iTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(std::holds_alternative<mixed>(x.i))
  {
    auto mis = std::get<mixed>(x.i);

    auto columnIndices = ints();
    for(int columnIndex = 0; columnIndex < static_cast<int>(columnIndices.size()); columnIndex++)
    {
      if(eval({iTable->nameOrder[columnIndex], match, mis[columnIndex]}).truth())
      {
        columnIndices.push_back(columnIndex);
      }
    }

    const Storage temp = makeTable(x);
    for(const auto& [fst, snd] : iTable->rows)
    {
      mixed row = fst;
      auto newRow = mixed();

      for(const int columnIndex : columnIndices)
      {
        newRow.push_back(row[columnIndex]);
      }

      insert(temp, MixedArray::make(newRow));
    }

    return temp;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Log::difference(const Storage& i, const Storage& x)
{
  Table *iTable = findTable(i);
  if(iTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  const Table *xTable = findTable(x);
  if(xTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(iTable->rowSize != xTable->rowSize)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(iTable->nameSet != xTable->nameSet)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  const auto flattenedNames = mixed(iTable->nameOrder);
  const Storage temp = makeTable(MixedArray::make(flattenedNames));

  for(const auto& [fst, snd] : iTable->rows)
  {
    insert(temp, MixedArray::make(fst));
  }

  for(const auto& [fst, snd] : xTable->rows)
  {
    remove(temp, MixedArray::make(fst));
  }

  return temp;
}

Storage Log::rename(const Storage& i, const Storage& x)
{
  Table *oldTable = findTable(i);
  if(oldTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  Storage newTableStorage = Log::copyTable(i);
  Table *newTable = findTable(newTableStorage);

  if(std::holds_alternative<mixed>(x.i))
  {
    const auto mis = std::get<mixed>(x.i);

    for(Storage y : mis)
    {
      if(std::holds_alternative<mixed>(y.i))
      {
        auto pair = std::get<mixed>(y.i);

        if(pair.size() != 2)
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        const Storage& oldName = pair[0];
        const Storage& newName = pair[1];

        if(oldTable->nameSet.find(oldName) == oldTable->nameSet.end())
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        const int nameIndex = oldTable->nameSet[oldName];
        newTable->nameOrder[nameIndex] = newName;
        newTable->nameSet[newName] = nameIndex;
      }
      else
      {
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
      }
    }

    return newTableStorage;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Log::crossProduct(const Storage& i, const Storage& x)
{
  Table *iTable = findTable(i);
  if(iTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  Table *xTable = findTable(x);
  if(xTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  for(const auto& iname : iTable->nameOrder)
  {
    if(xTable->nameSet.find(iname) != xTable->nameSet.end())
    {
      return Word::make(INVALID_ARGUMENT, NounType::ERROR);
    }
  }

  const auto iFlattenedNames = mixed(iTable->nameOrder);
  const auto xFlattenedNames = mixed(xTable->nameOrder);

  auto newNames = mixed(iFlattenedNames);
  newNames.insert(newNames.end(), xFlattenedNames.begin(), xFlattenedNames.end());

  const Storage temp = makeTable(MixedArray::make(newNames));

  for(const auto& [first, _] : iTable->rows)
  {
    for(const auto& [first, _] : xTable->rows)
    {
      auto newRow = mixed(first);
      newRow.insert(newRow.end(), first.begin(), first.end());

      insert(temp, MixedArray::make(newRow));
    }
  }

  return temp;
}

Storage Log::restrict(const Storage& i, const Storage& x)
{
  using namespace iota;

  Table *iTable = findTable(i);
  if(iTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(std::holds_alternative<mixed>(x.i))
  {
    auto mis = std::get<mixed>(x.i);

    Storage newTableReference = copyTable(i);

    for(Storage y : mis)
    {
      if(std::holds_alternative<mixed>(y.i))
      {
        auto pair = std::get<mixed>(y.i);

        if(pair.size() != 2)
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        const Storage& matchName = pair[0];
        Storage matchValue = pair[1];

        if(iTable->nameSet.find(matchName) == iTable->nameSet.end())
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        int columnIndex = iTable->nameSet[matchName];
        mixed column = iTable->columns[columnIndex];
        for(const auto& [first, second] : iTable->rows)
        {
          if(eval({first[columnIndex], match, matchValue}).truth())
          {
            insert(newTableReference, MixedArray::make(first));
          }
        }
      }
      else
      {
        return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
      }
    }

    return newTableReference;
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Log::intersection(const Storage& i, const Storage& x)
{
  Table *iTable = findTable(i);
  if(iTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  Table *xTable = findTable(x);
  if(xTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(iTable->rowSize != xTable->rowSize)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  if(iTable->nameSet != xTable->nameSet)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  const auto flattenedNames = mixed(iTable->nameOrder);
  const Storage temp = makeTable(MixedArray::make(flattenedNames));

  for(const auto& [first, second] : iTable->rows)
  {
    if(xTable->rows.find(first) != xTable->rows.end())
    {
      insert(temp, MixedArray::make(first));
    }
  }

  return temp;
}
