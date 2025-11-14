#ifndef INPUTUTIL_H
#define INPUTUTIL_H

#include <string>
#include "Timing.h"
#include "LabSession.h"
using namespace std;

class InputUtil {
public:
    static string readString(const string& prompt);
    static int readInt(const string& prompt);
    static Date readDate(const string& prompt);
    static Time readTime(const string& prompt);
    static int readDayOfWeek(const string& prompt);
    static bool readBoolean(const string& prompt);
};

#endif
