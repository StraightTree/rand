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

void Argument::initialize()
{
  provided_by_user_ = false;
  switch (arg_type_)
  {
    case ArgumentType::kBool:
    {
      *reinterpret_cast<DataType::BoolType*>(arg_) = false;
      break;
    }
    case ArgumentType::kSignedInteger:
    {
      *reinterpret_cast<DataType::SignedIntType *>(arg_) = 0;
      break;
    }
    case ArgumentType::kUnsignedInteger:
    {
      *reinterpret_cast<DataType::UnsignedIntType *>(arg_) = 0;
      break;
    }
    case ArgumentType::kFloat:
    {
      *reinterpret_cast<DataType::FloatType *>(arg_) = 0.0;
      break;
    }
    case ArgumentType::kString:
    {
      *reinterpret_cast<DataType::StringType *>(arg_) = "";
      break;
    }
    case ArgumentType::kStringList:
    {
      reinterpret_cast<DataType::StringListType *>(arg_)->clear();
      break;
    }
  }
}


