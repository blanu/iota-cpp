//
// Created by Dr. Brandon Wiley on 3/21/25.
//

#ifndef RELATION_SYMBOLS_H
#define RELATION_SYMBOLS_H

namespace effects::relation
{
  static constexpr int makeTable = 0;
  static constexpr int copyTable = 1;
  static constexpr int freeTable = 2;
  static constexpr int flatten = 3;

  static constexpr int insert = 4;
  static constexpr int remove = 5;
  static constexpr int iunion = 6;
  static constexpr int project = 7;
  static constexpr int difference = 8;
  static constexpr int rename = 9;
  static constexpr int crossProduct = 10;
  static constexpr int restrict = 11;
  static constexpr int intersection = 12;
}

#endif //RELATION_SYMBOLS_H
