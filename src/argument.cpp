//
// Created by david on 17/06/23.
//

#include "argument.hpp"

#include <utility>
Argument::Argument(std::string  brief, std::string  verbose, std::string  description, bool& arg) :
        Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::BOOL, reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string  brief, std::string  verbose, std::string  description, size_t& arg) :
        Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::UNSIGNED_INTEGER, reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string  brief, std::string  verbose, std::string  description, ssize_t& arg) :
        Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::SIGNED_INTEGER, reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string  brief, std::string  verbose, std::string  description, double& arg) :
        Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::FLOAT, reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string  brief, std::string  verbose, std::string  description, std::string& arg) :
        Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::STRING, reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string  brief, std::string  verbose, std::string  description, std::vector<std::string>& arg) :
          Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::STRING_LIST, reinterpret_cast<void*>(&arg))
{

}

const std::string& Argument::getBrief() const
{
  return brief_;
}

const std::string& Argument::getVerbose() const
{
  return verbose_;
}

const std::string& Argument::getDescription() const
{
  return description_;
}

Argument::ArgumentType Argument::getArgumentType() const
{
  return arg_type_;
}

const void* Argument::getArgument() const
{
  return arg_;
}

void* Argument::getArgument()
{
  return arg_;
}

bool Argument::providedByUser() const
{
  return provided_by_user_;
}

void Argument::setProvidedByUser()
{
  provided_by_user_ = true;
}


