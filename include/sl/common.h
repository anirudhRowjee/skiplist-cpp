// Custom utilities and commons header

#include <string>

/*
 * Error Type
 */
class SkiplistError {

public:
  enum ErrorVariant { BAD_ACCESS, ALLOC_FAIL, NOERR };
  ErrorVariant e = ErrorVariant::NOERR;
  std::string message;

  SkiplistError(ErrorVariant e, std::string message = "")
      : e(e), message(message){};

  operator bool() { return e != NOERR; }
};
