//
// Created by david on 30/06/23.
//
#pragma once
#include <random>
#include <chrono>

template<typename T>
class AbstractRandomEngine
{
public:
  virtual T getNumber() = 0;
};

template<typename T>
class UniformRandomEngine : public AbstractRandomEngine<T>
{
private:
  std::random_device random_device_;
  std::mt19937 random_generator_;
  std::uniform_int_distribution<T> distribution_;

public:
  UniformRandomEngine() : random_generator_(random_device_()), distribution_()
  {
    random_generator_.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  }

  T getNumber() override
  {
    return distribution_(random_generator_);
  }

};
