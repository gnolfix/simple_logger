# simple_logger
Logger for windows and linux C++23 standard

- Supports macros in log format string:
    - `%D`/`%d` - date and time (`Y-m-d H:M:S`)
    - `%L`/`%l` - log level string (`DEBUG`, `INFO`, `WARNING`, `ERROR`)
    - `%S`/`%s` - message string
- Custom log format strings allowed
- Format is validated via `validate_format()`; an exception is thrown if an invalid macro is used.
- Default format
```cpp
    "%L [%D] %S"
```
## Example Usage

```cpp
#include "Logger.hpp"

int main() {
  Logger logger;

  // Use default format
  logger.INFO("Example message");

  // Set a custom format
  logger.set_log_format("[%L](%D): %S");
  logger.WARNING("Custom message");

  return 0;
}
```
## Output
For the format `[%L](%D): %S`:
```cpp
    [INFO](2025-09-18 12:34:56): Example message
    [WARNING](2025-09-18 12:35:10): Custom message
```
## Format Configuration
- To change the log format, use:
```cpp
    void Logger::set_log_format(std::string format);
```
- The format string can include any combination of macros: `%D`, `%L`, `%S`.
- All macros are validated by `validate_format()` to ensure correctness.

