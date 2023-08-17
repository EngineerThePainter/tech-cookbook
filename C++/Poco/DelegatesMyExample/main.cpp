#include <iostream>
#include <string>
#include <vector>

#include <Poco/BasicEvent.h>
#include <Poco/Delegate.h>

class NormalStudent
{
public:
  void doPushUps(int n) { std::cout << "Normal  Student: I have to do: " << n << " push-ups." << std::endl; }
};

class NormalTrainer
{
public:
  void sayNumberOfReps(NormalStudent& student) { student.doPushUps(push_ups_nb_); }

private:
  const int push_ups_nb_ = 42;
};

class TrainerObserver
{
public:
  virtual void onNumberOfReps(int n) = 0;
};

class TrainerObservable
{
public:
  void addObserver(TrainerObserver* observer) { observers_.push_back(observer); }
  void removeObserver(TrainerObserver* observer)
  {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
  }
  void notifyObservers(int n)
  {
    for (auto& observer : observers_) {
      observer->onNumberOfReps(n);
    }
  }

private:
  std::vector<TrainerObserver*> observers_;
};

class StudentObserver : public TrainerObserver
{
  public:
  void onNumberOfReps(int n) override
  {
    std::cout << "StudentObserver: I have to do: " << n << " push-ups." << std::endl;
  } 
};

class EventTrainer
{
public:
  Poco::BasicEvent<int> reps_event_;
  void sayNumberOfReps(int n) { reps_event_(this, n); }
};

class DelegateStudent
{
public:
  void onNumberOfReps(const void* sender, int& arg)
  {
    std::cout << "DelegateStudent: I have to do: " << arg << " push-ups." << std::endl;
  }
};

int main()
{
  NormalTrainer normal_trainer_;
  NormalStudent normal_student_;
  normal_trainer_.sayNumberOfReps(normal_student_);

  TrainerObservable trainer_observable_;
  StudentObserver student_observer_;
  trainer_observable_.addObserver(&student_observer_);
  StudentObserver student_observer2_;
  trainer_observable_.addObserver(&student_observer2_);
  trainer_observable_.notifyObservers(42);
  trainer_observable_.removeObserver(&student_observer2_);
  trainer_observable_.removeObserver(&student_observer_);

  EventTrainer trainer;
  DelegateStudent student;
  trainer.reps_event_ += Poco::delegate(&student, &DelegateStudent::onNumberOfReps);
  trainer.sayNumberOfReps(42);
  trainer.reps_event_ -= Poco::delegate(&student, &DelegateStudent::onNumberOfReps);

  return 0;
}