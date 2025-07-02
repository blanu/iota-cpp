//
// Created by Dr. Brandon Wiley on 3/10/25.
//

#include "relation.h"

#include "../effects.h"

#include "../../verbs.h"
#include "../../nouns/error.h"
#include "../../api.h"

#include "../../storage/word.h"
#include "../../storage/word_array.h"

#include "../../nouns/noun.h"
#include "../../storage/mixed_array.h"

std::unordered_map<int, Log::Table*> Log::tables;

int Log::Table::nextId = 1;

Log::Table::Table(const mixed& i)
{
  rowSize = 0;

  for(Storage y : i)
  {
    nameSet[y] = rowSize++;
    nameOrder.push_back(y);
  }
}

// Copy constructor
Log::Table::Table(Table *x)
{
  rowSize = 0;

  for(auto name : x->nameOrder)
  {
    nameSet[name] = rowSize++;
    nameOrder.push_back(name);
  }

  for(auto pair : x->rows)
  {
    // Add new row to rows and columns
    rows[pair.first] = columnSize;
    for(int columnIndex = 0; columnIndex < rowSize; columnIndex++)
    {
      columns[columnIndex].push_back(pair.first[columnIndex]);
    }

    columnSize++;
  }
}

Storage Log::Table::nextIdStorage()
{
  return makeReference(nextId);
}

Storage Log::Table::makeReference(int id)
{
  return Word::make(id, NounType::RESOURCE);
}

Log::Table *Log::findTable(Storage i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

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
    mixed mis = std::get<mixed>(i.i);

    // New table
    // This moves i.i.
    int id = Table::nextId++;
    tables[id] = new Table(mis);
    return Table::makeReference(id);
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Log::copyTable(const Storage& i)
{
  Table *oldTable = findTable(i);
  if(oldTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  Table newTable(oldTable);
  Table* newTablePointer = &newTable;

  int newId = Table::nextId++;
  tables[newId] = newTablePointer;
  return Table::makeReference(newId);
}

Storage Log::freeTable(const Storage& i)
{
  if(std::holds_alternative<int>(i.i))
  {
    int ii = std::get<int>(i.i);

    if(tables.find(ii) == tables.end())
    {
      Table* table = tables[ii];
      tables.erase(ii);
      delete table;

      return WordArray::nil();
    }
  }

  return Word::make(UNSUPPORTED_OBJECT, NounType::ERROR);
}

Storage Log::flatten(const Storage& i)
{
  Table *oldTable = findTable(i);
  if(oldTable == nullptr)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  mixed results = mixed();
  for(auto pair : oldTable->rows)
  {
    results.push_back(MixedArray::make(pair.first));
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

  mixed mis = std::get<mixed>(x.i);

  // Check size of new row
  if(mis.size() != oldTable->rowSize)
  {
    return Word::make(INVALID_ARGUMENT, NounType::ERROR);
  }

  // Check if new row is a duplicate
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

  Storage mx = Noun::mix(x);
  mixed mis = std::get<mixed>(mx.i);

  auto rowIndex = oldTable->rows.find(mis);
  if(rowIndex == oldTable->rows.end())
  {
    // Idempotent
    return i;
  }

  // Remove selected row from rows and columns
  oldTable->rows.erase(rowIndex);
  for(int columnIndex = 0; columnIndex < mis.size(); columnIndex++)
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

  for(const auto& pair : iTable->rows)
  {
    insert(temp, MixedArray::make(pair.first));
  }

  for(const auto& pair : xTable->rows)
  {
    insert(temp, MixedArray::make(pair.first));
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
    mixed mis = std::get<mixed>(x.i);

    ints columnIndices = ints();
    for(int columnIndex = 0; columnIndex < columnIndices.size(); columnIndex++)
    {
      if(eval({iTable->nameOrder[columnIndex], match, mis[columnIndex]}).truth())
      {
        columnIndices.push_back(columnIndex);
      }
    }

    const Storage temp = makeTable(x);
    for(const auto& pair : iTable->rows)
    {
      mixed row = pair.first;
      mixed newRow = mixed();

      for(int columnIndex : columnIndices)
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

  for(const auto& pair : iTable->rows)
  {
    insert(temp, MixedArray::make(pair.first));
  }

  for(const auto& pair : xTable->rows)
  {
    remove(temp, MixedArray::make(pair.first));
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
    mixed mis = std::get<mixed>(x.i);

    for(Storage y : mis)
    {
      if(std::holds_alternative<mixed>(y.i))
      {
        mixed pair = std::get<mixed>(y.i);

        if(pair.size() != 2)
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        Storage oldName = pair[0];
        Storage newName = pair[1];

        if(oldTable->nameSet.find(oldName) == oldTable->nameSet.end())
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        int nameIndex = oldTable->nameSet[oldName];
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

  for(auto iname : iTable->nameOrder)
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

  for(const auto& iPair : iTable->rows)
  {
    for(const auto& xPair : xTable->rows)
    {
      mixed newRow = mixed(iPair.first);
      newRow.insert(newRow.end(), xPair.first.begin(), xPair.first.end());

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
    mixed mis = std::get<mixed>(x.i);

    Storage newTableReference = copyTable(i);

    for(Storage y : mis)
    {
      if(std::holds_alternative<mixed>(y.i))
      {
        mixed pair = std::get<mixed>(y.i);

        if(pair.size() != 2)
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        Storage matchName = pair[0];
        Storage matchValue = pair[1];

        if(iTable->nameSet.find(matchName) == iTable->nameSet.end())
        {
          return Word::make(INVALID_ARGUMENT, NounType::ERROR);
        }

        int columnIndex = iTable->nameSet[matchName];
        mixed column = iTable->columns[columnIndex];
        for(auto pair : iTable->rows)
        {
          if(eval({pair.first[columnIndex], match, matchValue}).truth())
          {
            insert(newTableReference, MixedArray::make(pair.first));
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

  for(const auto& pair : iTable->rows)
  {
    if(xTable->rows.find(pair.first) != xTable->rows.end())
    {
      insert(temp, MixedArray::make(pair.first));
    }
  }

  return temp;
}
