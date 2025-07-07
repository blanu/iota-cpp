#ifndef SQUEEZE_H_
#define SQUEEZE_H_

#include <tuple>
#include <vector>

#include "types.h"
#include "Connection.h"

class Storage;

bytes squeeze_int(int value);
bytes squeeze_bigint(ints value);
bytes squeeze_varint(const varint &value);
std::tuple<varint, bytes> expand_int(bytes value);
varint expand_int_from_bytes(const bytes &bytes);
varint expand_conn(Connection&);

bytes squeeze_floating(floating value);
maybe<floating> expand_floating(bytes value);
maybe<floating> expand_conn_floating(Connection& conn);

bytes squeeze_ints(const ints &value);
std::tuple<ints, bytes> expand_ints(const bytes& value);

bytes squeeze_floats(const floats& value);
// std::tuple<floats, bytes> expand_floats(bytes value);

#endif