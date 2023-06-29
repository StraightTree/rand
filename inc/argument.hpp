#pragma once

#include <utility>

#include "string"

class Argument
{
public:
  enum class ArgumentType
  {
    BOOL,
    SIGNED_INTEGER,
    UNSIGNED_INTEGER,
    FLOAT,
    STRING
  };

  bool operator==(const Argument& rhs) const
  {
    return    (arg_ == rhs.arg_)
           && (arg_type_ == rhs.arg_type_)
           && (brief_ == rhs.brief_)
           && (verbose_ == rhs.verbose_)
           && (description_ == rhs.description_);
  }

  bool operator!=(const Argument& rhs) const
  {
    return !operator==(rhs);
  }


private:
  Argument(std::string brief, std::string  verbose, std::string  description, ArgumentType type, void* arg) :
          brief_(std::move(brief)), verbose_(std::move(verbose)), description_(std::move(description)), arg_type_(type), arg_(arg) {};


  std::string brief_{};
  std::string verbose_{};
  std::string description_{};
  ArgumentType arg_type_{};
  void* arg_{};
  bool provided_by_user_{};

public:
  Argument(std::string  brief, std::string  verbose, std::string  description, bool& arg);
  Argument(std::string  brief, std::string  verbose, std::string  description, size_t& arg);
  Argument(std::string  brief, std::string  verbose, std::string  description, ssize_t& arg);
  Argument(std::string  brief, std::string  verbose, std::string  description, double& arg);
  Argument(std::string  brief, std::string  verbose, std::string  description, std::string& arg);

  [[nodiscard]] const std::string& getBrief() const;
  [[nodiscard]] const std::string& getVerbose() const;
  [[nodiscard]] const std::string& getDescription() const;
  [[nodiscard]] ArgumentType getArgumentType() const;
  [[nodiscard]] const void* getArgument() const;
  [[nodiscard]] void* getArgument();
  [[nodiscard]] bool providedByUser() const;
  void setProvidedByUser();
};

