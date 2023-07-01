#include <iostream>
#include "utility.hpp"
#include "rand.hpp"

int main(int argc, const char *argv[])
{
  try
  {
    const std::string kTerminalArgs = util::createStringFromCharPtrArray(argc-1, argv+1);
    Rand rand{};
    rand.runInTerminal(kTerminalArgs);
  }
  catch (const std::invalid_argument& invalid_argument)
  {
    std::cout << "Invalid argument!" << std::endl;
  }
  catch (const std::runtime_error& runtime_error)
  {
    std::cout << "Error occurred during runtime! " << runtime_error.what() << std::endl;
  }
  catch (const std::exception& exception)
  {
    std::cout << "Unspecified error occurred" << std::endl;
  }

  return 0;
}
