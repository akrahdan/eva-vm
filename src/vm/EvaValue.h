#ifndef EvaValue_h
#define EvaValue_h

#include <string>

enum class EvaValueType {
    NUMBER,
    OBJECT,
};

/**
 * @Object type
 */

enum class ObjectType  {
    STRING
};

/**
 * @Base Object
 * 
 */

struct Object {
    Object(ObjectType type): type(type) {}
    ObjectType type;
};

struct StringObject: public Object {
 StringObject(const std::string &str) : Object(ObjectType::STRING), string(str) {}
 std::string  string;
};
struct EvaValue {
  EvaValueType type;
  union {
    double number;
    Object object;
  };
  
};

//..............................
// Constructors

#define NUMBER(value) ((EvaValue){ EvaValueType::NUMBER, .number = value})
#define ALLOC_STRING(value) ((EvaValue){ EvaValueType::OBJECT, .object =(Object*)new StringObject(value)})


#define AS_NUMBER(evaValue) ((double)(evaValue).number)
#define AS_STRING(evaValue) ((StringObject)(evaValue).object)
#define AS_CPPSTRING(evaValue) (AS_STRING)(evaValue)->string)

#endif