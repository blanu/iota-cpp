#ifndef RELIABLE_CONNECTION_H_
#define RELIABLE_CONNECTION_H_

#include "types.h"

#define EXPORT

class EXPORT Connection
{
    public:
        virtual ~Connection() = default;

        [[nodiscard]] virtual char readOne() const = 0;
        [[nodiscard]] virtual bytes read(int size) const = 0;
        virtual void write(bytes bs) const = 0;
};

#endif