//
// Created by david on 17/06/23.
//

#include "argument.hpp"

#include <utility>

Argument::Argument(std::string brief, std::string verbose, std::string description, DataType::BoolType& arg) :
  Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::kBool,
           reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string brief, std::string verbose, std::string description, DataType::UnsignedIntType& arg) :
  Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::kUnsignedInteger,
           reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string brief, std::string verbose, std::string description, DataType::SignedIntType& arg) :
  Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::kSignedInteger,
           reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string brief, std::string verbose, std::string description, DataType::FloatType& arg) :
  Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::kFloat,
           reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string brief, std::string verbose, std::string description, DataType::StringType& arg) :
  Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::kString,
           reinterpret_cast<void*>(&arg))
{
}

Argument::Argument(std::string brief, std::string verbose, std::string description, DataType::StringListType& arg) :
  Argument(std::move(brief), std::move(verbose), std::move(description), ArgumentType::kStringList,
           reinterpret_cast<void*>(&arg))
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


